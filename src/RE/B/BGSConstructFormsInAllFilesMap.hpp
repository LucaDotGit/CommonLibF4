#pragma once

#include "BGSConstructedForms.hpp"
#include "RE/B/BSTHashMap.hpp"

namespace RE
{
	class BGSConstructFormsInFileMap;
	class TESFile;

	class BGSConstructFormsInAllFilesMap : BSTHashMap<TESFile*, BGSConstructFormsInFileMap*> // 0x00
	{
	public:
		// members
		BGSConstructedForms constructedForms; // 0x30
		std::uint32_t count;				  // 0x78
	};

	static_assert(sizeof(BGSConstructFormsInAllFilesMap) == 0x80);
}
