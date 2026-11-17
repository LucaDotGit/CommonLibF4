#pragma once

namespace RE
{
	enum class UI_MENU_FLAGS : std::uint32_t
	{
		None = 0,
		PausesGame = 1 << 0,
		AlwaysOpen = 1 << 1,
		UsesCursor = 1 << 2,
		UsesMenuContext = 1 << 3,
		Modal = 1 << 4,
		FreezeFrameBackground = 1 << 5,
		OnStack = 1 << 6,
		DisablePauseMenu = 1 << 7,
		RequiresUpdate = 1 << 8,
		TopmostRenderedMenu = 1 << 9,
		UpdateUsesCursor = 1 << 10,
		AllowSaving = 1 << 11,
		RendersOffscreenTargets = 1 << 12,
		InventoryItemMenu = 1 << 13,
		DoNotHideCursorWhenTopmost = 1 << 14,
		CustomRendering = 1 << 15,
		AssignCursorToRenderer = 1 << 16,
		ApplicationMenu = 1 << 17,
		HasButtonBar = 1 << 18,
		IsTopButtonBar = 1 << 19,
		AdvancesUnderPauseMenu = 1 << 20,
		RendersUnderPauseMenu = 1 << 21,
		UsesBlurredBackground = 1 << 22,
		CompanionAppAllowed = 1 << 23,
		FreezeFramePause = 1 << 24,
		SkipRenderDuringFreezeFrameScreenshot = 1 << 25,
		LargeScaleformRenderCacheMode = 1 << 26,
		UsesMovementToDirection = 1 << 27
	};
}
