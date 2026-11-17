#pragma once

#include "RE/B/BSFixedString.hpp"

namespace RE
{
	class HUDPerkVaultBoyData
	{
	public:
		// members
		BSFixedString swfName;			   // 0x00
		BGSSoundDescriptorForm* soundForm; // 0x08
		bool vatsCritAppliedAnim;		   // 0x10
		bool vatsCritFilledAnim;		   // 0x11
		bool dialogueSpeechChallengeAnim;  // 0x12
	};

	static_assert(sizeof(HUDPerkVaultBoyData) == 0x18);
}
