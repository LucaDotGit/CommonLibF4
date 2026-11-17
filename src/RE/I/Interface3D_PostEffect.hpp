#pragma once

namespace RE::Interface3D
{
	enum class PostEffect : std::int32_t
	{
		None = 0,
		Pipboy = 1,
		HUDGlass = 2,
		HUDGlassWithMod = 3,
		ModMenu = 4,
		ModMenuHighlightAll = 5,
		ModMenuHighlightAllNoPulseOrScanLines = 6
	};
}
