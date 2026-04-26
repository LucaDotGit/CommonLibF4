#pragma once

namespace RE::BSGraphics
{
	enum class TextureAddressMode : std::int32_t
	{
		kClamp_S_Clamp_T = 0,
		kClamp_S_Wrap_T = 1,
		kWrap_S_Clamp_T = 2,
		kWrap_S_Wrap_T = 3
	};
}
