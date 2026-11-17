#pragma once

#include "RE/B/BSFixedString.hpp"

namespace RE::AnimationSpeedInformationTypes
{
	class AnimationStateAdjustment
	{
	public:
		// members
		BSFixedString adjustmentName; // 0x00

		union
		{
		public:
			std::int32_t int32;
			REX::Float32 float32;
		} adjustmentVariable; // 0x08

		bool useFloat;	 // 0x0C
		bool isVariable; // 0x0D
	};

	static_assert(sizeof(AnimationStateAdjustment) == 0x10);
}
