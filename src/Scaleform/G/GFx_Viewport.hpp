#pragma once

#include "Scaleform/R/Render_Viewport.hpp"

namespace Scaleform::GFx
{
	class Viewport : public Render::Viewport
	{
	public:
		// members
		REX::Float32 scale;		  // 0x2C
		REX::Float32 aspectRatio; // 0x30
	};

	static_assert(sizeof(Viewport) == 0x34);
}
