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

	class __declspec(novtable) BasicEventHandler :
		public BSTEventSink<BGSLocationLoadedEvent>,						// 0x000
		public BSTEventSink<BGSOnPlayerCompanionDismiss>,					// 0x008
		public BSTEventSink<BGSOnPlayerEnterVertibirdEvent>,				// 0x010
		public BSTEventSink<BGSOnPlayerFallLongDistances>,					// 0x018
		public BSTEventSink<BGSOnPlayerFireWeaponEvent>,					// 0x020
		public BSTEventSink<BGSOnPlayerHealTeammateEvent>,					// 0x028
		public BSTEventSink<BGSOnPlayerModArmorWeaponEvent>,				// 0x030
		public BSTEventSink<BGSOnPlayerCreateRobotEvent>,					// 0x038
		public BSTEventSink<BGSOnPlayerModRobotEvent>,						// 0x040
		public BSTEventSink<BGSOnPlayerSwimmingEvent>,						// 0x048
		public BSTEventSink<BGSOnPlayerUseWorkBenchEvent>,					// 0x050
		public BSTEventSink<BGSOnSpeechChallengeAvailable>,					// 0x058
		public BSTEventSink<PlayerDifficultySettingChanged::Event>,			// 0x060
		public BSTEventSink<RadioManager::PipboyTransmitterDetectionEvent>, // 0x068
		public BSTEventSink<TESActiveEffectApplyRemoveEvent>,				// 0x070
		public BSTEventSink<TESActivateEvent>,								// 0x078
		public BSTEventSink<TESActorLocationChangeEvent>,					// 0x080
		public BSTEventSink<TESBookReadEvent>,								// 0x088
		public BSTEventSink<TESCellAttachDetachEvent>,						// 0x090
		public BSTEventSink<TESCellFullyLoadedEvent>,						// 0x098
		public BSTEventSink<TESCombatEvent>,								// 0x0A0
		public BSTEventSink<TESCommandModeCompleteCommandEvent>,			// 0x0A8
		public BSTEventSink<TESCommandModeEnterEvent>,						// 0x0B0
		public BSTEventSink<TESCommandModeExitEvent>,						// 0x0B8
		public BSTEventSink<TESCommandModeGiveCommandEvent>,				// 0x0C0
		public BSTEventSink<TESDeathEvent>,									// 0x0C8
		public BSTEventSink<TESDeferredKillEvent>,							// 0x0D0
		public BSTEventSink<TESDestructionStageChangedEvent>,				// 0x0D8
		public BSTEventSink<TESEnterBleedoutEvent>,							// 0x0E0
		public BSTEventSink<TESEnterSneakingEvent>,							// 0x0E8
		public BSTEventSink<TESEscortWaitStartEvent>,						// 0x0F0
		public BSTEventSink<TESEscortWaitStopEvent>,						// 0x0F8
		public BSTEventSink<TESExitFurnitureEvent>,							// 0x100
		public BSTEventSink<TESFurnitureEvent>,								// 0x108
		public BSTEventSink<TESGrabReleaseEvent>,							// 0x110
		public BSTEventSink<TESConsciousnessEvent>,							// 0x118
		public BSTEventSink<TESLimbCrippleEvent>,							// 0x120
		public BSTEventSink<TESLoadGameEvent>,								// 0x128
		public BSTEventSink<TESLocationClearedEvent>,						// 0x130
		public BSTEventSink<TESLockChangedEvent>,							// 0x138
		public BSTEventSink<TESObjectLoadedEvent>,							// 0x140
		public BSTEventSink<TESObjectREFRTranslationEvent>,					// 0x148
		public BSTEventSink<TESOnPCDialogueTargetEvent>,					// 0x150
		public BSTEventSink<TESOpenCloseEvent>,								// 0x158
		public BSTEventSink<TESPickpocketFailedEvent>,						// 0x160
		public BSTEventSink<TESQuestInitEvent>,								// 0x168
		public BSTEventSink<TESResetEvent>,									// 0x170
		public BSTEventSink<TESSellEvent>,									// 0x178
		public BSTEventSink<TESSpellCastEvent>,								// 0x180
		public BSTEventSink<TESSwitchRaceCompleteEvent>,					// 0x188
		public BSTEventSink<TESTrapHitEvent>,								// 0x190
		public BSTEventSink<TESTriggerEnterEvent>,							// 0x198
		public BSTEventSink<TESTriggerLeaveEvent>,							// 0x1A0
		public BSTEventSink<Workshop::ItemDestroyedEvent>,					// 0x1A8
		public BSTEventSink<Workshop::ItemMovedEvent>,						// 0x1B0
		public BSTEventSink<Workshop::ItemPlacedEvent>,						// 0x1B8
		public BSTEventSink<Workshop::ItemRepairedEvent>,					// 0x1C0
		public BSTEventSink<Workshop::ItemGrabbedEvent>,					// 0x1C8
		public BSTEventSink<Workshop::PowerOffEvent>,						// 0x1D0
		public BSTEventSink<Workshop::PowerOnEvent>,						// 0x1D8
		public BSTEventSink<WorkshopNPCTransferEvent>,						// 0x1E0
		public BSTEventSink<Workshop::WorkshopModeEvent>,					// 0x1E8
		public BSTSingletonSDM<BasicEventHandler>							// 0x1F0
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::GameScript__BasicEventHandler;
		inline static constexpr const auto& VTABLE = VTABLE::GameScript__BasicEventHandler;

		~BasicEventHandler() override; // 0x00

		// override (BSTEventSink<BGSLocationLoadedEvent>)
		auto ProcessEvent(
			const BGSLocationLoadedEvent& a_event,
			BSTEventSource<BGSLocationLoadedEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<BGSOnPlayerCompanionDismiss>)
		auto ProcessEvent(
			const BGSOnPlayerCompanionDismiss& a_event,
			BSTEventSource<BGSOnPlayerCompanionDismiss>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<BGSOnPlayerEnterVertibirdEvent>)
		auto ProcessEvent(
			const BGSOnPlayerEnterVertibirdEvent& a_event,
			BSTEventSource<BGSOnPlayerEnterVertibirdEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<BGSOnPlayerFallLongDistances>)
		auto ProcessEvent(
			const BGSOnPlayerFallLongDistances& a_event,
			BSTEventSource<BGSOnPlayerFallLongDistances>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<BGSOnPlayerFireWeaponEvent>)
		auto ProcessEvent(
			const BGSOnPlayerFireWeaponEvent& a_event,
			BSTEventSource<BGSOnPlayerFireWeaponEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<BGSOnPlayerHealTeammateEvent>)
		auto ProcessEvent(
			const BGSOnPlayerHealTeammateEvent& a_event,
			BSTEventSource<BGSOnPlayerHealTeammateEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<BGSOnPlayerModArmorWeaponEvent>)
		auto ProcessEvent(
			const BGSOnPlayerModArmorWeaponEvent& a_event,
			BSTEventSource<BGSOnPlayerModArmorWeaponEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<BGSOnPlayerCreateRobotEvent>)
		auto ProcessEvent(
			const BGSOnPlayerCreateRobotEvent& a_event,
			BSTEventSource<BGSOnPlayerCreateRobotEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<BGSOnPlayerModRobotEvent>)
		auto ProcessEvent(
			const BGSOnPlayerModRobotEvent& a_event,
			BSTEventSource<BGSOnPlayerModRobotEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<BGSOnPlayerSwimmingEvent>)
		auto ProcessEvent(
			const BGSOnPlayerSwimmingEvent& a_event,
			BSTEventSource<BGSOnPlayerSwimmingEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<BGSOnPlayerUseWorkBenchEvent>)
		auto ProcessEvent(
			const BGSOnPlayerUseWorkBenchEvent& a_event,
			BSTEventSource<BGSOnPlayerUseWorkBenchEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<BGSOnSpeechChallengeAvailable>)
		auto ProcessEvent(
			const BGSOnSpeechChallengeAvailable& a_event,
			BSTEventSource<BGSOnSpeechChallengeAvailable>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<PlayerDifficultySettingChanged::Event>)
		auto ProcessEvent(
			const PlayerDifficultySettingChanged::Event& a_event,
			BSTEventSource<PlayerDifficultySettingChanged::Event>* a_eventSource)
			-> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<RadioManager::PipboyTransmitterDetectionEvent>)
		auto ProcessEvent(
			const RadioManager::PipboyTransmitterDetectionEvent& a_event,
			BSTEventSource<RadioManager::PipboyTransmitterDetectionEvent>* a_eventSource)
			-> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESActiveEffectApplyRemoveEvent>)
		auto ProcessEvent(
			const TESActiveEffectApplyRemoveEvent& a_event,
			BSTEventSource<TESActiveEffectApplyRemoveEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESActivateEvent>)
		auto ProcessEvent(
			const TESActivateEvent& a_event,
			BSTEventSource<TESActivateEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESActorLocationChangeEvent>)
		auto ProcessEvent(
			const TESActorLocationChangeEvent& a_event,
			BSTEventSource<TESActorLocationChangeEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESBookReadEvent>)
		auto ProcessEvent(
			const TESBookReadEvent& a_event,
			BSTEventSource<TESBookReadEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESCellAttachDetachEvent>)
		auto ProcessEvent(
			const TESCellAttachDetachEvent& a_event,
			BSTEventSource<TESCellAttachDetachEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESCellFullyLoadedEvent>)
		auto ProcessEvent(
			const TESCellFullyLoadedEvent& a_event,
			BSTEventSource<TESCellFullyLoadedEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESCombatEvent>)
		auto ProcessEvent(const TESCombatEvent& a_event, BSTEventSource<TESCombatEvent>* a_eventSource)
			-> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESCommandModeCompleteCommandEvent>)
		auto ProcessEvent(
			const TESCommandModeCompleteCommandEvent& a_event,
			BSTEventSource<TESCommandModeCompleteCommandEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESCommandModeEnterEvent>)
		auto ProcessEvent(
			const TESCommandModeEnterEvent& a_event,
			BSTEventSource<TESCommandModeEnterEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESCommandModeExitEvent>)
		auto ProcessEvent(
			const TESCommandModeExitEvent& a_event,
			BSTEventSource<TESCommandModeExitEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESCommandModeGiveCommandEvent>)
		auto ProcessEvent(
			const TESCommandModeGiveCommandEvent& a_event,
			BSTEventSource<TESCommandModeGiveCommandEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESDeathEvent>)
		auto ProcessEvent(const TESDeathEvent& a_event, BSTEventSource<TESDeathEvent>* a_eventSource)
			-> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESDeferredKillEvent>)
		auto ProcessEvent(
			const TESDeferredKillEvent& a_event,
			BSTEventSource<TESDeferredKillEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESDestructionStageChangedEvent>)
		auto ProcessEvent(
			const TESDestructionStageChangedEvent& a_event,
			BSTEventSource<TESDestructionStageChangedEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESEnterBleedoutEvent>)
		auto ProcessEvent(
			const TESEnterBleedoutEvent& a_event,
			BSTEventSource<TESEnterBleedoutEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESEnterSneakingEvent>)
		auto ProcessEvent(
			const TESEnterSneakingEvent& a_event,
			BSTEventSource<TESEnterSneakingEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESEscortWaitStartEvent>)
		auto ProcessEvent(
			const TESEscortWaitStartEvent& a_event,
			BSTEventSource<TESEscortWaitStartEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESEscortWaitStopEvent>)
		auto ProcessEvent(
			const TESEscortWaitStopEvent& a_event,
			BSTEventSource<TESEscortWaitStopEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESExitFurnitureEvent>)
		auto ProcessEvent(
			const TESExitFurnitureEvent& a_event,
			BSTEventSource<TESExitFurnitureEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESFurnitureEvent>)
		auto ProcessEvent(
			const TESFurnitureEvent& a_event,
			BSTEventSource<TESFurnitureEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESGrabReleaseEvent>)
		auto ProcessEvent(
			const TESGrabReleaseEvent& a_event,
			BSTEventSource<TESGrabReleaseEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESConsciousnessEvent>)
		auto ProcessEvent(
			const TESConsciousnessEvent& a_event,
			BSTEventSource<TESConsciousnessEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESLimbCrippleEvent>)
		auto ProcessEvent(
			const TESLimbCrippleEvent& a_event,
			BSTEventSource<TESLimbCrippleEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESLoadGameEvent>)
		auto ProcessEvent(
			const TESLoadGameEvent& a_event,
			BSTEventSource<TESLoadGameEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESLocationClearedEvent>)
		auto ProcessEvent(
			const TESLocationClearedEvent& a_event,
			BSTEventSource<TESLocationClearedEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESLockChangedEvent>)
		auto ProcessEvent(
			const TESLockChangedEvent& a_event,
			BSTEventSource<TESLockChangedEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESObjectLoadedEvent>)
		auto ProcessEvent(
			const TESObjectLoadedEvent& a_event,
			BSTEventSource<TESObjectLoadedEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESObjectREFRTranslationEvent>)
		auto ProcessEvent(
			const TESObjectREFRTranslationEvent& a_event,
			BSTEventSource<TESObjectREFRTranslationEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESOnPCDialogueTargetEvent>)
		auto ProcessEvent(
			const TESOnPCDialogueTargetEvent& a_event,
			BSTEventSource<TESOnPCDialogueTargetEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESOpenCloseEvent>)
		auto ProcessEvent(
			const TESOpenCloseEvent& a_event,
			BSTEventSource<TESOpenCloseEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESPickpocketFailedEvent>)
		auto ProcessEvent(
			const TESPickpocketFailedEvent& a_event,
			BSTEventSource<TESPickpocketFailedEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESQuestInitEvent>)
		auto ProcessEvent(
			const TESQuestInitEvent& a_event,
			BSTEventSource<TESQuestInitEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESResetEvent>)
		auto ProcessEvent(const TESResetEvent& a_event, BSTEventSource<TESResetEvent>* a_eventSource)
			-> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESSellEvent>)
		auto ProcessEvent(const TESSellEvent& a_event, BSTEventSource<TESSellEvent>* a_eventSource)
			-> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESSpellCastEvent>)
		auto ProcessEvent(
			const TESSpellCastEvent& a_event,
			BSTEventSource<TESSpellCastEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESSwitchRaceCompleteEvent>)
		auto ProcessEvent(
			const TESSwitchRaceCompleteEvent& a_event,
			BSTEventSource<TESSwitchRaceCompleteEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESTrapHitEvent>)
		auto ProcessEvent(
			const TESTrapHitEvent& a_event,
			BSTEventSource<TESTrapHitEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESTriggerEnterEvent>)
		auto ProcessEvent(
			const TESTriggerEnterEvent& a_event,
			BSTEventSource<TESTriggerEnterEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESTriggerLeaveEvent>)
		auto ProcessEvent(
			const TESTriggerLeaveEvent& a_event,
			BSTEventSource<TESTriggerLeaveEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<Workshop::ItemDestroyedEvent>)
		auto ProcessEvent(
			const Workshop::ItemDestroyedEvent& a_event,
			BSTEventSource<Workshop::ItemDestroyedEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<Workshop::ItemMovedEvent>)
		auto ProcessEvent(
			const Workshop::ItemMovedEvent& a_event,
			BSTEventSource<Workshop::ItemMovedEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<Workshop::ItemPlacedEvent>)
		auto ProcessEvent(
			const Workshop::ItemPlacedEvent& a_event,
			BSTEventSource<Workshop::ItemPlacedEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<Workshop::ItemRepairedEvent>)
		auto ProcessEvent(
			const Workshop::ItemRepairedEvent& a_event,
			BSTEventSource<Workshop::ItemRepairedEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<Workshop::ItemGrabbedEvent>)
		auto ProcessEvent(
			const Workshop::ItemGrabbedEvent& a_event,
			BSTEventSource<Workshop::ItemGrabbedEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<Workshop::PowerOffEvent>)
		auto ProcessEvent(
			const Workshop::PowerOffEvent& a_event,
			BSTEventSource<Workshop::PowerOffEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<Workshop::PowerOnEvent>)
		auto ProcessEvent(
			const Workshop::PowerOnEvent& a_event,
			BSTEventSource<Workshop::PowerOnEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<WorkshopNPCTransferEvent>)
		auto ProcessEvent(
			const WorkshopNPCTransferEvent& a_event,
			BSTEventSource<WorkshopNPCTransferEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<Workshop::WorkshopModeEvent>)
		auto ProcessEvent(
			const Workshop::WorkshopModeEvent& a_event,
			BSTEventSource<Workshop::WorkshopModeEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		[[nodiscard]]
		static auto GetSingleton() noexcept -> BasicEventHandler*
		{
			static const auto SINGLETON =
				REL::Relocation<BasicEventHandler**>{ID::GameScript::BasicEventHandler::Singleton};
			return *SINGLETON;
		}

		// members
		GameVM* gameVM;								   // 0x1F8
		FragmentSystem* fragmentSystem;				   // 0x200
		HandlePolicy* handlePolicy;					   // 0x208
		ObjectBindPolicy* objectBindPolicy;			   // 0x210
		BSTSmartPointer<BSScript::IVirtualMachine> vm; // 0x218
	};

	static_assert(sizeof(BasicEventHandler) == 0x220);
}
