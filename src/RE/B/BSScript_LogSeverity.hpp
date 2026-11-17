#pragma once

namespace RE::BSScript
{
	enum class LogSeverity : std::int32_t
	{
		Info = 0,
		Warning = 1,
		Error = 2,
		Fatal = 3,

		_Count = 4
	};
}
