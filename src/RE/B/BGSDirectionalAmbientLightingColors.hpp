#pragma once

namespace RE
{
	class BGSDirectionalAmbientLightingColors
	{
	public:
		enum class ColorIndex : std::int32_t
		{
			XPos = 0,
			XNeg = 1,
			YPos = 2,
			YNeg = 3,
			ZPos = 4,
			ZNeg = 5,
			AxisCount = 6,
			SpecularTint = 6,

			_Count = 7
		};

		// members
		std::array<std::uint32_t, std::to_underlying(ColorIndex::_Count)> colorValues; // 0x00
		REX::Float32 fresnelPower;													   // 0x1C
	};

	static_assert(sizeof(BGSDirectionalAmbientLightingColors) == 0x20);
}
