#pragma once

namespace RE
{
	class BGSCureEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventIndex() noexcept -> std::uint32_t&
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>(ID::BGSCureEvent::EventIndex);
			return *EVENT_INDEX;
		}

		// members
		TESForm* infection; // 0x00
	};

	static_assert(sizeof(BGSCureEvent) == 0x08);
}
