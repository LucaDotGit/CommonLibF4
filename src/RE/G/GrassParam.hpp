#pragma once

namespace RE
{
	class GrassParam
	{
	public:
		// members
		const char* geomFilename;	  // 0x00
		std::uint32_t grassID;		  // 0x08
		REX::Float32 positionRange;	  // 0x0C
		REX::Float32 heightRange;	  // 0x10
		REX::Float32 colorRange;	  // 0x14
		REX::Float32 waveOffsetRange; // 0x18
		REX::Float32 wavePeriod;	  // 0x1C
		bool vertexLighting;		  // 0x20
		bool uniformScaling;		  // 0x21
		bool fitToSlope;			  // 0x22
		bool wind;					  // 0x23
	};

	static_assert(sizeof(GrassParam) == 0x28);
}
