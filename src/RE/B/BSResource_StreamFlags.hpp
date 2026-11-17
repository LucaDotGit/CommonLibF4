#pragma once

namespace RE::BSResource
{
	enum class StreamFlags : std::uint32_t
	{
		None = 0,
		Writable = 1 << 0,
		Buffered = 1 << 1,
		FullReadHint = 1 << 2,
		Opened = 1 << 3,

		Mask = 0x0F,

		RefCountMask = 0xFFFF'F000,
		RefCountIncrement = 0x1000,

		NonUserFlagsMask = Opened | Mask | RefCountMask,
		UserFlagsMask = ~NonUserFlagsMask
	};
}
