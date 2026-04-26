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

	class Stack
		: public BSIntrusiveRefCounted // 00
	{
	public:
		enum class StackType : std::int32_t
		{
		};

		enum class State : std::int32_t
		{
			kRunning = 0,
			kFinished = 1,
			kWaitingOnMemory = 2,
			kWaitingOnLatentFunction = 3,
			kWaitingInOtherStackForCall = 4,
			kWaitingInOtherStackForReturn = 5,
			kWaitingInOtherStackForReturnNoPop = 6,
			kRetryReturnNoPop = 7,
			kRetryCall = 8
		};

		class MemoryPageData
		{
		public:
			// members
			BSTAutoPointer<MemoryPage> page;	  // 00
			std::uint32_t availableMemoryInBytes; // 08
		};
		static_assert(sizeof(MemoryPageData) == 0x10);

		[[nodiscard]] std::uint32_t GetPageForFrame(const StackFrame* a_frame) const
		{
			using FuncType = decltype(&Stack::GetPageForFrame);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BSScript::Internal::Stack::GetPageForFrame };
			return std::invoke(FUNC, this, a_frame);
		}

		[[nodiscard]] Variable& GetStackFrameVariable(const StackFrame* a_frame, std::uint32_t a_index, std::uint32_t a_pageHint)
		{
			using FuncType = Variable& (Stack::*)(const StackFrame*, std::uint32_t, std::uint32_t);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BSScript::Internal::Stack::GetStackFrameVariable };
			return std::invoke(FUNC, this, a_frame, a_index, a_pageHint);
		}

		[[nodiscard]] const Variable& GetStackFrameVariable(const StackFrame* a_frame, std::uint32_t a_index, std::uint32_t a_pageHint) const
		{
			using FuncType = const Variable& (Stack::*)(const StackFrame*, std::uint32_t, std::uint32_t) const;
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BSScript::Internal::Stack::GetStackFrameVariable };
			return std::invoke(FUNC, this, a_frame, a_index, a_pageHint);
		}

		// members
		IMemoryPagePolicy* policy;							  // 08
		IProfilePolicy* profilePolicy;						  // 10
		BSTSmallArray<MemoryPageData, 3> pages;				  // 18
		std::uint32_t frames;								  // 58
		StackFrame* topFrame;								  // 60
		REX::Enum<State, std::int32_t> state;				  // 68
		REX::Enum<FreezeState, std::int32_t> freezeState;	  // 6C
		Variable returnValue;								  // 70
		StackID stackID;									  // 80
		REX::Enum<StackType, std::int32_t> stackType;		  // 84
		BSTSmartPointer<Internal::CodeTasklet> owningTasklet; // 88
		BSTSmartPointer<IStackCallbackFunctor> callback;	  // 90
		BSTSmartPointer<Object> objectToUnbind;				  // 98
		BSTSmartPointer<Stack> nextStack;					  // A0
	};
	static_assert(sizeof(Stack) == 0xA8);
}
