#pragma once

#include "RE/B/BSBTreeFile.hpp"
#include "RE/B/BSCriticalSection.hpp"
#include "RE/B/BSEventFlag.hpp"
#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSStringT.hpp"
#include "RE/B/BSSystemFileAsyncFunctor.hpp"
#include "RE/B/BSSystemFileStreamer.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/N/NiFile.hpp"

namespace RE
{
	class BSSystemFile;

	class __declspec(novtable) BSFile
		: public NiFile // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSFile };
		inline static constexpr auto VTABLE{ VTABLE::BSFile };

		class __declspec(novtable) PageCache
			: public BSIntrusiveRefCounted // 00
		{
		public:
			class _declspec(novtable) PhysReadType
				: public BSSystemFileAsyncFunctor // 00
			{
			public:
				inline static constexpr auto RTTI{ RTTI::BSFile__PageCache__PhysReadType };
				inline static constexpr auto VTABLE{ VTABLE::BSFile__PageCache__PhysReadType };

				~PhysReadType() override; // 00

				// members
				bool transferred; // 30
			};
			static_assert(sizeof(PhysReadType) == 0x38);

			class ReadState
			{
			public:
				// members
				std::size_t totalBytes;		// 00
				std::size_t filePage;		// 08
				volatile std::uint32_t tag; // 10
				std::uint32_t tagValue;		// 14
			};
			static_assert(sizeof(ReadState) == 0x18);

			// members
			PhysReadType physRead;			  // 08
			BSCriticalSection prot;			  // 40
			BSEventFlag readFinishedFlag;	  // 68
			std::uint32_t pageCount;		  // 70
			std::byte* pageRoot;			  // 78
			std::byte* memoryRoot;			  // 80
			BSBTreeFile::PageCache<16> cache; // 88
			ReadState* readStates;			  // C8
		};
		static_assert(sizeof(PageCache) == 0xD0);

		~BSFile() override; // 00

		// override (NiFile)
		std::size_t DoRead(void* a_buffer, std::size_t a_numBytes) override;			   // 05
		std::size_t DoWrite(const void* a_buffer, std::size_t a_numBytes) override;		   // 06
		void Seek(std::ptrdiff_t a_numBytes, std::size_t a_trueFilePosition = 0) override; // 07
		std::size_t GetFileSize() const override;										   // 08

		// add
		virtual bool Open();																		// 09
		virtual bool OpenByFilePointer(BSSystemFile* a_file);										// 0A
		virtual std::size_t GetSize() const;														// 0B
		virtual std::size_t ReadString(BSString& a_outValue, std::size_t a_maxSize);				// 0C
		virtual std::size_t ReadString(BSStringW& a_outValue, std::size_t a_maxSize);				// 0D
		virtual std::size_t GetLine(char* a_buffer, std::size_t a_bufferSize, wchar_t a_separator); // 0E
		virtual std::size_t WriteString(const BSString& a_value, bool a_binary);					// 0F
		virtual std::size_t WriteString(const BSStringW& a_value, bool a_binary);					// 10
		virtual bool Exist() const;																	// 11

		// members
		bool useAuxBuffer;							   // 050
		std::byte* auxBuffer;						   // 058
		std::int32_t auxTrueFilePos;				   // 060
		std::uint32_t auxBufferMinIndex;			   // 064
		std::uint32_t auxBufferMaxIndex;			   // 068
		std::array<char, REX::W32::MAX_PATH> fileName; // 06C
		std::size_t result;							   // 170
		std::size_t ioSize;							   // 178
		std::size_t trueFilePos;					   // 180
		std::size_t fileSize;						   // 188
		bool virtualAlloc;							   // 190
		BSTSmartPointer<PageCache> pageCache;		   // 198
		BSSystemFileStreamer::ID pathID;			   // 1A0
		std::uint32_t streamerPriority;				   // 1A4
		std::int8_t basePageOffset;					   // 1A8
		bool readThroughStreamer;					   // 1A9
	};
	static_assert(sizeof(BSFile) == 0x1B0);
}
