#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::GameScript::Internal
{
	class CustomEventTargets;

	class CustomEventRelay
		: public BSIntrusiveRefCounted // 00
	{
	public:
		// members
		BSTHashMap<BSFixedString, BSTSmartPointer<CustomEventTargets>> events; // 08
	};
	static_assert(sizeof(CustomEventRelay) == 0x38);
}
