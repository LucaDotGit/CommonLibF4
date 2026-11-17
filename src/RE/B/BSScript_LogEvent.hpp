#pragma once

#include "RE/B/BSFixedString.hpp"

namespace RE::BSScript
{
	enum class LogSeverity : std::int32_t;

	class ICachedErrorMessage;

	class LogEvent
	{
	public:
		// members
		const ICachedErrorMessage* errorMessage;	   // 0x00
		REX::Enum<LogSeverity, std::int32_t> severity; // 0x08
		BSFixedString logName;						   // 0x10
	};

	static_assert(sizeof(LogEvent) == 0x18);
}
