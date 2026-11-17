#pragma once

namespace RE
{
	class BGSStoryEvent
	{
	public:
		// members
		std::uint32_t id;					  // 0x00
		std::uint32_t index;				  // 0x04
		std::array<std::uint64_t, 6> members; // 0x08
	};

	static_assert(sizeof(BGSStoryEvent) == 0x38);
}
