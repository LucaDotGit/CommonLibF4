#pragma once

namespace Scaleform::Render
{
	enum class EdgeAAMode : std::uint32_t
	{
		kInherit = 0,
		kOn = 1 << 2,
		kOff = 1 << 3,
		kDisable = kOn | kOff
	};
}
