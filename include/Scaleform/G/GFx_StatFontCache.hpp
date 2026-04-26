#pragma once

#include "Scaleform/G/GFx_StatGroup.hpp"

namespace Scaleform::GFx
{
	enum StatFontCache : std::int32_t
	{
		kStatFC_Default = kStatGroup_GFxFontCache,

		kStatFC_Mem,
		kStatFC_Batch_Mem,
		kStatFC_GlyphCache_Mem,
		kStatFC_Other_Mem
	};
}
