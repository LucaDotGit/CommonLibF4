#pragma once

namespace RE
{
	class BGSSaveLoadFormInfo
	{
	public:
		// members
		std::uint8_t data; // 00
	};
	static_assert(sizeof(BGSSaveLoadFormInfo) == 0x01);
}
