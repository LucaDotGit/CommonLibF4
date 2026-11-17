#pragma once

#include "RE/B/BGSBaseAlias.hpp"
#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class TESCondition;

	enum class QuestEvent : std::int32_t;

	class __declspec(novtable) BGSRefAlias : public BGSBaseAlias // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSRefAlias;
		inline static constexpr const auto& VTABLE = VTABLE::BGSRefAlias;
		inline static constexpr auto FORM_TYPE = FormType::RefAlias;
		inline static constexpr auto ALIAS_TYPE = "Ref"sv;

		enum class FILL_TYPE : std::int16_t
		{
			Conditions = 0,
			Forced = 1,
			FromAlias = 2,
			FromEvent = 3,
			Created = 4,
			FromExternal = 5,
			UniqueActor = 6,
			NearAlias = 7
		};

		class ForcedFillData
		{
		public:
			// members
			ObjectRefHandle forcedRef; // 0x00
		};

		static_assert(sizeof(ForcedFillData) == 0x04);

		class FromAliasFillData
		{
		public:
			// members
			std::uint32_t forcedFromAlias;	   // 0x00
			BGSLocationRefType* forcedRefType; // 0x08
		};

		static_assert(sizeof(FromAliasFillData) == 0x10);

		class FromEventFillData
		{
		public:
			// members
			QuestEvent forcedFromEvent;	   // 0x00
			std::uint32_t forcedEventData; // 0x08
		};

		static_assert(sizeof(FromEventFillData) == 0x08);

		class CreatedFillData
		{
		public:
			enum class Level : std::int16_t
			{
				Easy = 0,
				Medium = 1,
				Hard = 2,
				VeryHard = 3,
				None = 4
			};

			class Alias
			{
			public:
				enum class Create : std::int16_t
				{
					In = -1,
					At = 0
				};

				// members
				std::uint16_t alias;					// 0x00
				REX::Enum<Create, std::int16_t> create; // 0x02
			};

			static_assert(sizeof(Alias) == 0x04);

			// members
			TESBoundObject* object;				  // 0x00
			Alias alias;						  // 0x08
			REX::Enum<Level, std::int16_t> level; // 0x0C
		};

		static_assert(sizeof(CreatedFillData) == 0x10);

		class FromExternalFillData
		{
		public:
			// members
			TESQuest* externalQuest;	 // 0x00
			std::uint32_t externalAlias; // 0x08
		};

		static_assert(sizeof(FromExternalFillData) == 0x10);

		class UniqueActorFillData
		{
		public:
			// members
			TESNPC* uniqueActor; // 0x00
		};

		static_assert(sizeof(UniqueActorFillData) == 0x08);

		class NearAliasFillData
		{
		public:
			enum class NEAR_FILL_TYPE : std::int32_t
			{
				LinkedChildren = 0,
				LinkedParents = 1
			};

			// members
			std::uint32_t nearAlias;							  // 0x00
			REX::Enum<NEAR_FILL_TYPE, std::int32_t> nearFillType; // 0x04
		};

		static_assert(sizeof(NearAliasFillData) == 0x08);

		union GenericFillData
		{
		public:
			class Padding
			{
			public:
				// members
				std::array<std::byte, 0x18> pad00; // 0x00
			};

			static_assert(sizeof(Padding) == 0x18);

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

		~BGSRefAlias() override; // 0x00

		// override (BGSBaseAlias)
		auto Load() -> bool override;						   // 0x01
		void InitItem() override;							   // 0x02
		auto QType() const -> const BSFixedString& override;   // 0x03
		auto QExternalQuest() const -> TESQuest* override;	   // 0x04
		void ClearExternalQuest() override;					   // 0x05
		void UpdateFromExternalAlias() const override;		   // 0x06
		auto GetLinkedAlias() const -> BGSBaseAlias* override; // 0x07

		// members
		GenericFillData fillData; // 0x28
		TESCondition* conditions; // 0x40
	};

	static_assert(sizeof(BGSRefAlias) == 0x48);

	static_assert(Impl::BGSBaseAliasConstraint<BGSRefAlias>);
}
