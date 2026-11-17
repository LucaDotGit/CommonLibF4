#pragma once

#include "RE/B/BSFixedString.hpp"

namespace RE
{
	class TESImageSpaceModifierForm;

	class ImageSpaceModifierFinder
	{
	public:
		// members
		TESImageSpaceModifierForm* modifier; // 0x00
		const BSFixedString& modifierToFind; // 0x08
	};

	static_assert(sizeof(ImageSpaceModifierFinder) == 0x10);
}
