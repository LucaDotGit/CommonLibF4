#pragma once

#include "RE/N/NiPoint.hpp"

namespace RE
{
	class MovementCorrectionData
	{
	public:
		// members
		NiPoint3 targetLocation;				// 00
		NiPoint3 targetRotation;				// 0C
		NiPoint3 translationCorrection;			// 18
		NiPoint3 rotationCorrection;			// 24
		NiPoint3 startVelocity;					// 30
		NiPoint3 endVelocity;					// 3C
		NiPoint3 startRotSpeed;					// 48
		NiPoint3 endRotSpeed;					// 54
		REX::Float32 correctionStartTime;		// 60
		REX::Float32 correctionEndTime;			// 64
		REX::Float32 correctionStartRotateTime; // 68
		REX::Float32 correctionEndRotateTime;	// 6C
		REX::Float32 totalTime;					// 70
	};
	static_assert(sizeof(MovementCorrectionData) == 0x74);
}
