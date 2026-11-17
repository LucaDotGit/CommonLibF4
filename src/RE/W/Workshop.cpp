#include "RE/W/Workshop.hpp"

namespace RE::Workshop
{
	auto FindNearestValidWorkshop(const TESObjectREFR& a_ref) -> TESObjectREFR*
	{
		using FuncType = decltype(&Workshop::FindNearestValidWorkshop);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Workshop::FindNearestValidWorkshop);
		return std::invoke(FUNC, a_ref);
	}

	auto FreeBuild() -> bool
	{
		using FuncType = decltype(&Workshop::FreeBuild);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Workshop::FreeBuild);
		return std::invoke(FUNC);
	}

	auto GetSelectedWorkshopMenuNode(std::uint32_t a_row, std::uint32_t& a_column) -> WorkshopMenuNode*
	{
		using FuncType = decltype(&Workshop::GetSelectedWorkshopMenuNode);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Workshop::GetSelectedWorkshopMenuNode);
		return std::invoke(FUNC, a_row, a_column);
	}

	void InitializePlacementReference(const ContextData& a_context, TESBoundObject& a_object)
	{
		using FuncType = decltype(&Workshop::InitializePlacementReference);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Workshop::InitializePlacementReference);
		std::invoke(FUNC, a_context, a_object);
	}

	auto IsLocationWithinBuildableArea(const TESObjectREFR& a_workshop, const NiPoint3& a_location) -> bool
	{
		using FuncType = decltype(&Workshop::IsLocationWithinBuildableArea);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Workshop::IsLocationWithinBuildableArea);
		return std::invoke(FUNC, a_workshop, a_location);
	}

	auto IsWorkshopItem(const TESObjectREFR* a_ref) -> bool
	{
		using FuncType = decltype(&Workshop::IsWorkshopItem);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Workshop::IsWorkshopItem);
		return std::invoke(FUNC, a_ref);
	}

	auto PlaceCurrentReference(const ContextData& a_context) -> bool
	{
		using FuncType = decltype(&Workshop::PlaceCurrentReference);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Workshop::PlaceCurrentReference);
		return std::invoke(FUNC, a_context);
	}

	void RequestExitWorkshop(bool a_allowReEntry)
	{
		using FuncType = decltype(&Workshop::RequestExitWorkshop);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Workshop::RequestExitWorkshop);
		std::invoke(FUNC, a_allowReEntry);
	}

	void ScrapReference(
		const ContextData& a_context,
		ObjectRefHandlePtr& a_scrapRef,
		BSTArray<BSTPair<TESBoundObject*, std::uint32_t>>* a_rewards)
	{
		using FuncType = decltype(&Workshop::ScrapReference);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Workshop::ScrapReference);
		std::invoke(FUNC, a_context, a_scrapRef, a_rewards);
	}

	void SetSelectedEditItem(ObjectRefHandle a_ref)
	{
		using FuncType = decltype(&Workshop::SetSelectedEditItem);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Workshop::SetSelectedEditItem);
		std::invoke(FUNC, a_ref);
	}

	void StartWorkshop(TESObjectREFR* a_workshopRef)
	{
		using FuncType = decltype(&Workshop::StartWorkshop);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Workshop::StartWorkshop);
		std::invoke(FUNC, a_workshopRef);
	}

	void ToggleEditMode(const ContextData& a_context)
	{
		using FuncType = decltype(&Workshop::ToggleEditMode);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Workshop::ToggleEditMode);
		std::invoke(FUNC, a_context);
	}

	void UpdateActiveEdit(const ContextData& a_context, bool a_multiselect)
	{
		using FuncType = decltype(&Workshop::UpdateActiveEdit);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Workshop::UpdateActiveEdit);
		std::invoke(FUNC, a_context, a_multiselect);
	}

	auto WorkshopCanShowRecipe(BGSConstructibleObject* a_recipe, BGSKeyword* a_filter) -> bool
	{
		using FuncType = decltype(&Workshop::WorkshopCanShowRecipe);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Workshop::WorkshopCanShowRecipe);
		return std::invoke(FUNC, a_recipe, a_filter);
	}

	auto GetCurrentPlacementItemData() noexcept -> PlacementItemData&
	{
		static const auto CURRENT_PLACEMENT_ITEM_DATA =
			REL::Relocation<PlacementItemData*>{ID::Workshop::CurrentPlacementItemData};
		return *CURRENT_PLACEMENT_ITEM_DATA;
	}

	auto GetCurrentRow() noexcept -> std::uint16_t&
	{
		static const auto CURRENT_ROW = REL::Relocation<std::uint16_t*>(ID::Workshop::CurrentRow);
		return *CURRENT_ROW;
	}

	auto GetPlacementItem() noexcept -> ObjectRefHandle&
	{
		static const auto PLACEMENT_ITEM = REL::Relocation<ObjectRefHandle*>(ID::Workshop::PlacementItem);
		return *PLACEMENT_ITEM;
	}
}
