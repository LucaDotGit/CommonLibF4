#pragma once

namespace RE
{
	class ADDON_DATA
	{
	public:
		// members
		std::uint16_t masterParticleCap; // 00
		std::int8_t flags;				 // 02
	};
	static_assert(sizeof(ADDON_DATA) == 0x04);
}
