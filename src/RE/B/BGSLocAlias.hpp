#pragma once

#include "RE/B/BGSBaseAlias.hpp"

namespace RE
{
	class TESCondition;

	class __declspec(novtable) BGSLocAlias : public BGSBaseAlias // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSLocAlias;
		inline static constexpr const auto& VTABLE = VTABLE::BGSLocAlias;
		inline static constexpr auto FORM_TYPE = FormType::LocationAlias;
		inline static constexpr auto ALIAS_TYPE = "Loc"sv;

		~BGSLocAlias() override; // 0x00

		// override (BGSBaseAlias)
		auto Load() -> bool override;						   // 0x01
		void InitItem() override;							   // 0x02
		auto QType() const -> const BSFixedString& override;   // 0x03
		auto QExternalQuest() const -> TESQuest* override;	   // 0x04
		void ClearExternalQuest() override;					   // 0x05
		void UpdateFromExternalAlias() const override;		   // 0x06
		auto GetLinkedAlias() const -> BGSBaseAlias* override; // 0x07

		// members
		BGSLocation* forcedLocation;	   // 0x28
		BGSKeyword* forcedFromAliasFilter; // 0x30
		TESQuest* externalQuest;		   // 0x38
		TESCondition* conditions;		   // 0x40
		std::uint32_t forcedFromAlias;	   // 0x48
		std::uint32_t forcedFromEvent;	   // 0x4C
		std::uint32_t forcedEventData;	   // 0x50
		std::uint32_t externalAlias;	   // 0x54
		std::uint32_t closestToAlias;	   // 0x58
	};

	static_assert(sizeof(BGSLocAlias) == 0x60);
}
