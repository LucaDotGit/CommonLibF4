#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTHashMap.hpp"

namespace RE
{
	class PersistentStringInfo
	{
	public:
		// members
		BSTHashMap<std::uint32_t, BSFixedStringCS> idStringMap; // 00
		BSFixedString filePath;									// 30
	};
	static_assert(sizeof(PersistentStringInfo) == 0x38);
}
