#pragma once

namespace RE::BSGraphics
{
	class ConstantGroup
	{
	public:
		// members
		REX::W32::ID3D11Buffer* buffer; // 0x00
		REX::Float32* data;				// 0x08
		bool dataIsCPUWorkBuffer;		// 0x10
	};

	static_assert(sizeof(ConstantGroup) == 0x18);
}
