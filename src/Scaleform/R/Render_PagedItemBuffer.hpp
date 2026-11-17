#pragma once

namespace Scaleform::Render
{
	template <class C, std::int32_t N>
	class PagedItemBuffer
	{
	public:
		class Page
		{
		public:
			// members
			Page* next;				// 0x00
			std::int32_t count;		// 0x08
			std::array<C, N> items; // 0x??
		};

		// members
		Page* pages; // 0x00
		Page* last;	 // 0x08
	};

	static_assert(sizeof(PagedItemBuffer<void*, 0>) == 0x10);
}
