#pragma once

#include "RE/Bethesda/BSFixedString.hpp"
#include "RE/Bethesda/BSScript/ErrorLogger.hpp"
#include "RE/Bethesda/BSScript/ICachedErrorMessage.hpp"

namespace RE::BSScript
{
	struct LogEvent
	{
	public:
		const ICachedErrorMessage& errorMsg;  // 00
		const ErrorLogger::Severity severity; // 08
		std::uint32_t pad0C;				  // 0C
		BSFixedString ownerModule;			  // 10
	};
	static_assert(sizeof(LogEvent) == 0x18);
}
