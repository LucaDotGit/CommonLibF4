#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSScript_ErrorLogger.hpp"

namespace RE::BSScript
{
	class ICachedErrorMessage;

	class LogEvent
	{
	public:
		// members
		ICachedErrorMessage* errorMessage;						 // 00
		REX::Enum<ErrorLogger::Severity, std::int32_t> severity; // 08
		BSFixedString logName;									 // 10
	};
	static_assert(sizeof(LogEvent) == 0x18);
}
