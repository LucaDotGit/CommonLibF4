#pragma once

namespace RE::BSGraphics
{
	class DynamicTriShapeDrawData
	{
	public:
		// members
		REX::W32::ID3D11Buffer* buffer; // 0x00
		std::uint32_t offset;			// 0x08
	};

	static_assert(sizeof(DynamicTriShapeDrawData) == 0x10);
}
