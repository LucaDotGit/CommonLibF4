#pragma once

namespace RE
{
	class BGSDirectionalAmbientLightingColors
	{
	public:
		enum class ColorIndex : std::int32_t
		{
			kXPos = 0,
			kXNeg = 1,
			kYPos = 2,
			kYNeg = 3,
			kZPos = 4,
			kZNeg = 5,
			kAxisCount = 6,
			kSpecularTint = 6,

			kTotal = 7
		};

		// members
		std::array<std::uint32_t, std::to_underlying(ColorIndex::kTotal)> colorValues; // 00
		REX::Float32 fresnelPower;													   // 1C
	};
	static_assert(sizeof(BGSDirectionalAmbientLightingColors) == 0x20);
}
