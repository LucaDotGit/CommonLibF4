#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class BGSPayFine
	{
	public:
		[[nodiscard]]
		static auto GetEventIndex() noexcept -> std::uint32_t&
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>(ID::BGSPayFine::EventIndex);
			return *EVENT_INDEX;
		}

		// members
		ObjectRefHandle criminalRef; // 0x00
		ObjectRefHandle guardRef;	 // 0x04
		TESForm* crimeGroup;		 // 0x08
		std::uint32_t crimeGoldPaid; // 0x10
	};

	static_assert(sizeof(BGSPayFine) == 0x18);
}
