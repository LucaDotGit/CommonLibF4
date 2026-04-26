#pragma once

namespace RE
{
	class NiNPShortPoint3
	{
	public:
		// members
		std::int16_t x; // 00
		std::int16_t y; // 02
		std::int16_t z; // 04
	};
	static_assert(sizeof(NiNPShortPoint3) == 0x06);
}
