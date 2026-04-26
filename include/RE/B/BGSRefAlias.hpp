#pragma once

#include "RE/B/BGSBaseAlias.hpp"
#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class TESCondition;

	enum class QuestEvent : std::int32_t;

	class __declspec(novtable) BGSRefAlias
		: public BGSBaseAlias // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSRefAlias };
		inline static constexpr auto VTABLE{ VTABLE::BGSRefAlias };
		inline static constexpr auto FORM_TYPE{ FormType::kRefAlias };
		inline static constexpr auto ALIAS_TYPE{ "Ref"sv };

		enum class FILL_TYPE : std::int16_t
		{
			kConditions = 0,
			kForced = 1,
			kFromAlias = 2,
			kFromEvent = 3,
			kCreated = 4,
			kFromExternal = 5,
			kUniqueActor = 6,
			kNearAlias = 7
		};

		class ForcedFillData
		{
		public:
			// members
			ObjectRefHandle forcedRef; // 00
		};
		static_assert(sizeof(ForcedFillData) == 0x04);

		class FromAliasFillData
		{
		public:
			// members
			std::uint32_t forcedFromAlias;	   // 00
			BGSLocationRefType* forcedRefType; // 08
		};
		static_assert(sizeof(FromAliasFillData) == 0x10);

		class FromEventFillData
		{
		public:
			// members
			QuestEvent forcedFromEvent;	   // 00
			std::uint32_t forcedEventData; // 08
		};
		static_assert(sizeof(FromEventFillData) == 0x08);

		class CreatedFillData
		{
		public:
			enum class Level : std::int16_t
			{
				kEasy = 0,
				kMedium = 1,
				kHard = 2,
				kVeryHard = 3,
				kNone = 4
			};

			class Alias
			{
			public:
				enum class Create : std::int16_t
				{
					kIn = -1,
					kAt = 0
				};

				// members
				std::uint16_t alias;					// 00
				REX::Enum<Create, std::int16_t> create; // 02
			};
			static_assert(sizeof(Alias) == 0x04);

			// members
			TESBoundObject* object;				  // 00
			Alias alias;						  // 08
			REX::Enum<Level, std::int16_t> level; // 0C
		};
		static_assert(sizeof(CreatedFillData) == 0x10);

		class FromExternalFillData
		{
		public:
			// members
			TESQuest* externalQuest;	 // 00
			std::uint32_t externalAlias; // 08
		};
		static_assert(sizeof(FromExternalFillData) == 0x10);

		class UniqueActorFillData
		{
		public:
			// members
			TESNPC* uniqueActor; // 00
		};
		static_assert(sizeof(UniqueActorFillData) == 0x08);

		class NearAliasFillData
		{
		public:
			enum class NEAR_FILL_TYPE : std::int32_t
			{
				kLinkedChildren = 0,
				kLinkedParents = 1
			};

			// members
			std::uint32_t nearAlias;							  // 00
			REX::Enum<NEAR_FILL_TYPE, std::int32_t> nearFillType; // 04
		};
		static_assert(sizeof(NearAliasFillData) == 0x08);

		union GenericFillData
		{
		public:
			class Padding
			{
			public:
				// members
				std::array<std::byte, 0x18> pad00; // 00
			};
			static_assert(sizeof(Padding) == 0x18);

			~GenericFillData() noexcept { return; }

			// members
			Padding padding{};
			ForcedFillData forced;
			FromAliasFillData fromAlias;
			FromEventFillData fromEvent;
			CreatedFillData created;
			FromExternalFillData fromExternal;
			UniqueActorFillData uniqueActor;
			NearAliasFillData nearAlias;
		};
		static_assert(sizeof(GenericFillData) == 0x18);

		~BGSRefAlias() override; // 00

		// override (BGSBaseAlias)
		bool Load() override;						   // 01
		void InitItem() override;					   // 02
		const BSFixedString& QType() const override;   // 03
		TESQuest* QExternalQuest() const override;	   // 04
		void ClearExternalQuest() override;			   // 05
		void UpdateFromExternalAlias() const override; // 06
		BGSBaseAlias* GetLinkedAlias() const override; // 07

		// members
		GenericFillData fillData; // 28
		TESCondition* conditions; // 40
	};
	static_assert(sizeof(BGSRefAlias) == 0x48);

	static_assert(Impl::BGSBaseAliasConstraint<BGSRefAlias>);

	extern template bool BGSBaseAlias::Is<BGSRefAlias>() const noexcept;
	extern template bool BGSBaseAlias::IsNot<BGSRefAlias>() const noexcept;

	extern template BGSRefAlias* BGSBaseAlias::As<BGSRefAlias>() noexcept;
	extern template const BGSRefAlias* BGSBaseAlias::As<BGSRefAlias>() const noexcept;
}
