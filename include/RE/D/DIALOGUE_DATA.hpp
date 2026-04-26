#pragma once

namespace RE
{
	class DIALOGUE_DATA
	{
	public:
		// members
		std::uint8_t flags;	   // 00
		std::int8_t type;	   // 01
		std::uint16_t subtype; // 02
	};
	static_assert(sizeof(DIALOGUE_DATA) == 0x04);
}
