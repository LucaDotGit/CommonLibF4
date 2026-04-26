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

	[[nodiscard]] TESObjectREFR* FindNearestValidWorkshop(const TESObjectREFR& a_ref);
	bool FreeBuild();
	[[nodiscard]] WorkshopMenuNode* GetSelectedWorkshopMenuNode(std::uint32_t a_row, std::uint32_t& a_column);
	void InitializePlacementReference(const ContextData& a_context, TESBoundObject& a_object);
	[[nodiscard]] bool IsLocationWithinBuildableArea(const TESObjectREFR& a_workshop, const NiPoint3& a_location);
	[[nodiscard]] bool IsWorkshopItem(const TESObjectREFR* a_ref);
	bool PlaceCurrentReference(const ContextData& a_context);
	void RequestExitWorkshop(bool a_allowReEntry);
	void ScrapReference(const ContextData& a_context, ObjectRefHandlePtr& a_scrapRef, BSTArray<BSTPair<TESBoundObject*, std::uint32_t>>* a_rewards);
	void SetSelectedEditItem(ObjectRefHandle a_ref);
	void StartWorkshop(TESObjectREFR* a_workshopRef);
	void ToggleEditMode(const ContextData& a_context);
	void UpdateActiveEdit(const ContextData& a_context, bool a_multiselect = false);
	[[nodiscard]] bool WorkshopCanShowRecipe(BGSConstructibleObject* a_recipe, BGSKeyword* a_filter);
	[[nodiscard]] PlacementItemData& GetCurrentPlacementItemData();
	[[nodiscard]] std::uint16_t& GetCurrentRow();
	[[nodiscard]] ObjectRefHandle& GetPlacementItem();
}
