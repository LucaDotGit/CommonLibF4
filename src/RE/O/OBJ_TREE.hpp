#pragma once

namespace RE
{
	class OBJ_TREE
	{
	public:
		// members
		REX::Float32 trunkFlexibility;	// 0x00
		REX::Float32 branchFlexibility; // 0x04
		REX::Float32 trunkAmplitude;	// 0x08
		REX::Float32 frontAmplitude;	// 0x0C
		REX::Float32 backAmplitude;		// 0x10
		REX::Float32 sideAmplitude;		// 0x14
		REX::Float32 frontFrequency;	// 0x18
		REX::Float32 backFrequency;		// 0x1C
		REX::Float32 sideFrequency;		// 0x20
		REX::Float32 leafFlexibility;	// 0x24
		REX::Float32 leafAmplitude;		// 0x28
		REX::Float32 leafFrequency;		// 0x2C
	};

	static_assert(sizeof(OBJ_TREE) == 0x30);
}
