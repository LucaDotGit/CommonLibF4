#pragma once

#include "RE/I/ImageSpaceBaseData.hpp"
#include "RE/I/ImageSpaceModData.hpp"

namespace RE
{
	class ImageSpaceData
	{
	public:
		// members
		ImageSpaceBaseData baseData;	// 0x00
		ImageSpaceModData modData;		// 0x58
		REX::Float32 highestTintAmount; // 0xA8
		REX::Float32 highestFadeAmount; // 0xAC
	};

	static_assert(sizeof(ImageSpaceData) == 0xB0);
}
