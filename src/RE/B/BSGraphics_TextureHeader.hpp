#pragma once

namespace RE::BSGraphics
{
	class TextureHeader
	{
	public:
		// members
		std::uint16_t height{0};  // 0x00
		std::uint16_t width{0};	  // 0x02
		std::uint8_t mipCount{0}; // 0x03
		std::uint8_t format{0};	  // 0x05
		std::uint8_t flags{0};	  // 0x06
		std::uint8_t tilemode{0}; // 0x07
	};

	static_assert(sizeof(TextureHeader) == 0x08);
}
