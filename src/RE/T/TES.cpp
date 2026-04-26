#include "RE/T/TES.hpp"

#include "RE/B/BSContainer_ForEachResult.hpp"
#include "RE/E/EXTERIOR_DATA.hpp"
#include "RE/G/GridCellArray.hpp"
#include "RE/N/NiPoint.hpp"
#include "RE/T/TESObjectCELL.hpp"
#include "RE/T/TESObjectREFR.hpp"
#include "RE/T/TESWorldSpace.hpp"

namespace RE
{
	TES* TES::GetSingleton()
	{
		static const auto SINGLETON = REL::Relocation<TES**>{ ID::TES::Singleton };
		return *SINGLETON;
	}

	BSContainer::ForEachResult TES::ForEachRefInSkyCell(
		const REX::NotNull<std::function<BSContainer::ForEachResult(const NiPointer<TESObjectREFR>&)>>& a_predicate) const
	{
		if (!worldSpace) {
			return BSContainer::ForEachResult::kContinue;
		}

		const auto* skyCell = worldSpace->GetSkyCell();
		if (!skyCell) {
			return BSContainer::ForEachResult::kContinue;
		}

		return skyCell->ForEachRef(a_predicate);
	}

	BSContainer::ForEachResult TES::ForEachRefInSkyCell(const NiPoint3& a_origin, REX::Float32 a_radius,
		const REX::NotNull<std::function<BSContainer::ForEachResult(const NiPointer<TESObjectREFR>&)>>& a_predicate) const
	{
		if (!worldSpace) {
			return BSContainer::ForEachResult::kContinue;
		}

		const auto* skyCell = worldSpace->GetSkyCell();
		if (!skyCell) {
			return BSContainer::ForEachResult::kContinue;
		}

		return skyCell->ForEachRefInRange(a_origin, a_radius, a_predicate);
	}

	BSContainer::ForEachResult TES::ForEachRef(
		const REX::NotNull<std::function<BSContainer::ForEachResult(const NiPointer<TESObjectREFR>&)>>& a_predicate) const
	{
		if (interiorCell) {
			if (interiorCell->ForEachRef(a_predicate) == BSContainer::ForEachResult::kStop) {
				return BSContainer::ForEachResult::kStop;
			}

			return ForEachRefInSkyCell(a_predicate);
		}

		const auto gridLength = gridCells ? gridCells->length : 0;
		if (gridLength <= 0) {
			return ForEachRefInSkyCell(a_predicate);
		}

		for (auto x = 0ui32; x < gridLength; x++) {
			for (auto y = 0ui32; y < gridLength; y++) {
				const auto* cell = gridCells->GetCell(x, y);
				if (!cell || !cell->IsAttached()) {
					continue;
				}

				if (cell->ForEachRef(a_predicate) == BSContainer::ForEachResult::kStop) {
					return BSContainer::ForEachResult::kStop;
				}
			}
		}

		return ForEachRefInSkyCell(a_predicate);
	}

	BSContainer::ForEachResult TES::ForEachRefInRange(const NiPoint3& a_center, REX::Float32 a_radius,
		const REX::NotNull<std::function<BSContainer::ForEachResult(const NiPointer<TESObjectREFR>&)>>& a_predicate) const
	{
		if (a_radius <= 0.0_f32) {
			return ForEachRef(a_predicate);
		}

		if (interiorCell) {
			if (interiorCell->ForEachRefInRange(a_center, a_radius, a_predicate) == BSContainer::ForEachResult::kStop) {
				return BSContainer::ForEachResult::kStop;
			}

			return ForEachRefInSkyCell(a_center, a_radius, a_predicate);
		}

		const auto gridLength = gridCells ? gridCells->length : 0;
		if (gridLength <= 0) {
			return ForEachRefInSkyCell(a_center, a_radius, a_predicate);
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

				const auto worldPos = NiPoint2{ cellCoords->worldX, cellCoords->worldY };
				const auto cellPlus = NiPoint2{ worldPos.x + CELL_SIZE, worldPos.y + CELL_SIZE };

				if (coordsPlus.x < worldPos.x || coordsPlus.y < worldPos.y || coordsMinus.x > cellPlus.x || coordsMinus.y > cellPlus.y) {
					continue;
				}

				if (cell->ForEachRefInRange(a_center, a_radius, a_predicate) == BSContainer::ForEachResult::kStop) {
					return BSContainer::ForEachResult::kStop;
				}
			}
		}

		return ForEachRefInSkyCell(a_center, a_radius, a_predicate);
	}

	BSContainer::ForEachResult TES::ForEachRefInRange(const TESObjectREFR* a_origin, REX::Float32 a_radius,
		const REX::NotNull<std::function<BSContainer::ForEachResult(const NiPointer<TESObjectREFR>&)>>& a_predicate) const
	{
		if (!a_origin) {
			return BSContainer::ForEachResult::kContinue;
		}

		return ForEachRefInRange(a_origin->GetPosition(), a_radius, a_predicate);
	}
}
