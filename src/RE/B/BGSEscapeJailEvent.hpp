#pragma once

namespace RE
{
	class BGSEscapeJailEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventIndex() noexcept -> std::uint32_t&
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>(ID::BGSEscapeJailEvent::EventIndex);
			return *EVENT_INDEX;
		}

		// members
		BGSLocation* location; // 0x00
		TESForm* crimeGroup;   // 0x08
	};

	static_assert(sizeof(BGSEscapeJailEvent) == 0x10);
}
