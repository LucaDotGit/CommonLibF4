#include "RE/B/BSScript_ErrorLogger.hpp"

#include "RE/B/BSScript_LogEvent.hpp"
#include "RE/B/BSScript_LogSeverity.hpp"
#include "RE/B/BSSpinLock.hpp"

namespace RE::BSScript
{
	void ErrorLogger::PostCachedError(const ICachedErrorMessage& a_errorMessage, LogSeverity a_severity)
	{
		{
			const auto errorLock = BSAutoSpinLock(dataLock);

			const auto&& [errorCounterIt, _] = threadErrors.try_emplace(REX::W32::GetCurrentThreadId());
			auto& errorCounter = errorCounterIt->second;

			switch (a_severity) {
				case LogSeverity::Warning: {
					errorCounter.warningCount++;
					break;
				}
				case LogSeverity::Error: {
					errorCounter.errorCount++;
					break;
				}
				case LogSeverity::Fatal: {
					errorCounter.fatalCount++;
					break;
				}
				default: {
					break;
				}
			}
		}

		PostErrorImpl(a_errorMessage, a_severity);

		const auto logEvent =
			LogEvent{.errorMessage = std::addressof(a_errorMessage), .severity = a_severity, .logName = logName};

		Notify(logEvent);
	}
}
