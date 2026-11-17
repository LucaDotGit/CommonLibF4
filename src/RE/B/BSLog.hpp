#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSSystemFile.hpp"

namespace RE
{
	class BSLog
	{
	public:
		// members
		BSFixedString logName;		   // 0x00
		BSFixedString logPath;		   // 0x08
		bool addTimestamps;			   // 0x10
		std::uint32_t logsToKeep;	   // 0x14
		mutable BSSpinLock bufferLock; // 0x18
		std::byte* buffer;			   // 0x20
		std::uint32_t bufferSize;	   // 0x28
		std::byte* writePos;		   // 0x30
		std::byte* readPos;			   // 0x38
		bool folderExists;			   // 0x40
		bool fileOpen;				   // 0x41
		BSSystemFile log;
	};

	static_assert(sizeof(BSLog) == 0x58);
}
