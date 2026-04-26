#pragma once

#include "RE/B/BSPathingAvoidNode.hpp"

namespace RE
{
	class AvoidAreaStruct
	{
	public:
		// members
		BSPathingAvoidNode avoidNode;		// 00
		REX::Float32 timeExpire{ 0.0_f32 }; // 24
		TESObjectREFR* refObj{ nullptr };	// 28
		AvoidAreaStruct* next{ nullptr };	// 30
	};
	static_assert(sizeof(AvoidAreaStruct) == 0x38);
}
