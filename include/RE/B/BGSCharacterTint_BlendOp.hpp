#pragma once

namespace RE::BGSCharacterTint
{
	enum class BlendOp : std::int32_t
	{
		kDefault = 0,
		kMultiply = 1,
		kOverlay = 2,
		kSoftLight = 3,
		kHardLight = 4,
		kTotal = 5
	};
}
