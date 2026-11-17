#pragma once

#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTObjectArena.hpp"
#include "RE/B/BSTOptional.hpp"
#include "RE/C/CanDisplayNextHUDObjective.hpp"
#include "RE/C/CountdownTimer.hpp"
#include "RE/E/ExperienceMeterDisplayEvent.hpp"
#include "RE/H/HUDModes.hpp"
#include "RE/H/HUDNotificationDisplayEvent.hpp"
#include "RE/H/HUDObjectiveDisplayEvent.hpp"
#include "RE/H/HUDQuestVaultBoySwfName.hpp"
#include "RE/H/HUDTutorialTextEvent.hpp"
#include "RE/H/HasHUDMessagesEvent.hpp"
#include "RE/M/ManualCountdownTimer.hpp"
#include "RE/N/nsUIDebug_UIDebugLogger_NoOp.hpp"
#include "RE/S/ShowingExperienceEvent.hpp"
#include "RE/S/ShowingFeaturedItemVaultBoyEvent.hpp"
#include "RE/X/XPChangeData.hpp"

namespace RE::nsHUDTypes
{
	class NotificationInfo;
}

namespace RE
{
	class HUDExperienceUpdateEvent;
	class HUDNotificationEvent;
	class HUDModeEvent;
	class ExperienceModelData;

	class __declspec(novtable) HUDNotificationsModel :
		public BSTEventSink<HUDExperienceUpdateEvent>, // 0x000
		public BSTEventSink<HUDNotificationEvent>,	   //	008
		public BSTEventSink<HUDModeEvent>,			   // 0x010
		public nsUIDebug::UIDebugLogger_NoOp		   // 0x018
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::HUDNotificationsModel;
		inline static constexpr const auto& VTABLE = VTABLE::HUDNotificationsModel;

		~HUDNotificationsModel() override; // 0x00

		// override (BSTEventSink<HUDExperienceUpdateEvent>)
		auto ProcessEvent(
			const HUDExperienceUpdateEvent& a_event,
			BSTEventSource<HUDExperienceUpdateEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<HUDNotificationEvent>)
		auto ProcessEvent(
			const HUDNotificationEvent& a_event,
			BSTEventSource<HUDNotificationEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<HUDModeEvent>)
		auto ProcessEvent(const HUDModeEvent& a_event, BSTEventSource<HUDModeEvent>* a_eventSource)
			-> BSEventNotifyControl override; // 0x01

		// members
		HUDModes questUpdateModes;														 // 0x018
		HUDModes experienceMeterModes;													 // 0x038
		HUDModes tutorialTextModes;														 // 0x058
		HUDModes messagesModes;															 // 0x078
		BSTArray<nsHUDTypes::NotificationInfo> notifications;							 // 0x098
		mutable BSSpinLock notificationsArrayLock;										 // 0x0B0
		BSTValueEventSource<HUDTutorialTextEvent> tutorialText;							 // 0x0B8
		BSTValueEventSource<HUDObjectiveDisplayEvent> currentObjective;					 // 0x0D8
		BSTValueEventSource<HUDQuestVaultBoySwfName> currentQuestVaultBoy;				 // 0x100
		BSTValueEventSource<HUDNotificationDisplayEvent> currentNotification;			 // 0x120
		BSTValueEventSource<ShowingExperienceEvent> showingExperience;					 // 0x148
		BSTValueEventSink<CanDisplayNextHUDObjective> canShowNextObjective;				 // 0x160
		BSTValueEventSink<HasHUDMessagesEvent> hasHUDMessages;							 // 0x178
		BSTValueEventSink<ShowingFeaturedItemVaultBoyEvent> showingFeaturedItemVaultBoy; // 0x190
		ManualCountdownTimer displayTimer;												 // 0x1A8
		ManualCountdownTimer postDisplayCooldownTimer;									 // 0x1B4
		ManualCountdownTimer syncedEventTimer;											 // 0x1C0
		BSTHeapObjectArena<ExperienceModelData, 0x20> experienceUpdatesA;				 // 0x1D0
		mutable BSSpinLock experienceArenaLock;											 // 0x208
		BSTValueEventSource<ExperienceMeterDisplayEvent> experienceDisplayData;			 // 0x210
		BSTOptional<XPChangeData> currentSyncedXP;										 // 0x230
		ManualCountdownTimer experienceDisplayTimer;									 // 0x244
		ManualCountdownTimer experienceSoundDelayTimer;									 // 0x250
		ManualCountdownTimer experienceDisplayCooldownTimer;							 // 0x25C
		CountdownTimer experienceSoundCooldownTimer;									 // 0x268
	};

	static_assert(sizeof(HUDNotificationsModel) == 0x280);
}
