#pragma once

namespace REX
{
	enum class SeekOrigin : std::int32_t
	{
		Begin = 1,
		Current,
		End,

		_Min = Begin,
		_Max = End,

		_Count = _Max
	};
}
