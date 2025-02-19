#pragma once

#include "RE/Bethesda/BSScript/IMemoryPagePolicy.hpp"
#include "RE/Bethesda/BSScript/IProfilePolicy.hpp"
#include "RE/Bethesda/BSScript/IStackCallbackFunctor.hpp"
#include "RE/Bethesda/BSScript/Object.hpp"
#include "RE/Bethesda/BSScript/StackFrame.hpp"
#include "RE/Bethesda/BSScript/Variable.hpp"
#include "RE/Bethesda/BSTSmartPointer.hpp"

namespace RE::BSScript
{
	class IProfilePolicy;
	class IStackCallbackFunctor;
	class MemoryPage; // stub
	class Object;
	class StackFrame;
	class Variable;

	struct IMemoryPagePolicy;

	namespace Internal
	{
		class CodeTasklet;
	}

	namespace UnlinkedTypes
	{
		struct Object; // stub
	}

	class Stack
		: public BSIntrusiveRefCounted // 00
	{
	public:
		enum class StackType;

		enum class FreezeState
		{
			kUnfrozen,
			kFreezing,
			kFrozen
		};

		enum class State
		{
			kRunning,
			kFinished,
			kWaitingOnMemory,
			kWaitingOnLatentFunction,
			kWaitingInOtherStackForCall,
			kWaitingInOtherStackForReturn,
			kWaitingInOtherStackForReturnNoPop,
			kRetryReturnNoPop,
			kRetryCall
		};

		struct MemoryPageData
		{
		public:
			// members
			BSTAutoPointer<MemoryPage> page;	  // 00
			std::uint32_t availableMemoryInBytes; // 08
		};
		static_assert(sizeof(MemoryPageData) == 0x10);

		[[nodiscard]] std::uint32_t GetPageForFrame(const StackFrame* a_frame) const
		{
			using func_t = decltype(&Stack::GetPageForFrame);
			static REL::Relocation<func_t> func{ REL::ID(1429302) };
			return func(this, a_frame);
		}

		[[nodiscard]] Variable& GetStackFrameVariable(const StackFrame* a_frame, std::uint32_t a_index, std::uint32_t a_pageHint)
		{
			using func_t = decltype(&Stack::GetStackFrameVariable);
			static REL::Relocation<func_t> func{ REL::RelocationID(897539, 2314681) };
			return func(this, a_frame, a_index, a_pageHint);
		}

		// members
		IMemoryPagePolicy* policy;							  // 08
		IProfilePolicy* profilePolicy;						  // 10
		BSTSmallArray<MemoryPageData, 3> pages;				  // 18
		std::uint32_t frames;								  // 58
		StackFrame* top;									  // 60
		REX::Enum<State, std::uint32_t> state;				  // 68
		REX::Enum<FreezeState, std::uint32_t> freezeState;	  // 6C
		Variable returnValue;								  // 70
		VMStackID stackID;									  // 80
		REX::Enum<StackType, std::int32_t> stackType;		  // 84
		BSTSmartPointer<Internal::CodeTasklet> owningTasklet; // 88
		BSTSmartPointer<IStackCallbackFunctor> callback;	  // 90
		BSTSmartPointer<Object> objToUnbind;				  // 98
		BSTSmartPointer<Stack> nextStack;					  // A0
	};
	static_assert(sizeof(Stack) == 0xA8);
}
