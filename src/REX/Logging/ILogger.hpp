#pragma once

#include "REX/Formatting.hpp"
#include "REX/Logging/Level.hpp"
#include "REX/SourceLocation.hpp"

namespace REX::Logging
{
	class ISink;
	class Context;

	class ILogger : public std::enable_shared_from_this<ILogger>
	{
	public:
		ILogger() noexcept = default;
		virtual ~ILogger() noexcept = default;

		ILogger(const ILogger&) = delete;
		ILogger(ILogger&&) = delete;

		auto operator=(const ILogger&) -> ILogger& = delete;
		auto operator=(ILogger&&) -> ILogger& = delete;

		[[nodiscard]]
		virtual auto GetName() const noexcept -> std::string_view = 0;

		[[nodiscard]]
		virtual auto GetMinLevel() const noexcept -> REX::Logging::Level = 0;

		virtual void SetMinLevel(REX::Logging::Level a_minLevel) noexcept = 0;

		[[nodiscard]]
		virtual auto GetFlushLevel() const noexcept -> REX::Logging::Level = 0;

		virtual void SetFlushLevel(REX::Logging::Level a_flushLevel) noexcept = 0;

		virtual void AddSink(REX::NotNull<std::shared_ptr<REX::Logging::ISink>> a_sink) = 0;

		virtual void AddSinkRange(std::span<const REX::NotNull<std::shared_ptr<REX::Logging::ISink>>> a_sinks) = 0;

		virtual void LogContext(const REX::Logging::Context& a_context) = 0;

		virtual void LogMessage(
			REX::Logging::Level a_level,
			std::string_view a_message,
			REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) = 0;

		virtual void LogMessage(
			REX::Logging::Level a_level,
			std::wstring_view a_message,
			REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) = 0;

		virtual void LogFormat(
			REX::Logging::Level a_level,
			std::string_view a_format,
			REX::FormatArgs a_args,
			REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) = 0;

		virtual void LogFormat(
			REX::Logging::Level a_level,
			std::wstring_view a_format,
			REX::WFormatArgs a_args,
			REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) = 0;

		// NOLINTBEGIN(cppcoreguidelines-missing-std-forward)

		template <class... Args>
		void Log(Level a_level, REX::FormatStringLocation<Args...> a_formatLocation, Args&&... a_args)
		{
			LogFormat(
				a_level,
				std::basic_string_view(a_formatLocation.format().get()),
				REX::CreateFormatArgs(a_args...),
				a_formatLocation.location());
		}

		template <class... Args>
		void Log(Level a_level, REX::WFormatStringLocation<Args...> a_formatLocation, Args&&... a_args)
		{
			LogFormat(
				a_level,
				std::basic_string_view(a_formatLocation.format().get()),
				REX::CreateWFormatArgs(a_args...),
				a_formatLocation.location());
		}

		// NOLINTEND(cppcoreguidelines-missing-std-forward)

		template <class... Args>
		void LogTrace(REX::FormatStringLocation<Args...> a_formatLocation, Args&&... a_args)
		{
			Log(REX::Logging::Level::Trace, a_formatLocation, std::forward<Args>(a_args)...);
		}

		template <class... Args>
		void LogTrace(REX::WFormatStringLocation<Args...> a_formatLocation, Args&&... a_args)
		{
			Log(REX::Logging::Level::Trace, a_formatLocation, std::forward<Args>(a_args)...);
		}

		template <class... Args>
		void LogDebug(REX::FormatStringLocation<Args...> a_formatLocation, Args&&... a_args)
		{
			Log(REX::Logging::Level::Debug, a_formatLocation, std::forward<Args>(a_args)...);
		}

		template <class... Args>
		void LogDebug(REX::WFormatStringLocation<Args...> a_formatLocation, Args&&... a_args)
		{
			Log(REX::Logging::Level::Debug, a_formatLocation, std::forward<Args>(a_args)...);
		}

		template <class... Args>
		void LogInformation(REX::FormatStringLocation<Args...> a_formatLocation, Args&&... a_args)
		{
			Log(REX::Logging::Level::Information, a_formatLocation, std::forward<Args>(a_args)...);
		}

		template <class... Args>
		void LogInformation(REX::WFormatStringLocation<Args...> a_formatLocation, Args&&... a_args)
		{
			Log(REX::Logging::Level::Information, a_formatLocation, std::forward<Args>(a_args)...);
		}

		template <class... Args>
		void LogWarning(REX::FormatStringLocation<Args...> a_formatLocation, Args&&... a_args)
		{
			Log(REX::Logging::Level::Warning, a_formatLocation, std::forward<Args>(a_args)...);
		}

		template <class... Args>
		void LogWarning(REX::WFormatStringLocation<Args...> a_formatLocation, Args&&... a_args)
		{
			Log(REX::Logging::Level::Warning, a_formatLocation, std::forward<Args>(a_args)...);
		}

		template <class... Args>
		void LogError(REX::FormatStringLocation<Args...> a_formatLocation, Args&&... a_args)
		{
			Log(REX::Logging::Level::Error, a_formatLocation, std::forward<Args>(a_args)...);
		}

		template <class... Args>
		void LogError(REX::WFormatStringLocation<Args...> a_formatLocation, Args&&... a_args)
		{
			Log(REX::Logging::Level::Error, a_formatLocation, std::forward<Args>(a_args)...);
		}

		template <class... Args>
		void LogCritical(REX::FormatStringLocation<Args...> a_formatLocation, Args&&... a_args)
		{
			Log(REX::Logging::Level::Critical, a_formatLocation, std::forward<Args>(a_args)...);
		}

		template <class... Args>
		void LogCritical(REX::WFormatStringLocation<Args...> a_formatLocation, Args&&... a_args)
		{
			Log(REX::Logging::Level::Critical, a_formatLocation, std::forward<Args>(a_args)...);
		}
	};
}
