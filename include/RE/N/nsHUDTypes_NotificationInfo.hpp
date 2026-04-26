#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTOptional.hpp"
#include "RE/C/CountdownTimer.hpp"
#include "RE/X/XPChangeData.hpp"

namespace RE::nsHUDTypes
{
	class ObjectiveData;

	class NotificationInfo
	{
	public:
		// members
		BSFixedStringCS title;							// 00
		BSFixedStringCS prefix;							// 08
		BSFixedString soundName;						// 10
		BSTArray<nsHUDTypes::ObjectiveData> objectives; // 18
		BSFixedString messageType;						// 30
		TESQuest* quest;								// 38
		CountdownTimer waitTime;						// 40
		BSTOptional<XPChangeData> xpChange;				// 58
	};
	static_assert(sizeof(NotificationInfo) == 0x70);
}
