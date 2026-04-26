#pragma once

#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTSingleton.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE
{
	class GameVM;
}

namespace RE::BSScript
{
	class IVirtualMachine;
}

namespace RE::GameScript::Internal
{
	class ScriptTimer;
}

namespace RE::GameScript
{
	class __declspec(novtable) TimerEventHandler
		: public BSTSingletonSDM<TimerEventHandler> // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::GameScript__TimerEventHandler };
		inline static constexpr auto VTABLE{ VTABLE::GameScript__TimerEventHandler };

		class WaitingTimer
		{
		public:
			// members
			std::uint32_t targetTime;					   // 00
			BSScript::StackID stackID;					   // 04
			BSTSmartPointer<BSScript::IVirtualMachine> vm; // 08
		};
		static_assert(sizeof(WaitingTimer) == 0x10);

		virtual ~TimerEventHandler(); // 00

		[[nodiscard]] static TimerEventHandler* GetSingleton()
		{
			static const auto SINGLETON = REL::Relocation<TimerEventHandler**>{ ID::GameScript::TimerEventHandler::Singleton };
			return *SINGLETON;
		}

		// members
		GameVM* gameVM;														 // 10
		BSTSmartPointer<BSScript::IVirtualMachine> vm;						 // 18
		mutable BSSpinLock waitTimerLock;									 // 20
		BSTArray<WaitingTimer> waitingTimers;								 // 28 - TODO: `BSTPriorityQueue<WaitingTimer, GreaterThanOperator<WaitingTimer>, BSTDefaultBinaryHeap>`
		BSTArray<WaitingTimer> menuModeWaitingTimers;						 // 40 - TODO: `BSTPriorityQueue<WaitingTimer, GreaterThanOperator<WaitingTimer>, BSTDefaultBinaryHeap>`
		BSTArray<WaitingTimer> gameModeWaitingTimers;						 // 58 - TODO: `BSTPriorityQueue<WaitingTimer, GreaterThanOperator<WaitingTimer>, BSTDefaultBinaryHeap>`
		mutable BSSpinLock timerLock;										 // 70
		BSTArray<BSTSmartPointer<Internal::ScriptTimer>> timerQueue;		 // 78 - TODO: `BSTPriorityQueue<BSTSmartPointer<Internal::ScriptTimer, BSTSmartPointerIntrusiveRefCount>, ScriptTimerCompare, BSTDefaultBinaryHeap>`
		BSTArray<BSTSmartPointer<Internal::ScriptTimer>> timerGameTimeQueue; // 90 - TODO: `BSTPriorityQueue<BSTSmartPointer<Internal::ScriptTimer, BSTSmartPointerIntrusiveRefCount>, ScriptTimerCompare, BSTDefaultBinaryHeap>`
	};
	static_assert(sizeof(TimerEventHandler) == 0xA8);
}
