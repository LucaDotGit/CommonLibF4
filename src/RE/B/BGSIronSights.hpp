#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class BGSIronSights
	{
	public:
		[[nodiscard]]
		static auto GetEventIndex() noexcept -> std::uint32_t&
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>(ID::BGSIronSights::EventIndex);
			return *EVENT_INDEX;
		}

		// members
		ObjectRefHandle actorRef; // 0x00
		TESObjectWEAP* weapon;	  // 0x04
	};

	static_assert(sizeof(BGSIronSights) == 0x10);
}
