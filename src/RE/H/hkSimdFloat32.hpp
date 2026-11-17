#pragma once

namespace RE
{
	using hkSimdFloat32 = __m128;
	static_assert(sizeof(hkSimdFloat32) == 0x10);
}
