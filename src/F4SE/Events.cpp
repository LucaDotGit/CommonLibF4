#include "F4SE/Events.hpp"

#include "F4SE/API.hpp"
#include "F4SE/PapyrusInterface.hpp"

#include "RE/B/BSScriptUtil_External.hpp" // IWYU pragma: keep
#include "RE/B/BSScriptUtil_InternalLogEvent.hpp"
#include "RE/B/BSScript_ErrorLogger.hpp"
#include "RE/B/BSScript_IStackCallbackFunctor.hpp"
#include "RE/B/BSScript_IVirtualMachine.hpp"
#include "RE/B/BSScript_Object.hpp"
#include "RE/B/BSScript_Variable.hpp"
#include "RE/G/GameVM.hpp"
#include "RE/M/MenuControls.hpp"

#include "REX/Contract.hpp"
#include "REX/Log.hpp"
#include "REX/Singleton.hpp"

namespace F4SE::Events::Impl
{
	using ScriptLogSeverity = RE::BSScript::ErrorLogger::Severity;
	using InternalLogLevel = REX::LogLevel;

	[[nodiscard]] static constexpr InternalLogLevel GetLogLevelForScriptSeverity(ScriptLogSeverity a_logLevel) noexcept
	{
		switch (a_logLevel) {
			case ScriptLogSeverity::kInfo: {
				return InternalLogLevel::kInformation;
			}
			case ScriptLogSeverity::kWarning: {
				return InternalLogLevel::kWarning;
			}
			case ScriptLogSeverity::kError: {
				return InternalLogLevel::kError;
			}
			case ScriptLogSeverity::kFatal: {
				return InternalLogLevel::kCritical;
			}
			[[unlikely]] default: {
				return InternalLogLevel::kNone;
			}
		}
	}

	class ScriptLogEventHandler final
		: public REX::Singleton<ScriptLogEventHandler>,
		  public RE::BSTEventSink<RE::BSScript::Impl::InternalLogEvent>
	{
	public:
		ScriptLogEventHandler() = default;
		~ScriptLogEventHandler() noexcept override = default;

		ScriptLogEventHandler(const ScriptLogEventHandler&) = delete;
		ScriptLogEventHandler(ScriptLogEventHandler&&) = delete;

		ScriptLogEventHandler& operator=(const ScriptLogEventHandler&) = delete;
		ScriptLogEventHandler& operator=(ScriptLogEventHandler&&) = delete;

		RE::BSEventNotifyControl ProcessEvent(const RE::BSScript::Impl::InternalLogEvent& a_event,
			[[maybe_unused]] RE::BSTEventSource<RE::BSScript::Impl::InternalLogEvent>* a_eventSource) override
		{
			const auto logMessage = a_event.message;
			const auto logLevel = GetLogLevelForScriptSeverity(a_event.severity.get());
			const auto stackID = a_event.stackID;

			REX::Log(logLevel, "[Papyrus] [Stack ID: {}] {}"sv,
				stackID, logMessage);
			return RE::BSEventNotifyControl::kContinue;
		}
	};
}

namespace F4SE::Events
{
	bool IsRegisteredForExternalEvent(const RE::BSFixedString& a_eventName, const ExternalEventInfo& a_eventInfo)
	{
		class ExternalEventVisitor final
		{
		public:
			ExternalEventInfo eventInfo;
			mutable bool hasFound{ false };
		};

		auto eventVisitor = ExternalEventVisitor{
			.eventInfo = a_eventInfo
		};

		F4SE::GetPapyrusInterface()->GetExternalEventRegistrations(a_eventName.data(), std::addressof(eventVisitor),
			[](RE::BSScript::ObjectHandle a_objectHandle, const char* a_scriptName, const char* a_callbackName, void* a_data) {
				const auto* eventVisitor = static_cast<const ExternalEventVisitor*>(a_data);
				if (!eventVisitor) [[unlikely]] {
					REX::Assert(false);
					return;
				}

				if (eventVisitor->hasFound) {
					return;
				}

				if (a_objectHandle != eventVisitor->eventInfo.objectHandle ||
					a_scriptName != eventVisitor->eventInfo.scriptName) {
					return;
				}

				const auto& functionName = eventVisitor->eventInfo.functionName;
				if (!functionName.empty() && functionName != a_callbackName) {
					return;
				}

				eventVisitor->hasFound = true;
			});

		return eventVisitor.hasFound;
	}

	auto GetExternalEventRegistrations(const RE::BSFixedString& a_eventName) -> std::vector<ExternalEventInfo>
	{
		class ExternalEventCollector final
		{
		public:
			mutable std::vector<ExternalEventInfo> events;
		};

		auto eventCollector = ExternalEventCollector();

		F4SE::GetPapyrusInterface()->GetExternalEventRegistrations(a_eventName.data(), std::addressof(eventCollector),
			[](RE::BSScript::ObjectHandle a_objectHandle, const char* a_scriptName, const char* a_callbackName, void* a_data) {
				const auto* eventCollector = static_cast<const ExternalEventCollector*>(a_data);
				if (!eventCollector) [[unlikely]] {
					REX::Assert(false);
					return;
				}

				auto eventInfo = ExternalEventInfo{
					.objectHandle = a_objectHandle,
					.scriptName = a_scriptName,
					.functionName = a_callbackName
				};

				eventCollector->events.push_back(std::move(eventInfo));
			});

		return eventCollector.events;
	}

	std::uint32_t SendAppliedExternalEvent(
		const RE::BSFixedString& a_eventName,
		const REX::NotNull<std::function<std::vector<RE::BSScript::Variable>()>>& a_argsFactory)
	{
		constexpr auto STACK_CALLBACK = RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor>();
		return SendAppliedExternalEventWithCallback(a_eventName, STACK_CALLBACK, a_argsFactory);
	}

	std::uint32_t SendAppliedExternalEventWithCallback(
		const RE::BSFixedString& a_eventName,
		const RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor>& a_callbackFunctor,
		const REX::NotNull<std::function<std::vector<RE::BSScript::Variable>()>>& a_argsFactory)
	{
		auto eventRegistrations = GetExternalEventRegistrations(a_eventName);
		if (eventRegistrations.empty()) {
			return 0;
		}

		auto scriptVM = RE::GameVM::GetVMInterface();
		if (!scriptVM) [[unlikely]] {
			REX::Assert(false);
			return 0;
		}

		const auto packedArgs = std::invoke(*a_argsFactory);

		auto invokeCount = 0ui32;

		for (const auto& eventInfo : eventRegistrations) {
			auto scriptObject = RE::BSTSmartPointer<RE::BSScript::Object>();
			if (!scriptVM->GetScriptObjectExact(eventInfo.scriptName, eventInfo.objectHandle, scriptObject) || !scriptObject) {
				continue;
			}

			if (scriptVM->InvokeAppliedMemberFunction(scriptObject, eventInfo.functionName, a_callbackFunctor, packedArgs)) {
				invokeCount++;
			}
		}

		return invokeCount;
	}

	bool IsRegisteredForScriptLogForwarding()
	{
		const auto& logEventSource = RE::BSScript::Impl::InternalLogEventSource::GetSingleton();
		return logEventSource->IsSinkRegistered(Impl::ScriptLogEventHandler::GetSingleton().get().get());
	}

	bool RegisterForScriptLogForwarding()
	{
		const auto& logEventSource = RE::BSScript::Impl::InternalLogEventSource::GetSingleton();
		return logEventSource->RegisterSink(Impl::ScriptLogEventHandler::GetSingleton().get().get());
	}

	bool UnregisterForScriptLogForwarding()
	{
		const auto& logEventSource = RE::BSScript::Impl::InternalLogEventSource::GetSingleton();
		return logEventSource->UnregisterSink(Impl::ScriptLogEventHandler::GetSingleton().get().get());
	}

	// Doing the same with `RE::PlayerControls` would cause the events to only fire in game mode,
	// so `RE::MenuControls` is used instead, which almost always processes input events.

	bool IsRegisteredForOnInput(REX::Observer<const RE::BSInputEventUser*> a_inputReceiver)
	{
		if (!a_inputReceiver) {
			return false;
		}

		auto* menuControls = RE::MenuControls::GetSingleton();
		if (!menuControls) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		const auto& eventHandlers = menuControls->handlers;
		return std::ranges::contains(eventHandlers, a_inputReceiver);
	}

	bool RegisterForOnInput(REX::Owner<RE::BSInputEventUser*> a_inputReceiver)
	{
		if (!a_inputReceiver) {
			return false;
		}

		auto* menuControls = RE::MenuControls::GetSingleton();
		if (!menuControls) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		menuControls->handlers.push_back(a_inputReceiver);
		return true;
	}

	bool UnregisterForOnInput(REX::Observer<const RE::BSInputEventUser*> a_inputReceiver)
	{
		if (!a_inputReceiver) {
			return false;
		}

		auto* menuControls = RE::MenuControls::GetSingleton();
		if (!menuControls) [[unlikely]] {
			REX::Assert(false);
			return false;
		}

		auto& eventHandlers = menuControls->handlers;

		const auto* handlerIt = std::ranges::find(eventHandlers, a_inputReceiver);
		if (handlerIt == eventHandlers.end()) {
			return false;
		}

		eventHandlers.erase(handlerIt);
		return true;
	}
}
