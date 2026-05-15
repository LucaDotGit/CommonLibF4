#include "RE/B/BGSCharacterTint_Entries.hpp"

#include "RE/B/BGSCharacterTint_Entry.hpp"

namespace RE::BGSCharacterTint
{
	Entry* Entries::GetEntryByID(std::uint16_t a_id) noexcept
	{
		const auto* entryIt = std::ranges::find_if(entries, [a_id](const Entry* a_entry) -> bool {
			return a_entry && a_entry->idLink == a_id;
		});

		if (entryIt == entries.end()) {
			return nullptr;
		}

		return *entryIt;
	}

	const Entry* Entries::GetEntryByID(std::uint16_t a_id) const noexcept
	{
		const auto* entryIt = std::ranges::find_if(entries, [a_id](const Entry* a_entry) -> bool {
			return a_entry && a_entry->idLink == a_id;
		});

		if (entryIt == entries.end()) {
			return nullptr;
		}

		return *entryIt;
	}
}
