#pragma once

namespace RE::BSBTreeFile
{
	class PageInfoTable
	{
	public:
		// members
		std::byte* available;	   // 0x00 - To-Do
		std::byte* lru;			   // 0x08 - To-Do
		std::byte** table;		   // 0x10 - To-Do
		std::byte* infos;		   // 0x18 - To-Do
		std::uint32_t tableSize;   // 0x20
		std::uint32_t activeCount; // 0x24
		std::uint32_t dirtyOnLRU;  // 0x28
	};

	static_assert(sizeof(PageInfoTable) == 0x30);

	template <std::uint32_t PageSize>
	class PageCache : public PageInfoTable // 0x00
	{
		std::byte* memory;		 // 0x30 - To-Do
		std::uint32_t pageCount; // 0x38
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
	class PGFSEDL : public PageBasics<Key, PageSize>
	{
	public:
		using key_type = Key;

		class LeafNode;
	};

	template <class Pager, class Impl, std::size_t MAX_DEPTH>
	class BPTree : public Impl // 0x00
	{
	public:
		class PagePtr
		{
		public:
			// members
			union
			{
			public:
				Impl::InteriorNode* interior;
				Impl::LeafNode* leaf;
				std::byte* ptr{nullptr};
			}; // 0x00
		};

		static_assert(sizeof(PagePtr) == 0x08);

		class Cursor
		{
		public:
			class PageEntry
			{
			public:
				// members
				PagePtr page;				// 0x00
				std::uint64_t pageIndex{0}; // 0x08
			};

			static_assert(sizeof(PageEntry) == 0x10);

			// members
			std::array<PageEntry, MAX_DEPTH> pages;			   // 0x00
			std::array<std::uint32_t, MAX_DEPTH> positions{0}; // 0x??
			std::uint32_t depth{0};							   // 0x??
		};

		// members
		Pager* fpol{nullptr};			// 0x00
		PagePtr* root{nullptr};			// 0x18
		std::uint64_t rootPageIndex{0}; // 0x10
		std::uint32_t active{0};		// 0x18
		std::uint32_t depth{0};			// 0x1C
	};

	// static_assert(sizeof(BPTree) == 0x20);
}
