#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	enum class SUBTITLE_PRIORITY : std::int32_t;

	class SubtitleInfo
	{
	public:
		// members
		ObjectRefHandle speaker;							 // 0x00
		BSFixedStringCS subtitleText;						 // 0x08
		TESTopicInfo* topicInfo;							 // 0x10
		REX::Enum<SUBTITLE_PRIORITY, std::int32_t> priority; // 0x18
		REX::Float32 distFromPlayer;						 // 0x1C
	};

	static_assert(sizeof(SubtitleInfo) == 0x20);
}
