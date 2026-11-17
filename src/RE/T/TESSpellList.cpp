#include "RE/T/TESSpellList.hpp"

#include "RE/B/BSContainer_ForEachResult.hpp"

namespace RE
{
	auto TESSpellList::SpellData::GetSpellCount() const noexcept -> std::uint32_t
	{
		return numSpells;
	}

	auto TESSpellList::SpellData::GetLevSpellCount() const noexcept -> std::uint32_t
	{
		return numLevSpells;
	}

	auto TESSpellList::SpellData::GetShoutCount() const noexcept -> std::uint32_t
	{
		return numShouts;
	}

	auto TESSpellList::SpellData::GetSpells() noexcept -> std::span<SpellItem*>
	{
		return {spells.data(), numSpells};
	}

	auto TESSpellList::SpellData::GetLevSpells() noexcept -> std::span<TESLevSpell*>
	{
		return {levSpells.data(), numLevSpells};
	}

	auto TESSpellList::SpellData::GetShouts() noexcept -> std::span<TESShout*>
	{
		return {shouts.data(), numShouts};
	}

	auto TESSpellList::SpellData::GetSpells() const noexcept -> std::span<SpellItem* const>
	{
		return {spells.data(), numSpells};
	}

	auto TESSpellList::SpellData::GetLevSpells() const noexcept -> std::span<TESLevSpell* const>
	{
		return {levSpells.data(), numLevSpells};
	}

	auto TESSpellList::SpellData::GetShouts() const noexcept -> std::span<TESShout* const>
	{
		return {shouts.data(), numShouts};
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

	auto TESSpellList::SpellData::ForEachSpell(
		const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(SpellItem*) const>>& a_predicate) const
		-> BSContainer::ForEachResult
	{
		if (!spells.data()) {
			return BSContainer::ForEachResult::Continue;
		}

		for (auto i = static_cast<std::uint32_t>(0); i < numSpells; i++) {
			auto* spell = spells[i];
			if (std::invoke(a_predicate.get(), spell) == BSContainer::ForEachResult::Stop) {
				return BSContainer::ForEachResult::Stop;
			}
		}

		return BSContainer::ForEachResult::Continue;
	}

	auto TESSpellList::SpellData::ForEachLevSpell(
		const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(TESLevSpell*) const>>& a_predicate) const
		-> BSContainer::ForEachResult
	{
		if (!levSpells.data()) {
			return BSContainer::ForEachResult::Continue;
		}

		for (auto i = static_cast<std::uint32_t>(0); i < numLevSpells; i++) {
			auto* levSpell = levSpells[i];
			if (std::invoke(a_predicate.get(), levSpell) == BSContainer::ForEachResult::Stop) {
				return BSContainer::ForEachResult::Stop;
			}
		}

		return BSContainer::ForEachResult::Continue;
	}

	auto TESSpellList::SpellData::ForEachShout(
		const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(TESShout*) const>>& a_predicate) const
		-> BSContainer::ForEachResult
	{
		if (!shouts.data()) {
			return BSContainer::ForEachResult::Continue;
		}

		for (auto i = static_cast<std::uint32_t>(0); i < numShouts; i++) {
			auto* shout = shouts[i];
			if (std::invoke(a_predicate.get(), shout) == BSContainer::ForEachResult::Stop) {
				return BSContainer::ForEachResult::Stop;
			}
		}

		return BSContainer::ForEachResult::Continue;
	}
}
