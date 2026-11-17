#pragma once

namespace RE
{
	enum class REMOVE_TYPE : std::int32_t
	{
		None = 0,
		Stolen = 1,
		Consumed = 2,
		Script = 3,
		Dropped = 4,
		Given = 5,
		PutInContainer = 6,

		_Count = 7
	};
}
