#pragma once

#include "RE/N/NiPoint.hpp"
#include "RE/N/NiRect.hpp"

namespace RE::BSGraphics
{
	class ViewData
	{
	public:
		// members
		NiRect<REX::Float32> viewPort;					  // 000
		NiPoint2 viewDepthRange;						  // 010
		__m128 viewUp;									  // 020
		__m128 viewRight;								  // 030
		__m128 viewDir;									  // 040
		std::array<__m128, 4> viewMat;					  // 050
		std::array<__m128, 4> projMat;					  // 090
		std::array<__m128, 4> viewProjMat;				  // 0D0
		std::array<__m128, 4> viewProjUnjittered;		  // 110
		std::array<__m128, 4> currentViewProjUnjittered;  // 150
		std::array<__m128, 4> previousViewProjUnjittered; // 190
		std::array<__m128, 4> inv1stPersonProjMat;		  // 1D0
	};
	static_assert(sizeof(ViewData) == 0x210);
}
