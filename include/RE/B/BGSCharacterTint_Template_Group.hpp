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

		[[nodiscard]] Entry* GetEntryByID(std::uint16_t a_id) noexcept;
		[[nodiscard]] const Entry* GetEntryByID(std::uint16_t a_id) const noexcept;

		[[nodiscard]] Entry* GetEntryBySlot(EntrySlot a_slot) noexcept;
		[[nodiscard]] const Entry* GetEntryBySlot(EntrySlot a_slot) const noexcept;

		// members
		BGSLocalizedString name;	// 00
		std::uint32_t id;			// 08
		std::uint32_t chargenIndex; // 0C
		BSTArray<Entry*> entries;	// 10
	};
	static_assert(sizeof(Group) == 0x28);
}
