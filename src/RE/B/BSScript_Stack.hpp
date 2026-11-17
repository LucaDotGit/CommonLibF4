#pragma once

#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSScript_Variable.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSScript::Internal
{
	class CodeTasklet;
}

namespace RE::BSScript
{
	enum class FreezeState : std::int32_t;

	class IMemoryPagePolicy;
	class IProfilePolicy;
	class IStackCallbackFunctor;
	class MemoryPage;
	class Object;
	class StackFrame;

	class Stack : public BSIntrusiveRefCounted // 0x00
	{
	public:
		enum class StackType : std::int32_t
		{
		};

		enum class State : std::int32_t
		{
			Running = 0,
			Finished = 1,
			WaitingOnMemory = 2,
			WaitingOnLatentFunction = 3,
			WaitingInOtherStackForCall = 4,
			WaitingInOtherStackForReturn = 5,
			WaitingInOtherStackForReturnNoPop = 6,
			RetryReturnNoPop = 7,
			RetryCall = 8
		};

		class MemoryPageData
		{
		public:
			// members
			BSTAutoPointer<MemoryPage> page;	  // 0x00
			std::uint32_t availableMemoryInBytes; // 0x08
		};

		static_assert(sizeof(MemoryPageData) == 0x10);

		[[nodiscard]]
		auto GetPageForFrame(const StackFrame* a_frame) const -> std::uint32_t
		{
			using FuncType = decltype(&Stack::GetPageForFrame);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BSScript::Internal::Stack::GetPageForFrame);
			return std::invoke(FUNC, this, a_frame);
		}

		[[nodiscard]]
		auto GetStackFrameVariable(const StackFrame* a_frame, std::uint32_t a_index, std::uint32_t a_pageHint) const
			-> const Variable&
		{
			using FuncType = const Variable& (Stack::*)(const StackFrame*, std::uint32_t, std::uint32_t) const;
			static const auto FUNC = REL::Relocation<FuncType>(ID::BSScript::Internal::Stack::GetStackFrameVariable);
			return std::invoke(FUNC, this, a_frame, a_index, a_pageHint);
		}

		// members
		IMemoryPagePolicy* policy;							  // 0x08
		IProfilePolicy* profilePolicy;						  // 0x10
		BSTSmallArray<MemoryPageData, 3> pages;				  // 0x18
		std::uint32_t frames;								  // 0x58
		StackFrame* topFrame;								  // 0x60
		REX::Enum<State, std::int32_t> state;				  // 0x68
		REX::Enum<FreezeState, std::int32_t> freezeState;	  // 0x6C
		Variable returnValue;								  // 0x70
		StackID stackID;									  // 0x80
		REX::Enum<StackType, std::int32_t> stackType;		  // 0x84
		BSTSmartPointer<Internal::CodeTasklet> owningTasklet; // 0x88
		BSTSmartPointer<IStackCallbackFunctor> callback;	  // 0x90
		BSTSmartPointer<Object> objectToUnbind;				  // 0x98
		BSTSmartPointer<Stack> nextStack;					  // 0xA0
	};

	static_assert(sizeof(Stack) == 0xA8);
}
