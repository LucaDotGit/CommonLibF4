#include "RE/W/Workshop.hpp"

namespace RE::Workshop
{
	TESObjectREFR* FindNearestValidWorkshop(const TESObjectREFR& a_ref)
	{
		using FuncType = decltype(&Workshop::FindNearestValidWorkshop);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::Workshop::FindNearestValidWorkshop };
		return std::invoke(FUNC, a_ref);
	}

	bool FreeBuild()
	{
		using FuncType = decltype(&Workshop::FreeBuild);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::Workshop::FreeBuild };
		return std::invoke(FUNC);
	}

	WorkshopMenuNode* GetSelectedWorkshopMenuNode(std::uint32_t a_row, std::uint32_t& a_column)
	{
		using FuncType = decltype(&Workshop::GetSelectedWorkshopMenuNode);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::Workshop::GetSelectedWorkshopMenuNode };
		return std::invoke(FUNC, a_row, a_column);
	}

	void InitializePlacementReference(const ContextData& a_context, TESBoundObject& a_object)
	{
		using FuncType = decltype(&Workshop::InitializePlacementReference);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::Workshop::InitializePlacementReference };
		FUNC(a_context, a_object);
	}

	bool IsLocationWithinBuildableArea(const TESObjectREFR& a_workshop, const NiPoint3& a_location)
	{
		using FuncType = decltype(&Workshop::IsLocationWithinBuildableArea);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::Workshop::IsLocationWithinBuildableArea };
		return std::invoke(FUNC, a_workshop, a_location);
	}

	bool IsWorkshopItem(const TESObjectREFR* a_ref)
	{
		using FuncType = decltype(&Workshop::IsWorkshopItem);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::Workshop::IsWorkshopItem };
		return std::invoke(FUNC, a_ref);
	}

	bool PlaceCurrentReference(const ContextData& a_context)
	{
		using FuncType = decltype(&Workshop::PlaceCurrentReference);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::Workshop::PlaceCurrentReference };
		return std::invoke(FUNC, a_context);
	}

	void RequestExitWorkshop(bool a_allowReEntry)
	{
		using FuncType = decltype(&Workshop::RequestExitWorkshop);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::Workshop::RequestExitWorkshop };
		FUNC(a_allowReEntry);
	}

	void ScrapReference(const ContextData& a_context, ObjectRefHandlePtr& a_scrapRef, BSTArray<BSTPair<TESBoundObject*, std::uint32_t>>* a_rewards)
	{
		using FuncType = decltype(&Workshop::ScrapReference);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::Workshop::ScrapReference };
		FUNC(a_context, a_scrapRef, a_rewards);
	}

	void SetSelectedEditItem(ObjectRefHandle a_ref)
	{
		using FuncType = decltype(&Workshop::SetSelectedEditItem);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::Workshop::SetSelectedEditItem };
		FUNC(a_ref);
	}

	void StartWorkshop(TESObjectREFR* a_workshopRef)
	{
		using FuncType = decltype(&Workshop::StartWorkshop);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::Workshop::StartWorkshop };
		FUNC(a_workshopRef);
	}

	void ToggleEditMode(const ContextData& a_context)
	{
		using FuncType = decltype(&Workshop::ToggleEditMode);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::Workshop::ToggleEditMode };
		FUNC(a_context);
	}

	void UpdateActiveEdit(const ContextData& a_context, bool a_multiselect)
	{
		using FuncType = decltype(&Workshop::UpdateActiveEdit);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::Workshop::UpdateActiveEdit };
		FUNC(a_context, a_multiselect);
	}

	bool WorkshopCanShowRecipe(BGSConstructibleObject* a_recipe, BGSKeyword* a_filter)
	{
		using FuncType = decltype(&Workshop::WorkshopCanShowRecipe);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::Workshop::WorkshopCanShowRecipe };
		return std::invoke(FUNC, a_recipe, a_filter);
	}

	PlacementItemData& GetCurrentPlacementItemData()
	{
		static const auto CURRENT_PLACEMENT_ITEM_DATA = REL::Relocation<PlacementItemData*>{ ID::Workshop::CurrentPlacementItemData };
		return *CURRENT_PLACEMENT_ITEM_DATA;
	}

	std::uint16_t& GetCurrentRow()
	{
		static const auto CURRENT_ROW = REL::Relocation<std::uint16_t*>{ ID::Workshop::CurrentRow };
		return *CURRENT_ROW;
	}

	ObjectRefHandle& GetPlacementItem()
	{
		static const auto PLACEMENT_ITEM = REL::Relocation<ObjectRefHandle*>{ ID::Workshop::PlacementItem };
		return *PLACEMENT_ITEM;
	}
}
