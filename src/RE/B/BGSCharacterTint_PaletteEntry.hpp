#pragma once

#include "RE/B/BGSCharacterTint_MaskEntry.hpp"

namespace RE::BGSCharacterTint
{
	class __declspec(novtable) PaletteEntry : public MaskEntry // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSCharacterTint__PaletteEntry;
		inline static constexpr const auto& VTABLE = VTABLE::BGSCharacterTint__PaletteEntry;

		~PaletteEntry() override; // 0x00

		// members
		std::uint32_t tintingColor; // 0x18
		std::uint16_t swatchID;		// 0x1C
	};

	static_assert(sizeof(PaletteEntry) == 0x20);
}
