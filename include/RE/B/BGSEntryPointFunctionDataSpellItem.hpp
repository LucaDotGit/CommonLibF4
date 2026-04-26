#pragma once

#include "RE/B/BGSEntryPointFunctionData.hpp"

namespace RE
{
	class __declspec(novtable) BGSEntryPointFunctionDataSpellItem
		: public BGSEntryPointFunctionData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSEntryPointFunctionDataSpellItem };
		inline static constexpr auto VTABLE{ VTABLE::BGSEntryPointFunctionDataSpellItem };
		inline static constexpr auto ENTRY_TYPE{ EntryPointFunctionType::kSpellItem };

		BGSEntryPointFunctionDataSpellItem();

		~BGSEntryPointFunctionDataSpellItem() override; // 00

		// override (BGSEntryPointFunctionData)
		EntryPointFunctionType GetType() const override;							  // 01
		void InitItem(TESForm* a_form) override;									  // 02
		void ApplyOnAdd(TESForm* a_form, BGSPerkEntry* a_entry) override;			  // 03
		BGSEntryPointFunctionData* CheckConvert(std::uint8_t a_arg01) const override; // 04
		bool LoadImpl(TESFile* a_file) override;									  // 05

		// members
		SpellItem* spell{ nullptr }; // 18
	};
	static_assert(sizeof(BGSEntryPointFunctionDataSpellItem) == 0x20);

	extern template bool BGSEntryPointFunctionData::Is<BGSEntryPointFunctionDataSpellItem>() const noexcept;
	extern template bool BGSEntryPointFunctionData::IsNot<BGSEntryPointFunctionDataSpellItem>() const noexcept;

	extern template BGSEntryPointFunctionDataSpellItem* BGSEntryPointFunctionData::As<BGSEntryPointFunctionDataSpellItem>() noexcept;
	extern template const BGSEntryPointFunctionDataSpellItem* BGSEntryPointFunctionData::As<BGSEntryPointFunctionDataSpellItem>() const noexcept;
}
