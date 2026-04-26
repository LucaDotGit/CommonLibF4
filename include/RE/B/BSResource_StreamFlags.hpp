#pragma once

namespace RE::BSResource
{
	enum class StreamFlags : std::uint32_t
	{
		kNone = 0,
		kWritable = 1 << 0,
		kBuffered = 1 << 1,
		kFullReadHint = 1 << 2,
		kOpened = 1 << 3,

		kMask = 0x0F,

		kRefCountMask = 0xFFFFF000,
		kRefCountIncrement = 0x1000,

		kNonUserFlagsMask = kOpened | kMask | kRefCountMask,
		kUserFlagsMask = ~kNonUserFlagsMask
	};
}
