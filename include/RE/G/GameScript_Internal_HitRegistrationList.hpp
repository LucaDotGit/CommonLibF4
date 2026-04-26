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
	class HitFilterSet;

	class HitRegistrationList
		: public BSIntrusiveRefCounted // 00
	{
	public:
		// members
		BSTHashMap<BSTSmartPointer<BSScript::Object>, BSTSmartPointer<HitFilterSet>> registrations; // 08
	};
	static_assert(sizeof(HitRegistrationList) == 0x38);
}
