#pragma once

namespace RE
{
	class BGSEscapeJailEvent
	{
	public:
		[[nodiscard]] static std::uint32_t& GetEventIndex()
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>{ ID::BGSEscapeJailEvent::EventIndex };
			return *EVENT_INDEX;
		}

		// members
		BGSLocation* location; // 00
		TESForm* crimeGroup;   // 08
	};
	static_assert(sizeof(BGSEscapeJailEvent) == 0x10);
}
