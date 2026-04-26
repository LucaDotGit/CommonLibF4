#pragma once

#include "Scaleform/A/Array.hpp"

namespace Scaleform::GFx
{
	class MemberValue;

	class MemberValueSet
		: public Array<MemberValue>
	{
	public:
	};
	static_assert(sizeof(MemberValueSet) == 0x18);
}
