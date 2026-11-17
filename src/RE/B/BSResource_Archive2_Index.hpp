#pragma once

#include "RE/B/BSBTreeFile.hpp"
#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSReadWriteLock.hpp"
#include "RE/B/BSResource_AsyncStream.hpp"
#include "RE/B/BSResource_ID.hpp"
#include "RE/B/BSResource_Stream.hpp"
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

	class __declspec(novtable) Index :
		public BSTEventSink<RegisteredEvent>,	// 0x00
		public BSTEventSink<ClearRegistryEvent> // 0x08
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSResource__Archive2__Index;
		inline static constexpr const auto& VTABLE = VTABLE::BSResource__Archive2__Index;

		class Pager;
		class NameIDAccess;

		class Chunk
		{
		public:
			// members
			std::uint64_t dataFileOffset;	// 0x00
			std::uint32_t compressedSize;	// 0x08
			std::uint32_t uncompressedSize; // 0x0C
		};

		static_assert(sizeof(Chunk) == 0x10);

		class Loose
		{
		public:
			// members
			Location* location;		// 0x00
			BSFixedString nameText; // 0x08
		};

		static_assert(sizeof(Loose) == 0x10);

		class EntryHeader
		{
		public:
#define RUNTIME_DATA_CONTENT                  \
	std::uint8_t chunkCount;		 /* 00 */ \
	std::uint16_t chunkOffsetOrType; /* 01 */

			class RuntimeData
			{
			public:
				// members
				RUNTIME_DATA_CONTENT; // 0x00
			};

			static_assert(sizeof(RuntimeData) == 0x04);

			[[nodiscard]]
			auto GetDataFileIndex() noexcept
				-> std::variant<std::reference_wrapper<std::uint8_t>, std::reference_wrapper<std::uint16_t>>;
			[[nodiscard]]
			auto GetDataFileIndex() const noexcept -> std::variant<
				std::reference_wrapper<const std::uint8_t>,
				std::reference_wrapper<const std::uint16_t>>;

			[[nodiscard]]
			auto GetRuntimeData() noexcept -> RuntimeData&;
			[[nodiscard]]
			auto GetRuntimeData() const noexcept -> const RuntimeData&;

			[[nodiscard]]
			auto IsChunk() const noexcept -> bool;
			[[nodiscard]]
			auto IsLoose() const noexcept -> bool;

			// members
			ID nameID; // 0x00
#if (COMMONLIB_RUNTIME_AE == 0)
			std::uint8_t dataFileIndex; // 0x0C
			RUNTIME_DATA_CONTENT;		// 0x0D
#elif (COMMONLIB_RUNTIME_VR == 0 && COMMONLIB_RUNTIME_OG == 0 && COMMONLIB_RUNTIME_NG == 0)
			std::uint16_t dataFileIndex; // 0x0C
			RUNTIME_DATA_CONTENT;		 // 0x0E
#endif
		};

#if (COMMONLIB_RUNTIME_AE == 0)
		static_assert(sizeof(EntryHeader) == 0x10);
#elif (COMMONLIB_RUNTIME_VR == 0 && COMMONLIB_RUNTIME_OG == 0 && COMMONLIB_RUNTIME_NG == 0)
		static_assert(sizeof(EntryHeader) == 0x14);
#else
		static_assert(sizeof(EntryHeader) == 0x0C);
#endif

#undef RUNTIME_DATA_CONTENT

		class Entry : public EntryHeader // 0x00
		{
		public:
			~Entry() noexcept
			{
				if (IsLoose()) {
					loose.~Loose();
					return;
				}

				chunk.~Chunk();
			}

			Entry(const Entry&) = delete;
			Entry(Entry&&) = delete;

			auto operator=(const Entry&) -> Entry& = delete;
			auto operator=(Entry&&) -> Entry& = delete;

			// members
			union
			{
			public:
				Chunk chunk;
				Loose loose;
				std::array<std::byte, std::max(sizeof(Chunk), sizeof(Loose))> buffer{static_cast<std::byte>(0)};
			}; // 0x10

			BSFixedString stringName; // 0x20
		};

#if (COMMONLIB_RUNTIME_AE == 0)
		static_assert(sizeof(Entry) == 0x28);
#elif (COMMONLIB_RUNTIME_VR == 0 && COMMONLIB_RUNTIME_OG == 0 && COMMONLIB_RUNTIME_NG == 0)
		static_assert(sizeof(Entry) == 0x30);
#else
		static_assert(sizeof(Entry) == 0x28);
#endif

		class CursorWithEntry :
			public BSBTreeFile::BPTree<Pager, BSBTreeFile::PGFSEDL<Entry, ID, 4'096>, 16>::Cursor // 0x00
		{
		public:
			// members
			Entry entry; // 0x148
		};

#if (COMMONLIB_RUNTIME_AE == 0)
		static_assert(sizeof(CursorWithEntry) == 0x170);
#elif (COMMONLIB_RUNTIME_VR == 0 && COMMONLIB_RUNTIME_OG == 0 && COMMONLIB_RUNTIME_NG == 0)
		static_assert(sizeof(CursorWithEntry) == 0x178);
#else
		static_assert(sizeof(CursorWithEntry) == 0x170);
#endif

#define RUNTIME_DATA_FILES_01                                                  \
	std::array<BSTSmartPointer<Stream>, 0x100> dataFiles;			/* 0000 */ \
	std::array<BSTSmartPointer<AsyncStream>, 0x100> asyncDataFiles; /* 0800 */ \
	std::array<ID, 0x100> dataFileNameIDs;							/* 1000 */

#define RUNTIME_DATA_FILES_02                                                  \
	std::array<BSTSmartPointer<Stream>, 0x400> dataFiles;			/* 0000 */ \
	std::array<BSTSmartPointer<AsyncStream>, 0x400> asyncDataFiles; /* 2000 */ \
	std::array<ID, 0x400> dataFileNameIDs;							/* 4000 */

#define RUNTIME_DATA_CONTENT                                                                 \
	std::uint32_t dataFileCount;													/* 00 */ \
	BSBTreeFile::BPTree<Pager, BSBTreeFile::PGFSEDL<Entry, ID, 0x1000>, 0x10> tree; /* 08 */ \
	mutable BSReadWriteLock lock;													/* 28 */

		class RuntimeDataFiles01
		{
		public:
			// members
			RUNTIME_DATA_FILES_01; // 0x0000
		};

		static_assert(sizeof(RuntimeDataFiles01) == 0x1C00);

		class RuntimeDataFiles02
		{
		public:
			// members
			RUNTIME_DATA_FILES_02; // 0x0000
		};

		static_assert(sizeof(RuntimeDataFiles02) == 0x7000);

		class RuntimeData
		{
		public:
			// members
			RUNTIME_DATA_CONTENT; // 0x00
		};

		static_assert(sizeof(RuntimeData) == 0x30);

		[[nodiscard]]
		auto GetRuntimeDataFiles() noexcept
			-> std::variant<std::reference_wrapper<RuntimeDataFiles01>, std::reference_wrapper<RuntimeDataFiles02>>;
		[[nodiscard]]
		auto GetRuntimeDataFiles() const noexcept -> std::variant<
			std::reference_wrapper<const RuntimeDataFiles01>,
			std::reference_wrapper<const RuntimeDataFiles02>>;

		[[nodiscard]]
		auto GetRuntimeData() noexcept -> RuntimeData&;
		[[nodiscard]]
		auto GetRuntimeData() const noexcept -> const RuntimeData&;

		// members
		BSTSmallIndexScatterTable<ID, NameIDAccess> nameTable; // 0x0010
#if (COMMONLIB_RUNTIME_AE == 0)
		RUNTIME_DATA_FILES_01; // 0x0030
		RUNTIME_DATA_CONTENT;  // 0x1C30
#elif (COMMONLIB_RUNTIME_VR == 0 && COMMONLIB_RUNTIME_OG == 0 && COMMONLIB_RUNTIME_NG == 0)
		RUNTIME_DATA_FILES_02; // 0x0030
		RUNTIME_DATA_CONTENT;  // 0x7030
#endif
	};

#if (COMMONLIB_RUNTIME_AE == 0)
	static_assert(sizeof(Index) == 0x1C60);
#elif (COMMONLIB_RUNTIME_VR == 0 && COMMONLIB_RUNTIME_OG == 0 && COMMONLIB_RUNTIME_NG == 0)
	static_assert(sizeof(Index) == 0x7060);
#else
	static_assert(sizeof(Index) == 0x30);
#endif
}

#undef RUNTIME_DATA_FILES_01
#undef RUNTIME_DATA_FILES_02
#undef RUNTIME_DATA_CONTENT
