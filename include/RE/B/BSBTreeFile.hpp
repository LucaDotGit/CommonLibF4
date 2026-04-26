#pragma once

namespace RE::BSBTreeFile
{
	class PageInfoTable
	{
	public:
		// members
		std::byte* available;	   // 00 - TODO
		std::byte* lru;			   // 08 - TODO
		std::byte** table;		   // 10 - TODO
		std::byte* infos;		   // 18 - TODO
		std::uint32_t tableSize;   // 20
		std::uint32_t activeCount; // 24
		std::uint32_t dirtyOnLRU;  // 28
	};
	static_assert(sizeof(PageInfoTable) == 0x30);

	template <std::uint32_t PageSize>
	class PageCache
		: public PageInfoTable // 00
	{
		std::byte* memory;		 // 30 - TODO
		std::uint32_t pageCount; // 38
	};
	static_assert(sizeof(PageCache<16>) == 0x40);

	template <class Key, std::size_t PageSize>
	class PageBasics
	{
	public:
		using key_type = Key;

		class InteriorNode;
	};

	template <class T, class Key, std::size_t PageSize>
	class PGFSEDL
		: public PageBasics<Key, PageSize>
	{
	public:
		using key_type = Key;

		class LeafNode;
	};

	template <class Pager, class Impl, std::size_t MAX_DEPTH>
	class BPTree
		: public Impl // 00
	{
	public:
		class PagePtr
		{
		public:
			// members
			union
			{
				Impl::InteriorNode* interior;
				Impl::LeafNode* leaf;
				std::byte* ptr{ nullptr };
			}; // 00
		};
		static_assert(sizeof(PagePtr) == 0x08);

		class Cursor
		{
		public:
			class PageEntry
			{
			public:
				// members
				PagePtr page;				  // 00
				std::uint64_t pageIndex{ 0 }; // 08
			};
			static_assert(sizeof(PageEntry) == 0x10);

			// members
			std::array<PageEntry, MAX_DEPTH> pages;				 // 00
			std::array<std::uint32_t, MAX_DEPTH> positions{ 0 }; // ??
			std::uint32_t depth{ 0 };							 // ??
		};

		// members
		Pager* fpol{ nullptr };			  // 00
		PagePtr* root{ nullptr };		  // 18
		std::uint64_t rootPageIndex{ 0 }; // 10
		std::uint32_t active{ 0 };		  // 18
		std::uint32_t depth{ 0 };		  // 1C
	};
	// static_assert(sizeof(BPTree) == 0x20);
}
