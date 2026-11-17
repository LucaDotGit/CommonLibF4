#pragma once

namespace RE::UserEvents
{
	enum class INPUT_CONTEXT_ID : std::int32_t
	{
		MainGameplay = 0,
		BasicMenuNav = 1,
		ThumbNav = 2,
		VirtualController = 3,
		Cursor = 4,
		LThumbCursor = 5,
		Console = 6,
		DebugText = 7,
		Book = 8,
		DebugOverlay = 9,
		TFC = 10,
		DebugMap = 11,
		Lockpick = 12,
		VATS = 13,
		VATSPlayback = 14,
		MultiActivate = 15,
		Workshop = 16,
		Scope = 17,
		SitWait = 18,
		LooksMenu = 19,
		WorkshopAddendum = 20,
		PauseMenu = 21,
		LevelUpMenu = 22,
		LevelUpMenuPrevNext = 23,
		MainMenu = 24,
		QuickContainerMenu = 25,
		SpecialActivateRollover = 26,
		TwoButtonRollover = 27,
		QuickContainerMenuPerk = 28,
		Vertibird = 29,
		PlayBinkMenu = 30,
		RobotModAddendum = 31,
		CreationClub = 32,

		_Count = 33,

		None = 34
	};

	enum class SENDER_ID : std::int32_t
	{
		None = 0,
		Gameplay = 1,
		Menu = 2,
		Script = 3,

		_Count = 4
	};

	enum class USER_EVENT_FLAG : std::uint32_t
	{
		None = 0,
		Movement = 1 << 0,
		Looking = 1 << 1,
		Activate = 1 << 2,
		Menu = 1 << 3,
		Console = 1 << 4,
		POVSwitch = 1 << 5,
		Fighting = 1 << 6,
		Sneaking = 1 << 7,
		MainFour = 1 << 8,
		WheelZoom = 1 << 9,
		Jumping = 1 << 10,
		VATS = 1 << 11,

		All = std::numeric_limits<std::underlying_type_t<USER_EVENT_FLAG>>::max()
	};
}
