#pragma once

#include "RE/B/BGSLocalizedString.hpp"
#include "RE/T/TESCondition.hpp"

namespace RE
{
	class TESFile;
}

namespace RE::BGSCharacterTint
{
	enum class EntrySlot : std::int32_t;
}

namespace RE::BGSCharacterTint::Template
{
	class __declspec(novtable) Entry
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSCharacterTint__Template__Entry };
		inline static constexpr auto VTABLE{ VTABLE::BGSCharacterTint__Template__Entry };

		enum class Flags : std::uint8_t
		{
			kNone = 0,
			kOnOffOnly = 1 << 0,
			kIsChargenDefault = 1 << 1,
			kTakesSkinTone = 1 << 2
		};

		virtual ~Entry(); // 00

		// add
		virtual REX::Float32 GetDefaultValue();							  // 01 - { return 0.0_f32; }
		virtual void InitItem(TESForm* a_owner);						  // 02
		virtual void CopyData(BGSCharacterTint::Template::Entry* a_copy); // 03
		virtual void LoadImpl(TESFile* a_file) = 0;						  // 04

		// members
		BGSLocalizedString name;								   // 08
		TESCondition chargenConditions;							   // 10
		REX::Enum<BGSCharacterTint::EntrySlot, std::int32_t> slot; // 18
		std::uint16_t uniqueID;									   // 1C
		REX::EnumSet<Flags, std::uint8_t> flags;				   // 1E
	};
	static_assert(sizeof(Entry) == 0x20);
}
