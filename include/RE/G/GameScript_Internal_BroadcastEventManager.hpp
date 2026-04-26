#pragma once

#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSScript
{
	class Object;
}

namespace RE::GameScript::Internal
{
	class BroadcastEventManager
	{
	public:
		// members
		mutable BSSpinLock eventLock;						// 08
		BSTArray<BSTSmartPointer<BSScript::Object>> events; // 10
	};
	static_assert(sizeof(BroadcastEventManager) == 0x20);
}
