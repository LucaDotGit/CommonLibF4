#pragma once

#include "Scaleform/R/Render_ContextImpl_RTHandle.hpp"

namespace Scaleform::Render::ContextImpl
{
	template <class C>
	class DisplayHandle
		: public RTHandle // 00
	{
	public:
	};
	static_assert(sizeof(DisplayHandle<std::any>) == 0x08);
}
