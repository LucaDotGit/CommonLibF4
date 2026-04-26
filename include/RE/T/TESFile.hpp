#pragma once

#include "RE/B/BSFile.hpp"
#include "RE/B/BSSimpleList.hpp"
#include "RE/B/BSStringT.hpp"
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
		// Resolves into `GetINISetting("fMasterFilePreLoadMB:General"sv)->GetFloat() * 1024.0_f32 * 1024.0_f32`.
		inline static constexpr auto RESOLVABLE_MASTER_BUFFER_SIZE = static_cast<std::uint32_t>(-3);
		// Resolves into `0x10000`.
		inline static constexpr auto RESOLVABLE_DEFAULT_BUFFER_SIZE = static_cast<std::uint32_t>(-2);
		// Resolves into no buffer allocation.
		inline static constexpr auto RESOLVABLE_INVALID_BUFFER_SIZE = static_cast<std::uint32_t>(-1);

		inline static constexpr auto DEFAULT_BUFFER_SIZE = static_cast<std::uint32_t>(0x10000ui32);

		enum class Flags : std::uint32_t
		{
			kNone = 0,
			kMaster = 1 << 0,
			kAltered = 1 << 1,
			kChecked = 1 << 2,
			kActive = 1 << 3,
			kOptimizedFile = 1 << 4,
			kTempIDOwner = 1 << 5,
			kLocalized = 1 << 7,
			kPrecalcDataOnly = 1 << 8,
			kSmallFile = 1 << 9
		};

		class InteriorCellOffsetDataStruct;

		~TESFile() = delete;

		void dtor();

		GAME_HEAP_REDEFINE_NEW(TESFile);

		[[nodiscard]] bool IsMaster() const noexcept;
		[[nodiscard]] bool IsLocalized() const noexcept;
		[[nodiscard]] bool IsLight() const noexcept;

		[[nodiscard]] bool IsActive() const noexcept;
		[[nodiscard]] bool IsFormInFile(TESFormID a_formID) const noexcept;

		[[nodiscard]] bool OpenTES(char* a_path, const char* a_filename, NiFile::OpenMode a_accessMode, bool a_lock = false);
		[[nodiscard]] bool OpenTES(NiFile::OpenMode a_accessMode, bool a_lock = false);
		[[nodiscard]] bool CloseTES(bool a_forceClose = true);

		[[nodiscard]] std::uint32_t GetTESChunk();
		[[nodiscard]] bool GetChunkData(void* a_data, std::uint32_t a_maxSize = 0);
		[[nodiscard]] bool NextChunk();
		[[nodiscard]] bool NextGroup();
		[[nodiscard]] bool NextForm(bool a_skipIgnored = true);
		[[nodiscard]] bool FindForm(const TESForm* a_form);
		void LoadForm(TESForm* a_form);
		void TESRewind(bool a_getForm = false);
		void TESRewindChunk();
		void ClearCurrentChunk();

		[[nodiscard]] bool HasThreadSafeParent() const noexcept;
		[[nodiscard]] bool HasThreadSafeParent(TESFile* a_parent) const noexcept;
		[[nodiscard]] TESFile* GetThreadSafeParent() const noexcept;
		void SetThreadSafeParent(TESFile* a_parent) noexcept;
		bool RemoveThreadSafeParent() noexcept;
		bool RemoveThreadSafeParent(TESFile* a_parent) noexcept;

		[[nodiscard]] bool HasThreadSafeFile() const;
		[[nodiscard]] bool HasThreadSafeFileForThread(REX::W32::THREAD_ID a_threadID) const;
		[[nodiscard]] TESFile* GetThreadSafeFile(std::uint32_t a_fileBufferSize = DEFAULT_BUFFER_SIZE);
		[[nodiscard]] TESFile* GetThreadSafeFileForThread(REX::W32::THREAD_ID a_threadID, std::uint32_t a_fileBufferSize = DEFAULT_BUFFER_SIZE);
		bool DeleteThreadSafeFile();
		bool DeleteThreadSafeFileForThread(REX::W32::THREAD_ID a_threadID);

		[[nodiscard]] std::uint32_t GetBufferSize() const noexcept;
		bool ChangeBufferSize(std::uint32_t a_size);

		// members
		REX::Enum<TES_RETURN_CODE, std::int32_t> lastError;				// 000
		TESFile* threadSafeParent;										// 008
		BSTHashMap<REX::W32::THREAD_ID, TESFile*> threadSafeFileMap;	// 010
		BSTSmartPointer<BSFile::PageCache> pageCache;					// 040
		BSFile* lockedFile;												// 048
		BSFile* file;													// 050
		TESBitArrayFile* formUserDataBitArray;							// 058
		TESBitArrayFile* formVersionBitArray;							// 060
		TESBitArrayFile* formIDBitArray;								// 068
		std::array<char, REX::W32::MAX_PATH> filename;					// 070
		std::array<char, REX::W32::MAX_PATH> path;						// 174
		std::byte* buffer;												// 278
		std::uint32_t bufferAllocSize;									// 280
		std::uint32_t firstCellOffset;									// 284
		std::uint32_t currentCellOffset;								// 288
		TESObjectCELL* currentCell;										// 290
		std::uint32_t currentRefOffset;									// 298
		FORM currentForm;												// 29C
		REX::Enum<CHUNK_ID, std::int32_t> currentChunkID;				// 2B4
		std::uint32_t actualChunkSize;									// 2B8
		std::uint32_t fileSize;											// 2BC
		std::uint32_t fileOffset;										// 2C0
		std::uint32_t formOffset;										// 2C4
		std::uint32_t chunkOffset;										// 2C8
		FORM saveForm;													// 2CC
		std::uint32_t saveFormOffset;									// 2E4
		std::uint32_t saveChunkOffset;									// 2E8
		BSSimpleList<FORM_GROUP*> groups;								// 2F0
		bool hasGroups;													// 300
		BSSystemFile::Info fileInfo;									// 308
		FILE_HEADER fileHeaderInfo;										// 328
		REX::EnumSet<Flags, std::uint32_t> flags;						// 334
		BSSimpleList<char*> masters;									// 338
		BSSimpleList<std::uint64_t*> mastersDataList;					// 348
		std::uint32_t masterCount;										// 358
		SimpleArray<TESFile*> masterPtrs;								// 360
		REX::W32::FILETIME deletedFormTime;								// 368
		std::uint8_t compileIndex;										// 370
		std::uint16_t smallFileCompileIndex;							// 372
		BSString createdBy;												// 378
		BSString summary;												// 388
		std::byte* decompressedFormBuffer;								// 398
		std::uint32_t decompressedFormBufferSize;						// 3A0
		std::byte* reservedDecompressionBuffer;							// 3A8
		std::uint32_t reservedDecompressionBufferSize;					// 3B0
		BSTArray<InteriorCellOffsetDataStruct>* interiorCellOffsetData; // 3B8
	};
	static_assert(sizeof(TESFile) == 0x3C0);
}
