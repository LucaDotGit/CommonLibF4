#pragma once

#include "RE/B/BSGraphics_ConstantGroup.hpp"

namespace RE::BSGraphics
{
	class ComputeShader
	{
	public:
		// members
		std::uint32_t id;										  // 0x00
		REX::W32::ID3D11ComputeShader* shader;					  // 0x08
		std::uint32_t byteCodeSize;								  // 0x10
		std::array<BSGraphics::ConstantGroup, 3> constantBuffers; // 0x18
		std::uint64_t shaderDesc;								  // 0x60
		std::array<std::int8_t, 32> constantTable;				  // 0x68
	};

	static_assert(sizeof(ComputeShader) == 0x88);
}
