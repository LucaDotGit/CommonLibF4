#pragma once

#include "RE/B/BSFile.hpp"
#include "RE/B/BSSimpleList.hpp"
#include "RE/B/BSString.hpp"
#include "RE/B/BSSystemFile.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/F/FILE_HEADER.hpp"
#include "RE/F/FORM.hpp"
#include "RE/M/MemoryManager.hpp"
#include "RE/N/NiFile.hpp"
#include "RE/S/SimpleArray.hpp"

namespace RE
{
	enum class CHUNK_ID : std::int32_t;
	enum class TES_RETURN_CODE : std::int32_t;

	class FORM_GROUP;
	class TESBitArrayFile;

	class TESFile
	{
	public:
		inline static constexpr auto DEFAULT_BUFFER_SIZE = static_cast<std::uint32_t>(REX::Kibibyte(64).count());

		// Resolves into `GetINISetting("fMasterFilePreLoadMB:General"sv)->GetFloat() *
		// static_cast<REX::Float32>(1024.0) * static_cast<REX::Float32>(1024.0)`.
		inline static constexpr auto RESOLVABLE_MASTER_BUFFER_SIZE = static_cast<std::uint32_t>(-3);
		// Resolves into `DEFAULT_BUFFER_SIZE`.
		inline static constexpr auto RESOLVABLE_DEFAULT_BUFFER_SIZE = static_cast<std::uint32_t>(-2);
		// Resolves into no buffer allocation.
		inline static constexpr auto RESOLVABLE_INVALID_BUFFER_SIZE = static_cast<std::uint32_t>(-1);

		enum class Flags : std::uint32_t
		{
			None = 0,
			Master = 1 << 0,
			Altered = 1 << 1,
			Checked = 1 << 2,
			Active = 1 << 3,
			OptimizedFile = 1 << 4,
			TempIDOwner = 1 << 5,
			Localized = 1 << 7,
			PrecalcDataOnly = 1 << 8,
			SmallFile = 1 << 9
		};

		class InteriorCellOffsetDataStruct;

		TESFile() = delete;
		~TESFile() = delete;

		TESFile(const TESFile&) = delete;
		TESFile(TESFile&&) = delete;

		auto operator=(const TESFile&) -> TESFile& = delete;
		auto operator=(TESFile&&) -> TESFile& = delete;

		void dtor();

		GAME_HEAP_REDEFINE_NEW(TESFile);

		[[nodiscard]]
		auto IsMaster() const noexcept -> bool;
		[[nodiscard]]
		auto IsLocalized() const noexcept -> bool;
		[[nodiscard]]
		auto IsLight() const noexcept -> bool;

		[[nodiscard]]
		auto IsActive() const noexcept -> bool;
		[[nodiscard]]
		auto IsFormInFile(TESFormID a_formID) const noexcept -> bool;

		[[nodiscard]]
		auto OpenTES(char* a_path, const char* a_filename, NiFile::OpenMode a_accessMode, bool a_lock = false) -> bool;
		[[nodiscard]]
		auto OpenTES(NiFile::OpenMode a_accessMode, bool a_lock = false) -> bool;
		[[nodiscard]]
		auto CloseTES(bool a_forceClose = true) -> bool;

		[[nodiscard]]
		auto GetTESChunk() -> std::uint32_t;
		[[nodiscard]]
		auto GetChunkData(void* a_data, std::uint32_t a_maxSize = 0) -> bool;
		[[nodiscard]]
		auto NextChunk() -> bool;
		[[nodiscard]]
		auto NextGroup() -> bool;
		[[nodiscard]]
		auto NextForm(bool a_skipIgnored = true) -> bool;
		[[nodiscard]]
		auto FindForm(const TESForm* a_form) -> bool;
		void LoadForm(TESForm* a_form);
		void TESRewind(bool a_getForm = false);
		void TESRewindChunk();
		void ClearCurrentChunk();

		[[nodiscard]]
		auto HasThreadSafeParent() const noexcept -> bool;
		[[nodiscard]]
		auto HasThreadSafeParent(TESFile* a_parent) const noexcept -> bool;
		[[nodiscard]]
		auto GetThreadSafeParent() const noexcept -> TESFile*;
		void SetThreadSafeParent(TESFile* a_parent) noexcept;
		auto RemoveThreadSafeParent() noexcept -> bool;
		auto RemoveThreadSafeParent(TESFile* a_parent) noexcept -> bool;

		[[nodiscard]]
		auto HasThreadSafeFile() const -> bool;
		[[nodiscard]]
		auto HasThreadSafeFileForThread(REX::W32::THREAD_ID a_threadID) const -> bool;
		[[nodiscard]]
		auto GetThreadSafeFile(std::uint32_t a_bufferSize = DEFAULT_BUFFER_SIZE) -> TESFile*;
		[[nodiscard]]
		auto GetThreadSafeFileForThread(
			REX::W32::THREAD_ID a_threadID,
			std::uint32_t a_bufferSize = DEFAULT_BUFFER_SIZE) -> TESFile*;
		auto DeleteThreadSafeFile() -> bool;
		auto DeleteThreadSafeFileForThread(REX::W32::THREAD_ID a_threadID) -> bool;

		[[nodiscard]]
		auto GetBufferSize() const noexcept -> std::uint32_t;
		auto ChangeBufferSize(std::uint32_t a_size) -> bool;

		// members
		REX::Enum<TES_RETURN_CODE, std::int32_t> lastError;				// 0x000
		TESFile* threadSafeParent;										// 0x008
		BSTHashMap<REX::W32::THREAD_ID, TESFile*> threadSafeFileMap;	// 0x010
		BSTSmartPointer<BSFile::PageCache> pageCache;					// 0x040
		BSFile* lockedFile;												// 0x048
		BSFile* file;													// 0x050
		TESBitArrayFile* formUserDataBitArray;							// 0x058
		TESBitArrayFile* formVersionBitArray;							// 0x060
		TESBitArrayFile* formIDBitArray;								// 0x068
		REX::StaticString<REX::W32::MAX_PATH> filename;					// 0x070
		REX::StaticString<REX::W32::MAX_PATH> path;						// 0x174
		std::byte* buffer;												// 0x278
		std::uint32_t bufferAllocSize;									// 0x280
		std::uint32_t firstCellOffset;									// 0x284
		std::uint32_t currentCellOffset;								// 0x288
		TESObjectCELL* currentCell;										// 0x290
		std::uint32_t currentRefOffset;									// 0x298
		FORM currentForm;												// 0x29C
		REX::Enum<CHUNK_ID, std::int32_t> currentChunkID;				// 0x2B4
		std::uint32_t actualChunkSize;									// 0x2B8
		std::uint32_t fileSize;											// 0x2BC
		std::uint32_t fileOffset;										// 0x2C0
		std::uint32_t formOffset;										// 0x2C4
		std::uint32_t chunkOffset;										// 0x2C8
		FORM saveForm;													// 0x2CC
		std::uint32_t saveFormOffset;									// 0x2E4
		std::uint32_t saveChunkOffset;									// 0x2E8
		BSSimpleList<FORM_GROUP*> groups;								// 0x2F0
		bool hasGroups;													// 0x300
		BSSystemFile::Info fileInfo;									// 0x308
		FILE_HEADER fileHeaderInfo;										// 0x328
		REX::EnumSet<Flags, std::uint32_t> flags;						// 0x334
		BSSimpleList<char*> masters;									// 0x338
		BSSimpleList<std::uint64_t*> mastersDataList;					// 0x348
		std::uint32_t masterCount;										// 0x358
		SimpleArray<TESFile*> masterPtrs;								// 0x360
		REX::W32::FILETIME deletedFormTime;								// 0x368
		std::uint8_t compileIndex;										// 0x370
		std::uint16_t smallFileCompileIndex;							// 0x372
		BSString createdBy;												// 0x378
		BSString summary;												// 0x388
		std::byte* decompressedFormBuffer;								// 0x398
		std::uint32_t decompressedFormBufferSize;						// 0x3A0
		std::byte* reservedDecompressionBuffer;							// 0x3A8
		std::uint32_t reservedDecompressionBufferSize;					// 0x3B0
		BSTArray<InteriorCellOffsetDataStruct>* interiorCellOffsetData; // 0x3B8
	};

	static_assert(sizeof(TESFile) == 0x3C0);
}
