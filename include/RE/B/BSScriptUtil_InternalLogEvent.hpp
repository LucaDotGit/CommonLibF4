#pragma once

#include "RE/B/BSScript_ErrorLogger.hpp"
#include "RE/B/BSTEvent.hpp"

namespace RE::BSScript::Impl
{
	class InternalLogEvent
	{
	public:
		std::string_view message;
		REX::Enum<ErrorLogger::Severity> severity;
		StackID stackID;
	};

	class InternalLogEventSource
		: public REX::Singleton<InternalLogEventSource>,
		  public BSTEventSource<InternalLogEvent>
	{
	public:
		InternalLogEventSource() = default;
		~InternalLogEventSource() noexcept = default;

		InternalLogEventSource(const InternalLogEventSource&) = delete;
		InternalLogEventSource(InternalLogEventSource&&) = delete;

		InternalLogEventSource& operator=(const InternalLogEventSource&) = delete;
		InternalLogEventSource& operator=(InternalLogEventSource&&) = delete;
	};
}
