#pragma once

namespace RE
{
	class bhkCollisionQueryResultHandle
	{
	public:
		// members
		std::uint64_t data; // 0x00
	};

	static_assert(sizeof(bhkCollisionQueryResultHandle) == 0x08);
}
