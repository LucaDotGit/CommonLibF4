#pragma once

namespace RE
{
	enum class UI_DEPTH_PRIORITY : std::int32_t
	{
		Undefined = 0,
		k3DUnderHUD = 1,
		BookMenu = 2,
		ScopeMenu = 3,
		SWFLoader = 4,
		HUDMenu = 5,
		Standard = 6,
		Standard3DModel = 7,
		Pipboy = 8,
		TerminalMenu = 9,
		GameMessage = 10,
		PauseMenu = 11,
		LoadingFader = 12,
		Loading3DModel = 13,
		LoadingMenu = 14,
		Message = 15,
		ButtonBarMenu = 16,
		ButtonBarSuppressingMenu = 17,
		Debug = 18,
		Console = 19,
		CursorMenu = 20,

		_Count = 21,

		PowerArmorHUDMenu = HUDMenu,
		PromptMenu = HUDMenu,

		BarterMenu = Standard,
		ContainerMenu = Standard,
		DialogueMenu = Standard,
		FaderMenu = Standard,
		FavoritesMenu = Standard,
		LockpickingMenu = Standard,
		MainMenu = Standard,
		PipboyMenu = Standard,
		PowerArmorRenderer = Standard,
		SPECIALMenu = Standard,
		SitWaitMenu = Standard,
		VATSMenu = Standard,
		WorkshopMenu = Standard,

		Container3D = Standard3DModel,
		WorkbenchItem3D = Standard3DModel,

		CookingMenu = TerminalMenu,
		ExamineMenu = TerminalMenu,
		LevelUpMenu = TerminalMenu,
		PipboyHolotapeMenu = TerminalMenu,
		PowerArmorModMenu = TerminalMenu,
		RobotModMenu = TerminalMenu,
		TerminalHolotapeMenu = TerminalMenu,

		MessageBoxMenu = GameMessage,
		SleepWaitMenu = GameMessage,

		BackgroundScreenModel = Loading3DModel,

		FlatScreenModel = ButtonBarMenu,
		HUDScreenModel = ButtonBarMenu,
		TerminalMenuButtons = ButtonBarMenu,

		ExamineConfirmMenu = ButtonBarSuppressingMenu
	};
}
