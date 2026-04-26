#pragma once

namespace RE
{
	class ImageSpaceBaseData
	{
	public:
		class HDR // HNAM
		{
		public:
			// members
			REX::Float32 eyeAdaptSpeed;			// 00
			REX::Float32 bloomBlurRadius;		// 04
			REX::Float32 bloomThreshold;		// 08
			REX::Float32 bloomScale;			// 0C
			REX::Float32 receiveBloomThreshold; // 10
			REX::Float32 white;					// 14
			REX::Float32 sunlightScale;			// 18
			REX::Float32 skyScale;				// 1C
			REX::Float32 eyeAdaptStrength;		// 20
		};
		static_assert(sizeof(HDR) == 0x24);

		class Cinematic // CNAM
		{
		public:
			// members
			REX::Float32 saturation; // 00
			REX::Float32 brightness; // 04
			REX::Float32 contrast;	 // 08
		};
		static_assert(sizeof(Cinematic) == 0x0C);

		class Tint // TNAM
		{
		public:
			class ColorF
			{
			public:
				// members
				REX::Float32 red;	// 00
				REX::Float32 green; // 04
				REX::Float32 blue;	// 08
			};
			static_assert(sizeof(ColorF) == 0x0C);

			// members
			REX::Float32 amount; // 00
			ColorF color;		 // 04
		};
		static_assert(sizeof(Tint) == 0x10);

		class DepthOfField // DNAM
		{
		public:
			// members
			REX::Float32 strength;		   // 00
			REX::Float32 distance;		   // 04
			REX::Float32 range;			   // 08
			REX::Float32 vignetteRadius;   // 0C
			REX::Float32 vignetteStrength; // 10
			REX::Float32 mode;			   // 14
		};
		static_assert(sizeof(DepthOfField) == 0x18);

		// members
		HDR hdrData;			 // 00
		Cinematic cinematicData; // 24
		Tint tintData;			 // 30
		DepthOfField dofData;	 // 40
	};
	static_assert(sizeof(ImageSpaceBaseData) == 0x58);
}
