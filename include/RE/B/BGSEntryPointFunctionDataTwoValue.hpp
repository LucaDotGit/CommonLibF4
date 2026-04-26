#pragma once

#include "RE/B/BGSEntryPointFunctionData.hpp"

namespace RE
{
	class __declspec(novtable) BGSEntryPointFunctionDataTwoValue
		: public BGSEntryPointFunctionData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSEntryPointFunctionDataTwoValue };
		inline static constexpr auto VTABLE{ VTABLE::BGSEntryPointFunctionDataTwoValue };
		inline static constexpr auto ENTRY_TYPE{ EntryPointFunctionType::kTwoValue };

		BGSEntryPointFunctionDataTwoValue();

		~BGSEntryPointFunctionDataTwoValue() override; // 00

		// override (BGSEntryPointFunctionData)
		EntryPointFunctionType GetType() const override;							  // 01
		void InitItem(TESForm* a_form) override;									  // 02
		void ApplyOnAdd(TESForm* a_form, BGSPerkEntry* a_entry) override;			  // 03
		BGSEntryPointFunctionData* CheckConvert(std::uint8_t a_arg01) const override; // 04
		bool LoadImpl(TESFile* a_file) override;									  // 05

		// members
		REX::Float32 value01{ 0.0_f32 }; // 18
		REX::Float32 value02{ 0.0_f32 }; // 1C
	};
	static_assert(sizeof(BGSEntryPointFunctionDataTwoValue) == 0x20);

	extern template bool BGSEntryPointFunctionData::Is<BGSEntryPointFunctionDataTwoValue>() const noexcept;
	extern template bool BGSEntryPointFunctionData::IsNot<BGSEntryPointFunctionDataTwoValue>() const noexcept;

	extern template BGSEntryPointFunctionDataTwoValue* BGSEntryPointFunctionData::As<BGSEntryPointFunctionDataTwoValue>() noexcept;
	extern template const BGSEntryPointFunctionDataTwoValue* BGSEntryPointFunctionData::As<BGSEntryPointFunctionDataTwoValue>() const noexcept;
}
