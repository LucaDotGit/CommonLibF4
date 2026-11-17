#include "RE/T/TES.hpp"

#include "RE/B/BSContainer_ForEachResult.hpp"
#include "RE/E/EXTERIOR_DATA.hpp"
#include "RE/G/GridCellArray.hpp"
#include "RE/N/NiPoint2.hpp"
#include "RE/T/TESObjectCELL.hpp"
#include "RE/T/TESObjectREFR.hpp"
#include "RE/T/TESWorldSpace.hpp"

namespace RE
{
	auto TES::GetSingleton() noexcept -> TES*
	{
		static const auto SINGLETON = REL::Relocation<TES**>(ID::TES::Singleton);
		return *SINGLETON;
	}

	void TES::CreateTextureImage(
		const char* a_filePath,
		NiPointer<NiTexture>& a_outTexture,
		bool a_mustFindFile,
		bool a_archiveOnly) const
	{
		using FuncType = decltype(&TES::CreateTextureImage);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TES::CreateTextureImage);
		std::invoke(FUNC, this, a_filePath, a_outTexture, a_mustFindFile, a_archiveOnly);
	}

	void TES::UpdateMultiBoundVisibility(BSCullingProcess* a_cullingProcess)
	{
		using FuncType = decltype(&TES::UpdateMultiBoundVisibility);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TES::UpdateMultiBoundVisibility);
		std::invoke(FUNC, this, a_cullingProcess);
	}

	auto TES::ForEachRefInSkyCell(
		const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(const NiPointer<TESObjectREFR>&) const>>&
			a_predicate) const -> BSContainer::ForEachResult
	{
		if (!worldSpace) {
			return BSContainer::ForEachResult::Continue;
		}

		const auto* skyCell = worldSpace->GetSkyCell();
		if (!skyCell) {
			return BSContainer::ForEachResult::Continue;
		}

		return skyCell->ForEachRef(a_predicate);
	}

	auto TES::ForEachRefInSkyCell(
		const NiPoint3& a_origin,
		REX::Float32 a_radius,
		const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(const NiPointer<TESObjectREFR>&) const>>&
			a_predicate) const -> BSContainer::ForEachResult
	{
		if (!worldSpace) {
			return BSContainer::ForEachResult::Continue;
		}

		const auto* skyCell = worldSpace->GetSkyCell();
		if (!skyCell) {
			return BSContainer::ForEachResult::Continue;
		}

		return skyCell->ForEachRefInRange(a_origin, a_radius, a_predicate);
	}

	auto TES::ForEachRef(
		const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(const NiPointer<TESObjectREFR>&) const>>&
			a_predicate) const -> BSContainer::ForEachResult
	{
		if (interiorCell) {
			if (interiorCell->ForEachRef(a_predicate) == BSContainer::ForEachResult::Stop) {
				return BSContainer::ForEachResult::Stop;
			}

			return ForEachRefInSkyCell(a_predicate);
		}

		const auto gridLength = gridCells ? gridCells->length : 0;
		if (gridLength <= 0) {
			return ForEachRefInSkyCell(a_predicate);
		}

		for (auto x = static_cast<std::uint32_t>(0); x < gridLength; x++) {
			for (auto y = static_cast<std::uint32_t>(0); y < gridLength; y++) {
				const auto* cell = gridCells->GetCell(x, y);
				if (!cell || !cell->IsAttached()) {
					continue;
				}

				if (cell->ForEachRef(a_predicate) == BSContainer::ForEachResult::Stop) {
					return BSContainer::ForEachResult::Stop;
				}
			}
		}

		return ForEachRefInSkyCell(a_predicate);
	}

	auto TES::ForEachRefInRange(
		const NiPoint3& a_center,
		REX::Float32 a_radius,
		const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(const NiPointer<TESObjectREFR>&) const>>&
			a_predicate) const -> BSContainer::ForEachResult
	{
		if (a_radius <= static_cast<REX::Float32>(0.0)) {
			return ForEachRef(a_predicate);
		}

		if (interiorCell) {
			if (interiorCell->ForEachRefInRange(a_center, a_radius, a_predicate) == BSContainer::ForEachResult::Stop) {
				return BSContainer::ForEachResult::Stop;
			}

			return ForEachRefInSkyCell(a_center, a_radius, a_predicate);
		}

		const auto gridLength = gridCells ? gridCells->length : 0;
		if (gridLength <= 0) {
			return ForEachRefInSkyCell(a_center, a_radius, a_predicate);
		}

		const auto coordsPlus = NiPoint2{a_center.x + a_radius, a_center.y + a_radius};
		const auto coordsMinus = NiPoint2{a_center.x - a_radius, a_center.y - a_radius};

		for (auto x = static_cast<std::uint32_t>(0); x < gridLength; x++) {
			for (auto y = static_cast<std::uint32_t>(0); y < gridLength; y++) {
				const auto* cell = gridCells->GetCell(x, y);
				if (!cell || !cell->IsAttached()) {
					continue;
				}

				const auto* cellCoords = cell->GetExteriorData();
				if (!cellCoords) {
					continue;
				}

				const auto worldPos = NiPoint2{cellCoords->worldX, cellCoords->worldY};
				const auto cellPlus =
					NiPoint2{worldPos.x + GridCellArray::CELL_SIZE, worldPos.y + GridCellArray::CELL_SIZE};

				if (coordsPlus.x < worldPos.x ||
					coordsPlus.y < worldPos.y ||
					coordsMinus.x > cellPlus.x ||
					coordsMinus.y > cellPlus.y) {
					continue;
				}

				if (cell->ForEachRefInRange(a_center, a_radius, a_predicate) == BSContainer::ForEachResult::Stop) {
					return BSContainer::ForEachResult::Stop;
				}
			}
		}

		return ForEachRefInSkyCell(a_center, a_radius, a_predicate);
	}

	auto TES::ForEachRefInRange(
		const TESObjectREFR* a_origin,
		REX::Float32 a_radius,
		const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(const NiPointer<TESObjectREFR>&) const>>&
			a_predicate) const -> BSContainer::ForEachResult
	{
		if (!a_origin) {
			return BSContainer::ForEachResult::Continue;
		}

		return ForEachRefInRange(a_origin->GetPosition(), a_radius, a_predicate);
	}
}
