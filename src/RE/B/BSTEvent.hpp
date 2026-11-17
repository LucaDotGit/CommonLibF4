#pragma once

#include "RE/B/BSEventNotifyControl.hpp"
#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTOptional.hpp"
#include "RE/B/BSTSingleton.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE
{
	template <class>
	class BSTEventSource;

	template <class Event>
	class __declspec(novtable) BSTEventSink
	{
	public:
		using event_type = Event;

		BSTEventSink() = default;

		BSTEventSink(const BSTEventSink&) = delete;
		BSTEventSink(BSTEventSink&&) = delete;

		auto operator=(const BSTEventSink&) -> BSTEventSink& = delete;
		auto operator=(BSTEventSink&&) -> BSTEventSink& = delete;

		virtual ~BSTEventSink() = default; // 0x00

		// add
		virtual auto ProcessEvent(
			const Event& a_event,
			BSTEventSource<Event>* a_eventSource) -> BSEventNotifyControl = 0; // 0x01
	};

	static_assert(sizeof(BSTEventSink<std::any>) == 0x08);

	template <class Event>
	class BSTEventSource
	{
	public:
		using event_type = Event;

		BSTEventSource() = default;
		~BSTEventSource() = default;

		BSTEventSource(const BSTEventSource&) = delete;
		BSTEventSource(BSTEventSource&&) = delete;

		auto operator=(const BSTEventSource&) -> BSTEventSource& = delete;
		auto operator=(BSTEventSource&&) -> BSTEventSource& = delete;

		[[nodiscard]]
		auto HasSinks() const noexcept -> bool
		{
			const auto sinkLock = BSAutoSpinLock(_lock);
			return !_sinks.empty() || !_pendingRegisters.empty();
		}

		[[nodiscard]]
		auto IsSinkRegistered(const BSTEventSink<event_type>* a_sink) const noexcept -> bool
		{
			const auto sinkLock = BSAutoSpinLock(_lock);
			return std::ranges::contains(_sinks, a_sink);
		}

		[[nodiscard]]
		auto IsSinkRegisterPending(const BSTEventSink<event_type>* a_sink) const noexcept -> bool
		{
			const auto sinkLock = BSAutoSpinLock(_lock);
			return std::ranges::contains(_pendingRegisters, a_sink);
		}

		[[nodiscard]]
		auto IsSinkUnregisterPending(const BSTEventSink<event_type>* a_sink) const noexcept -> bool
		{
			const auto sinkLock = BSAutoSpinLock(_lock);
			return std::ranges::contains(_pendingUnregisters, a_sink);
		}

		[[nodiscard]]
		auto GetPotentialSinkCount() const noexcept -> std::uint32_t
		{
			const auto sinkLock = BSAutoSpinLock(_lock);
			return _sinks.size() + _pendingRegisters.size();
		}

		[[nodiscard]]
		auto GetSinkCount() const noexcept -> std::uint32_t
		{
			const auto sinkLock = BSAutoSpinLock(_lock);
			return _sinks.size();
		}

		[[nodiscard]]
		auto GetPendingRegisterCount() const noexcept -> std::uint32_t
		{
			const auto sinkLock = BSAutoSpinLock(_lock);
			return _pendingRegisters.size();
		}

		[[nodiscard]]
		auto GetPendingUnregisterCount() const noexcept -> std::uint32_t
		{
			const auto sinkLock = BSAutoSpinLock(_lock);
			return _pendingUnregisters.size();
		}

		auto RegisterSink(BSTEventSink<event_type>* a_sink) -> bool
		{
			if (!a_sink) {
				return false;
			}

			const auto sinkLock = BSAutoSpinLock(_lock);

			if (_notifying != 0) {
				if (!std::ranges::contains(_pendingRegisters, a_sink)) {
					_pendingRegisters.push_back(a_sink);
				}
			}
			else {
				if (!std::ranges::contains(_sinks, a_sink)) {
					_sinks.push_back(a_sink);
				}
			}

			const auto sinkIt = std::ranges::find(_pendingUnregisters, a_sink);
			if (sinkIt != _pendingUnregisters.end()) {
				_pendingUnregisters.erase(sinkIt);
			}

			return true;
		}

		auto UnregisterSink(BSTEventSink<event_type>* a_sink) -> bool
		{
			if (!a_sink) {
				return false;
			}

			const auto sinkLock = BSAutoSpinLock(_lock);

			if (_notifying != 0) {
				if (!std::ranges::contains(_pendingUnregisters, a_sink)) {
					_pendingUnregisters.push_back(a_sink);
				}
			}
			else {
				const auto sinkIt = std::ranges::find(_sinks, a_sink);
				if (sinkIt != _sinks.end()) {
					_sinks.erase(sinkIt);
				}
			}

			const auto sinkIt = std::ranges::find(_pendingRegisters, a_sink);
			if (sinkIt != _pendingRegisters.end()) {
				_pendingRegisters.erase(sinkIt);
			}

			return true;
		}

		auto Notify(const event_type& a_event) -> std::uint32_t
		{
			const auto sinkLock = BSAutoSpinLock(_lock);

			if (_notifying == 0 && !_pendingRegisters.empty()) {
				for (auto* pendingRegister : _pendingRegisters) {
					if (!pendingRegister) {
						continue;
					}

					if (!std::ranges::contains(_sinks, pendingRegister)) {
						_sinks.push_back(pendingRegister);
					}
				}

				_pendingRegisters.clear();
			}

			auto notifyCount = static_cast<std::uint32_t>(0);
			_notifying++;

			for (auto* sink : _sinks) {
				if (!sink) {
					continue;
				}

				if (std::ranges::contains(_pendingUnregisters, sink)) {
					continue;
				}

				notifyCount++;

				if (sink->ProcessEvent(a_event, this) == BSEventNotifyControl::Stop) {
					break;
				}
			}

			const auto uncontended = _notifying-- == 1;
			if (uncontended == 0 || _pendingUnregisters.empty()) {
				return notifyCount;
			}

			for (auto* pendingUnregister : _pendingUnregisters) {
				if (!pendingUnregister) {
					continue;
				}

				const auto sinkIt = std::ranges::find(_sinks, pendingUnregister);
				if (sinkIt != _sinks.end()) {
					_sinks.erase(sinkIt);
				}
			}

			_pendingUnregisters.clear();
			return notifyCount;
		}

	private:
		// members
		mutable BSSpinLock _lock;								 // 0x00
		BSTArray<BSTEventSink<event_type>*> _sinks;				 // 0x08
		BSTArray<BSTEventSink<event_type>*> _pendingRegisters;	 // 0x20
		BSTArray<BSTEventSink<event_type>*> _pendingUnregisters; // 0x38
		std::int8_t _notifying{0};								 // 0x50
	};

	static_assert(sizeof(BSTEventSource<std::any>) == 0x58);

	template <class T>
	class BSTValueEvent
	{
	public:
		using value_type = T;

		BSTValueEvent() = default;
		~BSTValueEvent() = default;

		BSTValueEvent(const BSTValueEvent&) = delete;
		BSTValueEvent(BSTValueEvent&&) = delete;

		auto operator=(const BSTValueEvent&) -> BSTValueEvent& = delete;
		auto operator=(BSTValueEvent&&) -> BSTValueEvent& = delete;

		// members
		BSTOptional<T> optionalValue; // 0x00
	};

	template <class T>
	class /*__declspec(novtable)*/ BSTValueEventSink : public BSTEventSink<T> // 0x00
	{
	public:
		using event_type = T;

		class BSTEventValueData
		{
		public:
			// members
			BSTOptional<typename T::value_type> optionalValue; // 0x00
			bool eventReceived;								   // 0x??
		};

		BSTValueEventSink() = default;

		BSTValueEventSink(const BSTValueEventSink&) = delete;
		BSTValueEventSink(BSTValueEventSink&&) = delete;

		auto operator=(const BSTValueEventSink&) -> BSTValueEventSink& = delete;
		auto operator=(BSTValueEventSink&&) -> BSTValueEventSink& = delete;

		~BSTValueEventSink() override = default; // 0x00

		// override (BSTEventSink<T>)
		auto ProcessEvent([[maybe_unused]] const T& a_event, [[maybe_unused]] BSTEventSource<T>* a_eventSource)
			-> BSEventNotifyControl override // 0x01
		{
			return BSEventNotifyControl::Continue;
		}

		// members
		BSTEventValueData eventDataStruct; // 0x08
		mutable BSSpinLock dataLock;	   // 0x??
	};

	template <class T>
	class BSTValueRequestEvent
	{
	public:
		using value_type = T;

		BSTValueRequestEvent() = default;
		~BSTValueRequestEvent() = default;

		BSTValueRequestEvent(const BSTValueRequestEvent&) = delete;
		BSTValueRequestEvent(BSTValueRequestEvent&&) = delete;

		auto operator=(const BSTValueRequestEvent&) -> BSTValueRequestEvent& = delete;
		auto operator=(BSTValueRequestEvent&&) -> BSTValueRequestEvent& = delete;

		// members
		BSTValueEventSink<T>& valueEventSink; // 0x00
	};

	template <class T>
	class /*__declspec(novtable)*/ BSTValueEventSource : public BSTEventSink<BSTValueRequestEvent<T>> // 0x00
	{
	public:
		using event_type = BSTValueRequestEvent<T>;

		BSTValueEventSource() = default;

		BSTValueEventSource(const BSTValueEventSource&) = delete;
		BSTValueEventSource(BSTValueEventSource&&) = delete;

		auto operator=(const BSTValueEventSource&) -> BSTValueEventSource& = delete;
		auto operator=(BSTValueEventSource&&) -> BSTValueEventSource& = delete;

		~BSTValueEventSource() override = default; // 0x00

		// override (BSTEventSink<BSTValueRequestEvent<T>>)
		auto ProcessEvent(
			const event_type& a_event,
			[[maybe_unused]] BSTEventSource<event_type>* a_eventSource) -> BSEventNotifyControl override // 0x01
		{
			const auto eventLock = BSAutoSpinLock(dataLock);

			auto event = T();
			event.optionalValue = optionalValue;

			return a_event.valueEventSink.ProcessEvent(event, nullptr);
		}

		// members
		BSTOptional<typename T::value_type> optionalValue; // 0x??
		mutable BSSpinLock dataLock;					   // 0x??
	};

	class __declspec(novtable) BSTGlobalEvent : public BSTSingletonSDM<BSTGlobalEvent> // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSTGlobalEvent;
		inline static constexpr const auto& VTABLE = VTABLE::BSTGlobalEvent;

		class KillSDMEvent
		{
		public:
			KillSDMEvent() = default;
			~KillSDMEvent() = default;

			KillSDMEvent(const KillSDMEvent&) = delete;
			KillSDMEvent(KillSDMEvent&&) = delete;

			auto operator=(const KillSDMEvent&) -> KillSDMEvent& = delete;
			auto operator=(KillSDMEvent&&) -> KillSDMEvent& = delete;
		};

		static_assert(std::is_empty_v<KillSDMEvent>);

		class KillSDMEventSource : public BSTEventSource<KillSDMEvent> // 0x00
		{
		public:
			KillSDMEventSource() = default;
			~KillSDMEventSource() = default;

			KillSDMEventSource(const KillSDMEventSource&) = delete;
			KillSDMEventSource(KillSDMEventSource&&) = delete;

			auto operator=(const KillSDMEventSource&) -> KillSDMEventSource& = delete;
			auto operator=(KillSDMEventSource&&) -> KillSDMEventSource& = delete;
		};

		static_assert(sizeof(KillSDMEventSource) == 0x58);

		template <class Event>
		class /*__declspec(novtable)*/ EventSource :
			public BSTEventSink<KillSDMEvent>,			// 0x00
			public BSTSingletonSDM<EventSource<Event>>, // 0x08
			public BSTEventSource<Event>				// 0x10
		{
		public:
			explicit EventSource(KillSDMEventSource& a_eventSource)
			{
				a_eventSource.RegisterSink(this);
			}

			EventSource(const EventSource&) = delete;
			EventSource(EventSource&&) = delete;

			auto operator=(const EventSource&) -> EventSource& = delete;
			auto operator=(EventSource&&) -> EventSource& = delete;

			~EventSource() override = default; // 0x00

			// override (BSTEventSink<KillSDMEvent>)
			auto ProcessEvent(
				[[maybe_unused]] const KillSDMEvent& a_event,
				BSTEventSource<KillSDMEvent>* a_eventSource) -> BSEventNotifyControl override // 0x01
			{
				if (a_eventSource) {
					a_eventSource->UnregisterSink(this);
				}

				delete this;

				return BSEventNotifyControl::Continue;
			}

			GAME_HEAP_REDEFINE_NEW(EventSource);
		};

		static_assert(sizeof(EventSource<std::any>) == 0x68);

		BSTGlobalEvent(const BSTGlobalEvent&) = delete;
		BSTGlobalEvent(BSTGlobalEvent&&) = delete;

		auto operator=(const BSTGlobalEvent&) -> BSTGlobalEvent& = delete;
		auto operator=(BSTGlobalEvent&&) -> BSTGlobalEvent& = delete;

		virtual ~BSTGlobalEvent(); // 0x00

		[[nodiscard]]
		static auto GetSingleton() noexcept -> BSTGlobalEvent*
		{
			static const auto SINGLETON = REL::Relocation<BSTGlobalEvent**>(ID::BSTEvent::BSTGlobalEvent::Singleton);
			return *SINGLETON;
		}

		// members
		KillSDMEventSource eventSourceSDMKiller; // 0x10
	};

	static_assert(sizeof(BSTGlobalEvent) == 0x68);
}
