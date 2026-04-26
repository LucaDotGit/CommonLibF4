#pragma once

namespace RE
{
	class DECAL_DATA_DATA
	{
	public:
		enum class Flags : std::uint8_t
		{
			kNone = 0,
			kNoDecalData = 1 << 0
		};

		// members
		REX::Float32 decalMinWidth;				 // 00
		REX::Float32 decalMaxWidth;				 // 04
		REX::Float32 decalMinHeight;			 // 08
		REX::Float32 decalMaxHeight;			 // 0C
		REX::Float32 depth;						 // 10
		REX::Float32 shininess;					 // 14
		REX::Float32 parallaxScale;				 // 18
		std::int8_t parallaxPasses;				 // 1C
		REX::EnumSet<Flags, std::uint8_t> flags; // 1D
		std::uint32_t color;					 // 20
	};
	static_assert(sizeof(DECAL_DATA_DATA) == 0x24);
}
