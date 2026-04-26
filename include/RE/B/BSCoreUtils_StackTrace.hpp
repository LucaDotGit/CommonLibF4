#pragma once

namespace RE::BSCoreUtils
{
	class StackTrace
	{
	public:
		// members
		std::uint32_t numFrames;			 // 00
		std::array<std::int64_t, 64> frames; // 08
	};
	static_assert(sizeof(StackTrace) == 0x208);
}
