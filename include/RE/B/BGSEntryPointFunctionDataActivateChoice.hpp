#pragma once

#include "RE/B/BGSEntryPointFunctionData.hpp"
#include "RE/B/BGSLocalizedString.hpp"

namespace RE
{
	class __declspec(novtable) BGSEntryPointFunctionDataActivateChoice
		: public BGSEntryPointFunctionData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSEntryPointFunctionDataActivateChoice };
		inline static constexpr auto VTABLE{ VTABLE::BGSEntryPointFunctionDataActivateChoice };
		inline static constexpr auto ENTRY_TYPE{ EntryPointFunctionType::kActivateChoice };

		enum class Flags : std::uint16_t
		{
			kNone = 0,
			kRunImmediately = 1,
			kReplaceDefault = 2
		};

		BGSEntryPointFunctionDataActivateChoice();

		~BGSEntryPointFunctionDataActivateChoice() override; // 00

		// override (BGSEntryPointFunctionData)
		EntryPointFunctionType GetType() const override;							  // 01
		void InitItem(TESForm* a_form) override;									  // 02
		void ApplyOnAdd(TESForm* a_form, BGSPerkEntry* a_entry) override;			  // 03
		BGSEntryPointFunctionData* CheckConvert(std::uint8_t a_arg01) const override; // 04
		bool LoadImpl(TESFile* a_file) override;									  // 05

		// members
		BGSLocalizedString label;				  // 18
		SpellItem* spell{ nullptr };			  // 20
		REX::EnumSet<Flags, std::uint16_t> flags; // 28
	};
	static_assert(sizeof(BGSEntryPointFunctionDataActivateChoice) == 0x30);

	extern template bool BGSEntryPointFunctionData::Is<BGSEntryPointFunctionDataActivateChoice>() const noexcept;
	extern template bool BGSEntryPointFunctionData::IsNot<BGSEntryPointFunctionDataActivateChoice>() const noexcept;

	extern template BGSEntryPointFunctionDataActivateChoice* BGSEntryPointFunctionData::As<BGSEntryPointFunctionDataActivateChoice>() noexcept;
	extern template const BGSEntryPointFunctionDataActivateChoice* BGSEntryPointFunctionData::As<BGSEntryPointFunctionDataActivateChoice>() const noexcept;
}
