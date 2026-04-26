#pragma once

namespace RE
{
	class CONT_DATA
	{
	public:
		enum class Flags : std::uint8_t
		{
			kNone = 0,
			kAllowsSoundsWhenAnimation = 1 << 0,
			kRespawn = 1 << 1,
			kShowOwner = 1 << 2
		};

		// members
		REX::EnumSet<Flags, std::uint8_t> contFlags; // 00
	};
	static_assert(sizeof(CONT_DATA) == 0x01);
}
