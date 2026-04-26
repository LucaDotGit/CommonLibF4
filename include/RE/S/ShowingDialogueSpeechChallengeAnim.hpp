#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class ShowingDialogueSpeechChallengeAnim
		: public BSTValueEvent<bool> // 00
	{
	public:
	};
	static_assert(sizeof(ShowingDialogueSpeechChallengeAnim) == 0x02);
}
