#pragma once

namespace RE
{
	class PATH_DATA
	{
	public:
		enum class Flags : std::uint8_t
		{
			kNone = 0,
			kZoomDisable = 1 << 0,
			kZoomShotList = 1 << 1,
			kDynamicTimes = 1 << 2,
			kRandomPaths = 1 << 6,
			kAllowNoShots = 1 << 7
		};

		// members
		REX::EnumSet<Flags, std::uint8_t> flags; // 00
	};
	static_assert(sizeof(PATH_DATA) == 0x01);
}
