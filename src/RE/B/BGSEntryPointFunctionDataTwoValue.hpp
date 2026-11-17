#pragma once

#include "RE/B/BGSEntryPointFunctionData.hpp"

namespace RE
{
	class __declspec(novtable) BGSEntryPointFunctionDataTwoValue : public BGSEntryPointFunctionData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSEntryPointFunctionDataTwoValue;
		inline static constexpr const auto& VTABLE = VTABLE::BGSEntryPointFunctionDataTwoValue;
		inline static constexpr auto ENTRY_TYPE = EntryPointFunctionType::TwoValue;

		BGSEntryPointFunctionDataTwoValue();

		~BGSEntryPointFunctionDataTwoValue() override; // 0x00

		// override (BGSEntryPointFunctionData)
		auto GetType() const -> EntryPointFunctionType override;							  // 0x01
		void InitItem(TESForm* a_form) override;											  // 0x02
		void ApplyOnAdd(TESForm* a_form, BGSPerkEntry* a_entry) override;					  // 0x03
		auto CheckConvert(std::uint8_t a_arg01) const -> BGSEntryPointFunctionData* override; // 0x04
		auto LoadImpl(TESFile* a_file) -> bool override;									  // 0x05

		// members
		REX::Float32 value01{static_cast<REX::Float32>(0.0)}; // 0x18
		REX::Float32 value02{static_cast<REX::Float32>(0.0)}; // 0x1C
	};

	static_assert(sizeof(BGSEntryPointFunctionDataTwoValue) == 0x20);
}
