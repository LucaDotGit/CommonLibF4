#pragma once

#include "Scaleform/G/GFx_ASStringNodeHolder.hpp"

namespace Scaleform::GFx
{
	class ASConstString : public ASStringNodeHolder // 0x00
	{
	public:
		auto ToCStr() const noexcept -> const char*
		{
			return node->data;
		}
	};

	static_assert(sizeof(ASConstString) == 0x08);
}
