#pragma once

#include "RE/N/NiPoint3.hpp"

namespace RE
{
	class BSPathingFaceTarget
	{
	public:
		enum class FACE_TARGET_TYPE : std::int32_t
		{
			None = 0,
			Angle = 1,
			Point = 2,
			PointHeading = 3
		};

		// members
		REX::Enum<FACE_TARGET_TYPE, std::int32_t> type; // 0x00
		NiPoint3 point;									// 0x04
		REX::Float32 angle;								// 0x10
		REX::Float32 angleToleranceCCW;					// 0x14
		REX::Float32 angleToleranceCW;					// 0x18
	};

	static_assert(sizeof(BSPathingFaceTarget) == 0x1C);
}
