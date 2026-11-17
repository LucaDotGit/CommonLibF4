#pragma once

namespace RE::BSStorageDefs
{
	enum class SeekMode : std::int32_t
	{
		Begin = 0,
		Current = 1,
		End = 2,

		_Count = 3
	};
}
