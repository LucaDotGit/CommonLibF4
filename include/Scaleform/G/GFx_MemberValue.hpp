#pragma once

#include "Scaleform/G/GFx_Value.hpp"
#include "Scaleform/S/String.hpp"

namespace Scaleform::GFx
{
	class MemberValue
	{
	public:
		// members
		String name; // 00
		Value value; // 08
	};
	static_assert(sizeof(MemberValue) == 0x28);
}
