#include "F4SE/Events/ScriptLogEvent.hpp"

#include "F4SE/Api.hpp"
#include "RE/B/BSScript_ErrorLogger.hpp"
#include "RE/B/BSScript_IVirtualMachine.hpp"

namespace F4SE::Events
{
	auto IsRegisteredForOnScriptLog(RE::BSScript::IVirtualMachine& a_scriptVM) -> bool
	{
		return IsRegisteredForOnScriptLog(a_scriptVM, *(F4SE::GetScriptLogEventSink().get()));
	}

	auto RegisterForOnScriptLog(RE::BSScript::IVirtualMachine& a_scriptVM) -> bool
	{
		return RegisterForOnScriptLog(a_scriptVM, *(F4SE::GetScriptLogEventSink().get()));
	}

	auto UnregisterForOnScriptLog(RE::BSScript::IVirtualMachine& a_scriptVM) -> bool
	{
		return UnregisterForOnScriptLog(a_scriptVM, *(F4SE::GetScriptLogEventSink().get()));
	}

	auto IsRegisteredForOnScriptLog(
		RE::BSScript::IVirtualMachine& a_scriptVM,
		RE::BSTEventSink<RE::BSScript::LogEvent>& a_eventSink) -> bool
	{
		const auto& errorLogger = a_scriptVM.GetErrorLogger();
		return errorLogger.IsSinkRegistered(std::addressof(a_eventSink));
	}

	auto RegisterForOnScriptLog(
		RE::BSScript::IVirtualMachine& a_scriptVM,
		RE::BSTEventSink<RE::BSScript::LogEvent>& a_eventSink) -> bool
	{
		auto& errorLogger = a_scriptVM.GetErrorLogger();
		return errorLogger.RegisterSink(std::addressof(a_eventSink));
	}

	auto UnregisterForOnScriptLog(
		RE::BSScript::IVirtualMachine& a_scriptVM,
		RE::BSTEventSink<RE::BSScript::LogEvent>& a_eventSink) -> bool
	{
		auto& errorLogger = a_scriptVM.GetErrorLogger();
		return errorLogger.UnregisterSink(std::addressof(a_eventSink));
	}
}
