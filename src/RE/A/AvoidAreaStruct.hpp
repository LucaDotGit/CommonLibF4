#pragma once

#include "RE/B/BSPathingAvoidNode.hpp"

namespace RE
{
	class AvoidAreaStruct
	{
	public:
		// members
		BSPathingAvoidNode avoidNode;							 // 0x00
		REX::Float32 timeExpire{static_cast<REX::Float32>(0.0)}; // 0x24
		TESObjectREFR* refObj{nullptr};							 // 0x28
		AvoidAreaStruct* next{nullptr};							 // 0x30
	};

	static_assert(sizeof(AvoidAreaStruct) == 0x38);
}
