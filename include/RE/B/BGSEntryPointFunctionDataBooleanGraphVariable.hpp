#pragma once

#include "RE/B/BGSEntryPointFunctionData.hpp"
#include "RE/B/BSStringT.hpp"

namespace RE
{
	class __declspec(novtable) BGSEntryPointFunctionDataBooleanGraphVariable
		: public BGSEntryPointFunctionData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSEntryPointFunctionDataBooleanGraphVariable };
		inline static constexpr auto VTABLE{ VTABLE::BGSEntryPointFunctionDataBooleanGraphVariable };
		inline static constexpr auto ENTRY_TYPE{ EntryPointFunctionType::kBooleanGraphVariable };

		BGSEntryPointFunctionDataBooleanGraphVariable();

		~BGSEntryPointFunctionDataBooleanGraphVariable() override; // 00

		// override (BGSEntryPointFunctionData)
		EntryPointFunctionType GetType() const override;							  // 01
		void InitItem(TESForm* a_form) override;									  // 02
		void ApplyOnAdd(TESForm* a_form, BGSPerkEntry* a_entry) override;			  // 03
		BGSEntryPointFunctionData* CheckConvert(std::uint8_t a_arg01) const override; // 04
		bool LoadImpl(TESFile* a_file) override;									  // 05

		// members
		BSString variable; // 18
	};
	static_assert(sizeof(BGSEntryPointFunctionDataBooleanGraphVariable) == 0x28);

	extern template bool BGSEntryPointFunctionData::Is<BGSEntryPointFunctionDataBooleanGraphVariable>() const noexcept;
	extern template bool BGSEntryPointFunctionData::IsNot<BGSEntryPointFunctionDataBooleanGraphVariable>() const noexcept;

	extern template BGSEntryPointFunctionDataBooleanGraphVariable* BGSEntryPointFunctionData::As<BGSEntryPointFunctionDataBooleanGraphVariable>() noexcept;
	extern template const BGSEntryPointFunctionDataBooleanGraphVariable* BGSEntryPointFunctionData::As<BGSEntryPointFunctionDataBooleanGraphVariable>() const noexcept;
}
