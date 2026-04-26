#pragma once

namespace RE::BSStorageDefs
{
	enum class SeekMode : std::int32_t
	{
		kBegin = 0,
		kCurrent = 1,
		kEnd = 2,

		kTotal = 3
	};
}
