#pragma once

#include "RE/N/NiColor.hpp"

namespace RE
{
	class BSLensFlareSpriteData
	{
	public:
		enum class Flags : std::uint32_t
		{
			kNone = 0,
			kRotates = 1 << 0,
			kShrinks = 1 << 1
		};

		// members
		NiColor color;							  // 00
		REX::Float32 width;						  // 0C
		REX::Float32 height;					  // 10
		REX::Float32 position;					  // 14
		REX::Float32 angularFade;				  // 18
		REX::Float32 opacity;					  // 1C
		REX::EnumSet<Flags, std::uint32_t> flags; // 20
	};
	static_assert(sizeof(BSLensFlareSpriteData) == 0x24);
}
