#pragma once

#include "Scaleform/G/GFx_ASStringNodeHolder.hpp"

namespace Scaleform::GFx
{
	class ASConstString
		: public ASStringNodeHolder // 00
	{
	public:
		const char* ToCStr() const noexcept { return node->data; }
	};
	static_assert(sizeof(ASConstString) == 0x08);
}
