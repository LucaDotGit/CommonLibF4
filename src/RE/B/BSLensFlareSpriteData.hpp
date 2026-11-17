#pragma once

#include "RE/N/NiColor.hpp"

namespace RE
{
	class BSLensFlareSpriteData
	{
	public:
		enum class Flags : std::uint32_t
		{
			None = 0,
			Rotates = 1 << 0,
			Shrinks = 1 << 1
		};

		// members
		NiColor color;							  // 0x00
		REX::Float32 width;						  // 0x0C
		REX::Float32 height;					  // 0x10
		REX::Float32 position;					  // 0x14
		REX::Float32 angularFade;				  // 0x18
		REX::Float32 opacity;					  // 0x1C
		REX::EnumSet<Flags, std::uint32_t> flags; // 0x20
	};

	static_assert(sizeof(BSLensFlareSpriteData) == 0x24);
}
