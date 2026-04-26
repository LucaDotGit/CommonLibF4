#pragma once

#include "RE/B/BSBTreeFile.hpp"
#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSResource_AsyncStream.hpp"
#include "RE/B/BSResource_ID.hpp"
#include "RE/B/BSResource_Stream.hpp"
#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTSmallIndexScatterTable.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSResource
{
	class Location;
}

namespace RE::BSResource::Archive2
{
	class RegisteredEvent;
	class ClearRegistryEvent;

	class __declspec(novtable) Index
		: public BSTEventSink<RegisteredEvent>,	  // 00
		  public BSTEventSink<ClearRegistryEvent> // 08
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSResource__Archive2__Index };
		inline static constexpr auto VTABLE{ VTABLE::BSResource__Archive2__Index };

		class Pager;
		class NameIDAccess;

		class Chunk
		{
		public:
			// members
			std::uint64_t dataFileOffset;	// 00
			std::uint32_t compressedSize;	// 08
			std::uint32_t uncompressedSize; // 0C
		};
		static_assert(sizeof(Chunk) == 0x10);

		class Loose
		{
		public:
			// members
			Location* location;		// 00
			BSFixedString nameText; // 08
		};
		static_assert(sizeof(Loose) == 0x10);

		class EntryHeader
		{
		public:
			[[nodiscard]] bool IsChunk() const noexcept { return chunkOffsetOrType != 0; }
			[[nodiscard]] bool IsLoose() const noexcept { return chunkOffsetOrType == 0; }

			// members
			ID nameID;						 // 00
			std::uint8_t dataFileIndex;		 // 0C
			std::uint8_t chunkCount;		 // 0D
			std::uint16_t chunkOffsetOrType; // 0E
		};
		static_assert(sizeof(EntryHeader) == 0x10);

		class Entry
			: public EntryHeader // 00
		{
		public:
			~Entry()
			{
				if (IsLoose()) {
					loose.~Loose();
				}
				else {
					chunk.~Chunk();
				}
			}

			// members
			union
			{
				Chunk chunk;
				Loose loose;
				std::array<std::byte, std::max(sizeof(Chunk), sizeof(Loose))> buffer{ static_cast<std::byte>(0) };
			}; // 10
			BSFixedString stringName; // 20
		};
		static_assert(sizeof(Entry) == 0x28);

		class CursorWithEntry
			: public BSBTreeFile::BPTree<Pager, BSBTreeFile::PGFSEDL<Entry, ID, 4096>, 16>::Cursor // 00
		{
		public:
			// members
			Entry entry; // 148
		};
		static_assert(sizeof(CursorWithEntry) == 0x170);

		// members
		BSTSmallIndexScatterTable<ID, NameIDAccess> nameTable;							// 0010
		std::array<BSTSmartPointer<Stream>, 0x100> dataFiles;							// 0030
		std::array<BSTSmartPointer<AsyncStream>, 0x100> asyncDataFiles;					// 0830
		std::array<ID, 0x100> dataFileNameIDs;											// 1030
		std::uint32_t dataFileCount;													// 1C30
		BSBTreeFile::BPTree<Pager, BSBTreeFile::PGFSEDL<Entry, ID, 0x1000>, 0x10> tree; // 1C38
		mutable BSReadWriteLock lock;													// 1C58
	};
	static_assert(sizeof(Index) == 0x1C60);
}
