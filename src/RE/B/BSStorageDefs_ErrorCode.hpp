#pragma once

namespace RE::BSStorageDefs
{
	enum class ErrorCode : std::int32_t
	{
		None = 0,
		NotExist = 1,
		InvalidPath = 2,
		FileError = 3,
		InvalidType = 4,
		MemoryError = 5,
		Busy = 6,
		InvalidParam = 7,
		Unsupported = 8,

		_Count = 9
	};
}
