#include "RE/B/BGSPerkRankArray.hpp"

#include "RE/P/PerkRankData.hpp"

namespace RE
{
	std::span<PerkRankData* const> BGSPerkRankArray::GetPerks() const noexcept
	{
		return { perks.data(), perkCount };
	}

	void BGSPerkRankArray::SetPerks(std::span<std::unique_ptr<PerkRankData>> a_perks)
	{
		ClearPerks();

		perkCount = static_cast<std::uint32_t>(a_perks.size());
		perks.allocate_bytes(perkCount);

		for (auto i = 0ui32; i < perkCount; i++) {
			perks[i] = a_perks[i].release();
		}
	}

	void BGSPerkRankArray::ClearPerks()
	{
		if (!perks.data()) {
			perkCount = 0;
			return;
		}

		for (auto i = 0ui32; i < perkCount; i++) {
			auto*& perk = perks[i];
			if (!perk) {
				continue;
			}

			delete perk;
			perk = nullptr;
		}

		perks.deallocate_bytes();
		perkCount = 0;
	}
}
