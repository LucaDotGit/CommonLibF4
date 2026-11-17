#pragma once

namespace RE
{
	enum class COMMAND_REFUSAL_TYPE : std::int32_t
	{
		None = 0,
		Any = 1,
		Impossible = 2,
		Moral = 3,

		_Count = 4
	};
}
