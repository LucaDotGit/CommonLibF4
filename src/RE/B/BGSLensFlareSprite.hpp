#pragma once

#include "RE/B/BSLensFlareSpriteRenderData.hpp"
#include "RE/T/TESTexture.hpp"

namespace RE
{
	class __declspec(novtable) BGSLensFlareSprite : public BSLensFlareSpriteRenderData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSLensFlareSprite;
		inline static constexpr const auto& VTABLE = VTABLE::BGSLensFlareSprite;

		// members
		TESTexture spriteTexture; // 0x50
	};

	static_assert(sizeof(BGSLensFlareSprite) == 0x60);
}
