#pragma once

namespace RE
{
	class GrassParam
	{
	public:
		// members
		const char* geomFilename;	  // 00
		std::uint32_t grassID;		  // 08
		REX::Float32 positionRange;	  // 0C
		REX::Float32 heightRange;	  // 10
		REX::Float32 colorRange;	  // 14
		REX::Float32 waveOffsetRange; // 18
		REX::Float32 wavePeriod;	  // 1C
		bool vertexLighting;		  // 20
		bool uniformScaling;		  // 21
		bool fitToSlope;			  // 22
		bool wind;					  // 23
	};
	static_assert(sizeof(GrassParam) == 0x28);
}
