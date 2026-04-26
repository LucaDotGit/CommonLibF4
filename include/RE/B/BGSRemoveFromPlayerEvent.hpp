#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	enum class REMOVE_TYPE : std::int32_t;

	class BGSRemoveFromPlayerEvent
	{
	public:
		[[nodiscard]] static std::uint32_t& GetEventIndex()
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>{ ID::BGSRemoveFromPlayerEvent::EventIndex };
			return *EVENT_INDEX;
		}

		// members
		ObjectRefHandle ownerRef;						 // 00
		ObjectRefHandle itemRef;						 // 04
		BGSLocation* location;							 // 08
		TESForm* baseItem;								 // 10
		REX::Enum<REMOVE_TYPE, std::int32_t> removeType; // 18
		std::uint32_t itemValue;						 // 1C
	};
	static_assert(sizeof(BGSRemoveFromPlayerEvent) == 0x20);
}
