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
		BSFixedString logName;		   // 00
		BSFixedString logPath;		   // 08
		bool addTimestamps;			   // 10
		std::uint32_t logsToKeep;	   // 14
		mutable BSSpinLock bufferLock; // 18
		std::byte* buffer;			   // 20
		std::uint32_t bufferSize;	   // 28
		std::byte* writePos;		   // 30
		std::byte* readPos;			   // 38
		bool folderExists;			   // 40
		bool fileOpen;				   // 41
		BSSystemFile log;
	};
	static_assert(sizeof(BSLog) == 0x58);
}
