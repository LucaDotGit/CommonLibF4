#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTOptional.hpp"
#include "RE/X/XPChangeData.hpp"

namespace RE
{
	class BGSQuestObjective;
	class MapMarkerData;

	class HUDNotificationEvent
	{
	public:
		// members
		BSFixedString messageType;			// 0x00
		BSFixedStringCS messageTitle;		// 0x08
		TESQuest* quest;					// 0x10
		BGSQuestObjective* objective;		// 0x18
		MapMarkerData* markerData;			// 0x20
		BSTOptional<XPChangeData> xpChange; // 0x28
		bool suppressNotification;			// 0x50
	};
}
