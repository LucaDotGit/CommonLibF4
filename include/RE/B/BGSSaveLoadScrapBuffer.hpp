#pragma once

namespace RE
{
	class ScrapHeap;

	class BGSSaveLoadScrapBuffer
	{
	public:
		// members
		std::byte* buffer;		  // 00
		ScrapHeap* scrapHeap;	  // 08
		std::uint32_t bufferSize; // 10
	};
	static_assert(sizeof(BGSSaveLoadScrapBuffer) == 0x18);
}
