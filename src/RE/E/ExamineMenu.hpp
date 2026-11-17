#pragma once

#include "RE/E/ExamineConfirmMenu.hpp"
#include "RE/I/InventoryUserUIInterface.hpp"
#include "RE/U/UI_DEPTH_PRIORITY.hpp"
#include "RE/W/WorkbenchMenuBase.hpp"

namespace RE
{
	enum class EQUIP_TYPE : std::int32_t;

	class BGSObjectInstanceExtra;
	class NiAVObject;

	class __declspec(novtable) ExamineMenu : public WorkbenchMenuBase // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ExamineMenu;
		inline static constexpr const auto& VTABLE = VTABLE::ExamineMenu;
		inline static constexpr auto MENU_NAME = "ExamineMenu"sv;
		inline static constexpr auto MENU_DEPTH = UI_DEPTH_PRIORITY::ExamineMenu;

		enum class INSPECT_MODE_STATE : std::int32_t
		{
			ModSlotSelect = 0,
			SelectNewMod = 1,
			InvComponentSelect = 2,
			ItemSelect = 3,
			Confirm = 4
		};

		class ComponentBuilderFunctor
		{
		public:
			// members
			BSTArray<BSTPair<BGSComponent*, std::uint8_t>> components; // 0x00
			TESObjectMISC* object;									   // 0x18
			std::uint32_t index;									   // 0x20
		};

		static_assert(sizeof(ComponentBuilderFunctor) == 0x28);

		~ExamineMenu() override; // 0x00

		// override (WorkbenchMenuBase)
		void Call(const Params& a_params) override;								  // 0x01
		void MapCodeObjectFunctions() override;									  // 0x02
		auto ProcessMessage(UIMessage& a_message) -> UI_MESSAGE_RESULTS override; // 0x03
		void AdvanceMovie(DeltaTime a_deltaTime, std::time_t a_time) override;	  // 0x04
		void OnHideMenu() override;												  // 0x14
		void BuildConfirmed(bool a_ownerIsWorkbench) override;					  // 0x17
		auto TryCreate() -> bool override;										  // 0x1B

		// override (BSInputEventUser)
		auto ShouldHandleEvent(const InputEvent* a_event) -> bool override; // 0x01
		void OnThumbstickEvent(const ThumbstickEvent* a_event) override;	// 0x04
		void OnCursorMoveEvent(const CursorMoveEvent* a_event) override;	// 0x05
		void OnButtonEvent(const ButtonEvent* a_event) override;			// 0x08

		// add
		virtual auto GetInventoryEntryEquipState(const InventoryUserUIInterfaceEntry& a_entry) -> EQUIP_TYPE;  // 0x1C
		virtual void ShowCurrent3D();																		   // 0x1D
		virtual auto GetCurrentObj() -> TESBoundObject*;													   // 0x1E
		virtual void FindWeaponMods(TESBoundObject* a_object, Scaleform::GFx::Value& a_modList);			   // 0x1F
		virtual void BuildPossibleModList(TESBoundObject* a_object);										   // 0x20
		virtual void SwitchMod(std::int32_t a_index, Scaleform::GFx::Value& a_entryList);					   // 0x21
		virtual void NextItemPart();																		   // 0x22
		virtual void PreviousItemPart();																	   // 0x23
		virtual void AttachModToPreview(bool a_storeModelPosition);											   // 0x24
		virtual auto GetInitialObjectInstanceExtra() -> BGSObjectInstanceExtra*;							   // 0x25
		virtual auto GetObjectInstanceExtra() -> BGSObjectInstanceExtra*;									   // 0x26
		virtual auto GetItemExtraDataList() -> const ExtraDataList*;										   // 0x27
		virtual void HighlightWeaponPart();																	   // 0x28
		virtual void ResetHighlight();																		   // 0x29
		virtual void CreateModdedInventoryItem();															   // 0x2A
		virtual void RevertToInventoryItem();																   // 0x2B
		virtual auto GetCurrentName() -> const char*;														   // 0x2C
		virtual void RenameCurrent(const char* a_newName);													   // 0x2D
		virtual void UpdateItemCard(bool a_compare);														   // 0x2E
		virtual void UpdateItemList(std::int32_t a_indexToSelect);											   // 0x2F
		virtual auto GetBuildConfirmButtonLabel() -> const char*;											   // 0x30
		virtual void GetBuildConfirmQuestion(char* a_buffer, std::uint32_t a_bufferLength);					   // 0x31
		virtual auto GetCanRepairSelectedItem() -> bool;													   // 0x32
		virtual auto GetCurrent3D() -> NiAVObject*;															   // 0x33
		virtual auto GetCurrent3DLoaded() -> bool;															   // 0x34
		virtual auto GetIsValidInventoryItem(const BGSInventoryItem& a_item, std::uint32_t a_stackID) -> bool; // 0x35
		virtual auto GetMenuName() -> const char*;															   // 0x36
		virtual void OnSwitchBaseItem();																	   // 0x37
		virtual void PopulateInventoryItemObj(
			ObjectRefHandle a_owner,
			const InventoryUserUIInterfaceEntry& a_entry,
			Scaleform::GFx::Value& a_itemObj);																   // 0x38
		virtual void RegisterMenuComponents(const Scaleform::GFx::FunctionHandler::Params& a_params);		   // 0x39
		virtual void RepairSelectedItem();																	   // 0x3A
		virtual void SetFilter();																			   // 0x3B
		virtual void SetMouseRotation(bool a_rotation);														   // 0x3C
		virtual void ToggleItemEquipped();																	   // 0x3D
		virtual void UpdateModSlotList();																	   // 0x3E
		virtual void UpdateModChoiceList();																	   // 0x3F
		virtual auto GetRankSuffix(std::uint32_t a_rank) -> const char*;									   // 0x40
		virtual auto QIgnoreRank() -> bool;																	   // 0x41
		virtual auto ShouldInitToFirstMod() -> bool;														   // 0x42
		virtual void SetDataForConditionCheck();															   // 0x43
		virtual auto AddLooseModToModChoiceArray(BGSMod::Attachment::Mod* a_mod, std::uint8_t a_rank) -> bool; // 0x44
		virtual auto ShouldShowModSlot(const BGSKeyword* a_keyword) -> bool;								   // 0x45

		void BuildWeaponScrappingArray()
		{
			using FuncType = decltype(&ExamineMenu::BuildWeaponScrappingArray);
			static const auto FUNC = REL::Relocation<FuncType>(ID::ExamineMenu::BuildWeaponScrappingArray);
			std::invoke(FUNC, this);
		}

		[[nodiscard]]
		auto GetSelectedIndex() -> std::uint32_t
		{
			using FuncType = decltype(&ExamineMenu::GetSelectedIndex);
			static const auto FUNC = REL::Relocation<FuncType>(ID::ExamineMenu::GetSelectedIndex);
			return std::invoke(FUNC, this);
		}

		void ShowConfirmMenu(ExamineConfirmMenu::InitData* a_data, ExamineConfirmMenu::ICallback* a_callback)
		{
			using FuncType = decltype(&ExamineMenu::ShowConfirmMenu);
			static const auto FUNC = REL::Relocation<FuncType>(ID::ExamineMenu::ShowConfirmMenu);
			std::invoke(FUNC, this, a_data, a_callback);
		}

		void ConsumeSelectedItems(bool a_autoBuild, const BGSSoundDescriptorForm* a_consumeSound)
		{
			using FuncType = decltype(&ExamineMenu::ConsumeSelectedItems);
			static const auto FUNC = REL::Relocation<FuncType>(ID::ExamineMenu::ConsumeSelectedItems);
			std::invoke(FUNC, this, a_autoBuild, a_consumeSound);
		}

		// members
		ComponentBuilderFunctor componentFunctor;						  // 0x340
		REX::Enum<INSPECT_MODE_STATE, std::int32_t> inspectModeState;	  // 0x368
		ObjectRefHandle inventorySource;								  // 0x36C
		InventoryUserUIInterface invInterface;							  // 0x370
		InventoryInterface::Handle modItem;								  // 0x3F0
		std::uint32_t modStack;											  // 0x3F4
		BSTHashMap<std::uint32_t, std::uint32_t> scrappableItemsMap;	  // 0x3F8
		BSTArray<BSTPair<TESBoundObject*, std::uint32_t>> scrappingArray; // 0x428
		BSTArray<BSTPair<NiAVObject*, const BGSKeyword*>> slotObjects;	  // 0x440
		BSTSmartPointer<ExtraDataList> extraDataList;					  // 0x458
		std::uint32_t slotObjectIndex;									  // 0x460
		Scaleform::GFx::Value buttonAnimBase;							  // 0x468
		Scaleform::GFx::Value itemList;									  // 0x488
		Scaleform::GFx::Value itemNameTextField;						  // 0x4A8
		Scaleform::GFx::Value itemInfoList;								  // 0x4C8
		Scaleform::GFx::Value modChoiceList;							  // 0x4E8
		Scaleform::GFx::Value modSlotList;								  // 0x508
		Scaleform::GFx::Value currentModsList;							  // 0x528
		BGSInventoryItem moddedInventoryItem;							  // 0x548
		bool queueItemHighlight;										  // 0x558
		REX::Float32 zoomDistance;										  // 0x55C
		REX::Float32 lastFrameDelta;									  // 0x560
		REX::Float32 menuCursorLeftPct;									  // 0x564
		REX::Float32 menuCursorRightPct;								  // 0x568
		REX::Float32 menuCursorTopPct;									  // 0x56C
		REX::Float32 menuCursorBottomPct;								  // 0x570
		BSTArray<BGSComponent*> queuedSoundArray;						  // 0x578
		std::array<std::byte, 0x598 - 0x590>
			attachPointSource3D; // 0x590 - To-Do: `BSResource::RHandleType<BSResource::Entry<NiPointer<NiNode>,
								 // BSResource::EntryDBTraits<BSModelDB::DBTraits,
								 // BSResource::EntryDB<BSModelDB::DBTraits>>::CArgs>,
								 // BSResource::EntryDB<BSModelDB::DBTraits>>`
		BGSMod::Attachment::Mod* nullMod;				// 0x598
		Scaleform::GFx::Value requirementsList;			// 0x5A0
		Scaleform::GFx::Value itemSelectList;			// 0x5C0
		BGSKeyword* keyword;							// 0x5E0
		bool queueChangeCameraPosition;					// 0x5E8
		bool returnToInspect;							// 0x5E9
		bool highlightStoredItem;						// 0x5EA
		bool textEntry;									// 0x5EB
		bool virtualKeyboardPendingEvt;					// 0x5EC
		bool inspectMode;								// 0x5ED
		bool inspectingSingleItem;						// 0x5EE
		bool inspectingFeaturedItem;					// 0x5EF
		bool showFeaturedItemMessage;					// 0x5F0
		REX::StaticString<260> renameItemTo;			// 0x5F1
		REX::StaticString<260> renameItemCancelState;	// 0x6F5
		BSTSmartPointer<BSInputEnableLayer> inputLayer; // 0x800
	};

	static_assert(sizeof(ExamineMenu) == 0x810);
}
