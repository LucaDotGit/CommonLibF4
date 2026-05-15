#pragma once

#include "RE/H/hkMatrix3.hpp"

namespace RE
{
	class hkRotation
		: public hkMatrix3 // 00
	{
	public:
		using hkMatrix3::hkMatrix3;
	};
	static_assert(sizeof(hkRotation) == 0x30);
}
