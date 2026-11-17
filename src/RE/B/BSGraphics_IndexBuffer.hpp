#pragma once

#include "RE/B/BSGraphics_Buffer.hpp"

namespace RE::BSGraphics
{
	class IndexBuffer : public Buffer // 0x00
	{
	public:
	};

	static_assert(sizeof(IndexBuffer) == 0x50);
}
