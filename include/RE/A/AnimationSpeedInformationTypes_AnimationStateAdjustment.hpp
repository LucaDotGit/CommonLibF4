#pragma once

#include "RE/B/BSFixedString.hpp"

namespace RE::AnimationSpeedInformationTypes
{
	class AnimationStateAdjustment
	{
	public:
		// members
		BSFixedString adjustmentName; // 00
		union
		{
			std::int32_t int32;
			REX::Float32 float32;
		} adjustmentVariable; // 08
		bool useFloat;		  // 0C
		bool isVariable;	  // 0D
	};
	static_assert(sizeof(AnimationStateAdjustment) == 0x10);
}
