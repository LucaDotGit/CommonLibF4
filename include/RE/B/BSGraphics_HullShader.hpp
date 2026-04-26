#pragma once

#include "RE/B/BSGraphics_ConstantGroup.hpp"

namespace RE::BSGraphics
{
	class HullShader
	{
	public:
		// members
		std::uint32_t id;										  // 00
		REX::W32::ID3D11HullShader* shader;						  // 08
		std::uint32_t byteCodeSize;								  // 10
		std::array<BSGraphics::ConstantGroup, 3> constantBuffers; // 18
		std::uint64_t shaderDesc;								  // 60
		std::array<std::int8_t, 32> constantTable;				  // 68
	};
	static_assert(sizeof(HullShader) == 0x88);
}
