#pragma once

#include "RE/B/BSFixedString.hpp"

namespace RE
{
	class TutorialEvent
	{
	public:
		// members
		BSFixedString eventName; // 0x00
		BGSMessage* message;	 // 0x08
	};

	static_assert(sizeof(TutorialEvent) == 0x10);
}
