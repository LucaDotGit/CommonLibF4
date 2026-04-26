#include "RE/T/TESObjectCELL.hpp"

#include "RE/B/BSContainer_ForEachResult.hpp"
#include "RE/E/EXTERIOR_DATA.hpp"
#include "RE/E/ExtraCellWaterType.hpp"
#include "RE/I/INTERIOR_DATA.hpp"
#include "RE/T/TESObjectREFR.hpp"
#include "RE/T/TESWaterForm.hpp"
#include "RE/T/TESWorldSpace.hpp"

namespace RE
{
	bool TESObjectCELL::Load(TESFile* a_file)
	{
		using FuncType = decltype(&TESObjectCELL::Load);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::TESObjectCELL::Load };
		return std::invoke(FUNC, this, a_file);
	}

	bool TESObjectCELL::FindInFileFast(TESFile* a_file)
	{
		using FuncType = decltype(&TESObjectCELL::FindInFileFast);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::TESObjectCELL::FindInFileFast };
		return std::invoke(FUNC, this, a_file);
	}

	void TESObjectCELL::AttachReference3D(TESObjectREFR* a_ref, bool a_onTop, bool a_queueAttach)
	{
		using FuncType = decltype(&TESObjectCELL::AttachReference3D);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::TESObjectCELL::AttachReference3D };
		FUNC(this, a_ref, a_onTop, a_queueAttach);
	}

	void TESObjectCELL::RemoveReference(TESObjectREFR* a_ref)
	{
		using FuncType = decltype(&TESObjectCELL::RemoveReference);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::TESObjectCELL::RemoveReference };
		FUNC(this, a_ref);
	}

	void TESObjectCELL::SetCullCellMarkers(bool a_cull)
	{
		using FuncType = decltype(&TESObjectCELL::SetCullCellMarkers);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::TESObjectCELL::SetCullCellMarkers };
		FUNC(this, a_cull);
	}

	void TESObjectCELL::UpdateAllDecals()
	{
		using FuncType = decltype(&TESObjectCELL::UpdateAllDecals);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::TESObjectCELL::UpdateAllDecals };
		FUNC(this);
	}

	void TESObjectCELL::UpdateAllRefsLoaded()
	{
		using FuncType = decltype(&TESObjectCELL::UpdateAllRefsLoaded);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::TESObjectCELL::UpdateAllRefsLoaded };
		FUNC(this);
	}

	std::uint32_t TESObjectCELL::GetInteriorOffset() const
	{
		using FuncType = decltype(&TESObjectCELL::GetInteriorOffset);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::TESObjectCELL::GetInteriorOffset };
		return std::invoke(FUNC, this);
	}

	void TESObjectCELL::SetInteriorOffset(std::uint32_t a_offset)
	{
		using FuncType = decltype(&TESObjectCELL::SetInteriorOffset);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::TESObjectCELL::SetInteriorOffset };
		FUNC(this, a_offset);
	}

	auto TESObjectCELL::GetCellX() const noexcept -> std::optional<std::int32_t>
	{
		if (!IsExterior() || !exteriorData) {
			return std::nullopt;
		}

		return exteriorData->cellX;
	}

	auto TESObjectCELL::GetCellY() const noexcept -> std::optional<std::int32_t>
	{
		if (!IsExterior() || !exteriorData) {
			return std::nullopt;
		}

		return exteriorData->cellY;
	}

	auto TESObjectCELL::GetCellXAndY() const noexcept -> std::optional<std::tuple<std::int32_t, std::int32_t>>
	{
		if (!IsExterior() || !exteriorData) {
			return std::nullopt;
		}

		return std::make_tuple(exteriorData->cellX, exteriorData->cellY);
	}

	auto TESObjectCELL::GetDataX() const noexcept -> std::optional<std::int32_t>
	{
		if (!IsInterior() || !interiorData) {
			return std::nullopt;
		}

		return static_cast<std::int32_t>(interiorData->GetDirectionalX());
	}

	auto TESObjectCELL::GetDataY() const noexcept -> std::optional<std::int32_t>
	{
		if (!IsInterior() || !interiorData) {
			return std::nullopt;
		}

		return static_cast<std::int32_t>(interiorData->GetDirectionalY());
	}

	auto TESObjectCELL::GetDataXAndY() const noexcept -> std::optional<std::tuple<std::int32_t, std::int32_t>>
	{
		if (!IsInterior() || !interiorData) {
			return std::nullopt;
		}

		return std::make_tuple(
			static_cast<std::int32_t>(interiorData->GetDirectionalX()),
			static_cast<std::int32_t>(interiorData->GetDirectionalY()));
	}

	auto TESObjectCELL::GetWorldX() const noexcept -> std::optional<REX::Float32>
	{
		if (!IsExterior() || !exteriorData) {
			return std::nullopt;
		}

		return exteriorData->worldX;
	}

	auto TESObjectCELL::GetWorldY() const noexcept -> std::optional<REX::Float32>
	{
		if (!IsExterior() || !exteriorData) {
			return std::nullopt;
		}

		return exteriorData->worldY;
	}

	auto TESObjectCELL::GetWorldXAndY() const noexcept -> std::optional<std::tuple<REX::Float32, REX::Float32>>
	{
		if (!IsExterior() || !exteriorData) {
			return std::nullopt;
		}

		return std::make_tuple(exteriorData->worldX, exteriorData->worldY);
	}

	TESWaterForm* TESObjectCELL::GetWaterType() const noexcept
	{
		const auto* extraWater = extraList ? extraList->GetExtra<ExtraCellWaterType>() : nullptr;
		if (extraWater && extraWater->waterType) {
			return extraWater->waterType;
		}

		if (!IsExterior() || !worldSpace) {
			return TESWaterForm::GetDefaultWater();
		}

		auto* water = worldSpace->GetWaterType();
		return water ? water : TESWaterForm::GetDefaultWater();
	}

	REX::Float32 TESObjectCELL::GetExteriorWaterHeight() const noexcept
	{
		if (cellFlags.any(Flags::kIsInterior) || cellFlags.any(Flags::kHasWater)) {
			return -std::numeric_limits<REX::Float32>::infinity();
		}

		if (waterHeight < static_cast<REX::Float32>(std::numeric_limits<std::int32_t>::max())) {
			return waterHeight;
		}

		if (!worldSpace) {
			return -std::numeric_limits<REX::Float32>::infinity();
		}

		return worldSpace->GetDefaultWaterHeight();
	}

	BSTSmartPointer<ExtraDataList> TESObjectCELL::GetOrCreateExtraList()
	{
		if (extraList) {
			return extraList;
		}

		auto newExtraList = make_shared<ExtraDataList>();
		if (!newExtraList) [[unlikely]] {
			REX::AllocationFail();
		}

		extraList = std::move(newExtraList);
		return newExtraList;
	}

	BSContainer::ForEachResult TESObjectCELL::ForEachRef(
		const REX::NotNull<std::function<BSContainer::ForEachResult(const NiPointer<TESObjectREFR>&)>>& a_predicate) const
	{
		const auto cellLock = BSAutoLock(spinLock);

		for (const auto& ref : references) {
			if (ref && std::invoke(*a_predicate, ref) == BSContainer::ForEachResult::kStop) {
				return BSContainer::ForEachResult::kStop;
			}
		}

		return BSContainer::ForEachResult::kContinue;
	}

	BSContainer::ForEachResult TESObjectCELL::ForEachRefInRange(const NiPoint3& a_origin, REX::Float32 a_radius,
		const REX::NotNull<std::function<BSContainer::ForEachResult(const NiPointer<TESObjectREFR>&)>>& a_predicate) const
	{
		if (a_radius <= 0.0_f32) {
			return ForEachRef(a_predicate);
		}

		const auto squaredRadius = a_radius * a_radius;

		return ForEachRef([&](const NiPointer<TESObjectREFR>& a_ref) {
			const auto distance = a_origin.DistanceSquared(a_ref->GetPosition());
			if (distance <= squaredRadius) {
				return std::invoke(*a_predicate, a_ref);
			}

			return BSContainer::ForEachResult::kContinue;
		});
	}
}
