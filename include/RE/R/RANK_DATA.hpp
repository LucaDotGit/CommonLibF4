#pragma once

#include "RE/B/BGSLocalizedString.hpp"
#include "RE/S/SEX.hpp"
#include "RE/T/TESTexture.hpp"

namespace RE
{
	class RANK_DATA
	{
	public:
		// members
		std::array<BGSLocalizedString, std::to_underlying(SEX::kTotal)> rankTitles; // 00
		TESTexture textureInsignia;													// 10
	};
	static_assert(sizeof(RANK_DATA) == 0x20);
}
