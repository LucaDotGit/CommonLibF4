#pragma once

#include "RE/B/BGSInventoryList.hpp"
#include "RE/B/BGSTypedFormValuePair.hpp"
#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/B/BSTTuple.hpp"
#include "RE/G/GameMenuBase.hpp"
#include "RE/I/Inventory3DManager.hpp"
#include "RE/I/InventoryInterface.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/R/Rumble.hpp"

namespace RE
{
	class ExtraDataList;
	class NiNode;

	class __declspec(novtable) WorkbenchMenuBase
		: public GameMenuBase // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::WorkbenchMenuBase };
		inline static constexpr auto VTABLE{ VTABLE::WorkbenchMenuBase };

		enum class HighlightMode : std::int32_t
		{
			kModMenu = 0,
			kAll = 1,
			kWorld = 2
		};

		class InitParams
		{
		public:
			InitParams();

			// members
			ObjectRefHandle workbenchFurniture;											 // 00
			ObjectRefHandle inventorySource;											 // 04
			InventoryInterface::Handle item{ InventoryInterface::Handle::EMPTY_HANDLE }; // 08
			NiPointer<Actor> actor{ nullptr };											 // 10
			std::uint32_t stack{ 0 };													 // 18
			bool inspectMode{ true };													 // 1C
			bool inspectingSingleItem{ false };											 // 1D
			bool inspectingFeaturedItem{ false };										 // 1E
			bool showFeaturedItemMessage{ false };										 // 1F
			bool botCompanion{ false };													 // 20
		};
		static_assert(sizeof(InitParams) == 0x28);

		class ModChoiceData
		{
		public:
			// members
			union
			{
				BGSMod::Attachment::Mod* mod;
				TESBoundObject* object;
			}; // 00
			BGSConstructibleObject* recipe;												  // 08
			BSTArray<BSTPair<TESForm*, BGSTypedFormValuePair::SharedVal>>* requiredItems; // 10
			BSTArray<BSTPair<BGSPerk*, std::uint32_t>> requiredPerks;					  // 18
			std::uint8_t rank;															  // 30
			std::uint8_t index;															  // 31
		};
		static_assert(sizeof(ModChoiceData) == 0x38);

		~WorkbenchMenuBase() override; // 00

		// override (GameMenuBase)
		void Call(const Params& a_params) override;														// 01
		void MapCodeObjectFunctions() override;															// 02
		void PreDisplay() override;																		// 05
		void OnMenuStackChanged(const BSFixedString& a_topMenuName, bool a_passesTopMenuTest) override; // 09

		// override (BSInputEventUser)
		bool ShouldHandleEvent(const InputEvent* a_event) override;		 // 01
		void OnThumbstickEvent(const ThumbstickEvent* a_event) override; // 04
		void OnCursorMoveEvent(const CursorMoveEvent* a_event) override; // 05
		void OnButtonEvent(const ButtonEvent* a_event) override;		 // 08

		// add
		virtual void OnHideMenu();								  // 14
		virtual void UpdateMenu();								  // 15
		virtual void BuildCanceled();							  // 16
		virtual void BuildConfirmed(bool a_ownerIsWorkbench) = 0; // 17
		virtual bool GetWorkbenchHasInventory();				  // 18
		virtual const ModChoiceData* QCurrentModChoiceData();	  // 19
		virtual void ShowBuildFailureMessage();					  // 1A
		virtual bool TryCreate() = 0;							  // 1B

		void UpdateOptimizedAutoBuildInv()
		{
			using FuncType = decltype(&WorkbenchMenuBase::UpdateOptimizedAutoBuildInv);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::WorkbenchMenuBase::UpdateOptimizedAutoBuildInv };
			std::invoke(FUNC, this);
		}

		// members
		NiPointer<TESObjectREFR> sharedContainerRef;		  // 0E0
		NiPointer<TESObjectREFR> workbenchContainerRef;		  // 0E8
		BSTArray<NiPointer<TESObjectREFR>> sharedContainers;  // 0F0
		Inventory3DManager inv3DModelManager;				  // 110
		BGSInventoryList optimizedAutoBuildInv;				  // 250
		BSTArray<ModChoiceData> modChoiceArray;				  // 2D0
		std::uint32_t modChoiceIndex;						  // 2E8
		std::uint32_t lastModChoiceIndex;					  // 2EC
		bool repairing;										  // 2F0
		bool queueHide;										  // 2F1
		bool hiding;										  // 2F2
		bool vatsWasEnabled;								  // 2F3
		NiPointer<TESObjectREFR> workbenchRef;				  // 2F8
		BSTSmartPointer<ExtraDataList> recipeExtraDataList;	  // 300
		NiPointer<NiNode> item3DGeometry;					  // 308
		BSTArray<TESForm*> queuedCraftingComponents;		  // 310
		std::uint64_t soundTimer;							  // 328
		REX::Enum<HighlightMode, std::int32_t> highlightMode; // 330
		Rumble::AutoRumblePause autoRumblePause;			  // 334
		bool initialized;									  // 335
		bool soundsQueued;									  // 336
	};
	static_assert(sizeof(WorkbenchMenuBase) == 0x340);
}
