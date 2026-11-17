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
		std::array<BGSLocalizedString, std::to_underlying(SEX::_Count)> rankTitles; // 0x00
		TESTexture textureInsignia;													// 0x10
	};

	static_assert(sizeof(RANK_DATA) == 0x20);
}
