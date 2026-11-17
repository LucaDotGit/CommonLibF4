#pragma once

#include "RE/B/BGSLocalizedString.hpp"
#include "RE/B/BSFixedString.hpp"

namespace RE::BGSCharacterMorph
{
	class Preset
	{
	public:
		// members
		BGSLocalizedString name;   // 0x00
		BSFixedString morph;	   // 0x08
		BGSTextureSet* textureSet; // 0x10
		std::uint8_t flags;		   // 0x18
		std::uint32_t id;		   // 0x1C
	};

	static_assert(sizeof(Preset) == 0x20);
}
