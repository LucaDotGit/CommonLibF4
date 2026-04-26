#pragma once

#include "Scaleform/G/GFx_ASConstString.hpp"

namespace Scaleform::GFx
{
	class ASString
		: public ASConstString // 00
	{
	public:
	};
	static_assert(sizeof(ASString) == 0x08);
}
