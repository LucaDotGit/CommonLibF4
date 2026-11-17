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
	class __declspec(novtable) TimerEventHandler : public BSTSingletonSDM<TimerEventHandler> // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::GameScript__TimerEventHandler;
		inline static constexpr const auto& VTABLE = VTABLE::GameScript__TimerEventHandler;

		class WaitingTimer
		{
		public:
			// members
			std::uint32_t targetTime;					   // 0x00
			BSScript::StackID stackID;					   // 0x04
			BSTSmartPointer<BSScript::IVirtualMachine> vm; // 0x08
		};

		static_assert(sizeof(WaitingTimer) == 0x10);

		virtual ~TimerEventHandler(); // 0x00

		[[nodiscard]]
		static auto GetSingleton() noexcept -> TimerEventHandler*
		{
			static const auto SINGLETON =
				REL::Relocation<TimerEventHandler**>{ID::GameScript::TimerEventHandler::Singleton};
			return *SINGLETON;
		}

		// members
		GameVM* gameVM;								   // 0x10
		BSTSmartPointer<BSScript::IVirtualMachine> vm; // 0x18
		mutable BSSpinLock waitTimerLock;			   // 0x20
		BSTArray<WaitingTimer> waitingTimers;		   // 0x28 - To-Do: `BSTPriorityQueue<WaitingTimer,
													   // GreaterThanOperator<WaitingTimer>, BSTDefaultBinaryHeap>`
		BSTArray<WaitingTimer> menuModeWaitingTimers;  // 0x40 - To-Do: `BSTPriorityQueue<WaitingTimer,
													   // GreaterThanOperator<WaitingTimer>, BSTDefaultBinaryHeap>`
		BSTArray<WaitingTimer> gameModeWaitingTimers;  // 0x58 - To-Do: `BSTPriorityQueue<WaitingTimer,
													   // GreaterThanOperator<WaitingTimer>, BSTDefaultBinaryHeap>`
		mutable BSSpinLock timerLock;				   // 0x70
		BSTArray<BSTSmartPointer<Internal::ScriptTimer>>
			timerQueue; // 0x78 - To-Do: `BSTPriorityQueue<BSTSmartPointer<Internal::ScriptTimer,
						// BSTSmartPointerIntrusiveRefCount>, ScriptTimerCompare, BSTDefaultBinaryHeap>`
		BSTArray<BSTSmartPointer<Internal::ScriptTimer>>
			timerGameTimeQueue; // 0x90 - To-Do: `BSTPriorityQueue<BSTSmartPointer<Internal::ScriptTimer,
								// BSTSmartPointerIntrusiveRefCount>, ScriptTimerCompare, BSTDefaultBinaryHeap>`
	};

	static_assert(sizeof(TimerEventHandler) == 0xA8);
}
