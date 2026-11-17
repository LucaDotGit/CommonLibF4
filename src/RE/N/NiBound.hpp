#pragma once

#include "RE/N/NiPoint3.hpp"

namespace RE
{
	class NiBound
	{
	public:
		// members
		NiPoint3 center; // 0x00

		union
		{
		public:
			std::int32_t int32{0};
			REX::Float32 float32;
		} radius; // 0x0C
	};

	static_assert(sizeof(NiBound) == 0x10);
}
