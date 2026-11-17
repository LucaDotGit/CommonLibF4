#pragma once

#include "RE/B/BGSEntryPointFunctionData.hpp"
#include "RE/B/BGSLocalizedString.hpp"

namespace RE
{
	class __declspec(novtable) BGSEntryPointFunctionDataText : public BGSEntryPointFunctionData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSEntryPointFunctionDataText;
		inline static constexpr const auto& VTABLE = VTABLE::BGSEntryPointFunctionDataText;
		inline static constexpr auto ENTRY_TYPE = EntryPointFunctionType::Text;

		BGSEntryPointFunctionDataText();

		~BGSEntryPointFunctionDataText() override; // 0x00

		// override (BGSEntryPointFunctionData)
		auto GetType() const -> EntryPointFunctionType override;							  // 0x01
		void InitItem(TESForm* a_form) override;											  // 0x02
		void ApplyOnAdd(TESForm* a_form, BGSPerkEntry* a_entry) override;					  // 0x03
		auto CheckConvert(std::uint8_t a_arg01) const -> BGSEntryPointFunctionData* override; // 0x04
		auto LoadImpl(TESFile* a_file) -> bool override;									  // 0x05

		// members
		BGSLocalizedString text; // 0x18
	};

	static_assert(sizeof(BGSEntryPointFunctionDataText) == 0x20);
}
