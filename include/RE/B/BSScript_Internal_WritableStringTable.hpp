#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/B/BSTObjectArena.hpp"

#include "msvc/memory.hpp"

namespace RE::BSScript::Internal
{
	enum class StringIndexSize : std::int32_t;

	class WritableStringTable
	{
	public:
		// members
		msvc::unique_ptr<BSTScrapObjectArena<BSFixedString, 32>> stringTable;				// 00
		msvc::unique_ptr<BSTScrapHashMap<BSFixedString, std::uint32_t>> stringReferenceMap; // 08
		REX::Enum<StringIndexSize, std::int32_t> indexSize;									// 10
	};
	static_assert(sizeof(WritableStringTable) == 0x18);
}
