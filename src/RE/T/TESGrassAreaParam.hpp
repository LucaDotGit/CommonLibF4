#pragma once

#include "RE/G/GrassParam.hpp"

namespace RE
{
	class TESGrassAreaParam
	{
	public:
		// members
		GrassParam grassParam;				 // 0x00
		std::array<REX::Float32, 9> density; // 0x28
	};

	static_assert(sizeof(TESGrassAreaParam) == 0x50);
}
