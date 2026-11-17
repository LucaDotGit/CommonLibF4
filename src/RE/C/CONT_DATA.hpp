#pragma once

namespace RE
{
	class CONT_DATA
	{
	public:
		enum class Flags : std::uint8_t
		{
			None = 0,
			AllowsSoundsWhenAnimation = 1 << 0,
			Respawn = 1 << 1,
			ShowOwner = 1 << 2
		};

		// members
		REX::EnumSet<Flags, std::uint8_t> contFlags; // 0x00
	};

	static_assert(sizeof(CONT_DATA) == 0x01);
}
