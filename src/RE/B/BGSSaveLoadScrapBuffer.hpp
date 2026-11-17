#pragma once

namespace RE
{
	class ScrapHeap;

	class BGSSaveLoadScrapBuffer
	{
	public:
		// members
		std::byte* buffer;		  // 0x00
		ScrapHeap* scrapHeap;	  // 0x08
		std::uint32_t bufferSize; // 0x10
	};

	static_assert(sizeof(BGSSaveLoadScrapBuffer) == 0x18);
}
