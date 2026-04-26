#pragma once

#include "Scaleform/G/GFx_ASStringBuiltinManagerT.hpp"

namespace Scaleform::GFx::AS3
{
	enum class BuiltinType : std::int32_t;

	class StringManager
		: public ASStringBuiltinManagerT<BuiltinType, 65>
	{
	public:
	};
	static_assert(sizeof(StringManager) == 0x218);
}
