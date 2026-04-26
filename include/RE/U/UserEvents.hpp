#pragma once

namespace RE::UserEvents
{
	enum class INPUT_CONTEXT_ID : std::int32_t
	{
		kMainGameplay = 0,
		kBasicMenuNav = 1,
		kThumbNav = 2,
		kVirtualController = 3,
		kCursor = 4,
		kLThumbCursor = 5,
		kConsole = 6,
		kDebugText = 7,
		kBook = 8,
		kDebugOverlay = 9,
		kTFC = 10,
		kDebugMap = 11,
		kLockpick = 12,
		kVATS = 13,
		kVATSPlayback = 14,
		kMultiActivate = 15,
		kWorkshop = 16,
		kScope = 17,
		kSitWait = 18,
		kLooksMenu = 19,
		kWorkshopAddendum = 20,
		kPauseMenu = 21,
		kLevelUpMenu = 22,
		kLevelUpMenuPrevNext = 23,
		kMainMenu = 24,
		kQuickContainerMenu = 25,
		kSpecialActivateRollover = 26,
		kTwoButtonRollover = 27,
		kQuickContainerMenuPerk = 28,
		kVertibird = 29,
		kPlayBinkMenu = 30,
		kRobotModAddendum = 31,
		kCreationClub = 32,

		kTotal = 33,

		kNone = 34
	};

	enum class SENDER_ID : std::int32_t
	{
		kNone = 0,
		kGameplay = 1,
		kMenu = 2,
		kScript = 3
	};

	enum class USER_EVENT_FLAG : std::uint32_t
	{
		kAll = std::numeric_limits<std::underlying_type_t<USER_EVENT_FLAG>>::max(),

		kNone = 0,
		kMovement = 1 << 0,
		kLooking = 1 << 1,
		kActivate = 1 << 2,
		kMenu = 1 << 3,
		kConsole = 1 << 4,
		kPOVSwitch = 1 << 5,
		kFighting = 1 << 6,
		kSneaking = 1 << 7,
		kMainFour = 1 << 8,
		kWheelZoom = 1 << 9,
		kJumping = 1 << 10,
		kVATS = 1 << 11
	};
}
