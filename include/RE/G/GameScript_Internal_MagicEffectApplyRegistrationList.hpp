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
	class MagicEffectApplyFilterSet;

	class MagicEffectApplyRegistrationList
		: public BSIntrusiveRefCounted // 00
	{
	public:
		// members
		BSTHashMap<BSTSmartPointer<BSScript::Object>, BSTSmartPointer<MagicEffectApplyFilterSet>> registrations; // 08
	};
	static_assert(sizeof(MagicEffectApplyRegistrationList) == 0x38);
}
