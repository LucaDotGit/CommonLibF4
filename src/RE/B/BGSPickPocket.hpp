#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class BGSPickPocket
	{
	public:
		[[nodiscard]]
		static auto GetEventIndex() noexcept -> std::uint32_t&
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>(ID::BGSPickPocket::EventIndex);
			return *EVENT_INDEX;
		}

		// members
		ObjectRefHandle targetRef; // 0x00
		std::uint32_t success;	   // 0x04
	};

	static_assert(sizeof(BGSPickPocket) == 0x08);
}
