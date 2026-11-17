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
		BSFixedString name;				 // 0x00
		BSTArray<Preset> presets;		 // 0x08
		BSTArray<std::uint32_t> sliders; // 0x20
		std::uint16_t presetMaskID;		 // 0x38
	};

	static_assert(sizeof(Group) == 0x40);
}
