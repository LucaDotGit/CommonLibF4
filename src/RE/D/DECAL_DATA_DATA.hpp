#pragma once

namespace RE
{
	class DECAL_DATA_DATA
	{
	public:
		enum class Flags : std::uint8_t
		{
			None = 0,
			POMShadows = 1 << 0,
			AlphaBlending = 1 << 1,
			AlphaTesting = 1 << 2,
			NoSubtexture = 1 << 3,
			MultiplicativeBlending = 1 << 4
		};

		// members
		REX::Float32 decalMinWidth;				 // 0x00
		REX::Float32 decalMaxWidth;				 // 0x04
		REX::Float32 decalMinHeight;			 // 0x08
		REX::Float32 decalMaxHeight;			 // 0x0C
		REX::Float32 depth;						 // 0x10
		REX::Float32 shininess;					 // 0x14
		REX::Float32 parallaxScale;				 // 0x18
		std::uint8_t parallaxPasses;			 // 0x1C
		REX::EnumSet<Flags, std::uint8_t> flags; // 0x1D
		std::uint32_t color;					 // 0x20
	};

	static_assert(sizeof(DECAL_DATA_DATA) == 0x24);
}
