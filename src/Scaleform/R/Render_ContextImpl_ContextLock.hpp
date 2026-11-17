#pragma once

#include "Scaleform/L/Lock.hpp"
#include "Scaleform/R/RefCountBase.hpp"

namespace Scaleform::Render::ContextImpl
{
	class Context;

	class __declspec(novtable) ContextLock : public RefCountBase<ContextLock, 69> // 0x00
	{
	public:
		// members
		mutable Lock lockObject; // 0x10
		Context* context;		 // 0x38
	};

	static_assert(sizeof(ContextLock) == 0x40);
}
