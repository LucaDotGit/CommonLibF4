#pragma once

#include "RE/B/BSExtraData.hpp"
#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTTuple.hpp"

namespace RE
{
	class __declspec(novtable) ExtraTextDisplayData : public BSExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ExtraTextDisplayData;
		inline static constexpr const auto& VTABLE = VTABLE::ExtraTextDisplayData;
		inline static constexpr auto EXTRA_TYPE = EXTRA_DATA_TYPE::TextDisplayData;

		ExtraTextDisplayData() :
			BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraTextDisplayData() override; // 0x00

		// override (BSExtraData)
		auto CompareImpl(const BSExtraData& a_compare) const -> bool override; // 0x01

		enum class DisplayDataType : std::int32_t
		{
			CustomName = -2,
			Uninitialized = -1
		};

		[[nodiscard]]
		auto GetDisplayName(TESBoundObject* a_baseObject = nullptr) const -> BSFixedStringCS;

		[[nodiscard]]
		auto GetCustomName() const -> std::optional<BSFixedStringCS>;
		void SetCustomName(const BSFixedStringCS& a_name);

		// members
		BSFixedStringCS displayName;									// 0x18
		BGSMessage* displayNameText{nullptr};							// 0x20
		TESQuest* ownerQuest{nullptr};									// 0x28
		REX::Enum<DisplayDataType, std::int32_t> ownerInstance;			// 0x30
		BSTArray<BSTPair<BSFixedString, TESForm*>>* textPairs{nullptr}; // 0x38
		std::uint16_t customNameLength{0};								// 0x40
	};

	static_assert(sizeof(ExtraTextDisplayData) == 0x48);
}
