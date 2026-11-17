#pragma once

#include "RE/B/BGSLocalizedString.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE::BGSCharacterTint
{
	enum class EntrySlot : std::int32_t;
}

namespace RE::BGSCharacterTint::Template
{
	class Entry;

	class Group
	{
	public:
		GAME_HEAP_REDEFINE_NEW(Group);

		[[nodiscard]]
		auto GetEntryByID(std::uint16_t a_id) noexcept -> Entry*;
		[[nodiscard]]
		auto GetEntryByID(std::uint16_t a_id) const noexcept -> const Entry*;

		[[nodiscard]]
		auto GetEntryBySlot(EntrySlot a_slot) noexcept -> Entry*;
		[[nodiscard]]
		auto GetEntryBySlot(EntrySlot a_slot) const noexcept -> const Entry*;

		// members
		BGSLocalizedString name;	// 0x00
		std::uint32_t id;			// 0x08
		std::uint32_t chargenIndex; // 0x0C
		BSTArray<Entry*> entries;	// 0x10
	};

	static_assert(sizeof(Group) == 0x28);
}
