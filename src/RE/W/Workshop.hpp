#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSPointerHandleSmartPointer.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTTuple.hpp"

namespace RE
{
	class NiPoint3;
}

namespace RE::Workshop
{
	class ContextData;
	class ItemDestroyedEvent;
	class ItemMovedEvent;
	class ItemPlacedEvent;
	class PlacementItemData;
	class WorkshopMenuNode;
	class WorkshopModeEvent;

	[[nodiscard]]
	auto FindNearestValidWorkshop(const TESObjectREFR& a_ref) -> TESObjectREFR*;
	auto FreeBuild() -> bool;
	[[nodiscard]]
	auto GetSelectedWorkshopMenuNode(std::uint32_t a_row, std::uint32_t& a_column) -> WorkshopMenuNode*;
	void InitializePlacementReference(const ContextData& a_context, TESBoundObject& a_object);
	[[nodiscard]]
	auto IsLocationWithinBuildableArea(const TESObjectREFR& a_workshop, const NiPoint3& a_location) -> bool;
	[[nodiscard]]
	auto IsWorkshopItem(const TESObjectREFR* a_ref) -> bool;
	auto PlaceCurrentReference(const ContextData& a_context) -> bool;
	void RequestExitWorkshop(bool a_allowReEntry);
	void ScrapReference(
		const ContextData& a_context,
		ObjectRefHandlePtr& a_scrapRef,
		BSTArray<BSTPair<TESBoundObject*, std::uint32_t>>* a_rewards);
	void SetSelectedEditItem(ObjectRefHandle a_ref);
	void StartWorkshop(TESObjectREFR* a_workshopRef);
	void ToggleEditMode(const ContextData& a_context);
	void UpdateActiveEdit(const ContextData& a_context, bool a_multiselect = false);
	[[nodiscard]]
	auto WorkshopCanShowRecipe(BGSConstructibleObject* a_recipe, BGSKeyword* a_filter) -> bool;

	[[nodiscard]]
	auto GetCurrentPlacementItemData() noexcept -> PlacementItemData&;
	[[nodiscard]]
	auto GetCurrentRow() noexcept -> std::uint16_t&;
	[[nodiscard]]
	auto GetPlacementItem() noexcept -> ObjectRefHandle&;
}
