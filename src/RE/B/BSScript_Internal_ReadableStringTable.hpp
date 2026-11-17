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
			const char* originalData;	   // 0x00
			BSFixedString convertedString; // 0x08
		};

		static_assert(sizeof(StringEntry) == 0x10);

		class StringTableScrapPage
		{
		public:
			// members
			REX::StaticString<0x1000> buffer; // 0x0000
			char* current;					  // 0x1000
			const char* end;				  // 0x1008
		};

		static_assert(sizeof(StringTableScrapPage) == 0x1010);

		// members
		msvc::unique_ptr<BSTScrapObjectArena<StringTableScrapPage, 0x01>> scrapPages; // 0x00
		msvc::unique_ptr<BSScrapArray<StringEntry>> entries;						  // 0x08
		REX::Enum<StringIndexSize, std::int32_t> indexSize;							  // 0x10
	};

	static_assert(sizeof(ReadableStringTable) == 0x18);
}
