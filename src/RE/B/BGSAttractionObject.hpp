#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class BGSAttractionObject
	{
	public:
		[[nodiscard]]
		static auto GetEventIndex() noexcept -> std::uint32_t&
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>(ID::BGSAttractionObject::EventIndex);
			return *EVENT_INDEX;
		}

		// members
		ObjectRefHandle actorRef;  // 0x00
		ObjectRefHandle objectRef; // 0x04
		BGSLocation* location;	   // 0x08
		std::uint32_t commanded;   // 0x10
	};

	static_assert(sizeof(BGSAttractionObject) == 0x18);
}
