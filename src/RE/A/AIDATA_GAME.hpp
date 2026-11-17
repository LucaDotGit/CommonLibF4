#pragma once

namespace RE
{
	class AIDATA_GAME
	{
	public:
		// members
		std::uint32_t aggression	 : 2;		  // 0x00:00
		std::uint32_t confidence	 : 3;		  // 0x00:02
		std::uint32_t energy		 : 8;		  // 0x00:05
		std::uint32_t morality		 : 2;		  // 0x00:13
		std::uint32_t unused		 : 3;		  // 0x00:15
		std::uint32_t assistance	 : 2;		  // 0x00:18
		std::uint32_t useAggroRadius : 1;		  // 0x00:20
		std::array<std::uint16_t, 3> aggroRadius; // 0x04
		std::uint32_t noSlowApproach : 1;		  // 0x0A:00
	};

	static_assert(sizeof(AIDATA_GAME) == 0x10);
}
