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
			std::uint32_t id;	  // 0x00
			std::uint32_t offset; // 0x04
		};

		static_assert(sizeof(Entry) == 0x08);

		// members
		StringFileInfo::Entry* entries;				// 0x00
		std::uint32_t numEntries;					// 0x08
		std::byte* stringBlock;						// 0x10
		std::uint32_t stringBlockSize;				// 0x18
		std::uint32_t stringBlockOffset;			// 0x1C
		BSTSmartPointer<BSResource::Stream> stream; // 0x20
		mutable BSSpinLock streamLock;				// 0x28
		BSFixedString filePath;						// 0x30
	};

	static_assert(sizeof(StringFileInfo) == 0x38);
}
