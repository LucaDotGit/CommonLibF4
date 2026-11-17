#include "RE/T/TESWorldSpace.hpp"

#include "RE/G/GridCellArray.hpp"
#include "RE/N/NiPoint3.hpp"
#include "RE/T/TESObjectCELL.hpp"
#include "RE/T/TESWaterForm.hpp"

namespace RE
{
	auto TESWorldSpace::OFFSET_DATA::GetMinOffsetX() const noexcept -> std::int32_t
	{
		return static_cast<std::int32_t>(offsetMinCoords.x) / static_cast<std::int32_t>(GridCellArray::CELL_SIZE);
	}

	auto TESWorldSpace::OFFSET_DATA::GetMinOffsetY() const noexcept -> std::int32_t
	{
		return static_cast<std::int32_t>(offsetMinCoords.y) / static_cast<std::int32_t>(GridCellArray::CELL_SIZE);
	}

	auto TESWorldSpace::OFFSET_DATA::GetMaxOffsetX() const noexcept -> std::int32_t
	{
		return static_cast<std::int32_t>(offsetMaxCoords.x) / static_cast<std::int32_t>(GridCellArray::CELL_SIZE);
	}

	auto TESWorldSpace::OFFSET_DATA::GetMaxOffsetY() const noexcept -> std::int32_t
	{
		return static_cast<std::int32_t>(offsetMaxCoords.y) / static_cast<std::int32_t>(GridCellArray::CELL_SIZE);
	}

	auto TESWorldSpace::Load(TESFile* a_file) -> bool
	{
		using FuncType = decltype(&TESWorldSpace::Load);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESWorldSpace::Load);
		return std::invoke(FUNC, this, a_file);
	}

	auto TESWorldSpace::LoadPartial(TESFile* a_file) -> bool
	{
		using FuncType = decltype(&TESWorldSpace::LoadPartial);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESWorldSpace::LoadPartial);
		return std::invoke(FUNC, this, a_file);
	}

	auto TESWorldSpace::FindInFileFast(TESFile* a_file) -> bool
	{
		using FuncType = decltype(&TESWorldSpace::FindInFileFast);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESWorldSpace::FindInFileFast);
		return std::invoke(FUNC, this, a_file);
	}

	void TESWorldSpace::PrefetchCellData(TESFile* a_file, std::int32_t a_x, std::int32_t a_y, std::uint32_t a_priority)
	{
		using FuncType = decltype(&TESWorldSpace::PrefetchCellData);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESWorldSpace::PrefetchCellData);
		std::invoke(FUNC, this, a_file, a_x, a_y, a_priority);
	}

	auto TESWorldSpace::FindCellInFile(TESFile* a_file, std::int32_t a_x, std::int32_t a_y) -> bool
	{
		using FuncType = decltype(&TESWorldSpace::FindCellInFile);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESWorldSpace::FindCellInFile);
		return std::invoke(FUNC, this, a_file, a_x, a_y);
	}

	// NOLINTNEXTLINE(readability-make-member-function-const)
	void TESWorldSpace::ChangeMapMarkerPosition(NiPoint3 a_position, bool a_inverse) noexcept
	{
		if (!a_inverse) {
			a_position.x -= worldMapOffsetData.mapOffsetX;
			a_position.y -= worldMapOffsetData.mapOffsetY;
			a_position.z -= worldMapOffsetData.mapOffsetZ;
		}

		const auto worldMapScale = worldMapOffsetData.mapScale;
		if (worldMapScale != static_cast<REX::Float32>(1.0) && worldMapScale != static_cast<REX::Float32>(0.0)) {
			const auto maxX = (maximumCoords.x + minimumCoords.x) * static_cast<REX::Float32>(0.5);
			const auto maxY = (maximumCoords.y + minimumCoords.y) * static_cast<REX::Float32>(0.5);

			const auto deltaX = a_position.x - maxX;
			const auto deltaY = a_position.y - maxY;

			auto tempWorldMapScale = static_cast<REX::Float32>(0.0);
			if (a_inverse) {
				tempWorldMapScale = static_cast<REX::Float32>(1.0) / worldMapScale;
			}
			else {
				tempWorldMapScale = worldMapScale;
			}

			a_position.x = maxX + (deltaX * tempWorldMapScale);
			a_position.y = maxY + (deltaY * tempWorldMapScale);
			a_position.z *= tempWorldMapScale;
		}

		if (!a_inverse) {
			a_position.x += worldMapOffsetData.mapOffsetX;
			a_position.y += worldMapOffsetData.mapOffsetY;
			a_position.z += worldMapOffsetData.mapOffsetZ;
		}
	}

	auto TESWorldSpace::GetParentWorld(PARENT_USE_FLAG a_flags) const noexcept -> TESWorldSpace*
	{
		if (parentUseFlags.none(a_flags)) {
			return nullptr;
		}

		return parentWorld;
	}

	auto TESWorldSpace::GetLODWaterType() const noexcept -> TESWaterForm*
	{
		const auto* worldSpaceIt = this;
		for (const auto* parentWorldIt = this; parentWorldIt;
			 parentWorldIt = parentWorldIt->GetParentWorld(PARENT_USE_FLAG::LOD)) {
			worldSpaceIt = parentWorldIt;
		}

		if (!worldSpaceIt->lodWater) {
			return TESWaterForm::GetDefaultWater();
		}

		return worldSpaceIt->lodWater;
	}

	void TESWorldSpace::SetLODWaterType(TESWaterForm* a_waterType) noexcept
	{
		lodWater = a_waterType;
		lodWaterHeight = GetLODWaterHeight();

		flags.reset(Flags::NoLODWater);
		parentUseFlags.reset(PARENT_USE_FLAG::LOD);
	}

	auto TESWorldSpace::GetLODWaterHeight() const noexcept -> REX::Float32
	{
		const auto* worldSpaceIt = this;
		for (const auto* parentWorldIt = this; parentWorldIt;
			 parentWorldIt = parentWorldIt->GetParentWorld(PARENT_USE_FLAG::LOD)) {
			worldSpaceIt = parentWorldIt;
		}

		if (!worldSpaceIt) {
			return -std::numeric_limits<REX::Float32>::infinity();
		}

		return worldSpaceIt->lodWaterHeight;
	}

	void TESWorldSpace::SetLODWaterHeight(REX::Float32 a_waterHeight) noexcept
	{
		lodWater = GetLODWaterType();
		lodWaterHeight = a_waterHeight;

		flags.reset(Flags::NoLODWater);
		parentUseFlags.reset(PARENT_USE_FLAG::LOD);
	}

	auto TESWorldSpace::GetWaterType() const noexcept -> TESWaterForm*
	{
		const auto* worldSpaceIt = this;
		for (const auto* parentWorldIt = this; parentWorldIt;
			 parentWorldIt = parentWorldIt->GetParentWorld(PARENT_USE_FLAG::Water)) {
			worldSpaceIt = parentWorldIt;
		}

		if (!worldSpaceIt->worldWater) {
			return TESWaterForm::GetDefaultWater();
		}

		return worldSpaceIt->worldWater;
	}

	void TESWorldSpace::SetWaterType(TESWaterForm* a_waterType) noexcept
	{
		worldWater = a_waterType;
		parentUseFlags.reset(PARENT_USE_FLAG::Water);
	}

	auto TESWorldSpace::GetDefaultWaterHeight() const noexcept -> REX::Float32
	{
		const auto* worldSpaceIt = this;
		for (const auto* parentWorldIt = this; parentWorldIt;
			 parentWorldIt = parentWorldIt->GetParentWorld(PARENT_USE_FLAG::Land)) {
			worldSpaceIt = parentWorldIt;
		}

		if (!worldSpaceIt) {
			return -std::numeric_limits<REX::Float32>::infinity();
		}

		return worldSpaceIt->defaultWaterHeight;
	}

	void TESWorldSpace::SetDefaultWaterHeight(REX::Float32 a_waterHeight) noexcept
	{
		defaultWaterHeight = a_waterHeight;
		parentUseFlags.reset(PARENT_USE_FLAG::Land);
	}

	auto TESWorldSpace::GetClimate() const noexcept -> TESClimate*
	{
		const auto* worldSpaceIt = this;
		for (const auto* parentWorldIt = this; parentWorldIt;
			 parentWorldIt = parentWorldIt->GetParentWorld(PARENT_USE_FLAG::Climate)) {
			worldSpaceIt = parentWorldIt;
		}

		if (!worldSpaceIt) {
			return nullptr;
		}

		return worldSpaceIt->climate;
	}

	void TESWorldSpace::SetClimate(TESClimate* a_climate) noexcept
	{
		climate = a_climate;
		parentUseFlags.reset(PARENT_USE_FLAG::Climate);
	}

	auto TESWorldSpace::GetSkyCell() const noexcept -> TESObjectCELL*
	{
		const auto* worldSpaceIt = this;
		for (const auto* parentWorldIt = this; parentWorldIt;
			 parentWorldIt = parentWorldIt->GetParentWorld(PARENT_USE_FLAG::SkyCell)) {
			worldSpaceIt = parentWorldIt;
		}

		if (!worldSpaceIt) {
			return nullptr;
		}

		return worldSpaceIt->skyCell;
	}

	void TESWorldSpace::SetSkyCell(TESObjectCELL* a_skyCell) noexcept
	{
		skyCell = a_skyCell;
		parentUseFlags.reset(PARENT_USE_FLAG::SkyCell);
	}

	auto TESWorldSpace::GetKeyFromCellPosition(std::int32_t a_x, std::int32_t a_y) noexcept -> std::int32_t
	{
		constexpr auto COORDINATE_MASK = std::numeric_limits<std::uint16_t>::max();
		constexpr auto COORDINATE_SHIFT = std::numeric_limits<std::uint8_t>::digits * sizeof(std::uint16_t);

		return static_cast<std::int32_t>(
			(static_cast<std::uint32_t>(a_y) & COORDINATE_MASK) |
			((static_cast<std::uint32_t>(a_x) & COORDINATE_MASK) << COORDINATE_SHIFT));
	}

	auto TESWorldSpace::GetKeyFromCell(const TESObjectCELL* a_cell) noexcept -> std::optional<std::int32_t>
	{
		if (!a_cell) {
			return std::nullopt;
		}

		const auto cellXY = a_cell->GetCellXAndY();
		if (!cellXY.has_value()) {
			return std::nullopt;
		}
		return GetKeyFromCellPosition(cellXY->GetX(), cellXY->GetY());
	}

	auto TESWorldSpace::GetCellFromKey(std::int32_t a_cellKey) const -> TESObjectCELL*
	{
		const auto cellIt = cellMap.find(a_cellKey);
		if (cellIt == cellMap.end()) {
			return nullptr;
		}

		return cellIt->second;
	}

	auto TESWorldSpace::GetIndexForCellPosition(const OFFSET_DATA* a_offsetData, std::int32_t a_x, std::int32_t a_y)
		noexcept -> std::uint32_t
	{
		if (!a_offsetData) {
			return std::numeric_limits<std::uint32_t>::max();
		}

		const auto minX = a_offsetData->GetMinOffsetX();
		const auto minY = a_offsetData->GetMinOffsetY();
		const auto maxX = a_offsetData->GetMaxOffsetX();
		const auto maxY = a_offsetData->GetMaxOffsetY();

		if (a_x < minX || a_x > maxX || a_y < minY || a_y > maxY) {
			return std::numeric_limits<std::uint32_t>::max();
		}

		const auto xIndex = static_cast<std::uint32_t>(a_x - minX);
		const auto yIndex = static_cast<std::uint32_t>(a_y - minY);
		const auto width = static_cast<std::uint32_t>(maxX - minX + 1);

		return xIndex + (yIndex * width);
	}

	auto TESWorldSpace::GetOffsetData(TESFile* a_file) const -> TESWorldSpace::OFFSET_DATA*
	{
		using FuncType = decltype(&TESWorldSpace::GetOffsetData);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESWorldSpace::GetOffsetData);
		return std::invoke(FUNC, this, a_file);
	}

	auto TESWorldSpace::CreateOffsetData(TESFile* a_file) -> TESWorldSpace::OFFSET_DATA*
	{
		// This either gets or creates the offset data.
		using FuncType = decltype(&TESWorldSpace::GetOffsetData);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESWorldSpace::CreateOffsetData);
		return std::invoke(FUNC, this, a_file);
	}

	void TESWorldSpace::FreeOffsetData(TESFile* a_file)
	{
		using FuncType = decltype(&TESWorldSpace::FreeOffsetData);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESWorldSpace::FreeOffsetData);
		std::invoke(FUNC, this, a_file);
	}
}
