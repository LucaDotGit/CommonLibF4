#pragma once

#include "RE/B/BGSPerkEntry.hpp"

namespace RE
{
	class __declspec(novtable) BGSAbilityPerkEntry
		: public BGSPerkEntry // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSAbilityPerkEntry };
		inline static constexpr auto VTABLE{ VTABLE::BGSAbilityPerkEntry };
		inline static constexpr auto ENTRY_TYPE{ PERK_ENTRY_TYPE::kAbility };

		BGSAbilityPerkEntry();

		BGSEntryPoint::ENTRY_POINT GetFunction() override;			 // 00
		BGSEntryPointFunctionData* GetFunctionData() const override; // 01

		~BGSAbilityPerkEntry() override; // 02

		PERK_ENTRY_TYPE GetType() const override;	   // 03
		void ClearData() override;					   // 04
		void InitItem(TESFile* a_owner) override;	   // 05
		bool Load(TESFile* a_file) override;		   // 06
		void SetParent(BGSPerk* a_parent) override;	   // 07
		std::uint16_t GetID() const override;		   // 08
		void ApplyPerkEntry(Actor* a_actor) override;  // 09
		void RemovePerkEntry(Actor* a_actor) override; // 0A

		// members
		SpellItem* ability{ nullptr }; // 10
	};
	static_assert(sizeof(BGSAbilityPerkEntry) == 0x18);

	extern template bool BGSPerkEntry::Is<BGSAbilityPerkEntry>() const noexcept;
	extern template bool BGSPerkEntry::IsNot<BGSAbilityPerkEntry>() const noexcept;

	extern template BGSAbilityPerkEntry* BGSPerkEntry::As<BGSAbilityPerkEntry>() noexcept;
	extern template const BGSAbilityPerkEntry* BGSPerkEntry::As<BGSAbilityPerkEntry>() const noexcept;
}
