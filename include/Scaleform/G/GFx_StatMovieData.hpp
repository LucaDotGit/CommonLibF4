#pragma once

#include "Scaleform/G/GFx_StatGroup.hpp"

namespace Scaleform::GFx
{
	enum StatMovieData : std::int32_t
	{
		kStatMD_Default = kStatGroup_GFxMovieData,

		kStatMD_Mem,
		kStatMD_CharDefs_Mem,
		kStatMD_ShapeData_Mem,
		kStatMD_Tags_Mem,
		kStatMD_Fonts_Mem,
		kStatMD_Images_Mem,
		kStatMD_ASBinaryData_Mem,
		kStatMD_Other_Mem,

		kStatMD_Time,
		kStatMD_Load_Tks,
		kStatMD_Bind_Tks
	};
}
