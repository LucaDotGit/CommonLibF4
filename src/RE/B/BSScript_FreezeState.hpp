#pragma once

namespace RE::BSScript
{
	enum class FreezeState : std::int32_t
	{
		Unfrozen = 0,
		Freezing = 1,
		Frozen = 2
	};
}
