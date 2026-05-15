#pragma once

#include "RE/B/BGSListForm.hpp"
#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTInterpolator.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/B/BSTTuple.hpp"
#include "RE/D/DisplayItemModel.hpp"
#include "RE/G/GameMenuBase.hpp"
#include "RE/I/Inventory3DManager.hpp"
#include "RE/N/NiPoint.hpp"
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
	class PickRefUpdateEvent;
	class UserEventEnabledEvent;
	class WorkshopMenuGeometry;

	class __declspec(novtable) WorkshopMenu
		: public GameMenuBase,								  // 000
		  public BSTEventSink<UserEventEnabledEvent>,		  // 0E0
		  public BSTEventSink<Workshop::BuildableAreaEvent>,  // 0E8
		  public BSTEventSink<PickRefUpdateEvent>,			  // 0F0
		  public BSTEventSink<Workshop::PlacementStatusEvent> // 0F8
	{
	public:
		inline static constexpr auto RTTI{ RTTI::WorkshopMenu };
		inline static constexpr auto VTABLE{ VTABLE::WorkshopMenu };
		inline static constexpr auto MENU_NAME{ "WorkshopMenu"sv };
		inline static constexpr auto MENU_DEPTH{ UI_DEPTH_PRIORITY::kWorkshopMenu };

		enum class TAG_FOR_SEARCH_RESULT : std::int32_t
		{
			kNone = 0,
			kTaggedComponents = 1,
			kUntaggedComponents = 2
		};

		class __declspec(novtable) FXWorkshopMenu
			: public BSGFxShaderFXTarget // 00
		{
		public:
			inline static constexpr auto RTTI{ RTTI::WorkshopMenu__FXWorkshopMenu };
			inline static constexpr auto VTABLE{ VTABLE::WorkshopMenu__FXWorkshopMenu };

			~FXWorkshopMenu() override; // 00

			// members
			msvc::unique_ptr<BSGFxShaderFXTarget> happyBackground01;		  // 0B0
			msvc::unique_ptr<BSGFxShaderFXTarget> happyBackground02;		  // 0B8
			msvc::unique_ptr<BSGFxShaderFXTarget> happyBackground03;		  // 0C0
			msvc::unique_ptr<BSGFxShaderFXTarget> happyBackground04;		  // 0C8
			msvc::unique_ptr<BSGFxShaderFXTarget> happyBackground05;		  // 0D0
			msvc::unique_ptr<BSGFxShaderFXTarget> happyBackground06;		  // 0D8
			msvc::unique_ptr<BSGFxShaderFXTarget> happyBackground07;		  // 0E0
			msvc::unique_ptr<BSGFxShaderFXTarget> happyBackground08;		  // 0E8
			msvc::unique_ptr<BSGFxShaderFXTarget> buttonBackground;			  // 0F0
			msvc::unique_ptr<BSGFxShaderFXTarget> iconCardBackground;		  // 0F8
			msvc::unique_ptr<BSGFxShaderFXTarget> requirementsListBackground; // 100
			msvc::unique_ptr<BSGFxShaderFXTarget> happinessPeopleBase;		  // 108
			msvc::unique_ptr<BSGFxShaderFXTarget> happinessFoodBase;		  // 110
			msvc::unique_ptr<BSGFxShaderFXTarget> happinessWaterBase;		  // 118
			msvc::unique_ptr<BSGFxShaderFXTarget> happinessPowerBase;		  // 120
			msvc::unique_ptr<BSGFxShaderFXTarget> happinessSafetyBase;		  // 128
			msvc::unique_ptr<BSGFxShaderFXTarget> happinessBedsBase;		  // 130
			msvc::unique_ptr<BSGFxShaderFXTarget> happinessHappyValue;		  // 138
			msvc::unique_ptr<BSGFxShaderFXTarget> happinessHappyLabel;		  // 140
			msvc::unique_ptr<BSGFxShaderFXTarget> happinessHappyIcon;		  // 148
			msvc::unique_ptr<BSGFxShaderFXTarget> happinessHappyArrow;		  // 150
			msvc::unique_ptr<BSGFxShaderFXTarget> happinessSizeBase;		  // 158
			msvc::unique_ptr<BSGFxShaderFXTarget> happinessBarBrackets;		  // 160
			msvc::unique_ptr<BSGFxShaderFXTarget> requirementsBase;			  // 168
			msvc::unique_ptr<BSGFxShaderFXTarget> itemName;					  // 170
			msvc::unique_ptr<BSGFxShaderFXTarget> selectionBracket;			  // 178
			msvc::unique_ptr<BSGFxShaderFXTarget> itemCounts;				  // 180
			msvc::unique_ptr<BSGFxShaderFXTarget> newRecipeIcon;			  // 188
			msvc::unique_ptr<BSGFxShaderFXTarget> iconCardBracketsAndText;	  // 190
			msvc::unique_ptr<BSGFxShaderFXTarget> producesIcons;			  // 198
			msvc::unique_ptr<BSGFxShaderFXTarget> requiresIcon01;			  // 1A0
			msvc::unique_ptr<BSGFxShaderFXTarget> requiresIcon02;			  // 1A8
			msvc::unique_ptr<BSGFxShaderFXTarget> assignmentIcon;			  // 1B0
			msvc::unique_ptr<BSGFxShaderFXTarget> rowBrackets;				  // 1B8
			msvc::unique_ptr<BSGFxShaderFXTarget> displayPath;				  // 1C0
			msvc::unique_ptr<BSGFxShaderFXTarget> perkPanel01;				  // 1C8
			msvc::unique_ptr<BSGFxShaderFXTarget> perkPanel02;				  // 1D0
			msvc::unique_ptr<BSGFxShaderFXTarget> descriptionBase;			  // 1D8
			msvc::unique_ptr<BSGFxShaderFXTarget> iconBackground;			  // 1E0
		};
		static_assert(sizeof(FXWorkshopMenu) == 0x1E8);

		class IconBG
		{
		public:
			BSTAlignedArray<UIShaderFXInfo> cachedColorFXInfos;		 // 00
			BSTAlignedArray<UIShaderFXInfo> cachedBackgroundFXInfos; // 18
			mutable BSReadWriteLock cachedQuadsLock;				 // 30
		};
		static_assert(sizeof(IconBG) == 0x38);

		~WorkshopMenu() override; // 00

		void CheckAndSetItemForPlacement()
		{
			using FuncType = decltype(&WorkshopMenu::CheckAndSetItemForPlacement);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::WorkshopMenu::CheckAndSetItemForPlacement };
			std::invoke(FUNC, this);
		}

		void UpdateButtonText()
		{
			using FuncType = decltype(&WorkshopMenu::UpdateButtonText);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::WorkshopMenu::UpdateButtonText };
			std::invoke(FUNC, this);
		}

		// members
		std::array<BSTArray<NiPoint3>, 4> item3DPositions;																				  // 100
		BSTArray<BSTPair<DisplayItemModel, TESObjectREFR*>> displayItemModels;															  // 160
		IconBG iconBG;																													  // 178
		Inventory3DManager inventory3DModelManager;																						  // 1B0
		BSTArray<BSTPair<NiPointer<nsInventory3DManager::NewInventoryMenuItemLoadTask>, NiPoint3>> loadTasks;							  // 2F0
		BSTInterpolator<REX::Float32, EaseOutInterpolator, GetCurrentPositionFunctor> upDownGlassAnimationInterpolator;					  // 308
		std::array<BSTInterpolator<REX::Float32, EaseOutInterpolator, GetCurrentPositionFunctor>, 4> leftRightGlassAnimationInterpolator; // 320
		BSTSmartPointer<WorkshopMenuGeometry> displayGeometry;																			  // 380
		BSFixedString dPadInput;																										  // 388
		BGSListForm includeList;																										  // 390
		BGSListForm excludeList;																										  // 3D8
		REX::Float128 lastBudget;																										  // 420
		std::uint16_t topMenuCount;																										  // 428
		bool inputAdjustMode;																											  // 42A
		bool verticalAdjustment;																										  // 42B
		bool disableAdjustOnThumbEvent;																									  // 42C
		bool initialized;																												  // 42D
		bool inEditMode;																												  // 42E
		bool electricalDevice;																											  // 42F
		bool useMovementAsDirectional;																									  // 430
		bool motionBlurActive;																											  // 431
		bool exitDebounce;																												  // 432
		msvc::unique_ptr<FXWorkshopMenu> workshopMenuBase;																				  // 438
	};
	static_assert(sizeof(WorkshopMenu) == 0x440);
}
