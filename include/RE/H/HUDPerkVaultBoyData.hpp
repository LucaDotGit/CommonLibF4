#pragma once

#include "RE/B/BSFixedString.hpp"

namespace RE
{
	class HUDPerkVaultBoyData
	{
	public:
		// members
		BSFixedString swfName;			   // 00
		BGSSoundDescriptorForm* soundForm; // 08
		bool vatsCritAppliedAnim;		   // 10
		bool vatsCritFilledAnim;		   // 11
		bool dialogueSpeechChallengeAnim;  // 12
	};
	static_assert(sizeof(HUDPerkVaultBoyData) == 0x18);
}
