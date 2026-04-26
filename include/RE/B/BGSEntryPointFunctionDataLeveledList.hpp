#pragma once

#include "RE/B/BGSEntryPointFunctionData.hpp"

namespace RE
{
	class __declspec(novtable) BGSEntryPointFunctionDataLeveledList
		: public BGSEntryPointFunctionData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSEntryPointFunctionDataLeveledList };
		inline static constexpr auto VTABLE{ VTABLE::BGSEntryPointFunctionDataLeveledList };
		inline static constexpr auto ENTRY_TYPE{ EntryPointFunctionType::kLeveledList };

		BGSEntryPointFunctionDataLeveledList();

		~BGSEntryPointFunctionDataLeveledList() override; // 00

		// override (BGSEntryPointFunctionData)
		EntryPointFunctionType GetType() const override;							  // 01
		void InitItem(TESForm* a_form) override;									  // 02
		void ApplyOnAdd(TESForm* a_form, BGSPerkEntry* a_entry) override;			  // 03
		BGSEntryPointFunctionData* CheckConvert(std::uint8_t a_arg01) const override; // 04
		bool LoadImpl(TESFile* a_file) override;									  // 05

		// members
		TESLevItem* levList{ nullptr }; // 18
	};
	static_assert(sizeof(BGSEntryPointFunctionDataLeveledList) == 0x20);

	extern template bool BGSEntryPointFunctionData::Is<BGSEntryPointFunctionDataLeveledList>() const noexcept;
	extern template bool BGSEntryPointFunctionData::IsNot<BGSEntryPointFunctionDataLeveledList>() const noexcept;

	extern template BGSEntryPointFunctionDataLeveledList* BGSEntryPointFunctionData::As<BGSEntryPointFunctionDataLeveledList>() noexcept;
	extern template const BGSEntryPointFunctionDataLeveledList* BGSEntryPointFunctionData::As<BGSEntryPointFunctionDataLeveledList>() const noexcept;
}
