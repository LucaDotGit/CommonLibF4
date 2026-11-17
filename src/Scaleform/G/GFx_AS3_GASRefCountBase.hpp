#pragma once

#include "Scaleform/G/GFx_AS3_RefCountBaseGC.hpp"

namespace Scaleform::GFx::AS3
{
	class __declspec(novtable) GASRefCountBase : public RefCountBaseGC<328> // 0x00
	{
	public:
		~GASRefCountBase() override; // 0x00
	};

	static_assert(sizeof(GASRefCountBase) == 0x28);
}
