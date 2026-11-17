#pragma once

#include "RE/B/BSBTreeFile.hpp"
#include "RE/B/BSCriticalSection.hpp"
#include "RE/B/BSEventFlag.hpp"
#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSString.hpp"
#include "RE/B/BSSystemFileAsyncFunctor.hpp"
#include "RE/B/BSSystemFileStreamer.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/N/NiFile.hpp"

namespace RE
{
	class BSSystemFile;

	class __declspec(novtable) BSFile : public NiFile // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSFile;
		inline static constexpr const auto& VTABLE = VTABLE::BSFile;

		class __declspec(novtable) PageCache : public BSIntrusiveRefCounted // 0x00
		{
		public:
			class _declspec(novtable) PhysReadType : public BSSystemFileAsyncFunctor // 0x00
			{
			public:
				inline static constexpr const auto& RTTI = RTTI::BSFile__PageCache__PhysReadType;
				inline static constexpr const auto& VTABLE = VTABLE::BSFile__PageCache__PhysReadType;

				~PhysReadType() override; // 0x00

				// members
				bool transferred; // 0x30
			};

			static_assert(sizeof(PhysReadType) == 0x38);

			class ReadState
			{
			public:
				// members
				std::size_t totalBytes;		// 0x00
				std::size_t filePage;		// 0x08
				volatile std::uint32_t tag; // 0x10
				std::uint32_t tagValue;		// 0x14
			};

			static_assert(sizeof(ReadState) == 0x18);

			// members
			PhysReadType physRead;			  // 0x08
			BSCriticalSection prot;			  // 0x40
			BSEventFlag readFinishedFlag;	  // 0x68
			std::uint32_t pageCount;		  // 0x70
			std::byte* pageRoot;			  // 0x78
			std::byte* memoryRoot;			  // 0x80
			BSBTreeFile::PageCache<16> cache; // 0x88
			ReadState* readStates;			  // 0xC8
		};

		static_assert(sizeof(PageCache) == 0xD0);

		~BSFile() override; // 0x00

		// override (NiFile)
		auto DoRead(void* a_buffer, std::size_t a_numBytes) -> std::size_t override;		// 0x05
		auto DoWrite(const void* a_buffer, std::size_t a_numBytes) -> std::size_t override; // 0x06
		void Seek(std::ptrdiff_t a_numBytes, std::size_t a_trueFilePosition = 0) override;	// 0x07
		auto GetFileSize() const -> std::size_t override;									// 0x08

		// add
		virtual auto Open() -> bool;																		// 0x09
		virtual auto OpenByFilePointer(BSSystemFile* a_file) -> bool;										// 0x0A
		virtual auto GetSize() const -> std::size_t;														// 0x0B
		virtual auto ReadString(BSString& a_outValue, std::size_t a_maxSize) -> std::size_t;				// 0x0C
		virtual auto ReadString(BSStringW& a_outValue, std::size_t a_maxSize) -> std::size_t;				// 0x0D
		virtual auto GetLine(char* a_buffer, std::size_t a_bufferSize, wchar_t a_separator) -> std::size_t; // 0x0E
		virtual auto WriteString(const BSString& a_value, bool a_binary) -> std::size_t;					// 0x0F
		virtual auto WriteString(const BSStringW& a_value, bool a_binary) -> std::size_t;					// 0x10
		virtual auto Exist() const -> bool;																	// 0x11

		// members
		bool useAuxBuffer;								// 0x050
		std::byte* auxBuffer;							// 0x058
		std::int32_t auxTrueFilePos;					// 0x060
		std::uint32_t auxBufferMinIndex;				// 0x064
		std::uint32_t auxBufferMaxIndex;				// 0x068
		REX::StaticString<REX::W32::MAX_PATH> fileName; // 0x06C
		std::size_t result;								// 0x170
		std::size_t ioSize;								// 0x178
		std::size_t trueFilePos;						// 0x180
		std::size_t fileSize;							// 0x188
		bool virtualAlloc;								// 0x190
		BSTSmartPointer<PageCache> pageCache;			// 0x198
		BSSystemFileStreamer::ID pathID;				// 0x1A0
		std::uint32_t streamerPriority;					// 0x1A4
		std::int8_t basePageOffset;						// 0x1A8
		bool readThroughStreamer;						// 0x1A9
	};

	static_assert(sizeof(BSFile) == 0x1B0);
}
