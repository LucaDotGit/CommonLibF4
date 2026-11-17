#pragma once

#include "RE/B/BGSEntryPointFunctionData.hpp"
#include "RE/B/BGSLocalizedString.hpp"

namespace RE
{
	class __declspec(novtable) BGSEntryPointFunctionDataActivateChoice : public BGSEntryPointFunctionData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSEntryPointFunctionDataActivateChoice;
		inline static constexpr const auto& VTABLE = VTABLE::BGSEntryPointFunctionDataActivateChoice;
		inline static constexpr auto ENTRY_TYPE = EntryPointFunctionType::ActivateChoice;

		enum class Flags : std::uint16_t
		{
			None = 0,
			RunImmediately = 1,
			ReplaceDefault = 2
		};

		BGSEntryPointFunctionDataActivateChoice();

		~BGSEntryPointFunctionDataActivateChoice() override; // 0x00

		// override (BGSEntryPointFunctionData)
		auto GetType() const -> EntryPointFunctionType override;							  // 0x01
		void InitItem(TESForm* a_form) override;											  // 0x02
		void ApplyOnAdd(TESForm* a_form, BGSPerkEntry* a_entry) override;					  // 0x03
		auto CheckConvert(std::uint8_t a_arg01) const -> BGSEntryPointFunctionData* override; // 0x04
		auto LoadImpl(TESFile* a_file) -> bool override;									  // 0x05

		// members
		BGSLocalizedString label;				  // 0x18
		SpellItem* spell{nullptr};				  // 0x20
		REX::EnumSet<Flags, std::uint16_t> flags; // 0x28
	};

	static_assert(sizeof(BGSEntryPointFunctionDataActivateChoice) == 0x30);
}
