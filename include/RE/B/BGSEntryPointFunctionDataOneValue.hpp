#pragma once

#include "RE/B/BGSEntryPointFunctionData.hpp"

namespace RE
{
	class __declspec(novtable) BGSEntryPointFunctionDataOneValue
		: public BGSEntryPointFunctionData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSEntryPointFunctionDataOneValue };
		inline static constexpr auto VTABLE{ VTABLE::BGSEntryPointFunctionDataOneValue };
		inline static constexpr auto ENTRY_TYPE{ EntryPointFunctionType::kOneValue };

		BGSEntryPointFunctionDataOneValue();

		~BGSEntryPointFunctionDataOneValue() override; // 00

		// override (BGSEntryPointFunctionData)
		EntryPointFunctionType GetType() const override;							  // 01
		void InitItem(TESForm* a_form) override;									  // 02
		void ApplyOnAdd(TESForm* a_form, BGSPerkEntry* a_entry) override;			  // 03
		BGSEntryPointFunctionData* CheckConvert(std::uint8_t a_arg01) const override; // 04
		bool LoadImpl(TESFile* a_file) override;									  // 05

		// members
		REX::Float32 value{ 0.0_f32 }; // 18
	};
	static_assert(sizeof(BGSEntryPointFunctionDataOneValue) == 0x20);

	extern template bool BGSEntryPointFunctionData::Is<BGSEntryPointFunctionDataOneValue>() const noexcept;
	extern template bool BGSEntryPointFunctionData::IsNot<BGSEntryPointFunctionDataOneValue>() const noexcept;

	extern template BGSEntryPointFunctionDataOneValue* BGSEntryPointFunctionData::As<BGSEntryPointFunctionDataOneValue>() noexcept;
	extern template const BGSEntryPointFunctionDataOneValue* BGSEntryPointFunctionData::As<BGSEntryPointFunctionDataOneValue>() const noexcept;
}
