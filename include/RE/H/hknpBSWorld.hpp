#pragma once

#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/H/hkMultiMap.hpp"
#include "RE/H/hknpWorld.hpp"

namespace RE
{
	class hknpBodyId;

	class __declspec(novtable) hknpBSWorld
		: public hknpWorld // 000
	{
	public:
		inline static constexpr auto RTTI{ RTTI::hknpBSWorld };
		inline static constexpr auto VTABLE{ VTABLE::hknpBSWorld };

		~hknpBSWorld() override; // 00

		// members
		void* userData;													  // 6C0 - TODO
		mutable BSReadWriteLock worldLock;								  // 6C8
		BSTSet<hknpBodyId> activateBodyPostCollideSet;					  // 6E0
		mutable BSSpinLock activateBodyPostCollideLock;					  // 6F8
		hkMultiMap<std::uint32_t, std::uint32_t> constrainedBodyFromBody; // 700
	};
	static_assert(sizeof(hknpBSWorld) == 0x730);
}
