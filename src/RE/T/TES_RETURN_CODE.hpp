#pragma once

namespace RE
{
	enum class TES_RETURN_CODE : std::int32_t
	{
		None = 0,
		NotFound = 1,
		NoFile = 2,
		NoForm = 3,
		NoChunk = 4,
		NoID = 5,
		BadFile = 6,
		BadID = 7,
		FormOpen = 8,
		FileOpen = 9,
		WriteFailure = 10,
		InvalidFile = 11,
		FileInUse = 12,
		CreateFailure = 13
	};
}
