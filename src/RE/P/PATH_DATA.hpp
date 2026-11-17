#pragma once

namespace RE
{
	class PATH_DATA
	{
	public:
		enum class Flags : std::uint8_t
		{
			None = 0,
			ZoomDisable = 1 << 0,
			ZoomShotList = 1 << 1,
			DynamicTimes = 1 << 2,
			RandomPaths = 1 << 6,
			AllowNoShots = 1 << 7
		};

		// members
		REX::EnumSet<Flags, std::uint8_t> flags; // 0x00
	};

	static_assert(sizeof(PATH_DATA) == 0x01);
}
