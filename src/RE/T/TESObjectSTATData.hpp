#pragma once

namespace RE
{
	class TESObjectSTATData
	{
	public:
		// members
		BGSMaterialObject* materialObj;		 // 0x00
		REX::Float32 materialThresholdAngle; // 0x08
		REX::Float32 leafAmplitude;			 // 0x0C
		REX::Float32 leafFrequency;			 // 0x10
	};

	static_assert(sizeof(TESObjectSTATData) == 0x18);
}
