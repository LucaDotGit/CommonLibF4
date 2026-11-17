#pragma once

#include "RE/B/BSContainer_ForEachResult.hpp"
#include "RE/B/BSEventNotifyControl.hpp"
#include "RE/B/BSTEvent.hpp"
#include "REX/NotNull.hpp"
#include "REX/Ownership.hpp"

namespace F4SE::Events
{
	template <class T>
	using InlineEventCallback = RE::BSContainer::ForEachResult(const T& a_event) const;

	template <class T>
	class InlineEventSink final : public RE::BSTEventSink<T>
	{
	public:
		explicit InlineEventSink(REX::NotNull<std::move_only_function<InlineEventCallback<T>>> a_callbackFunctor) :
			_callback(std::move(a_callbackFunctor))
		{
		}

		~InlineEventSink() noexcept override = default;

		InlineEventSink(const InlineEventSink&) = delete;
		InlineEventSink(InlineEventSink&&) = delete;

		auto operator=(const InlineEventSink&) -> InlineEventSink& = delete;
		auto operator=(InlineEventSink&&) -> InlineEventSink& = delete;

		auto ProcessEvent(const T& a_event, RE::BSTEventSource<T>* a_eventSource) -> RE::BSEventNotifyControl override
		{
			if (std::invoke(_callback.get(), a_event) != RE::BSContainer::ForEachResult::Stop) {
				return RE::BSEventNotifyControl::Continue;
			}

			if (a_eventSource) {
				a_eventSource->UnregisterSink(this);
			}

			delete this;

			return RE::BSEventNotifyControl::Continue;
		}

	private:
		REX::NotNull<std::move_only_function<InlineEventCallback<T>>> _callback;
	};

	template <class T>
	auto RegisterForInlineEvent(REX::NotNull<std::move_only_function<InlineEventCallback<T>>> a_callbackFunctor) -> bool
		requires(std::is_invocable_r_v<RE::BSTEventSource<T>*, decltype(&T::GetEventSource)>)
	{
		return RegisterForInlineEvent<T>(T::GetEventSource(), std::move(a_callbackFunctor));
	}

	template <class T>
	auto RegisterForInlineEvent(
		REX::Observer<RE::BSTEventSource<T>*> a_eventSource,
		REX::NotNull<std::move_only_function<InlineEventCallback<T>>> a_callbackFunctor) -> bool
	{
		if (!a_eventSource) {
			return false;
		}

		auto eventSink = std::make_unique<InlineEventSink>(std::move(a_callbackFunctor));
		return a_eventSource->RegisterSink(eventSink.release());
	}
}
