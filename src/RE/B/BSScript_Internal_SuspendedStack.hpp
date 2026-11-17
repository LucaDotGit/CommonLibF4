#pragma once

#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSScript
{
	class Stack;
}

namespace RE::BSScript::Internal
{
	class IFuncCallQuery;

	class SuspendedStack
	{
	public:
		// members
		BSTSmartPointer<Stack> stack;				   // 0x00
		BSTSmartPointer<IFuncCallQuery> funcCallQuery; // 0x08
	};

	static_assert(sizeof(SuspendedStack) == 0x10);
}
