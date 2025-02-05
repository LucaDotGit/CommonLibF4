#pragma once

namespace RE::Scaleform::Render
{
	class Color;

	class Color
	{
	public:
		struct Rgb32
		{
		public:
			// members
			std::uint8_t blue;	// 00
			std::uint8_t green; // 01
			std::uint8_t red;	// 02
			std::uint8_t alpha; // 03
		};
		static_assert(sizeof(Rgb32) == 0x4);

		// members
		union
		{
			Rgb32 channels;
			std::uint32_t raw;
		}; // 00
	};
	static_assert(sizeof(Color) == 0x4);
}
