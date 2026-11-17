#pragma once

#include "RE/B/BSResource_Stream.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE::BSResource::Archive2
{
	class DataReader
	{
	public:
		class DataLoader
		{
		public:
			// members
			MemoryManager::AutoScrapBuffer buffer; // 0x00
			BSTSmartPointer<Stream> stream;		   // 0x08
			std::uint64_t initialPosition;		   // 0x10
			std::uint64_t position;				   // 0x18
			std::uint64_t ioBufferPos;			   // 0x20
			std::uint64_t ioBufferEnd;			   // 0x28
		};

		static_assert(sizeof(DataLoader) == 0x30);

		class StringLoader : public DataLoader // 0x00
		{
		public:
			REX::StaticString<REX::W32::MAX_PATH> currentString; // 0x030
			std::uint32_t totalStrings;							 // 0x134
			std::uint32_t nextStringIndex;						 // 0x138
			std::uint16_t currentStringLength;					 // 0x13C
		};

		static_assert(sizeof(StringLoader) == 0x140);

		// members
		BSTSmartPointer<Stream> stream; // 0x00
		DataLoader* dataLoader;			// 0x08
		StringLoader* stringLoader;		// 0x10
		std::uint32_t totalFiles;		// 0x18
	};

	static_assert(sizeof(DataReader) == 0x20);
}
