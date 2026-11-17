#pragma once

#include "RE/N/NiPoint2.hpp"

namespace RE::Interface3D
{
	class OldScreenEffectControl
	{
	public:
		// members
		NiPoint2 uvOffset;				 // 0x00
		REX::Float32 burstAmount;		 // 0x08
		REX::Float32 brightness;		 // 0x0C
		REX::Float32 vScanState;		 // 0x10
		REX::Float32 vScanRate;			 // 0x14
		REX::Float32 pulseIntensity;	 // 0x18
		REX::Float32 pulseRate;			 // 0x1C
		REX::Float32 flickerMinDelay;	 // 0x20
		REX::Float32 flickerMaxDelay;	 // 0x24
		REX::Float32 flickerMinDuration; // 0x28
		REX::Float32 flickerMaxDuration; // 0x2C
		REX::Float32 flickerFrequency;	 // 0x30
		REX::Float32 flickerBrightness;	 // 0x34
		REX::Float32 vScanDelayMin;		 // 0x38
		REX::Float32 vScanDelayMax;		 // 0x3C
		bool doScanlines;				 // 0x40
		REX::Float32 burstState;		 // 0x44
		REX::Float32 burstFadeRate;		 // 0x48
		REX::Float32 shudderState;		 // 0x4C
		REX::Float32 vScanDelay;		 // 0x50
		REX::Float32 flickerDelay;		 // 0x54
		REX::Float32 vHoldState;		 // 0x58
		REX::Float32 shudderScale;		 // 0x5C
		REX::Float32 shudderLength;		 // 0x60
		REX::Float32 vHoldRate;			 // 0x64
		REX::Float32 time;				 // 0x68
		bool flickering;				 // 0x6C
	};

	static_assert(sizeof(OldScreenEffectControl) == 0x70);
}
