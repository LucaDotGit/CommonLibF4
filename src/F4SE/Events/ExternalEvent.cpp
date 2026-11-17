#include "F4SE/Events/ExternalEvent.hpp"

#include "F4SE/Api.hpp"
#include "F4SE/PapyrusInterface.hpp"
#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSScriptUtility_External.hpp" // IWYU pragma: keep
#include "RE/B/BSScript_IStackCallbackFunctor.hpp"
#include "RE/B/BSScript_IVirtualMachine.hpp"
#include "RE/B/BSScript_Object.hpp"
#include "RE/B/BSScript_ObjectHandle.hpp"
#include "RE/B/BSScript_Variable.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/G/GameVM.hpp"
#include "REX/Contract.hpp"
#include "REX/NotNull.hpp"

namespace F4SE::Events
{
	auto IsRegisteredForExternalEvent(const RE::BSFixedString& a_eventName, ExternalEventInfo a_eventInfo) -> bool
	{
		class ExternalEventVisitor final
		{
		public:
			explicit ExternalEventVisitor(ExternalEventInfo a_eventInfo) noexcept :
				_eventInfo(std::move(a_eventInfo))
			{
			}

			~ExternalEventVisitor() noexcept = default;

			ExternalEventVisitor(const ExternalEventVisitor&) = delete;
			ExternalEventVisitor(ExternalEventVisitor&&) = delete;

			auto operator=(const ExternalEventVisitor&) -> ExternalEventVisitor& = delete;
			auto operator=(ExternalEventVisitor&&) -> ExternalEventVisitor& = delete;

			[[nodiscard]]
			auto GetEventInfo() const noexcept -> const auto&
			{
				return _eventInfo;
			}

			[[nodiscard]]
			auto GetHasFound() const noexcept
			{
				return _hasFound;
			}

			void SetHasFound(bool a_hasFound) noexcept
			{
				_hasFound = a_hasFound;
			}

		private:
			ExternalEventInfo _eventInfo;
			bool _hasFound{false};
		};

		auto eventVisitor = ExternalEventVisitor(std::move(a_eventInfo));

		F4SE::GetPapyrusInterface()->GetExternalEventRegistrations(
			a_eventName.data(),
			std::addressof(eventVisitor),
			[](RE::BSScript::ObjectHandle a_objectHandle,
			   const char* a_scriptName,
			   const char* a_callbackName,
			   void* a_data) noexcept -> void {
				auto* eventVisitor = static_cast<ExternalEventVisitor*>(a_data);
				if (!eventVisitor) [[unlikely]] {
					REX::Assert(false);
					return;
				}

				if (eventVisitor->GetHasFound()) {
					return;
				}

				if (a_objectHandle != eventVisitor->GetEventInfo().GetObjectHandle() ||
					a_scriptName != eventVisitor->GetEventInfo().GetScriptName()) {
					return;
				}

				const auto& functionName = eventVisitor->GetEventInfo().GetFunctionName();
				if (!functionName.empty() && functionName != a_callbackName) {
					return;
				}

				eventVisitor->SetHasFound(true);
			});

		return eventVisitor.GetHasFound();
	}

	auto GetExternalEventRegistrations(const RE::BSFixedString& a_eventName) -> RE::BSTArray<ExternalEventInfo>
	{
		using ExternalEventCollector = RE::BSTArray<ExternalEventInfo>;

		auto eventCollector = ExternalEventCollector();

		F4SE::GetPapyrusInterface()->GetExternalEventRegistrations(
			a_eventName.data(),
			std::addressof(eventCollector),
			[](RE::BSScript::ObjectHandle a_objectHandle,
			   const char* a_scriptName,
			   const char* a_callbackName,
			   void* a_data) -> void {
				auto* eventCollector = static_cast<ExternalEventCollector*>(a_data);
				if (!eventCollector) [[unlikely]] {
					REX::Assert(false);
					return;
				}

				auto eventInfo = ExternalEventInfo(a_objectHandle, a_scriptName, a_callbackName);
				eventCollector->push_back(std::move(eventInfo));
			});

		return eventCollector;
	}

	auto SendAppliedExternalEvent(
		RE::BSScript::IVirtualMachine& a_scriptVM,
		const RE::BSFixedString& a_eventName,
		const REX::NotNull<std::move_only_function<ArgsFactoryCallback>>& a_argsFactory) -> std::uint32_t
	{
		constexpr auto STACK_CALLBACK = RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor>();
		return SendAppliedExternalEventWithCallback(a_scriptVM, a_eventName, STACK_CALLBACK, a_argsFactory);
	}

	auto SendAppliedExternalEventWithCallback(
		RE::BSScript::IVirtualMachine& a_scriptVM,
		const RE::BSFixedString& a_eventName,
		const RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor>& a_callbackFunctor,
		const REX::NotNull<std::move_only_function<ArgsFactoryCallback>>& a_argsFactory) -> std::uint32_t
	{
		const auto eventRegistrations = GetExternalEventRegistrations(a_eventName);
		if (eventRegistrations.empty()) {
			return 0;
		}

		auto packedArgs = RE::BSScrapArray<RE::BSScript::Variable>();
		std::invoke(a_argsFactory.get(), packedArgs);

		auto invokeCount = static_cast<std::uint32_t>(0);

		for (const auto& eventInfo : eventRegistrations) {
			auto scriptObject = RE::BSTSmartPointer<RE::BSScript::Object>();
			if (!a_scriptVM.GetScriptObjectExact(
					eventInfo.GetScriptName(),
					eventInfo.GetObjectHandle(),
					scriptObject) ||
				!scriptObject) {
				continue;
			}

			if (a_scriptVM.InvokeAppliedMemberFunction(
					scriptObject,
					eventInfo.GetFunctionName(),
					a_callbackFunctor,
					packedArgs)) {
				invokeCount++;
			}
		}

		return invokeCount;
	}
}
