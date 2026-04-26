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
			kInvalid = 0,
			kCall = 1,
			kReturn = 2
		};

		// members
		REX::Enum<Type, std::int32_t> type;		   // 00
		BSTSmartPointer<Stack> stack;			   // 08
		BSTSmartPointer<IFuncCallQuery> funcQuery; // 10
	};
	static_assert(sizeof(FunctionMessage) == 0x18);
}
