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

		BSTEventSink& operator=(const BSTEventSink&) = delete;
		BSTEventSink& operator=(BSTEventSink&&) = delete;

		virtual ~BSTEventSink() = default; // 00

		// add
		virtual BSEventNotifyControl ProcessEvent(const Event& a_event, BSTEventSource<Event>* a_eventSource) = 0; // 01
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

		BSTEventSource& operator=(const BSTEventSource&) = delete;
		BSTEventSource& operator=(BSTEventSource&&) = delete;

		[[nodiscard]] bool HasSinks() const noexcept
		{
			const auto sinkLock = BSAutoLock(_lock);
			return !_sinks.empty() || !_pendingRegisters.empty();
		}

		[[nodiscard]] bool IsSinkRegistered(const BSTEventSink<event_type>* a_sink) const noexcept
		{
			const auto sinkLock = BSAutoLock(_lock);
			return std::ranges::contains(_sinks, a_sink);
		}

		[[nodiscard]] bool IsSinkRegisterPending(const BSTEventSink<event_type>* a_sink) const noexcept
		{
			const auto sinkLock = BSAutoLock(_lock);
			return std::ranges::contains(_pendingRegisters, a_sink);
		}

		[[nodiscard]] bool IsSinkUnregisterPending(const BSTEventSink<event_type>* a_sink) const noexcept
		{
			const auto sinkLock = BSAutoLock(_lock);
			return std::ranges::contains(_pendingUnregisters, a_sink);
		}

		[[nodiscard]] std::uint32_t GetPotentialSinkCount() const noexcept
		{
			const auto sinkLock = BSAutoLock(_lock);
			return _sinks.size() + _pendingRegisters.size();
		}

		[[nodiscard]] std::uint32_t GetSinkCount() const noexcept
		{
			const auto sinkLock = BSAutoLock(_lock);
			return _sinks.size();
		}

		[[nodiscard]] std::uint32_t GetPendingRegisterCount() const noexcept
		{
			const auto sinkLock = BSAutoLock(_lock);
			return _pendingRegisters.size();
		}

		[[nodiscard]] std::uint32_t GetPendingUnregisterCount() const noexcept
		{
			const auto sinkLock = BSAutoLock(_lock);
			return _pendingUnregisters.size();
		}

		template <class T, class... Args>
		bool CreateAndRegisterSink(Args&&... a_args)
			requires(std::derived_from<T, BSTEventSink<event_type>> &&
					 std::is_constructible_v<T, Args...>)
		{
			auto* sink = new T(std::forward<Args>(a_args)...);
			if (!sink) {
				return false;
			}

			return RegisterSink(sink);
		}

		template <class... Args>
		std::uint32_t CreateAndNotifyEvent(Args&&... a_args)
			requires(std::is_constructible_v<event_type, Args...>)
		{
			const auto event = event_type(std::forward<Args>(a_args)...);
			return Notify(event);
		}

		bool RegisterSink(BSTEventSink<event_type>* a_sink)
		{
			if (!a_sink) {
				return false;
			}

			const auto sinkLock = BSAutoLock(_lock);

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

		bool UnregisterSink(BSTEventSink<event_type>* a_sink)
		{
			if (!a_sink) {
				return false;
			}

			const auto sinkLock = BSAutoLock(_lock);

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

		std::uint32_t Notify(const event_type& a_event)
		{
			const auto sinkLock = BSAutoLock(_lock);

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

			auto notifyCount = 0ui32;
			_notifying++;

			for (auto* sink : _sinks) {
				if (!sink) {
					continue;
				}

				if (std::ranges::contains(_pendingUnregisters, sink)) {
					continue;
				}

				notifyCount++;

				if (sink->ProcessEvent(a_event, this) == BSEventNotifyControl::kStop) {
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
		mutable BSSpinLock _lock;								 // 00
		BSTArray<BSTEventSink<event_type>*> _sinks;				 // 08
		BSTArray<BSTEventSink<event_type>*> _pendingRegisters;	 // 20
		BSTArray<BSTEventSink<event_type>*> _pendingUnregisters; // 38
		std::int8_t _notifying{ 0 };							 // 50
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

		BSTValueEvent& operator=(const BSTValueEvent&) = delete;
		BSTValueEvent& operator=(BSTValueEvent&&) = delete;

		// members
		BSTOptional<T> optionalValue; // 00
	};

	template <class T>
	class /*__declspec(novtable)*/ BSTValueEventSink
		: public BSTEventSink<T> // 00
	{
	public:
		using event_type = T;

		class BSTEventValueData
		{
		public:
			// members
			BSTOptional<typename T::value_type> optionalValue; // 00
			bool eventReceived;								   // ??
		};

		BSTValueEventSink() = default;

		BSTValueEventSink(const BSTValueEventSink&) = delete;
		BSTValueEventSink(BSTValueEventSink&&) = delete;

		BSTValueEventSink& operator=(const BSTValueEventSink&) = delete;
		BSTValueEventSink& operator=(BSTValueEventSink&&) = delete;

		~BSTValueEventSink() override = default; // 00

		// override (BSTEventSink<T>)
		BSEventNotifyControl ProcessEvent([[maybe_unused]] const T& a_event, [[maybe_unused]] BSTEventSource<T>* a_eventSource) override { return BSEventNotifyControl::kContinue; } // 01

		// members
		BSTEventValueData eventDataStruct; // 08
		mutable BSSpinLock dataLock;	   // ??
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

		BSTValueRequestEvent& operator=(const BSTValueRequestEvent&) = delete;
		BSTValueRequestEvent& operator=(BSTValueRequestEvent&&) = delete;

		// members
		BSTValueEventSink<T>& valueEventSink; // 00
	};

	template <class T>
	class /*__declspec(novtable)*/ BSTValueEventSource
		: public BSTEventSink<BSTValueRequestEvent<T>> // 00
	{
	public:
		using event_type = BSTValueRequestEvent<T>;

		BSTValueEventSource() = default;

		BSTValueEventSource(const BSTValueEventSource&) = delete;
		BSTValueEventSource(BSTValueEventSource&&) = delete;

		BSTValueEventSource& operator=(const BSTValueEventSource&) = delete;
		BSTValueEventSource& operator=(BSTValueEventSource&&) = delete;

		~BSTValueEventSource() override = default; // 00

		// override (BSTEventSink<BSTValueRequestEvent<T>>)
		BSEventNotifyControl ProcessEvent(const event_type& a_event, [[maybe_unused]] BSTEventSource<event_type>* a_eventSource) override // 01
		{
			const auto eventLock = BSAutoLock(dataLock);

			auto event = T();
			event.optionalValue = optionalValue;

			return a_event.valueEventSink.ProcessEvent(event, nullptr);
		}

		// members
		BSTOptional<typename T::value_type> optionalValue; // ??
		mutable BSSpinLock dataLock;					   // ??
	};

	class __declspec(novtable) BSTGlobalEvent
		: public BSTSingletonSDM<BSTGlobalEvent> // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSTGlobalEvent };
		inline static constexpr auto VTABLE{ VTABLE::BSTGlobalEvent };

		class KillSDMEvent
		{
		public:
			KillSDMEvent() = default;
			~KillSDMEvent() = default;

			KillSDMEvent(const KillSDMEvent&) = delete;
			KillSDMEvent(KillSDMEvent&&) = delete;

			KillSDMEvent& operator=(const KillSDMEvent&) = delete;
			KillSDMEvent& operator=(KillSDMEvent&&) = delete;
		};
		static_assert(std::is_empty_v<KillSDMEvent>);

		class KillSDMEventSource
			: public BSTEventSource<KillSDMEvent> // 00
		{
		public:
			KillSDMEventSource() = default;
			~KillSDMEventSource() = default;

			KillSDMEventSource(const KillSDMEventSource&) = delete;
			KillSDMEventSource(KillSDMEventSource&&) = delete;

			KillSDMEventSource& operator=(const KillSDMEventSource&) = delete;
			KillSDMEventSource& operator=(KillSDMEventSource&&) = delete;
		};
		static_assert(sizeof(KillSDMEventSource) == 0x58);

		template <class Event>
		class /*__declspec(novtable)*/ EventSource
			: public BSTEventSink<KillSDMEvent>,		  // 00
			  public BSTSingletonSDM<EventSource<Event>>, // 08
			  public BSTEventSource<Event>				  // 10
		{
		public:
			EventSource(KillSDMEventSource& a_eventSource)
			{
				a_eventSource.RegisterSink(this);
			}

			EventSource(const EventSource&) = delete;
			EventSource(EventSource&&) = delete;

			EventSource& operator=(const EventSource&) = delete;
			EventSource& operator=(EventSource&&) = delete;

			~EventSource() override = default; // 00

			// override (BSTEventSink<KillSDMEvent>)
			BSEventNotifyControl ProcessEvent([[maybe_unused]] const KillSDMEvent& a_event, BSTEventSource<KillSDMEvent>* a_eventSource) override // 01
			{
				if (a_eventSource) {
					a_eventSource->UnregisterSink(this);
				}

				delete this;

				return BSEventNotifyControl::kContinue;
			}

			GAME_HEAP_REDEFINE_NEW(EventSource);
		};
		static_assert(sizeof(EventSource<std::any>) == 0x68);

		BSTGlobalEvent(const BSTGlobalEvent&) = delete;
		BSTGlobalEvent(BSTGlobalEvent&&) = delete;

		BSTGlobalEvent& operator=(const BSTGlobalEvent&) = delete;
		BSTGlobalEvent& operator=(BSTGlobalEvent&&) = delete;

		virtual ~BSTGlobalEvent(); // 00

		[[nodiscard]] static BSTGlobalEvent* GetSingleton()
		{
			static const auto SINGLETON = REL::Relocation<BSTGlobalEvent**>{ ID::BSTEvent::BSTGlobalEvent::Singleton };
			return *SINGLETON;
		}

		// members
		KillSDMEventSource eventSourceSDMKiller; // 10
	};
	static_assert(sizeof(BSTGlobalEvent) == 0x68);
}
