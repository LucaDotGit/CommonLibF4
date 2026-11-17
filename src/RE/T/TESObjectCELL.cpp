#include "RE/T/TESObjectCELL.hpp"

#include "RE/B/BSContainer_ForEachResult.hpp"
#include "RE/B/BSSpinLock.hpp"
#include "RE/E/EXTERIOR_DATA.hpp"
#include "RE/E/ExtraCellWaterType.hpp"
#include "RE/I/INTERIOR_DATA.hpp"
#include "RE/N/NiPoint2.hpp"
#include "RE/T/TESObjectREFR.hpp"
#include "RE/T/TESWaterForm.hpp"
#include "RE/T/TESWorldSpace.hpp"

namespace RE
{
	auto TESObjectCELL::Load(TESFile* a_file) -> bool
	{
		using FuncType = decltype(&TESObjectCELL::Load);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESObjectCELL::Load);
		return std::invoke(FUNC, this, a_file);
	}

	auto TESObjectCELL::FindInFileFast(TESFile* a_file) -> bool
	{
		using FuncType = decltype(&TESObjectCELL::FindInFileFast);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESObjectCELL::FindInFileFast);
		return std::invoke(FUNC, this, a_file);
	}

	void TESObjectCELL::AttachReference3D(TESObjectREFR* a_ref, bool a_onTop, bool a_queueAttach)
	{
		using FuncType = decltype(&TESObjectCELL::AttachReference3D);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESObjectCELL::AttachReference3D);
		std::invoke(FUNC, this, a_ref, a_onTop, a_queueAttach);
	}

	void TESObjectCELL::RemoveReference(TESObjectREFR* a_ref)
	{
		using FuncType = decltype(&TESObjectCELL::RemoveReference);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESObjectCELL::RemoveReference);
		std::invoke(FUNC, this, a_ref);
	}

	void TESObjectCELL::SetCullCellMarkers(bool a_cull)
	{
		using FuncType = decltype(&TESObjectCELL::SetCullCellMarkers);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESObjectCELL::SetCullCellMarkers);
		std::invoke(FUNC, this, a_cull);
	}

	void TESObjectCELL::UpdateAllDecals()
	{
		using FuncType = decltype(&TESObjectCELL::UpdateAllDecals);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESObjectCELL::UpdateAllDecals);
		std::invoke(FUNC, this);
	}

	void TESObjectCELL::UpdateAllRefsLoaded()
	{
		using FuncType = decltype(&TESObjectCELL::UpdateAllRefsLoaded);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESObjectCELL::UpdateAllRefsLoaded);
		std::invoke(FUNC, this);
	}

	auto TESObjectCELL::GetInteriorOffset() const -> std::uint32_t
	{
		using FuncType = decltype(&TESObjectCELL::GetInteriorOffset);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESObjectCELL::GetInteriorOffset);
		return std::invoke(FUNC, this);
	}

	void TESObjectCELL::SetInteriorOffset(std::uint32_t a_offset)
	{
		using FuncType = decltype(&TESObjectCELL::SetInteriorOffset);
		static const auto FUNC = REL::Relocation<FuncType>(ID::TESObjectCELL::SetInteriorOffset);
		std::invoke(FUNC, this, a_offset);
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

	auto TESObjectCELL::GetCellXAndY() const noexcept -> std::optional<REX::Vector<std::int32_t, 2>>
	{
		if (!IsExterior() || !exteriorData) {
			return std::nullopt;
		}

		return REX::Vector(exteriorData->cellX, exteriorData->cellY);
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

	auto TESObjectCELL::GetDataXAndY() const noexcept -> std::optional<REX::Vector<std::int32_t, 2>>
	{
		if (!IsInterior() || !interiorData) {
			return std::nullopt;
		}

		return REX::Vector(
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

	auto TESObjectCELL::GetWorldXAndY() const noexcept -> std::optional<NiPoint2>
	{
		if (!IsExterior() || !exteriorData) {
			return std::nullopt;
		}

		return NiPoint2(exteriorData->worldX, exteriorData->worldY);
	}

	auto TESObjectCELL::GetWaterType() const noexcept -> TESWaterForm*
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

	auto TESObjectCELL::GetExteriorWaterHeight() const noexcept -> REX::Float32
	{
		if (cellFlags.any(Flags::IsInterior) || cellFlags.any(Flags::HasWater)) {
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

	auto TESObjectCELL::GetOrCreateExtraList() -> BSTSmartPointer<ExtraDataList>
	{
		if (extraList) {
			return extraList;
		}

		auto newExtraList = make_shared<ExtraDataList>();
		if (!newExtraList) [[unlikely]] {
			REX::Assert(false);
			return nullptr;
		}

		extraList = newExtraList;
		return newExtraList;
	}

	auto TESObjectCELL::ForEachRef(
		const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(const NiPointer<TESObjectREFR>&) const>>&
			a_predicate) const -> BSContainer::ForEachResult
	{
		const auto cellLock = BSAutoSpinLock(spinLock);

		for (const auto& ref : references) {
			if (std::invoke(a_predicate.get(), ref) == BSContainer::ForEachResult::Stop) {
				return BSContainer::ForEachResult::Stop;
			}
		}

		return BSContainer::ForEachResult::Continue;
	}

	auto TESObjectCELL::ForEachRefInRange(
		const NiPoint3& a_origin,
		REX::Float32 a_radius,
		const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(const NiPointer<TESObjectREFR>&) const>>&
			a_predicate) const -> BSContainer::ForEachResult
	{
		if (a_radius <= static_cast<REX::Float32>(0.0)) {
			return ForEachRef(a_predicate);
		}

		const auto squaredRadius = a_radius * a_radius;

		return ForEachRef(
			[&a_origin, squaredRadius, &a_predicate](
				const NiPointer<TESObjectREFR>& a_ref) -> BSContainer::ForEachResult {
				const auto distance = a_origin.DistanceSquared(a_ref->GetPosition());
				if (distance <= squaredRadius) {
					return std::invoke(a_predicate.get(), a_ref);
				}

				return BSContainer::ForEachResult::Continue;
			});
	}
}
