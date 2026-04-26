#pragma once

#include "RE/B/BGSCharacterTint_BlendOp.hpp"
#include "RE/B/BGSCharacterTint_Template_Entry.hpp"
#include "RE/B/BSTArray.hpp"

namespace RE::BGSCharacterTint::Template
{
	class __declspec(novtable) Palette
		: public Entry // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSCharacterTint__Template__Palette };
		inline static constexpr auto VTABLE{ VTABLE::BGSCharacterTint__Template__Palette };

		class ColorValue
		{
		public:
			// members
			BGSColorForm* color;	// 00
			REX::Float32 value;		// 08
			BlendOp blendOp;		// 0C
			std::uint16_t swatchID; // 01
		};
		static_assert(sizeof(ColorValue) == 0x18);

		~Palette() override; // 00

		// members
		BSFixedString maskTextureName;	  // 20
		std::uint32_t defaultIndex;		  // 28
		BSTArray<ColorValue> colorValues; // 30
	};
	static_assert(sizeof(Palette) == 0x48);
}
