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
		BSFixedString messageType;			// 00
		BSFixedStringCS messageTitle;		// 08
		TESQuest* quest;					// 10
		BGSQuestObjective* objective;		// 18
		MapMarkerData* markerData;			// 20
		BSTOptional<XPChangeData> xpChange; // 28
		bool suppressNotification;			// 50
	};
}
