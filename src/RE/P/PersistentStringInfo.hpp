#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTHashMap.hpp"

namespace RE
{
	class PersistentStringInfo
	{
	public:
		// members
		BSTHashMap<std::uint32_t, BSFixedStringCS> idStringMap; // 0x00
		BSFixedString filePath;									// 0x30
	};

	static_assert(sizeof(PersistentStringInfo) == 0x38);
}
