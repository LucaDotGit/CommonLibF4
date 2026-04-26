#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTObjectArena.hpp"

#include "msvc/memory.hpp"

namespace RE::BSScript::Internal
{
	enum class StringIndexSize : std::int32_t;

	class ReadableStringTable
	{
	public:
		class StringEntry
		{
		public:
			// members
			const char* originalData;	   // 00
			BSFixedString convertedString; // 08
		};
		static_assert(sizeof(StringEntry) == 0x10);

		class StringTableScrapPage
		{
		public:
			// members
			std::array<char, 0x1000> buffer; // 0000
			char* current;					 // 1000
			const char* end;				 // 1008
		};
		static_assert(sizeof(StringTableScrapPage) == 0x1010);

		// members
		msvc::unique_ptr<BSTScrapObjectArena<StringTableScrapPage, 1>> scrapPages; // 00
		msvc::unique_ptr<BSScrapArray<StringEntry>> entries;					   // 08
		REX::Enum<StringIndexSize, std::int32_t> indexSize;						   // 10
	};
	static_assert(sizeof(ReadableStringTable) == 0x18);
}
