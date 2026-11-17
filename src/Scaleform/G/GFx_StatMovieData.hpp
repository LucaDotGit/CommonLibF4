#pragma once

#include "Scaleform/G/GFx_StatGroup.hpp"

namespace Scaleform::GFx
{
	enum StatMovieData : std::int32_t
	{
		StatMD_Default = StatGroup_GFxMovieData,

		StatMD_Mem,
		StatMD_CharDefs_Mem,
		StatMD_ShapeData_Mem,
		StatMD_Tags_Mem,
		StatMD_Fonts_Mem,
		StatMD_Images_Mem,
		StatMD_ASBinaryData_Mem,
		StatMD_Other_Mem,

		StatMD_Time,
		StatMD_Load_Tks,
		StatMD_Bind_Tks
	};
}
