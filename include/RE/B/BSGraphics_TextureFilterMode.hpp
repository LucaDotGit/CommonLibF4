#pragma once

namespace RE::BSGraphics
{
	enum class TextureFilterMode : std::int32_t
	{
		kNearest = 0,
		kBilerp = 1,
		kTrilerp = 2,
		kAniso = 3,
		kCompBilerp = 4
	};
}
