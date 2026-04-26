#include "RE/T/TESWorldSpace.hpp"

#include "RE/G/GridCellArray.hpp"
#include "RE/T/TESWaterForm.hpp"

namespace RE
{
	std::int32_t TESWorldSpace::OFFSET_DATA::GetMinOffsetX() const noexcept
	{
		return static_cast<std::int32_t>(offsetMinCoords.x) / static_cast<std::int32_t>(GridCellArray::CELL_SIZE);
	}

	std::int32_t TESWorldSpace::OFFSET_DATA::GetMinOffsetY() const noexcept
	{
		return static_cast<std::int32_t>(offsetMinCoords.y) / static_cast<std::int32_t>(GridCellArray::CELL_SIZE);
	}

	std::int32_t TESWorldSpace::OFFSET_DATA::GetMaxOffsetX() const noexcept
	{
		return static_cast<std::int32_t>(offsetMaxCoords.x) / static_cast<std::int32_t>(GridCellArray::CELL_SIZE);
	}

	std::int32_t TESWorldSpace::OFFSET_DATA::GetMaxOffsetY() const noexcept
	{
		return static_cast<std::int32_t>(offsetMaxCoords.y) / static_cast<std::int32_t>(GridCellArray::CELL_SIZE);
	}

	bool TESWorldSpace::Load(TESFile* a_file)
	{
		using FuncType = decltype(&TESWorldSpace::Load);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::TESWorldSpace::Load };
		return std::invoke(FUNC, this, a_file);
	}

	bool TESWorldSpace::LoadPartial(TESFile* a_file)
	{
		using FuncType = decltype(&TESWorldSpace::LoadPartial);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::TESWorldSpace::LoadPartial };
		return std::invoke(FUNC, this, a_file);
	}

	bool TESWorldSpace::FindInFileFast(TESFile* a_file)
	{
		using FuncType = decltype(&TESWorldSpace::FindInFileFast);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::TESWorldSpace::FindInFileFast };
		return std::invoke(FUNC, this, a_file);
	}

	void TESWorldSpace::PrefetchCellData(TESFile* a_file, std::int32_t a_x, std::int32_t a_y, std::uint32_t a_priority)
	{
		using FuncType = decltype(&TESWorldSpace::PrefetchCellData);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::TESWorldSpace::PrefetchCellData };
		FUNC(this, a_file, a_x, a_y, a_priority);
	}

	bool TESWorldSpace::FindCellInFile(TESFile* a_file, std::int32_t a_x, std::int32_t a_y)
	{
		using FuncType = decltype(&TESWorldSpace::FindCellInFile);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::TESWorldSpace::FindCellInFile };
		return std::invoke(FUNC, this, a_file, a_x, a_y);
	}

	TESWorldSpace* TESWorldSpace::GetParentWorld(PARENT_USE_FLAG a_flags) const noexcept
	{
		if (parentUseFlags.none(a_flags)) {
			return nullptr;
		}

		return parentWorld;
	}

	TESWaterForm* TESWorldSpace::GetLODWaterType() const noexcept
	{
		const auto* worldSpaceIt = this;
		for (; worldSpaceIt; worldSpaceIt = worldSpaceIt->GetParentWorld(PARENT_USE_FLAG::kLOD)) {
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

		flags.reset(Flags::kNoLODWater);
		parentUseFlags.reset(PARENT_USE_FLAG::kLOD);
	}

	REX::Float32 TESWorldSpace::GetLODWaterHeight() const noexcept
	{
		const auto* worldSpaceIt = this;
		for (; worldSpaceIt; worldSpaceIt = worldSpaceIt->GetParentWorld(PARENT_USE_FLAG::kLOD)) {
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

		flags.reset(Flags::kNoLODWater);
		parentUseFlags.reset(PARENT_USE_FLAG::kLOD);
	}

	TESWaterForm* TESWorldSpace::GetWaterType() const noexcept
	{
		const auto* worldSpaceIt = this;
		for (; worldSpaceIt; worldSpaceIt = worldSpaceIt->GetParentWorld(PARENT_USE_FLAG::kWater)) {
		}

		if (!worldSpaceIt->worldWater) {
			return TESWaterForm::GetDefaultWater();
		}

		return worldSpaceIt->worldWater;
	}

	void TESWorldSpace::SetWaterType(TESWaterForm* a_waterType) noexcept
	{
		worldWater = a_waterType;
		parentUseFlags.reset(PARENT_USE_FLAG::kWater);
	}

	REX::Float32 TESWorldSpace::GetDefaultWaterHeight() const noexcept
	{
		const auto* worldSpaceIt = this;
		for (; worldSpaceIt; worldSpaceIt = worldSpaceIt->GetParentWorld(PARENT_USE_FLAG::kLand)) {
		}

		if (!worldSpaceIt) {
			return -std::numeric_limits<REX::Float32>::infinity();
		}

		return worldSpaceIt->defaultWaterHeight;
	}

	void TESWorldSpace::SetDefaultWaterHeight(REX::Float32 a_waterHeight) noexcept
	{
		defaultWaterHeight = a_waterHeight;
		parentUseFlags.reset(PARENT_USE_FLAG::kLand);
	}

	TESClimate* TESWorldSpace::GetClimate() const noexcept
	{
		const auto* worldSpaceIt = this;
		for (; worldSpaceIt; worldSpaceIt = worldSpaceIt->GetParentWorld(PARENT_USE_FLAG::kClimate)) {
		}

		if (!worldSpaceIt) {
			return nullptr;
		}

		return worldSpaceIt->climate;
	}

	void TESWorldSpace::SetClimate(TESClimate* a_climate) noexcept
	{
		climate = a_climate;
		parentUseFlags.reset(PARENT_USE_FLAG::kClimate);
	}

	TESObjectCELL* TESWorldSpace::GetSkyCell() const noexcept
	{
		const auto* worldSpaceIt = this;
		for (; worldSpaceIt; worldSpaceIt = worldSpaceIt->GetParentWorld(PARENT_USE_FLAG::kSkyCell)) {
		}

		if (!worldSpaceIt) {
			return nullptr;
		}

		return worldSpaceIt->skyCell;
	}

	void TESWorldSpace::SetSkyCell(TESObjectCELL* a_skyCell) noexcept
	{
		skyCell = a_skyCell;
		parentUseFlags.reset(PARENT_USE_FLAG::kSkyCell);
	}

	std::int32_t TESWorldSpace::GetKeyFromCellCoord(std::int32_t a_x, std::int32_t a_y) noexcept
	{
		constexpr auto COORDINATE_MASK = std::numeric_limits<std::uint16_t>::max();
		constexpr auto COORDINATE_SHIFT = CHAR_BIT * sizeof(std::uint16_t);

		return static_cast<std::int32_t>(
			(static_cast<std::uint32_t>(a_y) & COORDINATE_MASK) |
			((static_cast<std::uint32_t>(a_x) & COORDINATE_MASK) << COORDINATE_SHIFT));
	}

	TESObjectCELL* TESWorldSpace::GetCellFromKey(std::int32_t a_cellKey) const
	{
		const auto cellIt = cellMap.find(a_cellKey);
		if (cellIt == cellMap.end()) {
			return nullptr;
		}

		return cellIt->second;
	}

	TESObjectCELL* TESWorldSpace::GetCellFromCellCoord(std::int32_t a_x, std::int32_t a_y) const
	{
		const auto cellKey = GetKeyFromCellCoord(a_x, a_y);
		return GetCellFromKey(cellKey);
	}

	std::uint32_t TESWorldSpace::GetIndexForCellCoord(const OFFSET_DATA* a_offsetData, std::int32_t a_x, std::int32_t a_y) noexcept
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

	std::uint32_t TESWorldSpace::GetIndexForCellCoord(TESFile* a_file, std::int32_t a_x, std::int32_t a_y) const
	{
		const auto* offsetData = GetOffsetData(a_file);
		return GetIndexForCellCoord(offsetData, a_x, a_y);
	}

	TESWorldSpace::OFFSET_DATA* TESWorldSpace::GetOffsetData(TESFile* a_file) const
	{
		using FuncType = decltype(&TESWorldSpace::GetOffsetData);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::TESWorldSpace::GetOffsetData };
		return std::invoke(FUNC, this, a_file);
	}

	TESWorldSpace::OFFSET_DATA* TESWorldSpace::CreateOffsetData(TESFile* a_file)
	{
		// This either gets or creates the offset data.
		using FuncType = decltype(&TESWorldSpace::GetOffsetData);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::TESWorldSpace::CreateOffsetData };
		return std::invoke(FUNC, this, a_file);
	}

	void TESWorldSpace::FreeOffsetData(TESFile* a_file)
	{
		using FuncType = decltype(&TESWorldSpace::FreeOffsetData);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::TESWorldSpace::FreeOffsetData };
		FUNC(this, a_file);
	}
}
