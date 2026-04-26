#pragma once

#include "Scaleform/S/System.hpp"

namespace Scaleform::GFx
{
	class System
		: public Scaleform::System // 00
	{
	public:
	};
	static_assert(std::is_empty_v<System>);
}
