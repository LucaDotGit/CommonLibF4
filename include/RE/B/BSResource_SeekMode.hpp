#pragma once

namespace RE::BSResource
{
	enum class SeekMode : std::int32_t
	{
		kSet = 0,
		kCurrent = 1,
		kEnd = 2
	};
}
