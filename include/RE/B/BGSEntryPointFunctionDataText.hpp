#pragma once

#include "RE/B/BGSEntryPointFunctionData.hpp"
#include "RE/B/BGSLocalizedString.hpp"

namespace RE
{
	class __declspec(novtable) BGSEntryPointFunctionDataText
		: public BGSEntryPointFunctionData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSEntryPointFunctionDataText };
		inline static constexpr auto VTABLE{ VTABLE::BGSEntryPointFunctionDataText };
		inline static constexpr auto ENTRY_TYPE{ EntryPointFunctionType::kText };

		BGSEntryPointFunctionDataText();

		~BGSEntryPointFunctionDataText() override; // 00

		// override (BGSEntryPointFunctionData)
		EntryPointFunctionType GetType() const override;							  // 01
		void InitItem(TESForm* a_form) override;									  // 02
		void ApplyOnAdd(TESForm* a_form, BGSPerkEntry* a_entry) override;			  // 03
		BGSEntryPointFunctionData* CheckConvert(std::uint8_t a_arg01) const override; // 04
		bool LoadImpl(TESFile* a_file) override;									  // 05

		// members
		BGSLocalizedString text; // 18
	};
	static_assert(sizeof(BGSEntryPointFunctionDataText) == 0x20);

	extern template bool BGSEntryPointFunctionData::Is<BGSEntryPointFunctionDataText>() const noexcept;
	extern template bool BGSEntryPointFunctionData::IsNot<BGSEntryPointFunctionDataText>() const noexcept;

	extern template BGSEntryPointFunctionDataText* BGSEntryPointFunctionData::As<BGSEntryPointFunctionDataText>() noexcept;
	extern template const BGSEntryPointFunctionDataText* BGSEntryPointFunctionData::As<BGSEntryPointFunctionDataText>() const noexcept;
}
