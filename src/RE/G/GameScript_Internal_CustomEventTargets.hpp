#pragma once

#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSScript
{
	class Object;
}

namespace RE::GameScript::Internal
{
	class CustomEventTargets : public BSIntrusiveRefCounted // 0x00
	{
	public:
		// members
		BSTSet<BSTSmartPointer<BSScript::Object>> targets; // 0x08
	};

	static_assert(sizeof(CustomEventTargets) == 0x38);
}
