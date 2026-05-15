#pragma once

#include "RE/E/ExamineMenu.hpp"
#include "RE/U/UI_DEPTH_PRIORITY.hpp"

namespace RE
{
	class __declspec(novtable) PowerArmorModMenu
		: public ExamineMenu // 000
	{
	public:
		inline static constexpr auto RTTI{ RTTI::PowerArmorModMenu };
		inline static constexpr auto VTABLE{ VTABLE::PowerArmorModMenu };
		inline static constexpr auto MENU_NAME{ "PowerArmorModMenu"sv };
		inline static constexpr auto MENU_DEPTH{ UI_DEPTH_PRIORITY::kPowerArmorModMenu };

		~PowerArmorModMenu() override; // 00

		// override (ExamineMenu)
		void PreDisplay() override;
		void BuildCanceled() override;																													   // 16
		void BuildConfirmed(bool a_ownerIsWorkbench) override;																							   // 17
		bool GetWorkbenchHasInventory() override;																										   // 18
		const ModChoiceData* QCurrentModChoiceData() override;																							   // 19
		void ShowBuildFailureMessage() override;																										   // 1A
		EQUIP_TYPE GetInventoryEntryEquipState(const InventoryUserUIInterfaceEntry& a_entry) override;													   // 1C
		void ShowCurrent3D() override;																													   // 1D
		void HighlightWeaponPart() override;																											   // 28
		void ResetHighlight() override;																													   // 29
		void CreateModdedInventoryItem() override;																										   // 2A
		const char* GetBuildConfirmButtonLabel() override;																								   // 30
		void GetBuildConfirmQuestion(char* a_buffer, std::uint32_t a_bufferLength) override;															   // 31
		bool GetCanRepairSelectedItem() override;																										   // 32
		NiAVObject* GetCurrent3D() override;																											   // 33
		bool GetCurrent3DLoaded() override;																												   // 34
		bool GetIsValidInventoryItem(const BGSInventoryItem& a_item, std::uint32_t a_stackID) override;													   // 35
		const char* GetMenuName() override;																												   // 36
		void OnSwitchBaseItem() override;																												   // 37
		void PopulateInventoryItemObj(ObjectRefHandle a_owner, const InventoryUserUIInterfaceEntry& a_entry, ::Scaleform::GFx::Value& a_itemObj) override; // 38
		void RegisterMenuComponents(const ::Scaleform::GFx::FunctionHandler::Params& a_params) override;												   // 39
		void RepairSelectedItem() override;																												   // 3A
		void SetFilter() override;																														   // 3B
		void ToggleItemEquipped() override;																												   // 3D
		void UpdateModChoiceList() override;																											   // 3F

		// members
		WorkbenchMenuBase::ModChoiceData repairData; // 810
		bool queuePreviewedPieceAttach;				 // 848
	};
	static_assert(sizeof(PowerArmorModMenu) == 0x850);
}
