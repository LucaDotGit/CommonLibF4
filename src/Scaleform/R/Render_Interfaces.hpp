#pragma once

#include "Scaleform/T/ThreadId.hpp"

namespace Scaleform::Render
{
	class HAL;
	class Renderer2D;
	class TextureManager;

	class Interfaces
	{
	public:
		// members
		TextureManager* textureManager; // 0x00
		HAL* hal;						// 0x08
		Renderer2D* renderer2D;			// 0x10
		ThreadId renderThreadID;		// 0x18
	};

	static_assert(sizeof(Interfaces) == 0x20);
}
