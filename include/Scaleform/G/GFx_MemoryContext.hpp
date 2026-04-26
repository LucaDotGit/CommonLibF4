#pragma once

#include "Scaleform/R/RefCountBase.hpp"

namespace Scaleform::GFx
{
	class __declspec(novtable) MemoryContext
		: public RefCountBase<MemoryContext, 2> // 00
	{
	public:
		~MemoryContext() override = default; // 00
	};
	static_assert(sizeof(MemoryContext) == 0x10);
}
