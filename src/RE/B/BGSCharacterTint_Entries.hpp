#pragma once

#include "RE/B/BSTArray.hpp"

namespace RE::BGSCharacterTint
{
	class Entry;

	class Entries
	{
	public:
		[[nodiscard]]
		auto GetEntryByID(std::uint16_t a_id) noexcept -> Entry*;
		[[nodiscard]]
		auto GetEntryByID(std::uint16_t a_id) const noexcept -> const Entry*;

		// members
		BSTArray<Entry*> entries; // 0x00
	};

	static_assert(sizeof(Entries) == 0x18);
}
