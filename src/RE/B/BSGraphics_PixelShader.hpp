#pragma once

#include "RE/B/BSGraphics_ConstantGroup.hpp"

namespace RE::BSGraphics
{
	class PixelShader
	{
	public:
		// members
		std::uint32_t id;										  // 0x00
		REX::W32::ID3D11PixelShader* shader;					  // 0x08
		std::array<BSGraphics::ConstantGroup, 3> constantBuffers; // 0x10
		std::array<std::int8_t, 32> constantTable;				  // 0x58
	};

	static_assert(sizeof(PixelShader) == 0x78);
}
