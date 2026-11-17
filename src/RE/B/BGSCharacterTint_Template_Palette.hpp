#pragma once

#include "RE/B/BGSCharacterTint_BlendOp.hpp"
#include "RE/B/BGSCharacterTint_Template_Entry.hpp"
#include "RE/B/BSTArray.hpp"

namespace RE::BGSCharacterTint::Template
{
	class __declspec(novtable) Palette : public Entry // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSCharacterTint__Template__Palette;
		inline static constexpr const auto& VTABLE = VTABLE::BGSCharacterTint__Template__Palette;

		class ColorValue
		{
		public:
			// members
			BGSColorForm* color;	// 0x00
			REX::Float32 value;		// 0x08
			BlendOp blendOp;		// 0x0C
			std::uint16_t swatchID; // 0x01
		};

		static_assert(sizeof(ColorValue) == 0x18);

		~Palette() override; // 0x00

		// members
		BSFixedString maskTextureName;	  // 0x20
		std::uint32_t defaultIndex;		  // 0x28
		BSTArray<ColorValue> colorValues; // 0x30
	};

	static_assert(sizeof(Palette) == 0x48);
}
