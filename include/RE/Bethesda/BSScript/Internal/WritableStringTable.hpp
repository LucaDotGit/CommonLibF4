#pragma once

#include "RE/Bethesda/BSFixedString.hpp"
#include "RE/Bethesda/BSTHashMap.hpp"
#include "RE/Bethesda/BSTObjectArena.hpp"

namespace RE::BSScript::Internal
{
	enum class StringIndexSize;

	class WritableStringTable
	{
	public:
		// members
		msvc::unique_ptr<BSTObjectArena<BSFixedString>> stringTable;						// 00
		msvc::unique_ptr<BSTScrapHashMap<BSFixedString, std::uint32_t>> stringReferenceMap; // 08
		REX::Enum<StringIndexSize, std::int32_t> indexSize;									// 10
	};
	static_assert(sizeof(WritableStringTable) == 0x18);
}
