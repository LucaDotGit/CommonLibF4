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
	class EventRegistrationObjectList
		: public BSIntrusiveRefCounted // 00
	{
	public:
		// members
		BSTSet<BSTSmartPointer<BSScript::Object>> registrations; // 08
	};
	static_assert(sizeof(EventRegistrationObjectList) == 0x38);
}
