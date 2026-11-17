#pragma once

#include "Scaleform/G/GFx_StatGroup.hpp"

namespace Scaleform::GFx
{
	enum StatFontCache : std::int32_t
	{
		StatFC_Default = StatGroup_GFxFontCache,

		StatFC_Mem,
		StatFC_Batch_Mem,
		StatFC_GlyphCache_Mem,
		StatFC_Other_Mem
	};
}
