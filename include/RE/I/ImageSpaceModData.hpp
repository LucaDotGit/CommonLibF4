#pragma once

#include "RE/I/ImageSpaceBaseData.hpp"

namespace RE
{
	class ImageSpaceModData
	{
	public:
		// members
		REX::Float32 fadeAmount;					   // 00
		REX::Float32 fadeR;							   // 04
		REX::Float32 fadeG;							   // 08
		REX::Float32 fadeB;							   // 0C
		REX::Float32 blurRadius;					   // 10
		REX::Float32 doubleVisionStrength;			   // 14
		REX::Float32 radiusBlurStrength;			   // 18
		REX::Float32 radiusBlurRampUp;				   // 1C
		REX::Float32 radiusBlurStart;				   // 20
		REX::Float32 radiusBlurRampDown;			   // 24
		REX::Float32 radiusBlurDownStart;			   // 28
		REX::Float32 radiusBlurCenterX;				   // 2C
		REX::Float32 radiusBlurCenterY;				   // 30
		ImageSpaceBaseData::DepthOfField depthOfField; // 34
		REX::Float32 motionBlurStrength;			   // 4C
	};
	static_assert(sizeof(ImageSpaceModData) == 0x50);
}
