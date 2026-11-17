#pragma once

#include "RE/B/BSFixedString.hpp"

namespace RE
{
	class DialogueResponse
	{
	public:
		// members
		BSFixedStringCS text;				// 0x00
		BGSKeyword* animFaceArchType;		// 0x08
		std::uint16_t percent;				// 0x10
		BSFixedString voice;				// 0x18
		TESIdleForm* speakerIdle;			// 0x20
		TESIdleForm* listenIdle;			// 0x28
		BGSSoundDescriptorForm* voiceSound; // 0x30
		bool useEmotion;					// 0x38
		bool soundLip;						// 0x39
		bool endOnSceneEnd;					// 0x3A
	};

	static_assert(sizeof(DialogueResponse) == 0x40);
}
