#pragma once

#include "RE/B/BSFixedString.hpp"

namespace RE::BSResource::Archive2
{
	class StreamOpenedEvent
	{
	public:
		// members
		BSFixedString streamName;	 // 0x00
		BSFixedString sourceName;	 // 0x08
		std::uint64_t startOffset;	 // 0x10
		std::uint32_t sizeInArchive; // 0x18
	};

	static_assert(sizeof(StreamOpenedEvent) == 0x20);
}
