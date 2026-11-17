#pragma once

#include "RE/N/NiColor.hpp"

namespace RE
{
	class ImageSpaceBaseData
	{
	public:
		class HDR // HNAM
		{
		public:
			// members
			REX::Float32 eyeAdaptSpeed;	  // 0x00
			REX::Float32 bloomBlurRadius; // 0x04
			REX::Float32 bloomThreshold;  // 0x08
			REX::Float32 bloomScale;	  // 0x0C
			REX::Float32 autoExposureMin; // 0x10
			REX::Float32 autoExposureMax; // 0x14
			REX::Float32 sunlightScale;	  // 0x18
			REX::Float32 skyScale;		  // 0x1C
			REX::Float32 middleGray;	  // 0x20
		};

		static_assert(sizeof(HDR) == 0x24);

		class Cinematic // 0xCNAM
		{
		public:
			// members
			REX::Float32 saturation; // 0x00
			REX::Float32 brightness; // 0x04
			REX::Float32 contrast;	 // 0x08
		};

		static_assert(sizeof(Cinematic) == 0x0C);

		class Tint // TNAM
		{
		public:
			// members
			REX::Float32 amount; // 0x00
			NiColor color;		 // 0x04
		};

		static_assert(sizeof(Tint) == 0x10);

		class DepthOfField // 0xDNAM
		{
		public:
			enum class SkyBlurRadius : std::int32_t
			{
				None = 0,
				Radius0 = 16'384,
				Radius1 = 16'672,
				Radius2 = 16'784,
				Radius3 = 16'848,
				Radius4 = 16'904,
				Radius5 = 16'936,
				Radius6 = 16'968,
				Radius7 = 17'000,
				NoSky_Radius0 = 16'576,
				NoSky_Radius1 = 16'736,
				NoSky_Radius2 = 16'816,
				NoSky_Radius3 = 16'880,
				NoSky_Radius4 = 16'920,
				NoSky_Radius5 = 16'952,
				NoSky_Radius6 = 16'984,
				NoSky_Radius7 = 17'016
			};

			// members
			REX::Float32 strength;								  // 0x00
			REX::Float32 distance;								  // 0x04
			REX::Float32 range;									  // 0x08
			REX::Float32 vignetteRadius;						  // 0x0C
			REX::Float32 vignetteStrength;						  // 0x10
			REX::Enum<SkyBlurRadius, std::int32_t> skyBlurRadius; // 0x14
		};

		static_assert(sizeof(DepthOfField) == 0x18);

		// members
		HDR hdrData{};			   // 0x00
		Cinematic cinematicData{}; // 0x24
		Tint tintData{};		   // 0x30
		DepthOfField dofData{};	   // 0x40
	};

	static_assert(sizeof(ImageSpaceBaseData) == 0x58);
}
