#pragma once

namespace RE
{
	class BGSServedTime
	{
	public:
		[[nodiscard]] static std::uint32_t& GetEventIndex()
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>{ ID::BGSServedTime::EventIndex };
			return *EVENT_INDEX;
		}

		// members
		BGSLocation* location;	  // 00
		TESForm* crimeGroup;	  // 08
		std::uint32_t crimeGold;  // 10
		std::uint32_t daysInJail; // 14
	};
	static_assert(sizeof(BGSServedTime) == 0x18);
}
