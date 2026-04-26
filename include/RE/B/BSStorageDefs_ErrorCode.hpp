#pragma once

namespace RE::BSStorageDefs
{
	enum class ErrorCode : std::int32_t
	{
		kNone = 0,
		kNotExist = 1,
		kInvalidPath = 2,
		kFileError = 3,
		kInvalidType = 4,
		kMemoryError = 5,
		kBusy = 6,
		kInvalidParam = 7,
		kUnsupported = 8,

		kTotal = 9
	};
}
