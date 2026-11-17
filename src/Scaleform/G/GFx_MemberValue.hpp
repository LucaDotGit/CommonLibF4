#pragma once

#include "Scaleform/G/GFx_Value.hpp"
#include "Scaleform/S/String.hpp"

namespace Scaleform::GFx
{
	class MemberValue
	{
	public:
		// members
		String name; // 0x00
		Value value; // 0x08
	};

	static_assert(sizeof(MemberValue) == 0x28);
}
