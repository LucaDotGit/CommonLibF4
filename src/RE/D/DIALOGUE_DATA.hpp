#pragma once

namespace RE
{
	class DIALOGUE_DATA
	{
	public:
		// members
		std::uint8_t flags;	   // 0x00
		std::int8_t type;	   // 0x01
		std::uint16_t subtype; // 0x02
	};

	static_assert(sizeof(DIALOGUE_DATA) == 0x04);
}
