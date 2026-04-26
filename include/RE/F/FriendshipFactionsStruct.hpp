#pragma once

namespace RE
{
	class FriendshipFactionsStruct
	{
	public:
		// members
		std::array<std::uint16_t, 4> friendCounts; // 00
	};
	static_assert(sizeof(FriendshipFactionsStruct) == 0x08);
}
