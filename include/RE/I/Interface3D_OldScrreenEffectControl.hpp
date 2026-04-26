#pragma once

#include "RE/N/NiPoint.hpp"

namespace RE::Interface3D
{
	class OldScreenEffectControl
	{
	public:
		// members
		NiPoint2 uvOffset;				 // 00
		REX::Float32 burstAmount;		 // 08
		REX::Float32 brightness;		 // 0C
		REX::Float32 vScanState;		 // 10
		REX::Float32 vScanRate;			 // 14
		REX::Float32 pulseIntensity;	 // 18
		REX::Float32 pulseRate;			 // 1C
		REX::Float32 flickerMinDelay;	 // 20
		REX::Float32 flickerMaxDelay;	 // 24
		REX::Float32 flickerMinDuration; // 28
		REX::Float32 flickerMaxDuration; // 2C
		REX::Float32 flickerFrequency;	 // 30
		REX::Float32 flickerBrightness;	 // 34
		REX::Float32 vScanDelayMin;		 // 38
		REX::Float32 vScanDelayMax;		 // 3C
		bool doScanlines;				 // 40
		REX::Float32 burstState;		 // 44
		REX::Float32 burstFadeRate;		 // 48
		REX::Float32 shudderState;		 // 4C
		REX::Float32 vScanDelay;		 // 50
		REX::Float32 flickerDelay;		 // 54
		REX::Float32 vHoldState;		 // 58
		REX::Float32 shudderScale;		 // 5C
		REX::Float32 shudderLength;		 // 60
		REX::Float32 vHoldRate;			 // 64
		REX::Float32 time;				 // 68
		bool flickering;				 // 6C
	};
	static_assert(sizeof(OldScreenEffectControl) == 0x70);
}
