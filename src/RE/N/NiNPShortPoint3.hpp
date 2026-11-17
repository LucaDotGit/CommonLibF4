#pragma once

namespace RE
{
	class NiNPShortPoint3
	{
	public:
		// members
		std::int16_t x; // 0x00
		std::int16_t y; // 0x02
		std::int16_t z; // 0x04
	};

	static_assert(sizeof(NiNPShortPoint3) == 0x06);
}
