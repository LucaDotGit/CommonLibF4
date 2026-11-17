#include "RE/B/BGSCharacterTint_Entries.hpp"

#include "RE/B/BGSCharacterTint_Entry.hpp"

namespace RE::BGSCharacterTint
{
	auto Entries::GetEntryByID(std::uint16_t a_id) noexcept -> Entry*
	{
		const auto* entryIt = std::ranges::find_if(entries, [a_id](const Entry* a_entry) noexcept -> bool {
			return a_entry && a_entry->idLink == a_id;
		});

		if (entryIt == entries.end()) {
			return nullptr;
		}

		return *entryIt;
	}

	auto Entries::GetEntryByID(std::uint16_t a_id) const noexcept -> const Entry*
	{
		const auto* entryIt = std::ranges::find_if(entries, [a_id](const Entry* a_entry) noexcept -> bool {
			return a_entry && a_entry->idLink == a_id;
		});

		if (entryIt == entries.end()) {
			return nullptr;
		}

		return *entryIt;
	}
}
