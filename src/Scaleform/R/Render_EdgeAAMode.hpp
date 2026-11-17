#pragma once

namespace Scaleform::Render
{
	enum class EdgeAAMode : std::uint32_t
	{
		Inherit = 0,
		On = 1 << 2,
		Off = 1 << 3,
		Disable = On | Off
	};
}
