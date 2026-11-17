#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTTuple.hpp"

namespace RE
{
	class INSTANCE_FILTER
	{
	public:
		// members
		std::uint32_t levelOverride;									  // 0x00
		std::uint8_t tierStartLevel;									  // 0x04
		std::uint8_t altLevelsPerTier;									  // 0x05
		bool epic;														  // 0x06
		BSScrapArray<BSTPair<BGSKeyword*, std::uint32_t>> keywordChances; // 0x08
	};

	static_assert(sizeof(INSTANCE_FILTER) == 0x28);
}
