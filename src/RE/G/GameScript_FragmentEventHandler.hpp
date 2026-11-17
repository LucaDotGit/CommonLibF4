#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTSingleton.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE
{
	class GameVM;
	class TerminalMenuItemRunEvent;
	class TESPackageEvent;
	class TESPerkEntryRunEvent;
	class TESQuestStageEvent;
	class TESSceneActionEvent;
	class TESSceneEvent;
	class TESScenePhaseEvent;
	class TESTopicInfoEvent;
}

namespace RE::BSScript
{
	class IVirtualMachine;
}

namespace RE::GameScript
{
	class FragmentSystem;
	class HandlePolicy;
}

namespace RE::GameScript
{
	class __declspec(novtable) FragmentEventHandler :
		public BSTEventSink<TerminalMenuItemRunEvent>, // 0x00
		public BSTEventSink<TESPackageEvent>,		   // 0x08
		public BSTEventSink<TESPerkEntryRunEvent>,	   // 0x10
		public BSTEventSink<TESQuestStageEvent>,	   // 0x18
		public BSTEventSink<TESSceneActionEvent>,	   // 0x20
		public BSTEventSink<TESSceneEvent>,			   // 0x28
		public BSTEventSink<TESScenePhaseEvent>,	   // 0x30
		public BSTEventSink<TESTopicInfoEvent>,		   // 0x38
		public BSTSingletonSDM<FragmentEventHandler>   // 0x40
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::GameScript__FragmentEventHandler;
		inline static constexpr const auto& VTABLE = VTABLE::GameScript__FragmentEventHandler;

		~FragmentEventHandler() override; // 0x00

		// override (BSTEventSink<TerminalMenuItemRunEvent>)
		auto ProcessEvent(
			const TerminalMenuItemRunEvent& a_event,
			BSTEventSource<TerminalMenuItemRunEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESPackageEvent>)
		auto ProcessEvent(
			const TESPackageEvent& a_event,
			BSTEventSource<TESPackageEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESPerkEntryRunEvent>)
		auto ProcessEvent(
			const TESPerkEntryRunEvent& a_event,
			BSTEventSource<TESPerkEntryRunEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESQuestStageEvent>)
		auto ProcessEvent(
			const TESQuestStageEvent& a_event,
			BSTEventSource<TESQuestStageEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESSceneActionEvent>)
		auto ProcessEvent(
			const TESSceneActionEvent& a_event,
			BSTEventSource<TESSceneActionEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESSceneEvent>)
		auto ProcessEvent(const TESSceneEvent& a_event, BSTEventSource<TESSceneEvent>* a_eventSource)
			-> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESScenePhaseEvent>)
		auto ProcessEvent(
			const TESScenePhaseEvent& a_event,
			BSTEventSource<TESScenePhaseEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESTopicInfoEvent>)
		auto ProcessEvent(
			const TESTopicInfoEvent& a_event,
			BSTEventSource<TESTopicInfoEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		[[nodiscard]]
		static auto GetSingleton() noexcept -> FragmentEventHandler*
		{
			static const auto SINGLETON =
				REL::Relocation<FragmentEventHandler**>{ID::GameScript::FragmentEventHandler::Singleton};
			return *SINGLETON;
		}

		// members
		GameVM* gameVM;								   // 0x48
		FragmentSystem* fragmentSystem;				   // 0x50
		HandlePolicy* handlePolicy;					   // 0x58
		BSTSmartPointer<BSScript::IVirtualMachine> vm; // 0x60
	};

	static_assert(sizeof(FragmentEventHandler) == 0x68);
}
