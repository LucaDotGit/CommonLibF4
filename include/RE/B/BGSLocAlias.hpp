#pragma once

#include "RE/B/BGSBaseAlias.hpp"

namespace RE
{
	class TESCondition;

	class __declspec(novtable) BGSLocAlias
		: public BGSBaseAlias // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSLocAlias };
		inline static constexpr auto VTABLE{ VTABLE::BGSLocAlias };
		inline static constexpr auto FORM_TYPE{ FormType::kLocationAlias };
		inline static constexpr auto ALIAS_TYPE{ "Loc"sv };

		~BGSLocAlias() override; // 00

		// override (BGSBaseAlias)
		bool Load() override;						   // 01
		void InitItem() override;					   // 02
		const BSFixedString& QType() const override;   // 03
		TESQuest* QExternalQuest() const override;	   // 04
		void ClearExternalQuest() override;			   // 05
		void UpdateFromExternalAlias() const override; // 06
		BGSBaseAlias* GetLinkedAlias() const override; // 07

		// members
		BGSLocation* forcedLocation;	   // 28
		BGSKeyword* forcedFromAliasFilter; // 30
		TESQuest* externalQuest;		   // 38
		TESCondition* conditions;		   // 40
		std::uint32_t forcedFromAlias;	   // 48
		std::uint32_t forcedFromEvent;	   // 4C
		std::uint32_t forcedEventData;	   // 50
		std::uint32_t externalAlias;	   // 54
		std::uint32_t closestToAlias;	   // 58
	};
	static_assert(sizeof(BGSLocAlias) == 0x60);

	extern template bool BGSBaseAlias::Is<BGSLocAlias>() const noexcept;
	extern template bool BGSBaseAlias::IsNot<BGSLocAlias>() const noexcept;

	extern template BGSLocAlias* BGSBaseAlias::As<BGSLocAlias>() noexcept;
	extern template const BGSLocAlias* BGSBaseAlias::As<BGSLocAlias>() const noexcept;
}
