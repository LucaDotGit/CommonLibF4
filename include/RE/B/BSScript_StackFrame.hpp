#pragma once

#include "RE/B/BSScript_Variable.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSScript
{
	class IFunction;
	class Object;
	class ObjectTypeInfo;
	class Stack;

	class StackFrame
	{
	public:
		[[nodiscard]] std::uint32_t GetPageForFrame() const;
		[[nodiscard]] BSTSmartPointer<Object> GetSelfObject() const;
		[[nodiscard]] ObjectHandle GetSelfObjectHandle() const;
		[[nodiscard]] Variable* GetStackFrameVariable(std::uint32_t a_index, std::uint32_t a_pageHint) const;

		// members
		Stack* parentStack;								  // 00
		StackFrame* previousFrame;						  // 08
		BSTSmartPointer<IFunction> owningFunction;		  // 10
		BSTSmartPointer<ObjectTypeInfo> owningObjectType; // 18
		std::uint32_t ip;								  // 20
		Variable self;									  // 28
		std::uint32_t size;								  // 38
		bool instructionsValid;							  // 3C
	};
	static_assert(sizeof(StackFrame) == 0x40);
}
