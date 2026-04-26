#pragma once

#include "RE/B/BSInputEventReceiver.hpp"
#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class MenuOpenCloseEvent;
	class IdleInputEvent;

	class __declspec(novtable) BSIdleInputWatcher
		: public BSInputEventReceiver,				  // 00
		  public BSTEventSink<MenuOpenCloseEvent>,	  // 10
		  public BSTSingletonSDM<BSIdleInputWatcher>, // 18
		  public BSTEventSource<IdleInputEvent>		  // 20

	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSIdleInputWatcher };
		inline static constexpr auto VTABLE{ VTABLE::BSIdleInputWatcher };

		~BSIdleInputWatcher() override; // 00

		// override (BSInputEventReceiver)
		void PerformInputProcessing(const InputEvent* a_queueHead) override; // 01

		// override (BSTEventSink<MenuOpenCloseEvent>)
		BSEventNotifyControl ProcessEvent(const MenuOpenCloseEvent& a_event, BSTEventSource<MenuOpenCloseEvent>* a_eventSource) override; // 01

		[[nodiscard]] static BSIdleInputWatcher* GetSingleton()
		{
			static const auto SINGLETON = REL::Relocation<BSIdleInputWatcher**>{ ID::BSIdleInputWatcher::Singleton };
			return *SINGLETON;
		}

		// members
		std::uint64_t lastInputTime; // 78
		std::uint8_t disableCount;	 // 80
		bool isInputIdle;			 // 81
	};
	static_assert(sizeof(BSIdleInputWatcher) == 0x88);
}
