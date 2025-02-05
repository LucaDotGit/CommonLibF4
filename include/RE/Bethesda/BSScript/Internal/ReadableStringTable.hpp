#pragma once

#include "RE/Bethesda/BSContainer.hpp"
#include "RE/Bethesda/BSFixedString.hpp"
#include "RE/Bethesda/BSLock.hpp"
#include "RE/Bethesda/BSTArray.hpp"
#include "RE/Bethesda/BSTEvent.hpp"
#include "RE/Bethesda/BSTHashMap.hpp"
#include "RE/Bethesda/BSTObjectArena.hpp"
#include "RE/Bethesda/BSTSmartPointer.hpp"
#include "RE/Bethesda/BSTTuple.hpp"
#include "RE/Bethesda/MemoryManager.hpp"

namespace RE
{
	namespace BSScript
	{
		namespace Internal
		{
			enum class StringIndexSize
			{
				kSmall,
				kLarge
			};

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
					char buffer[0x1000];   // 0000
					char* curr;			   // 1000
					const char* const end; // 1008
				};
				static_assert(sizeof(StringTableScrapPage) == 0x1010);

				// members
				msvc::unique_ptr<BSTObjectArena<StringTableScrapPage, BSTObjectArenaScrapAlloc, 1>> scrapPages; // 00
				msvc::unique_ptr<BSScrapArray<StringEntry>> entries;											// 08
				REX::Enum<StringIndexSize, std::uint32_t> indexSize;											// 10
			};
			static_assert(sizeof(ReadableStringTable) == 0x18);
		}
	}
}
