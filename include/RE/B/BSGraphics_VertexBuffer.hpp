#pragma once

#include "RE/B/BSGraphics_Buffer.hpp"

namespace RE::BSGraphics
{
	class VertexBuffer
		: public Buffer // 00
	{
	public:
	};
	static_assert(sizeof(VertexBuffer) == 0x50);
}
