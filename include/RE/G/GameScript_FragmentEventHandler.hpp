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
	class __declspec(novtable) FragmentEventHandler
		: public BSTEventSink<TerminalMenuItemRunEvent>, // 00
		  public BSTEventSink<TESPackageEvent>,			 // 08
		  public BSTEventSink<TESPerkEntryRunEvent>,	 // 10
		  public BSTEventSink<TESQuestStageEvent>,		 // 18
		  public BSTEventSink<TESSceneActionEvent>,		 // 20
		  public BSTEventSink<TESSceneEvent>,			 // 28
		  public BSTEventSink<TESScenePhaseEvent>,		 // 30
		  public BSTEventSink<TESTopicInfoEvent>,		 // 38
		  public BSTSingletonSDM<FragmentEventHandler>	 // 40
	{
	public:
		inline static constexpr auto RTTI{ RTTI::GameScript__FragmentEventHandler };
		inline static constexpr auto VTABLE{ VTABLE::GameScript__FragmentEventHandler };

		~FragmentEventHandler() override; // 00

		// override (BSTEventSink<TerminalMenuItemRunEvent>)
		BSEventNotifyControl ProcessEvent(const TerminalMenuItemRunEvent& a_event, BSTEventSource<TerminalMenuItemRunEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESPackageEvent>)
		BSEventNotifyControl ProcessEvent(const TESPackageEvent& a_event, BSTEventSource<TESPackageEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESPerkEntryRunEvent>)
		BSEventNotifyControl ProcessEvent(const TESPerkEntryRunEvent& a_event, BSTEventSource<TESPerkEntryRunEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESQuestStageEvent>)
		BSEventNotifyControl ProcessEvent(const TESQuestStageEvent& a_event, BSTEventSource<TESQuestStageEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESSceneActionEvent>)
		BSEventNotifyControl ProcessEvent(const TESSceneActionEvent& a_event, BSTEventSource<TESSceneActionEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESSceneEvent>)
		BSEventNotifyControl ProcessEvent(const TESSceneEvent& a_event, BSTEventSource<TESSceneEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESScenePhaseEvent>)
		BSEventNotifyControl ProcessEvent(const TESScenePhaseEvent& a_event, BSTEventSource<TESScenePhaseEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESTopicInfoEvent>)
		BSEventNotifyControl ProcessEvent(const TESTopicInfoEvent& a_event, BSTEventSource<TESTopicInfoEvent>* a_eventSource) override; // 01

		[[nodiscard]] static FragmentEventHandler* GetSingleton()
		{
			static const auto SINGLETON = REL::Relocation<FragmentEventHandler**>{ ID::GameScript::FragmentEventHandler::Singleton };
			return *SINGLETON;
		}

		// members
		GameVM* gameVM;								   // 48
		FragmentSystem* fragmentSystem;				   // 50
		HandlePolicy* handlePolicy;					   // 58
		BSTSmartPointer<BSScript::IVirtualMachine> vm; // 60
	};
	static_assert(sizeof(FragmentEventHandler) == 0x68);
}
