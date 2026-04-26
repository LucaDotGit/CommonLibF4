#pragma once

#include "RE/B/BGSLocalizedString.hpp"
#include "RE/B/BSFixedString.hpp"

namespace RE::BGSCharacterMorph
{
	class Preset
	{
	public:
		// members
		BGSLocalizedString name;   // 00
		BSFixedString morph;	   // 08
		BGSTextureSet* textureSet; // 10
		std::uint8_t flags;		   // 18
		std::uint32_t id;		   // 1C
	};
	static_assert(sizeof(Preset) == 0x20);
}
