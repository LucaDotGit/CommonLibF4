#pragma once

#include "RE/B/BSScript_Object.hpp"
#include "RE/B/BSTPointerAndFlags.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSScript::Internal
{
	class AttachedScript
		: public BSTPointerAndFlags<BSTSmartPointer<Object>, 1> // 00
	{
	};
	static_assert(sizeof(AttachedScript) == 0x08);
}
