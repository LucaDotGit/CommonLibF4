#pragma once

#include "RE/B/BGSCharacterTint_MaskEntry.hpp"

namespace RE::BGSCharacterTint
{
	class __declspec(novtable) PaletteEntry
		: public MaskEntry // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSCharacterTint__PaletteEntry };
		inline static constexpr auto VTABLE{ VTABLE::BGSCharacterTint__PaletteEntry };

		// members
		std::uint32_t tintingColor; // 18
		std::uint16_t swatchID;		// 1C
	};
	static_assert(sizeof(PaletteEntry) == 0x20);
}
