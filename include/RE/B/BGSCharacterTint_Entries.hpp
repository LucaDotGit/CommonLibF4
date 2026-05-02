#pragma once

#include "RE/B/BSTArray.hpp"

namespace RE::BGSCharacterTint
{
	class Entry;

	class Entries
	{
	public:
		[[nodiscard]] Entry* GetEntryByID(std::uint16_t a_id) noexcept;
		[[nodiscard]] const Entry* GetEntryByID(std::uint16_t a_id) const noexcept;

		// members
		BSTArray<Entry*> entries; // 00
	};
	static_assert(sizeof(Entries) == 0x18);
}
