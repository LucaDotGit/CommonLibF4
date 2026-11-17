#pragma once

namespace RE::BSGraphics
{
	enum class TextureAddressMode : std::int32_t
	{
		Clamp_S_Clamp_T = 0,
		Clamp_S_Wrap_T = 1,
		Wrap_S_Clamp_T = 2,
		Wrap_S_Wrap_T = 3
	};
}
