#pragma once

#include "RE/B/BSInputEventReceiver.hpp"
#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class MenuOpenCloseEvent;
	class IdleInputEvent;

	class __declspec(novtable) BSIdleInputWatcher :
		public BSInputEventReceiver,				// 0x00
		public BSTEventSink<MenuOpenCloseEvent>,	// 0x10
		public BSTSingletonSDM<BSIdleInputWatcher>, // 0x18
		public BSTEventSource<IdleInputEvent>		// 0x20

	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSIdleInputWatcher;
		inline static constexpr const auto& VTABLE = VTABLE::BSIdleInputWatcher;

		~BSIdleInputWatcher() override; // 0x00

		// override (BSInputEventReceiver)
		void PerformInputProcessing(const InputEvent* a_queueHead) override; // 0x01

		// override (BSTEventSink<MenuOpenCloseEvent>)
		auto ProcessEvent(
			const MenuOpenCloseEvent& a_event,
			BSTEventSource<MenuOpenCloseEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		[[nodiscard]]
		static auto GetSingleton() noexcept -> BSIdleInputWatcher*
		{
			static const auto SINGLETON = REL::Relocation<BSIdleInputWatcher**>(ID::BSIdleInputWatcher::Singleton);
			return *SINGLETON;
		}

		// members
		std::uint64_t lastInputTime; // 0x78
		std::uint8_t disableCount;	 // 0x80
		bool isInputIdle;			 // 0x81
	};

	static_assert(sizeof(BSIdleInputWatcher) == 0x88);
}
