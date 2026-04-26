#pragma once

namespace RE
{
	enum class UI_DEPTH_PRIORITY : std::int32_t
	{
		kUndefined = 0,
		k3DUnderHUD = 1,
		kBookMenu = 2,
		kScopeMenu = 3,
		kSWFLoader = 4,
		kHUDMenu = 5,
		kStandard = 6,
		kStandard3DModel = 7,
		kPipboy = 8,
		kTerminalMenu = 9,
		kGameMessage = 10,
		kPauseMenu = 11,
		kLoadingFader = 12,
		kLoading3DModel = 13,
		kLoadingMenu = 14,
		kMessage = 15,
		kButtonBarMenu = 16,
		kButtonBarSuppressingMenu = 17,
		kDebug = 18,
		kConsole = 19,
		kCursorMenu = 20,

		kTotal = 21,

		kPowerArmorHUDMenu = kHUDMenu,
		kPromptMenu = kHUDMenu,

		kBarterMenu = kStandard,
		kContainerMenu = kStandard,
		kDialogueMenu = kStandard,
		kFaderMenu = kStandard,
		kFavoritesMenu = kStandard,
		kLockpickingMenu = kStandard,
		kMainMenu = kStandard,
		kPipboyMenu = kStandard,
		kPowerArmorRenderer = kStandard,
		kSPECIALMenu = kStandard,
		kSitWaitMenu = kStandard,
		kVATSMenu = kStandard,
		kWorkshopMenu = kStandard,

		kContainer3D = kStandard3DModel,
		kWorkbenchItem3D = kStandard3DModel,

		kCookingMenu = kTerminalMenu,
		kExamineMenu = kTerminalMenu,
		kLevelUpMenu = kTerminalMenu,
		kPipboyHolotapeMenu = kTerminalMenu,
		kPowerArmorModMenu = kTerminalMenu,
		kRobotModMenu = kTerminalMenu,
		kTerminalHolotapeMenu = kTerminalMenu,

		kMessageBoxMenu = kGameMessage,
		kSleepWaitMenu = kGameMessage,

		kBackgroundScreenModel = kLoading3DModel,

		kFlatScreenModel = kButtonBarMenu,
		kHUDScreenModel = kButtonBarMenu,
		kTerminalMenuButtons = kButtonBarMenu,

		kExamineConfirmMenu = kButtonBarSuppressingMenu
	};
}
