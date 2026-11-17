#pragma once

namespace RE
{
	class BGSServedTime
	{
	public:
		[[nodiscard]]
		static auto GetEventIndex() noexcept -> std::uint32_t&
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>(ID::BGSServedTime::EventIndex);
			return *EVENT_INDEX;
		}

		// members
		BGSLocation* location;	  // 0x00
		TESForm* crimeGroup;	  // 0x08
		std::uint32_t crimeGold;  // 0x10
		std::uint32_t daysInJail; // 0x14
	};

	static_assert(sizeof(BGSServedTime) == 0x18);
}
