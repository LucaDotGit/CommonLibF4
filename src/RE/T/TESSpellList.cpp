#include "RE/T/TESSpellList.hpp"

#include "RE/B/BSContainer_ForEachResult.hpp"

namespace RE
{
	std::uint32_t TESSpellList::SpellData::GetSpellCount() const noexcept
	{
		return numSpells;
	}

	std::uint32_t TESSpellList::SpellData::GetLevSpellCount() const noexcept
	{
		return numLevSpells;
	}

	std::uint32_t TESSpellList::SpellData::GetShoutCount() const noexcept
	{
		return numShouts;
	}

	std::span<SpellItem*> TESSpellList::SpellData::GetSpells() noexcept
	{
		return { spells.data(), numSpells };
	}

	std::span<TESLevSpell*> TESSpellList::SpellData::GetLevSpells() noexcept
	{
		return { levSpells.data(), numLevSpells };
	}

	std::span<TESShout*> TESSpellList::SpellData::GetShouts() noexcept
	{
		return { shouts.data(), numShouts };
	}

	std::span<SpellItem* const> TESSpellList::SpellData::GetSpells() const noexcept
	{
		return { spells.data(), numSpells };
	}

	std::span<TESLevSpell* const> TESSpellList::SpellData::GetLevSpells() const noexcept
	{
		return { levSpells.data(), numLevSpells };
	}

	std::span<TESShout* const> TESSpellList::SpellData::GetShouts() const noexcept
	{
		return { shouts.data(), numShouts };
	}

	void TESSpellList::SpellData::SetSpells(std::span<SpellItem*> a_spells)
	{
		ClearSpells();

		numSpells = static_cast<std::uint32_t>(a_spells.size());
		spells.allocate_bytes(numSpells);
		std::ranges::copy(a_spells, spells.data());
	}

	void TESSpellList::SpellData::SetLevSpells(std::span<TESLevSpell*> a_levSpells)
	{
		ClearLevSpells();

		numLevSpells = static_cast<std::uint32_t>(a_levSpells.size());
		levSpells.allocate_bytes(numLevSpells);
		std::ranges::copy(a_levSpells, levSpells.data());
	}

	void TESSpellList::SpellData::SetShouts(std::span<TESShout*> a_shouts)
	{
		ClearShouts();

		numShouts = static_cast<std::uint32_t>(a_shouts.size());
		shouts.allocate_bytes(numShouts);
		std::ranges::copy(a_shouts, shouts.data());
	}

	void TESSpellList::SpellData::ClearSpells()
	{
		spells.deallocate_bytes();
		numSpells = 0;
	}

	void TESSpellList::SpellData::ClearLevSpells()
	{
		levSpells.deallocate_bytes();
		numLevSpells = 0;
	}

	void TESSpellList::SpellData::ClearShouts()
	{
		shouts.deallocate_bytes();
		numShouts = 0;
	}

	BSContainer::ForEachResult TESSpellList::SpellData::ForEachSpell(
		const REX::NotNull<std::function<BSContainer::ForEachResult(SpellItem*)>>& a_predicate) const
	{
		if (!spells.data()) {
			return BSContainer::ForEachResult::kContinue;
		}

		for (auto i = 0ui32; i < numSpells; i++) {
			auto* spell = spells[i];
			if (std::invoke(*a_predicate, spell) == BSContainer::ForEachResult::kStop) {
				return BSContainer::ForEachResult::kStop;
			}
		}

		return BSContainer::ForEachResult::kContinue;
	}

	BSContainer::ForEachResult TESSpellList::SpellData::ForEachLevSpell(
		const REX::NotNull<std::function<BSContainer::ForEachResult(TESLevSpell*)>>& a_predicate) const
	{
		if (!levSpells.data()) {
			return BSContainer::ForEachResult::kContinue;
		}

		for (auto i = 0ui32; i < numLevSpells; i++) {
			auto* levSpell = levSpells[i];
			if (std::invoke(*a_predicate, levSpell) == BSContainer::ForEachResult::kStop) {
				return BSContainer::ForEachResult::kStop;
			}
		}

		return BSContainer::ForEachResult::kContinue;
	}

	BSContainer::ForEachResult TESSpellList::SpellData::ForEachShout(
		const REX::NotNull<std::function<BSContainer::ForEachResult(TESShout*)>>& a_predicate) const
	{
		if (!shouts.data()) {
			return BSContainer::ForEachResult::kContinue;
		}

		for (auto i = 0ui32; i < numShouts; i++) {
			auto* shout = shouts[i];
			if (std::invoke(*a_predicate, shout) == BSContainer::ForEachResult::kStop) {
				return BSContainer::ForEachResult::kStop;
			}
		}

		return BSContainer::ForEachResult::kContinue;
	}
}
