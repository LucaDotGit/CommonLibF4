#pragma once

#include "RE/B/BGSEntryPointFunctionData.hpp"

namespace RE
{
	class __declspec(novtable) BGSEntryPointFunctionDataAVAndValue
		: public BGSEntryPointFunctionData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSEntryPointFunctionDataAVAndValue };
		inline static constexpr auto VTABLE{ VTABLE::BGSEntryPointFunctionDataAVAndValue };
		inline static constexpr auto ENTRY_TYPE{ EntryPointFunctionType::kActorValue };

		BGSEntryPointFunctionDataAVAndValue();

		~BGSEntryPointFunctionDataAVAndValue() override; // 00

		// override (BGSEntryPointFunctionData)
		EntryPointFunctionType GetType() const override;							  // 01
		void InitItem(TESForm* a_form) override;									  // 02
		void ApplyOnAdd(TESForm* a_form, BGSPerkEntry* a_entry) override;			  // 03
		BGSEntryPointFunctionData* CheckConvert(std::uint8_t a_arg01) const override; // 04
		bool LoadImpl(TESFile* a_file) override;									  // 05

		// members
		ActorValueInfo* actorValue{ nullptr }; // 18
		REX::Float32 value{ 0.0_f32 };		   // 20
	};
	static_assert(sizeof(BGSEntryPointFunctionDataAVAndValue) == 0x28);

	extern template bool BGSEntryPointFunctionData::Is<BGSEntryPointFunctionDataAVAndValue>() const noexcept;
	extern template bool BGSEntryPointFunctionData::IsNot<BGSEntryPointFunctionDataAVAndValue>() const noexcept;

	extern template BGSEntryPointFunctionDataAVAndValue* BGSEntryPointFunctionData::As<BGSEntryPointFunctionDataAVAndValue>() noexcept;
	extern template const BGSEntryPointFunctionDataAVAndValue* BGSEntryPointFunctionData::As<BGSEntryPointFunctionDataAVAndValue>() const noexcept;
}
