#include "RE/T/TESRegionList.hpp"

#include "RE/T/TESRegion.hpp"

namespace RE
{
	void TESRegionList::SetRegions(std::span<TESRegion*> a_regions)
	{
		ClearRegions();

		for (auto* region : a_regions) {
			push_back(region);
		}
	}

	void TESRegionList::ClearRegions()
	{
		if (!ownsRegionMemory) {
			clear();
			return;
		}

		for (auto*& region : *this) {
			if (!region) {
				continue;
			}

			delete region;
			region = nullptr;
		}

		clear();

		ownsRegionMemory = false;
	}
}
