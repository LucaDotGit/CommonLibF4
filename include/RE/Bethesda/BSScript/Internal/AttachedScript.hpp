#pragma once

#include "RE/Bethesda/BSScript/Object.hpp"
#include "RE/Bethesda/BSTPointerAndFlags.hpp"

namespace RE::BSScript::Internal
{
	class AttachedScript
		: public BSTPointerAndFlags<BSTSmartPointer<Object>, 1> // 00
	{
	};
	static_assert(sizeof(AttachedScript) == 0x8);
}
