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
		inline static constexpr const auto& RTTI = RTTI::BGSCharacterTint__Template__Entry;
		inline static constexpr const auto& VTABLE = VTABLE::BGSCharacterTint__Template__Entry;

		enum class Flags : std::uint8_t
		{
			None = 0,
			OnOffOnly = 1 << 0,
			IsChargenDefault = 1 << 1,
			TakesSkinTone = 1 << 2
		};

		virtual ~Entry(); // 0x00

		// add
		virtual auto GetDefaultValue() -> REX::Float32; // 0x01 - { return static_cast<REX::Float32>(0.0); }
		virtual void InitItem(TESForm* a_owner);		// 0x02
		virtual void CopyData(BGSCharacterTint::Template::Entry* a_copy); // 0x03
		virtual void LoadImpl(TESFile* a_file) = 0;						  // 0x04

		// members
		BGSLocalizedString name;								   // 0x08
		TESCondition chargenConditions;							   // 0x10
		REX::Enum<BGSCharacterTint::EntrySlot, std::int32_t> slot; // 0x18
		std::uint16_t uniqueID;									   // 0x1C
		REX::EnumSet<Flags, std::uint8_t> flags;				   // 0x1E
	};

	static_assert(sizeof(Entry) == 0x20);
}
