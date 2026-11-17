#pragma once

#include "RE/E/ExamineMenu.hpp"
#include "RE/U/UI_DEPTH_PRIORITY.hpp"

namespace RE
{
	class __declspec(novtable) PowerArmorModMenu : public ExamineMenu // 0x000
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::PowerArmorModMenu;
		inline static constexpr const auto& VTABLE = VTABLE::PowerArmorModMenu;
		inline static constexpr auto MENU_NAME = "PowerArmorModMenu"sv;
		inline static constexpr auto MENU_DEPTH = UI_DEPTH_PRIORITY::PowerArmorModMenu;

		~PowerArmorModMenu() override; // 0x00

		// override (ExamineMenu)
		void PreDisplay() override;
		void BuildCanceled() override;																			// 0x16
		void BuildConfirmed(bool a_ownerIsWorkbench) override;													// 0x17
		auto GetWorkbenchHasInventory() -> bool override;														// 0x18
		auto QCurrentModChoiceData() -> const ModChoiceData* override;											// 0x19
		void ShowBuildFailureMessage() override;																// 0x1A
		auto GetInventoryEntryEquipState(const InventoryUserUIInterfaceEntry& a_entry) -> EQUIP_TYPE override;	// 0x1C
		void ShowCurrent3D() override;																			// 0x1D
		void HighlightWeaponPart() override;																	// 0x28
		void ResetHighlight() override;																			// 0x29
		void CreateModdedInventoryItem() override;																// 0x2A
		auto GetBuildConfirmButtonLabel() -> const char* override;												// 0x30
		void GetBuildConfirmQuestion(char* a_buffer, std::uint32_t a_bufferLength) override;					// 0x31
		auto GetCanRepairSelectedItem() -> bool override;														// 0x32
		auto GetCurrent3D() -> NiAVObject* override;															// 0x33
		auto GetCurrent3DLoaded() -> bool override;																// 0x34
		auto GetIsValidInventoryItem(const BGSInventoryItem& a_item, std::uint32_t a_stackID) -> bool override; // 0x35
		auto GetMenuName() -> const char* override;																// 0x36
		void OnSwitchBaseItem() override;																		// 0x37
		void PopulateInventoryItemObj(
			ObjectRefHandle a_owner,
			const InventoryUserUIInterfaceEntry& a_entry,
			Scaleform::GFx::Value& a_itemObj) override;												   // 0x38
		void RegisterMenuComponents(const Scaleform::GFx::FunctionHandler::Params& a_params) override; // 0x39
		void RepairSelectedItem() override;															   // 0x3A
		void SetFilter() override;																	   // 0x3B
		void ToggleItemEquipped() override;															   // 0x3D
		void UpdateModChoiceList() override;														   // 0x3F

		// members
		WorkbenchMenuBase::ModChoiceData repairData; // 0x810
		bool queuePreviewedPieceAttach;				 // 0x848
	};

	static_assert(sizeof(PowerArmorModMenu) == 0x850);
}
