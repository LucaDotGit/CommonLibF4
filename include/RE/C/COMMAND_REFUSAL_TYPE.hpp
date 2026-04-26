#pragma once

namespace RE
{
	enum class COMMAND_REFUSAL_TYPE : std::int32_t
	{
		kNone = 0,
		kAny = 1,
		kImpossible = 2,
		kMoral = 3,

		kTotal = 4
	};
}
