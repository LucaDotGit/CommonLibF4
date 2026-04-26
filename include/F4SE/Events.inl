#pragma once

#include "F4SE/Events.hpp"

#include "RE/B/BSContainer_ForEachResult.hpp"
#include "RE/B/BSScriptUtil_Core.hpp"
#include "RE/B/BSTEvent.hpp"

namespace F4SE::Events
{
	template <class T>
	bool RegisterForInlineEvent(std::function<InlineEventCallbackType<T>> a_callbackFunctor)
		requires(std::is_invocable_r_v<RE::BSTEventSource<T>*, decltype(&T::GetEventSource)>)
	{
		return RegisterForInlineEvent<T>(T::GetEventSource(), std::move(a_callbackFunctor));
	}

	template <class T>
	bool RegisterForInlineEvent(RE::BSTEventSource<T>* a_eventSource, std::function<InlineEventCallbackType<T>> a_callbackFunctor)
	{
		class InlineEventSink final
			: public RE::BSTEventSink<T>
		{
		public:
			InlineEventSink(std::function<InlineEventCallbackType<T>> a_callbackFunctor)
				: _callback(std::move(a_callbackFunctor))
			{
			}

			~InlineEventSink() noexcept override = default;

			InlineEventSink(const InlineEventSink&) = delete;
			InlineEventSink(InlineEventSink&&) = delete;

			InlineEventSink& operator=(const InlineEventSink&) = delete;
			InlineEventSink& operator=(InlineEventSink&&) = delete;

			RE::BSEventNotifyControl ProcessEvent(const T& a_event, RE::BSTEventSource<T>* a_eventSource) override
			{
				if (_callback(a_event) != RE::BSContainer::ForEachResult::kStop) {
					return RE::BSEventNotifyControl::kContinue;
				}

				if (a_eventSource) {
					a_eventSource->UnregisterSink(this);
				}

				delete this;

				return RE::BSEventNotifyControl::kContinue;
			}

		private:
			std::function<InlineEventCallbackType<T>> _callback;
		};

		if (!a_eventSource) {
			return false;
		}

		return a_eventSource->template CreateAndRegisterSink<InlineEventSink>(std::move(a_callbackFunctor));
	}

	template <class... Args>
	std::uint32_t SendExternalEvent(
		const RE::BSFixedString& a_eventName,
		Args&&... a_args)
		requires((RE::BSScript::ValidateParameter<std::remove_reference_t<Args>>() && ...))
	{
		const auto argsFactory = std::function([... a_args = std::forward<Args>(a_args)]() mutable {
			return RE::BSScript::PackVariables(std::forward<Args>(a_args)...);
		});

		return SendAppliedExternalEvent(a_eventName, argsFactory);
	}

	template <class... Args>
	std::uint32_t SendExternalEventWithCallback(
		const RE::BSFixedString& a_eventName,
		const RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor>& a_callbackFunctor,
		Args&&... a_args)
		requires((RE::BSScript::ValidateParameter<std::remove_reference_t<Args>>() && ...))
	{
		const auto argsFactory = std::function([... a_args = std::forward<Args>(a_args)]() mutable {
			return RE::BSScript::PackVariables(std::forward<Args>(a_args)...);
		});

		return SendAppliedExternalEventWithCallback(a_eventName, a_callbackFunctor, argsFactory);
	}
}
