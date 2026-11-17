#pragma once

namespace RE
{
	class BGSClearLocationEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventIndex() noexcept -> std::uint32_t&
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>(ID::BGSClearLocationEvent::EventIndex);
			return *EVENT_INDEX;
		}

		// members
		BGSLocation* location; // 0x00
	};

	static_assert(sizeof(BGSClearLocationEvent) == 0x08);
}
