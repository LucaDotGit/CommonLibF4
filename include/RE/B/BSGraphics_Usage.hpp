#pragma once

namespace RE::BSGraphics
{
	enum class Usage : std::int32_t
	{
		kDefault = 0,
		kImmutable = 1,
		kDynamic = 2,
		kStaging = 3
	};
}
