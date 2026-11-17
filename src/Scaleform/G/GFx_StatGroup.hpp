#pragma once

#include "Scaleform/S/StatBasicValues.hpp"

namespace Scaleform
{
	enum StatGroup : std::int32_t
	{
		StatGroup_Renderer = 1 << 6,
		StatGroup_RenderGen = 2 << 6,
		StatGroup_GFxFontCache = 3 << 6,
		StatGroup_GFxMovieData = 4 << 6,
		StatGroup_GFxMovieView = 5 << 6,
		StatGroup_GFxRenderCache = 6 << 6,
		StatGroup_GFxPlayer = 7 << 6,
		StatGroup_GFxIME = 8 << 6,
		StatGroup_GFxAmp = 9 << 6,

		// General Memory
		Stat_Image_Mem = Stat_Default_Mem + 1,
		Stat_String_Mem,

		Stat_Debug_Mem,
		Stat_DebugHUD_Mem,
		Stat_DebugTracker_Mem,
		Stat_StatBag_Mem
	};
}
