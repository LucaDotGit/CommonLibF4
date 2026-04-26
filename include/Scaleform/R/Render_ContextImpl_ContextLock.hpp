#pragma once

#include "Scaleform/L/Lock.hpp"
#include "Scaleform/R/RefCountBase.hpp"

namespace Scaleform::Render::ContextImpl
{
	class Context;

	class __declspec(novtable) ContextLock
		: public RefCountBase<ContextLock, 69> // 00
	{
	public:
		// members
		Lock lockObject;  // 10
		Context* context; // 38
	};
	static_assert(sizeof(ContextLock) == 0x40);
}
