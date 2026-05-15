#include "RE/B/BGSSaveLoadGame.hpp"

#include "RE/B/BGSSaveLoadChangesMap.hpp"
#include "RE/B/BSSpinLock.hpp"

namespace RE
{
	bool BGSSaveLoadGame::HasChangeFlag(TESFormID a_formID, BGSChangeFlags a_flags) const
	{
		if (!changesMap) {
			return false;
		}

		const auto flagLock = BSAutoReadLock(changesMap->rwLock);

		const auto flagsIt = changesMap->find(a_formID);
		if (flagsIt == changesMap->end()) {
			return false;
		}

		return (flagsIt->second.changeFlags.flags & a_flags.flags) != 0;
	}

	auto BGSSaveLoadGame::GetChangeFlags(TESFormID a_formID) const
		-> std::optional<BGSChangeFlags>
	{
		if (!changesMap) {
			return std::nullopt;
		}

		const auto flagLock = BSAutoReadLock(changesMap->rwLock);

		const auto flagsIt = changesMap->find(a_formID);
		if (flagsIt == changesMap->end()) {
			return std::nullopt;
		}

		return BGSChangeFlags{ .flags = flagsIt->second.changeFlags.flags };
	}

	bool BGSSaveLoadGame::SetChangeFlags(TESFormID a_formID, BGSChangeFlags a_flags) const
	{
		if (!changesMap) {
			return false;
		}

		const auto flagLock = BSAutoWriteLock(changesMap->rwLock);

		(*changesMap)[a_formID].changeFlags.flags = a_flags.flags;
		return true;
	}

	bool BGSSaveLoadGame::AddChangeFlag(TESFormID a_formID, BGSChangeFlags a_flag) const
	{
		if (!changesMap) {
			return false;
		}

		const auto flagLock = BSAutoWriteLock(changesMap->rwLock);

		(*changesMap)[a_formID].changeFlags.flags |= a_flag.flags;
		return true;
	}

	bool BGSSaveLoadGame::RemoveChangeFlag(TESFormID a_formID, BGSChangeFlags a_flag) const
	{
		if (!changesMap) {
			return false;
		}

		const auto flagLock = BSAutoWriteLock(changesMap->rwLock);

		const auto flagsIt = changesMap->find(a_formID);
		if (flagsIt == changesMap->end()) {
			return false;
		}

		flagsIt->second.changeFlags.flags &= ~a_flag.flags;
		return true;
	}

	bool BGSSaveLoadGame::ClearChangeFlags(TESFormID a_formID) const
	{
		if (!changesMap) {
			return false;
		}

		const auto flagLock = BSAutoWriteLock(changesMap->rwLock);

		const auto flagsIt = changesMap->find(a_formID);
		if (flagsIt == changesMap->end()) {
			return false;
		}

		changesMap->erase(flagsIt);
		return true;
	}
}
