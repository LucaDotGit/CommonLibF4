#pragma once

#include "RE/B/BGSListForm.hpp"
#include "RE/B/BSGFxShaderFXTarget.hpp"
#include "RE/B/BSReadWriteLock.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTInterpolator.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/B/BSTTuple.hpp"
#include "RE/D/DisplayItemModel.hpp"
#include "RE/G/GameMenuBase.hpp"
#include "RE/I/Inventory3DManager.hpp"
#include "RE/N/NiPoint3.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/U/UI_DEPTH_PRIORITY.hpp"
#include "msvc/memory.hpp"

namespace RE::Workshop
{
	class BuildableAreaEvent;
	class PlacementStatusEvent;
}

namespace RE
{
	class EaseOutInterpolator;
	class PickRefUpdateEvent;
	class UserEventEnabledEvent;
	class WorkshopMenuGeometry;

	class __declspec(novtable) WorkshopMenu :
		public GameMenuBase,								// 0x000
		public BSTEventSink<UserEventEnabledEvent>,			// 0x0E0
		public BSTEventSink<Workshop::BuildableAreaEvent>,	// 0x0E8
		public BSTEventSink<PickRefUpdateEvent>,			// 0x0F0
		public BSTEventSink<Workshop::PlacementStatusEvent> // 0x0F8
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::WorkshopMenu;
		inline static constexpr const auto& VTABLE = VTABLE::WorkshopMenu;
		inline static constexpr auto MENU_NAME = "WorkshopMenu"sv;
		inline static constexpr auto MENU_DEPTH = UI_DEPTH_PRIORITY::WorkshopMenu;

		enum class TAG_FOR_SEARCH_RESULT : std::int32_t
		{
			None = 0,
			TaggedComponents = 1,
			UntaggedComponents = 2
		};

		class __declspec(novtable) FXWorkshopMenu : public BSGFxShaderFXTarget // 0x00
		{
		public:
			inline static constexpr const auto& RTTI = RTTI::WorkshopMenu__FXWorkshopMenu;
			inline static constexpr const auto& VTABLE = VTABLE::WorkshopMenu__FXWorkshopMenu;

			~FXWorkshopMenu() override; // 0x00

			// members
			msvc::unique_ptr<BSGFxShaderFXTarget> happyBackground01;		  // 0x0B0
			msvc::unique_ptr<BSGFxShaderFXTarget> happyBackground02;		  // 0x0B8
			msvc::unique_ptr<BSGFxShaderFXTarget> happyBackground03;		  // 0x0C0
			msvc::unique_ptr<BSGFxShaderFXTarget> happyBackground04;		  // 0x0C8
			msvc::unique_ptr<BSGFxShaderFXTarget> happyBackground05;		  // 0x0D0
			msvc::unique_ptr<BSGFxShaderFXTarget> happyBackground06;		  // 0x0D8
			msvc::unique_ptr<BSGFxShaderFXTarget> happyBackground07;		  // 0x0E0
			msvc::unique_ptr<BSGFxShaderFXTarget> happyBackground08;		  // 0x0E8
			msvc::unique_ptr<BSGFxShaderFXTarget> buttonBackground;			  // 0x0F0
			msvc::unique_ptr<BSGFxShaderFXTarget> iconCardBackground;		  // 0x0F8
			msvc::unique_ptr<BSGFxShaderFXTarget> requirementsListBackground; // 0x100
			msvc::unique_ptr<BSGFxShaderFXTarget> happinessPeopleBase;		  // 0x108
			msvc::unique_ptr<BSGFxShaderFXTarget> happinessFoodBase;		  // 0x110
			msvc::unique_ptr<BSGFxShaderFXTarget> happinessWaterBase;		  // 0x118
			msvc::unique_ptr<BSGFxShaderFXTarget> happinessPowerBase;		  // 0x120
			msvc::unique_ptr<BSGFxShaderFXTarget> happinessSafetyBase;		  // 0x128
			msvc::unique_ptr<BSGFxShaderFXTarget> happinessBedsBase;		  // 0x130
			msvc::unique_ptr<BSGFxShaderFXTarget> happinessHappyValue;		  // 0x138
			msvc::unique_ptr<BSGFxShaderFXTarget> happinessHappyLabel;		  // 0x140
			msvc::unique_ptr<BSGFxShaderFXTarget> happinessHappyIcon;		  // 0x148
			msvc::unique_ptr<BSGFxShaderFXTarget> happinessHappyArrow;		  // 0x150
			msvc::unique_ptr<BSGFxShaderFXTarget> happinessSizeBase;		  // 0x158
			msvc::unique_ptr<BSGFxShaderFXTarget> happinessBarBrackets;		  // 0x160
			msvc::unique_ptr<BSGFxShaderFXTarget> requirementsBase;			  // 0x168
			msvc::unique_ptr<BSGFxShaderFXTarget> itemName;					  // 0x170
			msvc::unique_ptr<BSGFxShaderFXTarget> selectionBracket;			  // 0x178
			msvc::unique_ptr<BSGFxShaderFXTarget> itemCounts;				  // 0x180
			msvc::unique_ptr<BSGFxShaderFXTarget> newRecipeIcon;			  // 0x188
			msvc::unique_ptr<BSGFxShaderFXTarget> iconCardBracketsAndText;	  // 0x190
			msvc::unique_ptr<BSGFxShaderFXTarget> producesIcons;			  // 0x198
			msvc::unique_ptr<BSGFxShaderFXTarget> requiresIcon01;			  // 0x1A0
			msvc::unique_ptr<BSGFxShaderFXTarget> requiresIcon02;			  // 0x1A8
			msvc::unique_ptr<BSGFxShaderFXTarget> assignmentIcon;			  // 0x1B0
			msvc::unique_ptr<BSGFxShaderFXTarget> rowBrackets;				  // 0x1B8
			msvc::unique_ptr<BSGFxShaderFXTarget> displayPath;				  // 0x1C0
			msvc::unique_ptr<BSGFxShaderFXTarget> perkPanel01;				  // 0x1C8
			msvc::unique_ptr<BSGFxShaderFXTarget> perkPanel02;				  // 0x1D0
			msvc::unique_ptr<BSGFxShaderFXTarget> descriptionBase;			  // 0x1D8
			msvc::unique_ptr<BSGFxShaderFXTarget> iconBackground;			  // 0x1E0
		};

		static_assert(sizeof(FXWorkshopMenu) == 0x1E8);

		class IconBG
		{
		public:
			BSTAlignedArray<UIShaderFXInfo> cachedColorFXInfos;		 // 0x00
			BSTAlignedArray<UIShaderFXInfo> cachedBackgroundFXInfos; // 0x18
			mutable BSReadWriteLock cachedQuadsLock;				 // 0x30
		};

		static_assert(sizeof(IconBG) == 0x38);

		~WorkshopMenu() override; // 0x00

		void CheckAndSetItemForPlacement()
		{
			using FuncType = decltype(&WorkshopMenu::CheckAndSetItemForPlacement);
			static const auto FUNC = REL::Relocation<FuncType>(ID::WorkshopMenu::CheckAndSetItemForPlacement);
			std::invoke(FUNC, this);
		}

		void UpdateButtonText()
		{
			using FuncType = decltype(&WorkshopMenu::UpdateButtonText);
			static const auto FUNC = REL::Relocation<FuncType>(ID::WorkshopMenu::UpdateButtonText);
			std::invoke(FUNC, this);
		}

		// members
		std::array<BSTArray<NiPoint3>, 4> item3DPositions;													  // 0x100
		BSTArray<BSTPair<DisplayItemModel, TESObjectREFR*>> displayItemModels;								  // 0x160
		IconBG iconBG;																						  // 0x178
		Inventory3DManager inventory3DModelManager;															  // 0x1B0
		BSTArray<BSTPair<NiPointer<nsInventory3DManager::NewInventoryMenuItemLoadTask>, NiPoint3>> loadTasks; // 0x2F0
		BSTInterpolator<REX::Float32, EaseOutInterpolator, GetCurrentPositionFunctor>
			upDownGlassAnimationInterpolator; // 0x308
		std::array<BSTInterpolator<REX::Float32, EaseOutInterpolator, GetCurrentPositionFunctor>, 4>
			leftRightGlassAnimationInterpolator;			   // 0x320
		BSTSmartPointer<WorkshopMenuGeometry> displayGeometry; // 0x380
		BSFixedString dPadInput;							   // 0x388
		BGSListForm includeList;							   // 0x390
		BGSListForm excludeList;							   // 0x3D8
		REX::Float128 lastBudget;							   // 0x420
		std::uint16_t topMenuCount;							   // 0x428
		bool inputAdjustMode;								   // 0x42A
		bool verticalAdjustment;							   // 0x42B
		bool disableAdjustOnThumbEvent;						   // 0x42C
		bool initialized;									   // 0x42D
		bool inEditMode;									   // 0x42E
		bool electricalDevice;								   // 0x42F
		bool useMovementAsDirectional;						   // 0x430
		bool motionBlurActive;								   // 0x431
		bool exitDebounce;									   // 0x432
		msvc::unique_ptr<FXWorkshopMenu> workshopMenuBase;	   // 0x438
	};

	static_assert(sizeof(WorkshopMenu) == 0x440);
}
