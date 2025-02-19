#pragma once

#include "RE/Bethesda/BSScript/Stack.hpp"

namespace RE::BSScript
{
	class Stack;
}

namespace RE::BSScript::Internal
{
	class RawFuncCallQuery;

	struct SuspendedStack
	{
	public:
		// members
		BSTSmartPointer<Stack> stack;				   // 00
		BSTSmartPointer<IFuncCallQuery> funcCallQuery; // 08
	};
	static_assert(sizeof(SuspendedStack) == 0x10);
}
