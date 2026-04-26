#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class BGSAttractionObject
	{
	public:
		[[nodiscard]] static std::uint32_t& GetEventIndex()
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>{ ID::BGSAttractionObject::EventIndex };
			return *EVENT_INDEX;
		}

		// members
		ObjectRefHandle actorRef;  // 00
		ObjectRefHandle objectRef; // 04
		BGSLocation* location;	   // 08
		std::uint32_t commanded;   // 10
	};
	static_assert(sizeof(BGSAttractionObject) == 0x18);
}
