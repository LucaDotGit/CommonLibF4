#include "RE/B/BGSCharacterTint_Template_Group.hpp"

#include "RE/B/BGSCharacterTint_EntrySlot.hpp"
#include "RE/B/BGSCharacterTint_Template_Entry.hpp"

namespace RE::BGSCharacterTint::Template
{
	Entry* Group::GetEntryByID(std::uint16_t a_id) noexcept
	{
		const auto* entryIt = std::ranges::find_if(entries, [a_id](const Entry* a_entry) {
			return a_entry && a_entry->uniqueID == a_id;
		});

		if (entryIt == entries.end()) {
			return nullptr;
		}

		return *entryIt;
	}

	const Entry* Group::GetEntryByID(std::uint16_t a_id) const noexcept
	{
		const auto* entryIt = std::ranges::find_if(entries, [a_id](const Entry* a_entry) {
			return a_entry && a_entry->uniqueID == a_id;
		});

		if (entryIt == entries.end()) {
			return nullptr;
		}

		return *entryIt;
	}

	Entry* Group::GetEntryBySlot(EntrySlot a_slot) noexcept
	{
		const auto* entryIt = std::ranges::find_if(entries, [a_slot](const Entry* a_entry) {
			return a_entry && a_entry->slot == a_slot;
		});

		if (entryIt == entries.end()) {
			return nullptr;
		}

		return *entryIt;
	}

	const Entry* Group::GetEntryBySlot(EntrySlot a_slot) const noexcept
	{
		const auto* entryIt = std::ranges::find_if(entries, [a_slot](const Entry* a_entry) {
			return a_entry && a_entry->slot == a_slot;
		});

		if (entryIt == entries.end()) {
			return nullptr;
		}

		return *entryIt;
	}
}
