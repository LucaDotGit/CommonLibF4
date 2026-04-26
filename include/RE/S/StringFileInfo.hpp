#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSResource
{
	class Stream;
}

namespace RE
{
	class StringFileInfo
	{
	public:
		class Entry
		{
		public:
			// members
			std::uint32_t id;	  // 00
			std::uint32_t offset; // 04
		};
		static_assert(sizeof(Entry) == 0x08);

		// members
		StringFileInfo::Entry* entries;				// 00
		std::uint32_t numEntries;					// 08
		std::byte* stringBlock;						// 10
		std::uint32_t stringBlockSize;				// 18
		std::uint32_t stringBlockOffset;			// 1C
		BSTSmartPointer<BSResource::Stream> stream; // 20
		mutable BSSpinLock streamLock;				// 28
		BSFixedString filePath;						// 30
	};
	static_assert(sizeof(StringFileInfo) == 0x38);
}
