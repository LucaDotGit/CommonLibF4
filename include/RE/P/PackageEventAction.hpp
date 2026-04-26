#pragma once

#include "RE/B/BGSTopicSubtypeUnion.hpp"

namespace RE
{
	enum class PACK_EVENT_ACTION_TYPE : std::int32_t;

	class PackageEventAction
	{
	public:
		// members
		TESIdleForm* idle;										   // 00
		REX::Enum<PACK_EVENT_ACTION_TYPE, std::int32_t> eventType; // 08
		BGSTopicSubtypeUnion topicSubtypeUnion;					   // 0C
	};
	static_assert(sizeof(PackageEventAction) == 0x18);
}
