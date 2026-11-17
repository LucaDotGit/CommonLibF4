#pragma once

#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSScript
{
	class Stack;
}

namespace RE::BSScript::Internal
{
	class IFuncCallQuery;

	class FunctionMessage
	{
	public:
		enum class Type : std::int32_t
		{
			Invalid = 0,
			Call = 1,
			Return = 2
		};

		// members
		REX::Enum<Type, std::int32_t> type;		   // 0x00
		BSTSmartPointer<Stack> stack;			   // 0x08
		BSTSmartPointer<IFuncCallQuery> funcQuery; // 0x10
	};

	static_assert(sizeof(FunctionMessage) == 0x18);
}
