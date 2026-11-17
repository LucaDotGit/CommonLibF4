#pragma once

#include "RE/N/NiPoint3.hpp"

namespace RE
{
	class MovementCorrectionData
	{
	public:
		// members
		NiPoint3 targetLocation;				// 0x00
		NiPoint3 targetRotation;				// 0x0C
		NiPoint3 translationCorrection;			// 0x18
		NiPoint3 rotationCorrection;			// 0x24
		NiPoint3 startVelocity;					// 0x30
		NiPoint3 endVelocity;					// 0x3C
		NiPoint3 startRotSpeed;					// 0x48
		NiPoint3 endRotSpeed;					// 0x54
		REX::Float32 correctionStartTime;		// 0x60
		REX::Float32 correctionEndTime;			// 0x64
		REX::Float32 correctionStartRotateTime; // 0x68
		REX::Float32 correctionEndRotateTime;	// 0x6C
		REX::Float32 totalTime;					// 0x70
	};

	static_assert(sizeof(MovementCorrectionData) == 0x74);
}
