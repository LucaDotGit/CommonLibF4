#pragma once

#include "RE/B/BSFixedString.hpp"

namespace RE
{
	class TutorialEvent
	{
	public:
		// members
		BSFixedString eventName; // 00
		BGSMessage* message;	 // 08
	};
	static_assert(sizeof(TutorialEvent) == 0x10);
}
