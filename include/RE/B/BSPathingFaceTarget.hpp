#pragma once

#include "RE/N/NiPoint.hpp"

namespace RE
{
	class BSPathingFaceTarget
	{
	public:
		enum class FACE_TARGET_TYPE : std::int32_t
		{
			kNone = 0,
			kAngle = 1,
			kPoint = 2,
			kPointHeading = 3
		};

		// members
		REX::Enum<FACE_TARGET_TYPE, std::int32_t> type; // 00
		NiPoint3 point;									// 04
		REX::Float32 angle;								// 10
		REX::Float32 angleToleranceCCW;					// 14
		REX::Float32 angleToleranceCW;					// 18
	};
	static_assert(sizeof(BSPathingFaceTarget) == 0x1C);
}
