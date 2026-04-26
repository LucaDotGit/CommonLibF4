#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class BGSPickPocket
	{
	public:
		[[nodiscard]] static std::uint32_t& GetEventIndex()
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>{ ID::BGSPickPocket::EventIndex };
			return *EVENT_INDEX;
		}

		// members
		ObjectRefHandle targetRef; // 00
		std::uint32_t success;	   // 04
	};
	static_assert(sizeof(BGSPickPocket) == 0x08);
}
