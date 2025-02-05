#include "RE/Bethesda/TES.hpp"

#include "RE/Bethesda/BSContainer.hpp"
#include "RE/Bethesda/GridCellArray.hpp"
#include "RE/Bethesda/TESObjectREFRs.hpp"
#include "RE/Bethesda/TESWorldSpace.hpp"

namespace RE
{
	BSContainer::ForEachResult TES::ForEachRefInSkyCell(std::function<BSContainer::ForEachResult(TESObjectREFR*)> a_callback) const
	{
		if (!worldSpace) {
			return BSContainer::ForEachResult::kContinue;
		}

		const auto* skyCell = worldSpace->GetSkyCell();
		if (!skyCell) {
			return BSContainer::ForEachResult::kContinue;
		}

		return skyCell->ForEachRef(a_callback);
	}

	BSContainer::ForEachResult TES::ForEachRefInSkyCell(const NiPoint3& a_origin, float a_radius,
		std::function<BSContainer::ForEachResult(TESObjectREFR*)> a_callback) const
	{
		if (!worldSpace) {
			return BSContainer::ForEachResult::kContinue;
		}

		const auto* skyCell = worldSpace->GetSkyCell();
		if (!skyCell) {
			return BSContainer::ForEachResult::kContinue;
		}

		return skyCell->ForEachRefInRange(a_origin, a_radius, a_callback);
	}

	BSContainer::ForEachResult TES::ForEachRef(std::function<BSContainer::ForEachResult(TESObjectREFR*)> a_callback) const
	{
		if (interiorCell) {
			if (interiorCell->ForEachRef(a_callback) == BSContainer::ForEachResult::kStop) {
				return BSContainer::ForEachResult::kStop;
			}

			return ForEachRefInSkyCell(a_callback);
		}

		const auto gridLength = gridCells ? gridCells->length : 0;
		if (gridLength <= 0) {
			return ForEachRefInSkyCell(a_callback);
		}

		for (auto x = 0ui32; x < gridLength; x++) {
			for (auto y = 0ui32; y < gridLength; y++) {
				const auto* cell = gridCells->GetCell(x, y);
				if (!cell || !cell->IsAttached()) {
					continue;
				}

				if (cell->ForEachRef(a_callback) == BSContainer::ForEachResult::kStop) {
					return BSContainer::ForEachResult::kStop;
				}
			}
		}

		return ForEachRefInSkyCell(a_callback);
	}

	BSContainer::ForEachResult TES::ForEachRefInRange(const NiPoint3& a_center, float a_radius,
		std::function<BSContainer::ForEachResult(TESObjectREFR*)> a_callback) const
	{
		if (a_radius <= 0.0f) {
			return ForEachRef(a_callback);
		}

		if (interiorCell) {
			if (interiorCell->ForEachRefInRange(a_center, a_radius, a_callback) == BSContainer::ForEachResult::kStop) {
				return BSContainer::ForEachResult::kStop;
			}

			return ForEachRefInSkyCell(a_center, a_radius, a_callback);
		}

		const auto gridLength = gridCells ? gridCells->length : 0;
		if (gridLength <= 0) {
			return ForEachRefInSkyCell(a_center, a_radius, a_callback);
		}

		constexpr auto CELL_SIZE = GridCellArray::CELL_SIZE;

		const auto coordsPlus = NiPoint2{ a_center.x + a_radius, a_center.y + a_radius };
		const auto coordsMinus = NiPoint2{ a_center.x - a_radius, a_center.y - a_radius };

		for (auto x = 0ui32; x < gridLength; x++) {
			for (auto y = 0ui32; y < gridLength; y++) {
				const auto* cell = gridCells->GetCell(x, y);
				if (!cell || !cell->IsAttached()) {
					continue;
				}

				const auto* cellCoords = cell->GetExteriorData();
				if (!cellCoords) {
					continue;
				}

				const auto worldPos = cellCoords->worldPos;
				const auto cellPlus = NiPoint2{ worldPos.x + CELL_SIZE, worldPos.y + CELL_SIZE };

				if (coordsPlus.x < worldPos.x || coordsPlus.y < worldPos.y || coordsMinus.x > cellPlus.x || coordsMinus.y > cellPlus.y) {
					continue;
				}

				if (cell->ForEachRefInRange(a_center, a_radius, a_callback) == BSContainer::ForEachResult::kStop) {
					return BSContainer::ForEachResult::kStop;
				}
			}
		}

		return ForEachRefInSkyCell(a_center, a_radius, a_callback);
	}

	BSContainer::ForEachResult TES::ForEachRefInRange(const TESObjectREFR* a_origin, float a_radius,
		std::function<BSContainer::ForEachResult(TESObjectREFR*)> a_callback) const
	{
		if (!a_origin) {
			return BSContainer::ForEachResult::kContinue;
		}

		return ForEachRefInRange(a_origin->GetPosition(), a_radius, a_callback);
	}
}
