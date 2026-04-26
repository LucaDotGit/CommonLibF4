#pragma once

#include "RE/B/BSLensFlareSpriteRenderData.hpp"
#include "RE/T/TESTexture.hpp"

namespace RE
{
	class __declspec(novtable) BGSLensFlareSprite
		: public BSLensFlareSpriteRenderData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSLensFlareSprite };
		inline static constexpr auto VTABLE{ VTABLE::BGSLensFlareSprite };

		// members
		TESTexture spriteTexture; // 50
	};
	static_assert(sizeof(BGSLensFlareSprite) == 0x60);
}
