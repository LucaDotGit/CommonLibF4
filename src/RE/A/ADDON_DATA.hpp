#pragma once

namespace RE
{
	class ADDON_DATA
	{
	public:
		// members
		std::uint16_t masterParticleCap; // 0x00
		std::int8_t flags;				 // 0x02
	};

	static_assert(sizeof(ADDON_DATA) == 0x04);
}
