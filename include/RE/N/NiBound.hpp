#pragma once

#include "RE/N/NiPoint.hpp"

namespace RE
{
	class NiBound
	{
	public:
		// members
		NiPoint3 center; // 00
		union
		{
			std::int32_t int32{ 0 };
			REX::Float32 float32;
		} radius; // 0C
	};
	static_assert(sizeof(NiBound) == 0x10);
}
