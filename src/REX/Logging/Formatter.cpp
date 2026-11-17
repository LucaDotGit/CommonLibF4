#include "REX/Logging/Formatter.hpp"

#include "REX/DateTime.hpp"
#include "REX/Formatting.hpp"
#include "REX/Logging/Context.hpp"
#include "REX/Path.hpp"
#include "REX/SourceLocation.hpp"

namespace REX::Logging
{
	void Formatter::Format(const REX::Logging::Context& a_context, std::pmr::string& a_buffer) const
	{
		const auto doFormat = [&a_context, &a_buffer]<class Clock, class Duration>(
								  std::chrono::time_point<Clock, Duration> a_timePoint) -> void {
			REX::FormatTo(
				std::back_inserter(a_buffer),
				"[{:%F %T}] [Thread: {:0>10}] [{}] [{}] [{}@{}#{:0>5}]\n\t{}\n"sv,
				a_timePoint,
				a_context.GetThreadId(),
				REX::Logging::GetShortNameForLevel(a_context.GetLevel()),
				a_context.GetName(),
				REX::GetFileNameWithoutExtension(a_context.GetSourceLocation().GetFilePath()),
				a_context.GetSourceLocation().GetFunctionName(),
				a_context.GetSourceLocation().GetLineNumber(),
				a_context.GetRawMessage());
		};

		const auto currentTimeZone = REX::DateTime::GetCurrentTimeZone();
		if (!currentTimeZone.has_value()) [[unlikely]] {
			doFormat(a_context.GetTimePoint());
			return;
		}

		const auto localTimePoint = (*currentTimeZone)->to_local(a_context.GetTimePoint());
		doFormat(localTimePoint);
	}
}
