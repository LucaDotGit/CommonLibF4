#pragma once

namespace RE
{
	class PlayerActiveEffectIcons
	{
	public:
		// members
		std::array<std::uint64_t, 4> effectIIcons; // 00
	};
	static_assert(sizeof(PlayerActiveEffectIcons) == 0x20);
}
