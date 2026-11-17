#pragma once

namespace RE::BSGraphics
{
	enum class Usage : std::int32_t
	{
		Default = 0,
		Immutable = 1,
		Dynamic = 2,
		Staging = 3
	};
}
