#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class BGSIronSights
	{
	public:
		[[nodiscard]] static std::uint32_t& GetEventIndex()
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>{ ID::BGSIronSights::EventIndex };
			return *EVENT_INDEX;
		}

		// members
		ObjectRefHandle actorRef; // 00
		TESObjectWEAP* weapon;	  // 04
	};
	static_assert(sizeof(BGSIronSights) == 0x10);
}
