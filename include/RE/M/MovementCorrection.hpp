#pragma once

#include "RE/N/NiPoint.hpp"

namespace RE
{
	class MovementCorrection
	{
	public:
		enum class CORRECTION_TYPE : std::int32_t
		{
			kNone = 0,
			kTargetPosVelAndIdle = 1,
			kFixedDelta = 2,
			kUpdateToFaceTarget = 3
		};

		// members
		REX::Enum<CORRECTION_TYPE, std::int32_t> correctionType; // 00
		std::array<NiPoint3, 10> parameters;					 // 04
		REX::Float32 correctionStartTime;						 // 7C
		REX::Float32 correctionEndTime;							 // 80
		REX::Float32 correctionStartRotateTime;					 // 84
		REX::Float32 correctionEndRotateTime;					 // 88
		REX::Float32 totalTime;									 // 8C
	};
	static_assert(sizeof(MovementCorrection) == 0x90);
}
