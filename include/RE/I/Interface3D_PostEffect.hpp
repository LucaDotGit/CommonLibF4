#pragma once

namespace RE::Interface3D
{
	enum class PostEffect : std::int32_t
	{
		kNone = 0,
		kPipboy = 1,
		kHUDGlass = 2,
		kHUDGlassWithMod = 3,
		kModMenu = 4,
		kModMenuHighlightAll = 5,
		kModMenuHighlightAllNoPulseOrScanLines = 6
	};
}
