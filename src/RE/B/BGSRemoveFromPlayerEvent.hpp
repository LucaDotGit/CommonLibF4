#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	enum class REMOVE_TYPE : std::int32_t;

	class BGSRemoveFromPlayerEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventIndex() noexcept -> std::uint32_t&
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>(ID::BGSRemoveFromPlayerEvent::EventIndex);
			return *EVENT_INDEX;
		}

		// members
		ObjectRefHandle ownerRef;						 // 0x00
		ObjectRefHandle itemRef;						 // 0x04
		BGSLocation* location;							 // 0x08
		TESForm* baseItem;								 // 0x10
		REX::Enum<REMOVE_TYPE, std::int32_t> removeType; // 0x18
		std::uint32_t itemValue;						 // 0x1C
	};

	static_assert(sizeof(BGSRemoveFromPlayerEvent) == 0x20);
}
