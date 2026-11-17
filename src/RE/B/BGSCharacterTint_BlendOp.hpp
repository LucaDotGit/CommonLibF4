#pragma once

namespace RE::BGSCharacterTint
{
	enum class BlendOp : std::int32_t
	{
		Default = 0,
		Multiply = 1,
		Overlay = 2,
		SoftLight = 3,
		HardLight = 4,
		_Count = 5
	};
}
