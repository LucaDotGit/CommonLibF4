#pragma once

#include "RE/N/NiAnimationKey.hpp"

namespace RE
{
	class NiFloatKey : public NiAnimationKey // 0x00
	{
	public:
		// members
		REX::Float32 value; // 0x00
	};

	static_assert(sizeof(NiFloatKey) == 0x08);
}
