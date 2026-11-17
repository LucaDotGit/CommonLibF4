#pragma once

#include "RE/N/NiPoint2.hpp"
#include "RE/N/NiRect.hpp"

namespace RE::BSGraphics
{
	class ViewData
	{
	public:
		// members
		NiRectF viewPort;								  // 0x000
		NiPoint2 viewDepthRange;						  // 0x010
		__m128 viewUp;									  // 0x020
		__m128 viewRight;								  // 0x030
		__m128 viewDir;									  // 0x040
		std::array<__m128, 4> viewMat;					  // 0x050
		std::array<__m128, 4> projMat;					  // 0x090
		std::array<__m128, 4> viewProjMat;				  // 0x0D0
		std::array<__m128, 4> viewProjUnjittered;		  // 0x110
		std::array<__m128, 4> currentViewProjUnjittered;  // 0x150
		std::array<__m128, 4> previousViewProjUnjittered; // 0x190
		std::array<__m128, 4> inv1stPersonProjMat;		  // 0x1D0
	};

	static_assert(sizeof(ViewData) == 0x210);
}
