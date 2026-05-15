#pragma once

#include "RE/CoreTypes.hpp"

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSScriptUtil_Concepts.hpp"
#include "RE/B/BSTSmartPointer.hpp"

#include "REX/NotNull.hpp"
#include "REX/Own.hpp"

namespace RE
{
	template <class T>
	class BSTEventSource;

	class BSInputEventUser;
}

namespace RE::BSContainer
{
	enum class ForEachResult : std::int32_t;
}

namespace RE::BSScript
{
	class IStackCallbackFunctor;
	class Object;
	class Variable;
}

namespace F4SE::Events
{
	// These functions should only be used after the game data is ready;
	// they are also thread-safe, except for the input event registrations.

	template <class T>
	using InlineEventCallbackType = RE::BSContainer::ForEachResult(const T& a_event);

	template <class T>
	bool RegisterForInlineEvent(std::function<InlineEventCallbackType<T>> a_callbackFunctor)
		requires(std::is_invocable_r_v<RE::BSTEventSource<T>*, decltype(&T::GetEventSource)>);

	template <class T>
	bool RegisterForInlineEvent(RE::BSTEventSource<T>* a_eventSource, std::function<InlineEventCallbackType<T>> a_callbackFunctor);

	class ExternalEventInfo final
	{
	public:
		RE::BSScript::ObjectHandle objectHandle;
		RE::BSFixedString scriptName;
		RE::BSFixedString functionName{ ""sv };
	};

	[[nodiscard]] bool IsRegisteredForExternalEvent(const RE::BSFixedString& a_eventName, const ExternalEventInfo& a_eventInfo);
	[[nodiscard]] auto GetExternalEventRegistrations(const RE::BSFixedString& a_eventName)
		-> std::vector<ExternalEventInfo>;

	std::uint32_t SendAppliedExternalEvent(
		const RE::BSFixedString& a_eventName,
		const REX::NotNull<std::function<std::vector<RE::BSScript::Variable>()>>& a_argsFactory);

	std::uint32_t SendAppliedExternalEventWithCallback(
		const RE::BSFixedString& a_eventName,
		const RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor>& a_callbackFunctor,
		const REX::NotNull<std::function<std::vector<RE::BSScript::Variable>()>>& a_argsFactory);

	template <class... Args>
	std::uint32_t SendExternalEvent(
		const RE::BSFixedString& a_eventName,
		Args&&... a_args)
		requires((RE::BSScript::ValidateParameter<std::remove_reference_t<Args>>() && ...));

	template <class... Args>
	std::uint32_t SendExternalEventWithCallback(
		const RE::BSFixedString& a_eventName,
		const RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor>& a_callbackFunctor,
		Args&&... a_args)
		requires((RE::BSScript::ValidateParameter<std::remove_reference_t<Args>>() && ...));

	[[nodiscard]] bool IsRegisteredForOnInput(REX::Observer<const RE::BSInputEventUser*> a_inputReceiver);
	bool RegisterForOnInput(REX::Owner<RE::BSInputEventUser*> a_inputReceiver);
	bool UnregisterForOnInput(REX::Observer<const RE::BSInputEventUser*> a_inputReceiver);

	[[nodiscard]] bool IsRegisteredForScriptLogForwarding();
	bool RegisterForScriptLogForwarding();
	bool UnregisterForScriptLogForwarding();
}

#include "F4SE/Events.inl"
