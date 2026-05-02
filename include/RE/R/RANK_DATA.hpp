#pragma once

#include "RE/B/BGSLocalizedString.hpp"
#include "RE/S/SEX.hpp"
#include "RE/T/TESTexture.hpp"

namespace RE
{
	class RANK_DATA
	{
	public:
		~RANK_DATA()
		{
			for (auto& rankTitle : rankTitles) {
				rankTitle.~BGSLocalizedString();
			}
		}

		// members
		union
		{
			struct
			{
				BGSLocalizedString maleRankTitle;
				BGSLocalizedString femaleRankTitle;
			};
			std::array<BGSLocalizedString, std::to_underlying(SEX::kTotal)> rankTitles{};
		}; // 00
		TESTexture textureInsignia; // 10
	};
	static_assert(sizeof(RANK_DATA) == 0x20);
}
