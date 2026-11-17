#pragma once

#include "RE/I/ImageSpaceBaseData.hpp"

namespace RE
{
	class ImageSpaceModData
	{
	public:
		// members
		REX::Float32 fadeAmount;					   // 0x00
		REX::Float32 fadeR;							   // 0x04
		REX::Float32 fadeG;							   // 0x08
		REX::Float32 fadeB;							   // 0x0C
		REX::Float32 blurRadius;					   // 0x10
		REX::Float32 doubleVisionStrength;			   // 0x14
		REX::Float32 radiusBlurStrength;			   // 0x18
		REX::Float32 radiusBlurRampUp;				   // 0x1C
		REX::Float32 radiusBlurStart;				   // 0x20
		REX::Float32 radiusBlurRampDown;			   // 0x24
		REX::Float32 radiusBlurDownStart;			   // 0x28
		REX::Float32 radiusBlurCenterX;				   // 0x2C
		REX::Float32 radiusBlurCenterY;				   // 0x30
		ImageSpaceBaseData::DepthOfField depthOfField; // 0x34
		REX::Float32 motionBlurStrength;			   // 0x4C
	};

	static_assert(sizeof(ImageSpaceModData) == 0x50);
}
