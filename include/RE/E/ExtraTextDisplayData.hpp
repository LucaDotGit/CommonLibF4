#pragma once

#include "RE/B/BSExtraData.hpp"
#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTTuple.hpp"

namespace RE
{
	class __declspec(novtable) ExtraTextDisplayData
		: public BSExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ExtraTextDisplayData };
		inline static constexpr auto VTABLE{ VTABLE::ExtraTextDisplayData };
		inline static constexpr auto EXTRA_TYPE{ EXTRA_DATA_TYPE::kTextDisplayData };

		ExtraTextDisplayData()
			: BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraTextDisplayData() override; // 00

		// override (BSExtraData)
		bool CompareImpl(const BSExtraData& a_compare) const override; // 01

		enum class DisplayDataType : std::int32_t
		{
			kCustomName = -2,
			kUninitialized = -1
		};

		[[nodiscard]] BSFixedStringCS GetDisplayName(TESBoundObject* a_baseObject = nullptr) const;

		[[nodiscard]] auto GetCustomName() const -> std::optional<BSFixedStringCS>;
		void SetCustomName(const BSFixedStringCS& a_name);

		// members
		BSFixedStringCS displayName;									  // 18
		BGSMessage* displayNameText{ nullptr };							  // 20
		TESQuest* ownerQuest{ nullptr };								  // 28
		REX::Enum<DisplayDataType, std::int32_t> ownerInstance;			  // 30
		BSTArray<BSTPair<BSFixedString, TESForm*>>* textPairs{ nullptr }; // 38
		std::uint16_t customNameLength{ 0 };							  // 40
	};
	static_assert(sizeof(ExtraTextDisplayData) == 0x48);
}
