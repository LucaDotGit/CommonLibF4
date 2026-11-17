#pragma once

namespace Scaleform
{
	class MemoryHeap;
}

namespace Scaleform::Render
{
	class LinearHeap
	{
	public:
		class PageType
		{
		public:
			// members
			std::byte* start; // 0x00
			std::byte* end;	  // 0x08
			std::byte* free;  // 0x10
		};

		static_assert(sizeof(PageType) == 0x18);

		// members
		MemoryHeap* heap;		 // 0x00
		std::size_t granularity; // 0x08
		PageType* pagePool;		 // 0x10
		PageType* lastPage;		 // 0x18
		std::size_t maxPages;	 // 0x20
	};

	static_assert(sizeof(LinearHeap) == 0x28);
}
