#pragma once

namespace RE::BSScript
{
	enum class FreezeState : std::int32_t
	{
		kUnfrozen = 0,
		kFreezing = 1,
		kFrozen = 2
	};
}
