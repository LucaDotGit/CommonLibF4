#pragma once

namespace RE
{
	class CHAR_NORM
	{
	public:
		// members
		char x; // 0x00
		char y; // 0x01
		char z; // 0x02
	};

	static_assert(sizeof(CHAR_NORM) == 0x03);
}
