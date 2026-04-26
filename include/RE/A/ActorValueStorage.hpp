#pragma once

#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTTuple.hpp"
#include "RE/M/Modifiers.hpp"

namespace RE
{
	class ActorValueStorage
	{
	public:
		// members
		BSTArray<BSTPair<std::uint32_t, REX::Float32>> baseValues; // 00
		BSTArray<BSTPair<std::uint32_t, Modifiers>> modifiers;	   // 18
		mutable BSReadWriteLock avLock;							   // 30
	};
	static_assert(sizeof(ActorValueStorage) == 0x38);
}
