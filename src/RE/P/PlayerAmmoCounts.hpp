#pragma once

namespace RE
{
	class PlayerAmmoCounts
	{
	public:
		// members
		std::uint32_t clipAmmo;	   // 0x00
		std::uint32_t reserveAmmo; // 0x04
	};

	static_assert(sizeof(PlayerAmmoCounts) == 0x08);
}
