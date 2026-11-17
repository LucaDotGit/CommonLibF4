#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSScriptUtility_Concepts.hpp"
#include "RE/B/BSScriptUtility_Core.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/CoreTypes.hpp"
#include "REX/NotNull.hpp"

namespace RE::BSScript
{
	class IStackCallbackFunctor;
	class IVirtualMachine;
	class Variable;
}

namespace F4SE::Events
{
	using ArgsFactoryCallback = void(RE::BSScrapArray<RE::BSScript::Variable>& a_outArgs) const;

	class ExternalEventInfo final
	{
	public:
		ExternalEventInfo(RE::BSScript::ObjectHandle a_objectHandle, RE::BSFixedString a_scriptName) :
			_objectHandle(a_objectHandle),
			_scriptName(std::move(a_scriptName))
		{
		}

		ExternalEventInfo(
			RE::BSScript::ObjectHandle a_objectHandle,
			RE::BSFixedString a_scriptName,
			RE::BSFixedString a_functionName) :
			_objectHandle(a_objectHandle),
			_scriptName(std::move(a_scriptName)),
			_functionName(std::move(a_functionName))
		{
		}

		~ExternalEventInfo() noexcept = default;

		ExternalEventInfo(const ExternalEventInfo&) = default;
		ExternalEventInfo(ExternalEventInfo&&) noexcept = default;

		auto operator=(const ExternalEventInfo&) -> ExternalEventInfo& = default;
		auto operator=(ExternalEventInfo&&) noexcept -> ExternalEventInfo& = default;

		[[nodiscard]]
		auto GetObjectHandle() const noexcept
		{
			return _objectHandle;
		}

		[[nodiscard]]
		auto GetScriptName() const noexcept
		{
			return _scriptName;
		}

		[[nodiscard]]
		auto GetFunctionName() const noexcept
		{
			return _functionName;
		}

	private:
		RE::BSScript::ObjectHandle _objectHandle;
		RE::BSFixedString _scriptName;
		RE::BSFixedString _functionName;
	};

	[[nodiscard]]
	auto IsRegisteredForExternalEvent(const RE::BSFixedString& a_eventName, ExternalEventInfo a_eventInfo) -> bool;

	[[nodiscard]]
	auto GetExternalEventRegistrations(const RE::BSFixedString& a_eventName) -> RE::BSTArray<ExternalEventInfo>;

	auto SendAppliedExternalEvent(
		RE::BSScript::IVirtualMachine& a_scriptVM,
		const RE::BSFixedString& a_eventName,
		const REX::NotNull<std::move_only_function<ArgsFactoryCallback>>& a_argsFactory) -> std::uint32_t;

	auto SendAppliedExternalEventWithCallback(
		RE::BSScript::IVirtualMachine& a_scriptVM,
		const RE::BSFixedString& a_eventName,
		const RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor>& a_callbackFunctor,
		const REX::NotNull<std::move_only_function<ArgsFactoryCallback>>& a_argsFactory) -> std::uint32_t;

	template <class... Args>
	auto SendExternalEvent(const RE::BSFixedString& a_eventName, Args&&... a_args) -> std::uint32_t
		requires((RE::BSScript::ValidateParameter<std::remove_reference_t<Args>>() && ...))
	{
		return SendAppliedExternalEvent(a_eventName, [... a_args = std::forward<Args>(a_args)]() mutable -> auto {
			return RE::BSScript::PackVariables(std::forward<Args>(a_args)...);
		});
	}

	template <class... Args>
	auto SendExternalEventWithCallback(
		RE::BSScript::IVirtualMachine& a_scriptVM,
		const RE::BSFixedString& a_eventName,
		const RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor>& a_callbackFunctor,
		Args&&... a_args) -> std::uint32_t
		requires((RE::BSScript::ValidateParameter<std::remove_reference_t<Args>>() && ...))
	{
		return SendAppliedExternalEventWithCallback(
			a_scriptVM,
			a_eventName,
			a_callbackFunctor,
			[... a_args = std::forward<Args>(a_args)]() mutable -> auto {
				return RE::BSScript::PackVariables(std::forward<Args>(a_args)...);
			});
	}
}
