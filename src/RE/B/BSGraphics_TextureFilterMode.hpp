#pragma once

namespace RE::BSGraphics
{
	enum class TextureFilterMode : std::int32_t
	{
		Nearest = 0,
		Bilerp = 1,
		Trilerp = 2,
		Aniso = 3,
		CompBilerp = 4
	};
}
