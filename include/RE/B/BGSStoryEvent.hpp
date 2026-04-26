#pragma once

namespace RE
{
	class BGSStoryEvent
	{
	public:
		// members
		std::uint32_t id;					  // 00
		std::uint32_t index;				  // 04
		std::array<std::uint64_t, 6> members; // 08
	};
	static_assert(sizeof(BGSStoryEvent) == 0x38);
}
