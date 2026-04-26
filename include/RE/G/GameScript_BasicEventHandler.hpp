#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTSingleton.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE
{
	class BGSLocationLoadedEvent;
	class BGSOnPlayerCompanionDismiss;
	class BGSOnPlayerCreateRobotEvent;
	class BGSOnPlayerCreateRobotEvent;
	class BGSOnPlayerEnterVertibirdEvent;
	class BGSOnPlayerFallLongDistances;
	class BGSOnPlayerFireWeaponEvent;
	class BGSOnPlayerHealTeammateEvent;
	class BGSOnPlayerModArmorWeaponEvent;
	class BGSOnPlayerModRobotEvent;
	class BGSOnPlayerSwimmingEvent;
	class BGSOnPlayerUseWorkBenchEvent;
	class BGSOnSpeechChallengeAvailable;
	class TESActivateEvent;
	class TESActiveEffectApplyRemoveEvent;
	class TESActorLocationChangeEvent;
	class TESBookReadEvent;
	class TESCellAttachDetachEvent;
	class TESCellFullyLoadedEvent;
	class TESCombatEvent;
	class TESCommandModeCompleteCommandEvent;
	class TESCommandModeEnterEvent;
	class TESCommandModeExitEvent;
	class TESCommandModeGiveCommandEvent;
	class TESConsciousnessEvent;
	class TESDeathEvent;
	class TESDeferredKillEvent;
	class TESDestructionStageChangedEvent;
	class TESEnterBleedoutEvent;
	class TESEnterSneakingEvent;
	class TESEscortWaitStartEvent;
	class TESEscortWaitStopEvent;
	class TESExitFurnitureEvent;
	class TESFurnitureEvent;
	class TESGrabReleaseEvent;
	class TESLimbCrippleEvent;
	class TESLoadGameEvent;
	class TESLocationClearedEvent;
	class TESLockChangedEvent;
	class TESObjectLoadedEvent;
	class TESObjectREFRTranslationEvent;
	class TESOnPCDialogueTargetEvent;
	class TESOpenCloseEvent;
	class TESPickpocketFailedEvent;
	class TESQuestInitEvent;
	class TESResetEvent;
	class TESSellEvent;
	class TESSpellCastEvent;
	class TESSwitchRaceCompleteEvent;
	class TESTrapHitEvent;
	class TESTriggerEnterEvent;
	class TESTriggerLeaveEvent;
	class WorkshopNPCTransferEvent;
}

namespace RE::BSScript
{
	class IVirtualMachine;
	class Object;
}

namespace RE::PlayerDifficultySettingChanged
{
	class Event;
}

namespace RE::RadioManager
{
	class PipboyTransmitterDetectionEvent;
}

namespace RE::Workshop
{
	class ItemDestroyedEvent;
	class ItemGrabbedEvent;
	class ItemMovedEvent;
	class ItemPlacedEvent;
	class ItemRepairedEvent;
	class PowerOffEvent;
	class PowerOnEvent;
	class WorkshopModeEvent;
}

namespace RE::GameScript
{
	class FragmentSystem;
	class GameVM;
	class HandlePolicy;
	class ObjectBindPolicy;

	class __declspec(novtable) BasicEventHandler
		: public BSTEventSink<BGSLocationLoadedEvent>,						  // 000
		  public BSTEventSink<BGSOnPlayerCompanionDismiss>,					  // 008
		  public BSTEventSink<BGSOnPlayerEnterVertibirdEvent>,				  // 010
		  public BSTEventSink<BGSOnPlayerFallLongDistances>,				  // 018
		  public BSTEventSink<BGSOnPlayerFireWeaponEvent>,					  // 020
		  public BSTEventSink<BGSOnPlayerHealTeammateEvent>,				  // 028
		  public BSTEventSink<BGSOnPlayerModArmorWeaponEvent>,				  // 030
		  public BSTEventSink<BGSOnPlayerCreateRobotEvent>,					  // 038
		  public BSTEventSink<BGSOnPlayerModRobotEvent>,					  // 040
		  public BSTEventSink<BGSOnPlayerSwimmingEvent>,					  // 048
		  public BSTEventSink<BGSOnPlayerUseWorkBenchEvent>,				  // 050
		  public BSTEventSink<BGSOnSpeechChallengeAvailable>,				  // 058
		  public BSTEventSink<PlayerDifficultySettingChanged::Event>,		  // 060
		  public BSTEventSink<RadioManager::PipboyTransmitterDetectionEvent>, // 068
		  public BSTEventSink<TESActiveEffectApplyRemoveEvent>,				  // 070
		  public BSTEventSink<TESActivateEvent>,							  // 078
		  public BSTEventSink<TESActorLocationChangeEvent>,					  // 080
		  public BSTEventSink<TESBookReadEvent>,							  // 088
		  public BSTEventSink<TESCellAttachDetachEvent>,					  // 090
		  public BSTEventSink<TESCellFullyLoadedEvent>,						  // 098
		  public BSTEventSink<TESCombatEvent>,								  // 0A0
		  public BSTEventSink<TESCommandModeCompleteCommandEvent>,			  // 0A8
		  public BSTEventSink<TESCommandModeEnterEvent>,					  // 0B0
		  public BSTEventSink<TESCommandModeExitEvent>,						  // 0B8
		  public BSTEventSink<TESCommandModeGiveCommandEvent>,				  // 0C0
		  public BSTEventSink<TESDeathEvent>,								  // 0C8
		  public BSTEventSink<TESDeferredKillEvent>,						  // 0D0
		  public BSTEventSink<TESDestructionStageChangedEvent>,				  // 0D8
		  public BSTEventSink<TESEnterBleedoutEvent>,						  // 0E0
		  public BSTEventSink<TESEnterSneakingEvent>,						  // 0E8
		  public BSTEventSink<TESEscortWaitStartEvent>,						  // 0F0
		  public BSTEventSink<TESEscortWaitStopEvent>,						  // 0F8
		  public BSTEventSink<TESExitFurnitureEvent>,						  // 100
		  public BSTEventSink<TESFurnitureEvent>,							  // 108
		  public BSTEventSink<TESGrabReleaseEvent>,							  // 110
		  public BSTEventSink<TESConsciousnessEvent>,						  // 118
		  public BSTEventSink<TESLimbCrippleEvent>,							  // 120
		  public BSTEventSink<TESLoadGameEvent>,							  // 128
		  public BSTEventSink<TESLocationClearedEvent>,						  // 130
		  public BSTEventSink<TESLockChangedEvent>,							  // 138
		  public BSTEventSink<TESObjectLoadedEvent>,						  // 140
		  public BSTEventSink<TESObjectREFRTranslationEvent>,				  // 148
		  public BSTEventSink<TESOnPCDialogueTargetEvent>,					  // 150
		  public BSTEventSink<TESOpenCloseEvent>,							  // 158
		  public BSTEventSink<TESPickpocketFailedEvent>,					  // 160
		  public BSTEventSink<TESQuestInitEvent>,							  // 168
		  public BSTEventSink<TESResetEvent>,								  // 170
		  public BSTEventSink<TESSellEvent>,								  // 178
		  public BSTEventSink<TESSpellCastEvent>,							  // 180
		  public BSTEventSink<TESSwitchRaceCompleteEvent>,					  // 188
		  public BSTEventSink<TESTrapHitEvent>,								  // 190
		  public BSTEventSink<TESTriggerEnterEvent>,						  // 198
		  public BSTEventSink<TESTriggerLeaveEvent>,						  // 1A0
		  public BSTEventSink<Workshop::ItemDestroyedEvent>,				  // 1A8
		  public BSTEventSink<Workshop::ItemMovedEvent>,					  // 1B0
		  public BSTEventSink<Workshop::ItemPlacedEvent>,					  // 1B8
		  public BSTEventSink<Workshop::ItemRepairedEvent>,					  // 1C0
		  public BSTEventSink<Workshop::ItemGrabbedEvent>,					  // 1C8
		  public BSTEventSink<Workshop::PowerOffEvent>,						  // 1D0
		  public BSTEventSink<Workshop::PowerOnEvent>,						  // 1D8
		  public BSTEventSink<WorkshopNPCTransferEvent>,					  // 1E0
		  public BSTEventSink<Workshop::WorkshopModeEvent>,					  // 1E8
		  public BSTSingletonSDM<BasicEventHandler>							  // 1F0
	{
	public:
		inline static constexpr auto RTTI{ RTTI::GameScript__BasicEventHandler };
		inline static constexpr auto VTABLE{ VTABLE::GameScript__BasicEventHandler };

		~BasicEventHandler() override; // 00

		// override (BSTEventSink<BGSLocationLoadedEvent>)
		BSEventNotifyControl ProcessEvent(const BGSLocationLoadedEvent& a_event, BSTEventSource<BGSLocationLoadedEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<BGSOnPlayerCompanionDismiss>)
		BSEventNotifyControl ProcessEvent(const BGSOnPlayerCompanionDismiss& a_event, BSTEventSource<BGSOnPlayerCompanionDismiss>* a_eventSource) override; // 01

		// override (BSTEventSink<BGSOnPlayerEnterVertibirdEvent>)
		BSEventNotifyControl ProcessEvent(const BGSOnPlayerEnterVertibirdEvent& a_event, BSTEventSource<BGSOnPlayerEnterVertibirdEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<BGSOnPlayerFallLongDistances>)
		BSEventNotifyControl ProcessEvent(const BGSOnPlayerFallLongDistances& a_event, BSTEventSource<BGSOnPlayerFallLongDistances>* a_eventSource) override; // 01

		// override (BSTEventSink<BGSOnPlayerFireWeaponEvent>)
		BSEventNotifyControl ProcessEvent(const BGSOnPlayerFireWeaponEvent& a_event, BSTEventSource<BGSOnPlayerFireWeaponEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<BGSOnPlayerHealTeammateEvent>)
		BSEventNotifyControl ProcessEvent(const BGSOnPlayerHealTeammateEvent& a_event, BSTEventSource<BGSOnPlayerHealTeammateEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<BGSOnPlayerModArmorWeaponEvent>)
		BSEventNotifyControl ProcessEvent(const BGSOnPlayerModArmorWeaponEvent& a_event, BSTEventSource<BGSOnPlayerModArmorWeaponEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<BGSOnPlayerCreateRobotEvent>)
		BSEventNotifyControl ProcessEvent(const BGSOnPlayerCreateRobotEvent& a_event, BSTEventSource<BGSOnPlayerCreateRobotEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<BGSOnPlayerModRobotEvent>)
		BSEventNotifyControl ProcessEvent(const BGSOnPlayerModRobotEvent& a_event, BSTEventSource<BGSOnPlayerModRobotEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<BGSOnPlayerSwimmingEvent>)
		BSEventNotifyControl ProcessEvent(const BGSOnPlayerSwimmingEvent& a_event, BSTEventSource<BGSOnPlayerSwimmingEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<BGSOnPlayerUseWorkBenchEvent>)
		BSEventNotifyControl ProcessEvent(const BGSOnPlayerUseWorkBenchEvent& a_event, BSTEventSource<BGSOnPlayerUseWorkBenchEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<BGSOnSpeechChallengeAvailable>)
		BSEventNotifyControl ProcessEvent(const BGSOnSpeechChallengeAvailable& a_event, BSTEventSource<BGSOnSpeechChallengeAvailable>* a_eventSource) override; // 01

		// override (BSTEventSink<PlayerDifficultySettingChanged::Event>)
		BSEventNotifyControl ProcessEvent(const PlayerDifficultySettingChanged::Event& a_event, BSTEventSource<PlayerDifficultySettingChanged::Event>* a_eventSource) override; // 01

		// override (BSTEventSink<RadioManager::PipboyTransmitterDetectionEvent>)
		BSEventNotifyControl ProcessEvent(const RadioManager::PipboyTransmitterDetectionEvent& a_event, BSTEventSource<RadioManager::PipboyTransmitterDetectionEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESActiveEffectApplyRemoveEvent>)
		BSEventNotifyControl ProcessEvent(const TESActiveEffectApplyRemoveEvent& a_event, BSTEventSource<TESActiveEffectApplyRemoveEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESActivateEvent>)
		BSEventNotifyControl ProcessEvent(const TESActivateEvent& a_event, BSTEventSource<TESActivateEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESActorLocationChangeEvent>)
		BSEventNotifyControl ProcessEvent(const TESActorLocationChangeEvent& a_event, BSTEventSource<TESActorLocationChangeEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESBookReadEvent>)
		BSEventNotifyControl ProcessEvent(const TESBookReadEvent& a_event, BSTEventSource<TESBookReadEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESCellAttachDetachEvent>)
		BSEventNotifyControl ProcessEvent(const TESCellAttachDetachEvent& a_event, BSTEventSource<TESCellAttachDetachEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESCellFullyLoadedEvent>)
		BSEventNotifyControl ProcessEvent(const TESCellFullyLoadedEvent& a_event, BSTEventSource<TESCellFullyLoadedEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESCombatEvent>)
		BSEventNotifyControl ProcessEvent(const TESCombatEvent& a_event, BSTEventSource<TESCombatEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESCommandModeCompleteCommandEvent>)
		BSEventNotifyControl ProcessEvent(const TESCommandModeCompleteCommandEvent& a_event, BSTEventSource<TESCommandModeCompleteCommandEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESCommandModeEnterEvent>)
		BSEventNotifyControl ProcessEvent(const TESCommandModeEnterEvent& a_event, BSTEventSource<TESCommandModeEnterEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESCommandModeExitEvent>)
		BSEventNotifyControl ProcessEvent(const TESCommandModeExitEvent& a_event, BSTEventSource<TESCommandModeExitEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESCommandModeGiveCommandEvent>)
		BSEventNotifyControl ProcessEvent(const TESCommandModeGiveCommandEvent& a_event, BSTEventSource<TESCommandModeGiveCommandEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESDeathEvent>)
		BSEventNotifyControl ProcessEvent(const TESDeathEvent& a_event, BSTEventSource<TESDeathEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESDeferredKillEvent>)
		BSEventNotifyControl ProcessEvent(const TESDeferredKillEvent& a_event, BSTEventSource<TESDeferredKillEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESDestructionStageChangedEvent>)
		BSEventNotifyControl ProcessEvent(const TESDestructionStageChangedEvent& a_event, BSTEventSource<TESDestructionStageChangedEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESEnterBleedoutEvent>)
		BSEventNotifyControl ProcessEvent(const TESEnterBleedoutEvent& a_event, BSTEventSource<TESEnterBleedoutEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESEnterSneakingEvent>)
		BSEventNotifyControl ProcessEvent(const TESEnterSneakingEvent& a_event, BSTEventSource<TESEnterSneakingEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESEscortWaitStartEvent>)
		BSEventNotifyControl ProcessEvent(const TESEscortWaitStartEvent& a_event, BSTEventSource<TESEscortWaitStartEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESEscortWaitStopEvent>)
		BSEventNotifyControl ProcessEvent(const TESEscortWaitStopEvent& a_event, BSTEventSource<TESEscortWaitStopEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESExitFurnitureEvent>)
		BSEventNotifyControl ProcessEvent(const TESExitFurnitureEvent& a_event, BSTEventSource<TESExitFurnitureEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESFurnitureEvent>)
		BSEventNotifyControl ProcessEvent(const TESFurnitureEvent& a_event, BSTEventSource<TESFurnitureEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESGrabReleaseEvent>)
		BSEventNotifyControl ProcessEvent(const TESGrabReleaseEvent& a_event, BSTEventSource<TESGrabReleaseEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESConsciousnessEvent>)
		BSEventNotifyControl ProcessEvent(const TESConsciousnessEvent& a_event, BSTEventSource<TESConsciousnessEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESLimbCrippleEvent>)
		BSEventNotifyControl ProcessEvent(const TESLimbCrippleEvent& a_event, BSTEventSource<TESLimbCrippleEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESLoadGameEvent>)
		BSEventNotifyControl ProcessEvent(const TESLoadGameEvent& a_event, BSTEventSource<TESLoadGameEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESLocationClearedEvent>)
		BSEventNotifyControl ProcessEvent(const TESLocationClearedEvent& a_event, BSTEventSource<TESLocationClearedEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESLockChangedEvent>)
		BSEventNotifyControl ProcessEvent(const TESLockChangedEvent& a_event, BSTEventSource<TESLockChangedEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESObjectLoadedEvent>)
		BSEventNotifyControl ProcessEvent(const TESObjectLoadedEvent& a_event, BSTEventSource<TESObjectLoadedEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESObjectREFRTranslationEvent>)
		BSEventNotifyControl ProcessEvent(const TESObjectREFRTranslationEvent& a_event, BSTEventSource<TESObjectREFRTranslationEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESOnPCDialogueTargetEvent>)
		BSEventNotifyControl ProcessEvent(const TESOnPCDialogueTargetEvent& a_event, BSTEventSource<TESOnPCDialogueTargetEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESOpenCloseEvent>)
		BSEventNotifyControl ProcessEvent(const TESOpenCloseEvent& a_event, BSTEventSource<TESOpenCloseEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESPickpocketFailedEvent>)
		BSEventNotifyControl ProcessEvent(const TESPickpocketFailedEvent& a_event, BSTEventSource<TESPickpocketFailedEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESQuestInitEvent>)
		BSEventNotifyControl ProcessEvent(const TESQuestInitEvent& a_event, BSTEventSource<TESQuestInitEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESResetEvent>)
		BSEventNotifyControl ProcessEvent(const TESResetEvent& a_event, BSTEventSource<TESResetEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESSellEvent>)
		BSEventNotifyControl ProcessEvent(const TESSellEvent& a_event, BSTEventSource<TESSellEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESSpellCastEvent>)
		BSEventNotifyControl ProcessEvent(const TESSpellCastEvent& a_event, BSTEventSource<TESSpellCastEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESSwitchRaceCompleteEvent>)
		BSEventNotifyControl ProcessEvent(const TESSwitchRaceCompleteEvent& a_event, BSTEventSource<TESSwitchRaceCompleteEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESTrapHitEvent>)
		BSEventNotifyControl ProcessEvent(const TESTrapHitEvent& a_event, BSTEventSource<TESTrapHitEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESTriggerEnterEvent>)
		BSEventNotifyControl ProcessEvent(const TESTriggerEnterEvent& a_event, BSTEventSource<TESTriggerEnterEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESTriggerLeaveEvent>)
		BSEventNotifyControl ProcessEvent(const TESTriggerLeaveEvent& a_event, BSTEventSource<TESTriggerLeaveEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<Workshop::ItemDestroyedEvent>)
		BSEventNotifyControl ProcessEvent(const Workshop::ItemDestroyedEvent& a_event, BSTEventSource<Workshop::ItemDestroyedEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<Workshop::ItemMovedEvent>)
		BSEventNotifyControl ProcessEvent(const Workshop::ItemMovedEvent& a_event, BSTEventSource<Workshop::ItemMovedEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<Workshop::ItemPlacedEvent>)
		BSEventNotifyControl ProcessEvent(const Workshop::ItemPlacedEvent& a_event, BSTEventSource<Workshop::ItemPlacedEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<Workshop::ItemRepairedEvent>)
		BSEventNotifyControl ProcessEvent(const Workshop::ItemRepairedEvent& a_event, BSTEventSource<Workshop::ItemRepairedEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<Workshop::ItemGrabbedEvent>)
		BSEventNotifyControl ProcessEvent(const Workshop::ItemGrabbedEvent& a_event, BSTEventSource<Workshop::ItemGrabbedEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<Workshop::PowerOffEvent>)
		BSEventNotifyControl ProcessEvent(const Workshop::PowerOffEvent& a_event, BSTEventSource<Workshop::PowerOffEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<Workshop::PowerOnEvent>)
		BSEventNotifyControl ProcessEvent(const Workshop::PowerOnEvent& a_event, BSTEventSource<Workshop::PowerOnEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<WorkshopNPCTransferEvent>)
		BSEventNotifyControl ProcessEvent(const WorkshopNPCTransferEvent& a_event, BSTEventSource<WorkshopNPCTransferEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<Workshop::WorkshopModeEvent>)
		BSEventNotifyControl ProcessEvent(const Workshop::WorkshopModeEvent& a_event, BSTEventSource<Workshop::WorkshopModeEvent>* a_eventSource) override; // 01

		[[nodiscard]] static BasicEventHandler* GetSingleton()
		{
			static const auto SINGLETON = REL::Relocation<BasicEventHandler**>{ ID::GameScript::BasicEventHandler::Singleton };
			return *SINGLETON;
		}

		// members
		GameVM* gameVM;								   // 1F8
		FragmentSystem* fragmentSystem;				   // 200
		HandlePolicy* handlePolicy;					   // 208
		ObjectBindPolicy* objectBindPolicy;			   // 210
		BSTSmartPointer<BSScript::IVirtualMachine> vm; // 218
	};
	static_assert(sizeof(BasicEventHandler) == 0x220);
}
