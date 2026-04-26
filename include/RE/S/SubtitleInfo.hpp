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
		ObjectRefHandle speaker;							 // 00
		BSFixedStringCS subtitleText;						 // 08
		TESTopicInfo* topicInfo;							 // 10
		REX::Enum<SUBTITLE_PRIORITY, std::int32_t> priority; // 18
		REX::Float32 distFromPlayer;						 // 1C
	};
	static_assert(sizeof(SubtitleInfo) == 0x20);
}
