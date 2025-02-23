#pragma once

#include "RE/Bethesda/BSLock.hpp"
#include "RE/Bethesda/BSTArray.hpp"
#include "RE/Bethesda/BSTOptional.hpp"
#include "RE/Bethesda/BSTSingleton.hpp"

namespace RE
{
	enum class BSEventNotifyControl : std::uint32_t
	{
		kContinue,
		kStop
	};

	template <class>
	class BSTEventSource;

	template <class Event>
	class __declspec(novtable) BSTEventSink
	{
	public:
		virtual ~BSTEventSink() = default; // 00

		// add
		virtual BSEventNotifyControl ProcessEvent(const Event& a_event, BSTEventSource<Event>* a_source) = 0; // 01
	};
	static_assert(sizeof(BSTEventSink<void*>) == 0x8);

	template <class Event>
	class BSTEventSource
	{
	public:
		using event_type = Event;

		[[nodiscard]] bool IsSinkRegistered(const BSTEventSink<event_type>* a_sink) const
		{
			if (!a_sink) {
				return false;
			}

			const auto lock = BSAutoLock{ _lock };
			return std::ranges::contains(_sinks, a_sink);
		}

		[[nodiscard]] bool IsSinkRegisterPending(const BSTEventSink<event_type>* a_sink) const
		{
			if (!a_sink) {
				return false;
			}

			const auto lock = BSAutoLock{ _lock };
			return std::ranges::contains(_pendingRegisters, a_sink);
		}

		[[nodiscard]] bool IsSinkUnregisterPending(const BSTEventSink<event_type>* a_sink) const
		{
			if (!a_sink) {
				return false;
			}

			const auto lock = BSAutoLock{ _lock };
			return std::ranges::contains(_pendingUnregisters, a_sink);
		}

		[[nodiscard]] std::uint32_t GetSinkCount() const
		{
			const auto lock = BSAutoLock{ _lock };
			return _sinks.size();
		}

		[[nodiscard]] std::uint32_t GetPendingRegisterCount() const
		{
			const auto lock = BSAutoLock{ _lock };
			return _pendingRegisters.size();
		}

		[[nodiscard]] std::uint32_t GetPendingUnregisterCount() const
		{
			const auto lock = BSAutoLock{ _lock };
			return _pendingUnregisters.size();
		}

		[[nodiscard]] std::int8_t GetNotifying() const
		{
			const auto lock = BSAutoLock{ _lock };
			return _notifying;
		}

		[[nodiscard]] BSTEventSink<event_type>* GetNthSink(std::uint32_t a_index)
		{
			const auto lock = BSAutoLock{ _lock };
			return a_index < _sinks.size() ? _sinks[a_index] : nullptr;
		}

		[[nodiscard]] const BSTEventSink<event_type>* GetNthSink(std::uint32_t a_index) const
		{
			const auto lock = BSAutoLock{ _lock };
			return a_index < _sinks.size() ? _sinks[a_index] : nullptr;
		}

		[[nodiscard]] BSTEventSink<event_type>* GetNthPendingRegister(std::uint32_t a_index)
		{
			const auto lock = BSAutoLock{ _lock };
			return a_index < _pendingRegisters.size() ? _pendingRegisters[a_index] : nullptr;
		}

		[[nodiscard]] const BSTEventSink<event_type>* GetNthPendingRegister(std::uint32_t a_index) const
		{
			const auto lock = BSAutoLock{ _lock };
			return a_index < _pendingRegisters.size() ? _pendingRegisters[a_index] : nullptr;
		}

		[[nodiscard]] BSTEventSink<event_type>* GetNthPendingUnregister(std::uint32_t a_index)
		{
			const auto lock = BSAutoLock{ _lock };
			return a_index < _pendingUnregisters.size() ? _pendingUnregisters[a_index] : nullptr;
		}

		[[nodiscard]] const BSTEventSink<event_type>* GetNthPendingUnregister(std::uint32_t a_index) const
		{
			const auto lock = BSAutoLock{ _lock };
			return a_index < _pendingUnregisters.size() ? _pendingUnregisters[a_index] : nullptr;
		}

		bool RegisterSink(BSTEventSink<event_type>* a_sink)
		{
			if (!a_sink) {
				return false;
			}

			const auto lock = BSAutoLock{ _lock };

			const auto it = std::ranges::find(_pendingUnregisters, a_sink);
			if (it != _pendingUnregisters.end()) {
				_pendingUnregisters.erase(it);
			}

			if (_notifying && !std::ranges::contains(_pendingRegisters, a_sink)) {
				_pendingRegisters.push_back(a_sink);
				return true;
			}

			if (!std::ranges::contains(_sinks, a_sink)) {
				_sinks.push_back(a_sink);
				return true;
			}

			return false;
		}

		bool UnregisterSink(BSTEventSink<event_type>* a_sink)
		{
			if (!a_sink) {
				return false;
			}

			const auto lock = BSAutoLock{ _lock };

			const auto pendingIt = std::ranges::find(_pendingRegisters, a_sink);
			if (pendingIt != _pendingRegisters.end()) {
				_pendingRegisters.erase(pendingIt);
			}

			if (_notifying && !std::ranges::contains(_pendingUnregisters, a_sink)) {
				_pendingUnregisters.push_back(a_sink);
				return true;
			}

			const auto it = std::ranges::find(_sinks, a_sink);
			if (it != _sinks.end()) {
				_sinks.erase(it);
				return true;
			}

			return false;
		}

		std::uint32_t Notify(const event_type& a_event)
		{
			const auto lock = BSAutoLock{ _lock };

			if (!_notifying && !_pendingRegisters.empty()) {
				for (const auto& element : _pendingRegisters) {
					if (!std::ranges::contains(_sinks, element)) {
						_sinks.push_back(element);
					}
				}

				_pendingRegisters.clear();
			}

			auto count = 0ui32;
			_notifying++;

			for (const auto& sink : _sinks) {
				if (!std::ranges::contains(_pendingUnregisters, sink) &&
					sink->ProcessEvent(a_event, this) == BSEventNotifyControl::kStop) {
					break;
				}

				count++;
			}

			const auto uncontended = _notifying-- == 1;
			if (!uncontended || _pendingUnregisters.empty()) {
				return count;
			}

			for (const auto& element : _pendingUnregisters) {
				const auto it = std::ranges::find(_sinks, element);
				if (it != _sinks.end()) {
					_sinks.erase(it);
				}
			}

			_pendingUnregisters.clear();
			return count;
		}

	private:
		// members
		mutable BSSpinLock _lock;								 // 00
		BSTArray<BSTEventSink<event_type>*> _sinks;				 // 08
		BSTArray<BSTEventSink<event_type>*> _pendingRegisters;	 // 20
		BSTArray<BSTEventSink<event_type>*> _pendingUnregisters; // 38
		std::int8_t _notifying{ 0 };							 // 50
	};
	static_assert(sizeof(BSTEventSource<void*>) == 0x58);

	template <class T>
	class BSTValueEvent
	{
	public:
		using value_type = T;

		// members
		BSTOptional<T> optionalValue; // 00
	};

	template <class T>
	class BSTValueEventSink
		: public BSTEventSink<T> // 00
	{
	public:
		struct BSTEventValueData
		{
		public:
			// members
			BSTOptional<typename T::value_type> optionalValue; // 00
			bool eventReceived;								   // ??
		};

		// override (BSTEventSink<T>)
		virtual BSEventNotifyControl ProcessEvent([[maybe_unused]] const T& a_event, BSTEventSource<T>*) override { return BSEventNotifyControl::kContinue; } // 01

		// members
		BSTEventValueData eventDataStruct; // 08
		mutable BSSpinLock dataLock;	   // ??
	};

	template <class T>
	class BSTValueRequestEvent
	{
	public:
		// members
		BSTValueEventSink<T>& valueEventSink; // 00
	};

	template <class T>
	class BSTValueEventSource
		: public BSTEventSink<BSTValueRequestEvent<T>> // 00
	{
	public:
		using event_type = BSTValueRequestEvent<T>;

		// override (BSTEventSink<BSTValueRequestEvent<T>>)
		BSEventNotifyControl ProcessEvent(const event_type& a_event, BSTEventSource<event_type>*) override // 01
		{
			const auto lock = BSAutoLock{ dataLock };

			auto event = T();
			event.optionalValue = optionalValue;

			a_event.valueEventSink.ProcessEvent(event, nullptr);
		}

		// members
		BSTOptional<typename T::value_type> optionalValue; // ??
		mutable BSSpinLock dataLock;					   // ??
	};

	class BSTGlobalEvent
		: public BSTSingletonSDM<BSTGlobalEvent>
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSTGlobalEvent };
		inline static constexpr auto VTABLE{ RTTI::BSTGlobalEvent };

		struct KillSDMEvent
		{
		};
		static_assert(sizeof(KillSDMEvent) == 0x01);

		class KillSDMEventSource
			: public BSTEventSource<KillSDMEvent>
		{
		};
		static_assert(sizeof(KillSDMEventSource) == 0x58);

		template <class Event>
		class EventSource
			: public BSTEventSink<KillSDMEvent>,
			  public BSTSingletonSDM<EventSource<Event>>,
			  public BSTEventSource<Event>
		{
		public:
			EventSource(KillSDMEventSource* a_source)
			{
				a_source->RegisterSink(this);
			}

			virtual ~EventSource() = default; // 00

			// override
			virtual BSEventNotifyControl ProcessEvent([[maybe_unused]] const KillSDMEvent& a_event, BSTEventSource<KillSDMEvent>* a_source) override // 01
			{
				a_source->UnregisterSink(this);
				delete this;

				return BSEventNotifyControl::kContinue;
			}
		};
		static_assert(sizeof(EventSource<void*>) == 0x68);

		virtual ~BSTGlobalEvent(); // 00

		[[nodiscard]] static BSTGlobalEvent* GetSingleton()
		{
			static REL::Relocation<BSTGlobalEvent**> singleton{ REL::RelocationID(1424022, 2688814) };
			return *singleton;
		}

		// members
		KillSDMEventSource eventSourceSDMKiller; // 10
	};
	static_assert(sizeof(BSTGlobalEvent) == 0x68);
}
