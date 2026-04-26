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

	class __declspec(novtable) HUDNotificationsModel
		: public BSTEventSink<HUDExperienceUpdateEvent>, // 000
		  public BSTEventSink<HUDNotificationEvent>,	 //	008
		  public BSTEventSink<HUDModeEvent>,			 // 010
		  public nsUIDebug::UIDebugLogger_NoOp			 // 018
	{
	public:
		inline static constexpr auto RTTI{ RTTI::HUDNotificationsModel };
		inline static constexpr auto VTABLE{ VTABLE::HUDNotificationsModel };

		~HUDNotificationsModel() override; // 00

		// override (BSTEventSink<HUDExperienceUpdateEvent>)
		BSEventNotifyControl ProcessEvent(const HUDExperienceUpdateEvent& a_event, BSTEventSource<HUDExperienceUpdateEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<HUDNotificationEvent>)
		BSEventNotifyControl ProcessEvent(const HUDNotificationEvent& a_event, BSTEventSource<HUDNotificationEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<HUDModeEvent>)
		BSEventNotifyControl ProcessEvent(const HUDModeEvent& a_event, BSTEventSource<HUDModeEvent>* a_eventSource) override; // 01

		// members
		HUDModes questUpdateModes;															 // 018
		HUDModes experienceMeterModes;														 // 038
		HUDModes tutorialTextModes;															 // 058
		HUDModes messagesModes;																 // 078
		BSTArray<nsHUDTypes::NotificationInfo> notifications;								 // 098
		mutable BSSpinLock notificationsArrayLock;											 // 0B0
		BSTValueEventSource<HUDTutorialTextEvent> tutorialText;								 // 0B8
		BSTValueEventSource<HUDObjectiveDisplayEvent> currentObjective;						 // 0D8
		BSTValueEventSource<HUDQuestVaultBoySwfName> currentQuestVaultBoy;					 // 100
		BSTValueEventSource<HUDNotificationDisplayEvent> currentNotification;				 // 120
		BSTValueEventSource<ShowingExperienceEvent> showingExperience;						 // 148
		BSTValueEventSink<CanDisplayNextHUDObjective> canShowNextObjective;					 // 160
		BSTValueEventSink<HasHUDMessagesEvent> hasHUDMessages;								 // 178
		BSTValueEventSink<ShowingFeaturedItemVaultBoyEvent> showingFeaturedItemVaultBoy;	 // 190
		ManualCountdownTimer displayTimer;													 // 1A8
		ManualCountdownTimer postDisplayCooldownTimer;										 // 1B4
		ManualCountdownTimer syncedEventTimer;												 // 1C0
		BSTObjectArena<ExperienceModelData, BSTObjectArenaHeapAlloc, 32> experienceUpdatesA; // 1D0
		mutable BSSpinLock experienceArenaLock;												 // 208
		BSTValueEventSource<ExperienceMeterDisplayEvent> experienceDisplayData;				 // 210
		BSTOptional<XPChangeData> currentSyncedXP;											 // 230
		ManualCountdownTimer experienceDisplayTimer;										 // 244
		ManualCountdownTimer experienceSoundDelayTimer;										 // 250
		ManualCountdownTimer experienceDisplayCooldownTimer;								 // 25C
		CountdownTimer experienceSoundCooldownTimer;										 // 268
	};
	static_assert(sizeof(HUDNotificationsModel) == 0x280);
}
