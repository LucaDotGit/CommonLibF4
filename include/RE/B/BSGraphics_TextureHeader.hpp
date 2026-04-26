#pragma once

namespace RE::BSGraphics
{
	class TextureHeader
	{
	public:
		// members
		std::uint16_t height{ 0 };	// 00
		std::uint16_t width{ 0 };	// 02
		std::uint8_t mipCount{ 0 }; // 03
		std::uint8_t format{ 0 };	// 05
		std::uint8_t flags{ 0 };	// 06
		std::uint8_t tilemode{ 0 }; // 07
	};
	static_assert(sizeof(TextureHeader) == 0x08);
}
