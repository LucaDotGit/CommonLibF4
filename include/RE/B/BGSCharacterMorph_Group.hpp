#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTArray.hpp"

namespace RE::BGSCharacterMorph
{
	class Preset;

	class Group
	{
	public:
		// members
		BSFixedString name;				 // 00
		BSTArray<Preset> presets;		 // 08
		BSTArray<std::uint32_t> sliders; // 20
		std::uint16_t presetMaskID;		 // 38
	};
	static_assert(sizeof(Group) == 0x40);
}
