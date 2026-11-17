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
		BSFixedStringCS title;							// 0x00
		BSFixedStringCS prefix;							// 0x08
		BSFixedString soundName;						// 0x10
		BSTArray<nsHUDTypes::ObjectiveData> objectives; // 0x18
		BSFixedString messageType;						// 0x30
		TESQuest* quest;								// 0x38
		CountdownTimer waitTime;						// 0x40
		BSTOptional<XPChangeData> xpChange;				// 0x58
	};

	static_assert(sizeof(NotificationInfo) == 0x70);
}
