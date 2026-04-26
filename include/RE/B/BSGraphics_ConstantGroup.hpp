#pragma once

namespace RE::BSGraphics
{
	class ConstantGroup
	{
	public:
		// members
		REX::W32::ID3D11Buffer* buffer; // 00
		REX::Float32* data;				// 08
		bool dataIsCPUWorkBuffer;		// 10
	};
	static_assert(sizeof(ConstantGroup) == 0x18);
}
