#pragma once

#include "RE/I/ImageSpaceBaseData.hpp"
#include "RE/I/ImageSpaceModData.hpp"

namespace RE
{
	class ImageSpaceData
	{
	public:
		// members
		ImageSpaceBaseData baseData;	// 00
		ImageSpaceModData modData;		// 58
		REX::Float32 highestTintAmount; // A8
		REX::Float32 highestFadeAmount; // AC
	};
	static_assert(sizeof(ImageSpaceData) == 0xB0);
}
