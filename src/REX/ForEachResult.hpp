#pragma once

namespace REX
{
	enum class ForEachResult : std::int32_t
	{
		Break = 1,
		Continue,

		_Min = Break,
		_Max = Continue,

		_Count = _Max
	};
}
