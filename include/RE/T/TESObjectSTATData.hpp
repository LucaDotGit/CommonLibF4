#pragma once

namespace RE
{
	class TESObjectSTATData
	{
	public:
		// members
		BGSMaterialObject* materialObj;		 // 00
		REX::Float32 materialThresholdAngle; // 08
		REX::Float32 leafAmplitude;			 // 0C
		REX::Float32 leafFrequency;			 // 10
	};
	static_assert(sizeof(TESObjectSTATData) == 0x18);
}
