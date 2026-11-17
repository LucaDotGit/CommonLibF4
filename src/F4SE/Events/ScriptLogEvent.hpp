#pragma once

namespace RE
{
	template <class T>
	class BSTEventSink;
}

namespace RE::BSScript
{
	class IVirtualMachine;
	class LogEvent;
}

namespace F4SE::Events
{
	[[nodiscard]]
	auto IsRegisteredForOnScriptLog(RE::BSScript::IVirtualMachine& a_scriptVM) -> bool;
	auto RegisterForOnScriptLog(RE::BSScript::IVirtualMachine& a_scriptVM) -> bool;
	auto UnregisterForOnScriptLog(RE::BSScript::IVirtualMachine& a_scriptVM) -> bool;

	[[nodiscard]]
	auto IsRegisteredForOnScriptLog(
		RE::BSScript::IVirtualMachine& a_scriptVM,
		RE::BSTEventSink<RE::BSScript::LogEvent>& a_eventSink) -> bool;
	auto RegisterForOnScriptLog(
		RE::BSScript::IVirtualMachine& a_scriptVM,
		RE::BSTEventSink<RE::BSScript::LogEvent>& a_eventSink) -> bool;
	auto UnregisterForOnScriptLog(
		RE::BSScript::IVirtualMachine& a_scriptVM,
		RE::BSTEventSink<RE::BSScript::LogEvent>& a_eventSink) -> bool;
}
