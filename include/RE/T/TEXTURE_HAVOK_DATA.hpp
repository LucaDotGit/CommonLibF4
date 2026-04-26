#pragma once

namespace RE
{
	class TEXTURE_HAVOK_DATA
	{
	public:
		// members
		std::int8_t friction;	 // 00
		std::int8_t restitution; // 01
	};
	static_assert(sizeof(TEXTURE_HAVOK_DATA) == 0x02);
}
