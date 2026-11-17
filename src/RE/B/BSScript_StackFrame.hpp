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
		[[nodiscard]]
		auto GetPageForFrame() const -> std::uint32_t;
		[[nodiscard]]
		auto GetSelfObject() const -> BSTSmartPointer<Object>;
		[[nodiscard]]
		auto GetSelfObjectHandle() const -> ObjectHandle;
		[[nodiscard]]
		auto GetStackFrameVariable(std::uint32_t a_index, std::uint32_t a_pageHint) const -> const Variable*;

		// members
		Stack* parentStack;								  // 0x00
		StackFrame* previousFrame;						  // 0x08
		BSTSmartPointer<IFunction> owningFunction;		  // 0x10
		BSTSmartPointer<ObjectTypeInfo> owningObjectType; // 0x18
		std::uint32_t ip;								  // 0x20
		Variable self;									  // 0x28
		std::uint32_t size;								  // 0x38
		bool instructionsValid;							  // 0x3C
	};

	static_assert(sizeof(StackFrame) == 0x40);
}
