#pragma once

#include "RE/B/BGSInventoryList.hpp"
#include "RE/B/BGSTypedFormValuePair.hpp"
#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/B/BSTTuple.hpp"
#include "RE/G/GameMenuBase.hpp"
#include "RE/I/Inventory3DManager.hpp"
#include "RE/I/InventoryInterface_Handle.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/R/Rumble.hpp"

namespace RE
{
	class ExtraDataList;
	class NiNode;

	class __declspec(novtable) WorkbenchMenuBase : public GameMenuBase // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::WorkbenchMenuBase;
		inline static constexpr const auto& VTABLE = VTABLE::WorkbenchMenuBase;

		enum class HighlightMode : std::int32_t
		{
			ModMenu = 0,
			All = 1,
			World = 2
		};

		class InitParams
		{
		public:
			InitParams();

			// members
			ObjectRefHandle workbenchFurniture;										   // 0x00
			ObjectRefHandle inventorySource;										   // 0x04
			InventoryInterface::Handle item{InventoryInterface::Handle::EMPTY_HANDLE}; // 0x08
			NiPointer<Actor> actor{nullptr};										   // 0x10
			std::uint32_t stack{0};													   // 0x18
			bool inspectMode{true};													   // 0x1C
			bool inspectingSingleItem{false};										   // 0x1D
			bool inspectingFeaturedItem{false};										   // 0x1E
			bool showFeaturedItemMessage{false};									   // 0x1F
			bool botCompanion{false};												   // 0x20
		};

		static_assert(sizeof(InitParams) == 0x28);

		class ModChoiceData
		{
		public:
			// members
			union
			{
			public:
				BGSMod::Attachment::Mod* mod;
				TESBoundObject* object;
			}; // 0x00

			BGSConstructibleObject* recipe;												  // 0x08
			BSTArray<BSTPair<TESForm*, BGSTypedFormValuePair::SharedVal>>* requiredItems; // 0x10
			BSTArray<BSTPair<BGSPerk*, std::uint32_t>> requiredPerks;					  // 0x18
			std::uint8_t rank;															  // 0x30
			std::uint8_t index;															  // 0x31
		};

		static_assert(sizeof(ModChoiceData) == 0x38);

		~WorkbenchMenuBase() override; // 0x00

		// override (GameMenuBase)
		void Call(const Params& a_params) override;														// 0x01
		void MapCodeObjectFunctions() override;															// 0x02
		void PreDisplay() override;																		// 0x05
		void OnMenuStackChanged(const BSFixedString& a_topMenuName, bool a_passesTopMenuTest) override; // 0x09

		// override (BSInputEventUser)
		auto ShouldHandleEvent(const InputEvent* a_event) -> bool override; // 0x01
		void OnThumbstickEvent(const ThumbstickEvent* a_event) override;	// 0x04
		void OnCursorMoveEvent(const CursorMoveEvent* a_event) override;	// 0x05
		void OnButtonEvent(const ButtonEvent* a_event) override;			// 0x08

		// add
		virtual void OnHideMenu();									  // 0x14
		virtual void UpdateMenu();									  // 0x15
		virtual void BuildCanceled();								  // 0x16
		virtual void BuildConfirmed(bool a_ownerIsWorkbench) = 0;	  // 0x17
		virtual auto GetWorkbenchHasInventory() -> bool;			  // 0x18
		virtual auto QCurrentModChoiceData() -> const ModChoiceData*; // 0x19
		virtual void ShowBuildFailureMessage();						  // 0x1A
		virtual auto TryCreate() -> bool = 0;						  // 0x1B

		void UpdateOptimizedAutoBuildInv()
		{
			using FuncType = decltype(&WorkbenchMenuBase::UpdateOptimizedAutoBuildInv);
			static const auto FUNC = REL::Relocation<FuncType>(ID::WorkbenchMenuBase::UpdateOptimizedAutoBuildInv);
			std::invoke(FUNC, this);
		}

		// members
		NiPointer<TESObjectREFR> sharedContainerRef;		  // 0x0E0
		NiPointer<TESObjectREFR> workbenchContainerRef;		  // 0x0E8
		BSTArray<NiPointer<TESObjectREFR>> sharedContainers;  // 0x0F0
		Inventory3DManager inv3DModelManager;				  // 0x110
		BGSInventoryList optimizedAutoBuildInv;				  // 0x250
		BSTArray<ModChoiceData> modChoiceArray;				  // 0x2D0
		std::uint32_t modChoiceIndex;						  // 0x2E8
		std::uint32_t lastModChoiceIndex;					  // 0x2EC
		bool repairing;										  // 0x2F0
		bool queueHide;										  // 0x2F1
		bool hiding;										  // 0x2F2
		bool vatsWasEnabled;								  // 0x2F3
		NiPointer<TESObjectREFR> workbenchRef;				  // 0x2F8
		BSTSmartPointer<ExtraDataList> recipeExtraDataList;	  // 0x300
		NiPointer<NiNode> item3DGeometry;					  // 0x308
		BSTArray<TESForm*> queuedCraftingComponents;		  // 0x310
		std::uint64_t soundTimer;							  // 0x328
		REX::Enum<HighlightMode, std::int32_t> highlightMode; // 0x330
		Rumble::AutoRumblePause autoRumblePause;			  // 0x334
		bool initialized;									  // 0x335
		bool soundsQueued;									  // 0x336
	};

	static_assert(sizeof(WorkbenchMenuBase) == 0x340);
}
