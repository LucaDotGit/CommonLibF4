#pragma once

namespace RE
{
	class OBJ_TREE
	{
	public:
		// members
		REX::Float32 trunkFlexibility;	// 00
		REX::Float32 branchFlexibility; // 04
		REX::Float32 trunkAmplitude;	// 08
		REX::Float32 frontAmplitude;	// 0C
		REX::Float32 backAmplitude;		// 10
		REX::Float32 sideAmplitude;		// 14
		REX::Float32 frontFrequency;	// 18
		REX::Float32 backFrequency;		// 1C
		REX::Float32 sideFrequency;		// 20
		REX::Float32 leafFlexibility;	// 24
		REX::Float32 leafAmplitude;		// 28
		REX::Float32 leafFrequency;		// 2C
	};
	static_assert(sizeof(OBJ_TREE) == 0x30);
}
