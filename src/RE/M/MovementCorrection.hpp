#pragma once

#include "RE/N/NiPoint3.hpp"

namespace RE
{
	class MovementCorrection
	{
	public:
		enum class CORRECTION_TYPE : std::int32_t
		{
			None = 0,
			TargetPosVelAndIdle = 1,
			FixedDelta = 2,
			UpdateToFaceTarget = 3
		};

		// members
		REX::Enum<CORRECTION_TYPE, std::int32_t> correctionType; // 0x00
		std::array<NiPoint3, 10> parameters;					 // 0x04
		REX::Float32 correctionStartTime;						 // 0x7C
		REX::Float32 correctionEndTime;							 // 0x80
		REX::Float32 correctionStartRotateTime;					 // 0x84
		REX::Float32 correctionEndRotateTime;					 // 0x88
		REX::Float32 totalTime;									 // 0x8C
	};

	static_assert(sizeof(MovementCorrection) == 0x90);
}
