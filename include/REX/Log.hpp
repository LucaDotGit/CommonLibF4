#pragma once

#include "REX/Contract.hpp"
#include "REX/Enum.hpp"
#include "REX/Format.hpp"
#include "REX/NotNull.hpp"

#include <spdlog/logger.h>
#include <spdlog/pattern_formatter.h>

namespace REX
{
	inline constexpr auto DEFAULT_LOGGER_NAME = "Default Logger"sv;
	inline constexpr auto DEFAULT_LOGGER_FORMAT = "[%Y-%m-%d %H:%M:%S.%e] [Thread: %t] [%l] [%G] %v"sv;

	enum class LogLevel : std::int32_t
	{
		kTrace = static_cast<std::underlying_type_t<LogLevel>>(spdlog::level::trace),
		kDebug = static_cast<std::underlying_type_t<LogLevel>>(spdlog::level::debug),
		kInformation = static_cast<std::underlying_type_t<LogLevel>>(spdlog::level::info),
		kWarning = static_cast<std::underlying_type_t<LogLevel>>(spdlog::level::warn),
		kError = static_cast<std::underlying_type_t<LogLevel>>(spdlog::level::err),
		kCritical = static_cast<std::underlying_type_t<LogLevel>>(spdlog::level::critical),
		kNone = static_cast<std::underlying_type_t<LogLevel>>(spdlog::level::off),

		kTotal
	};

	class LogInitInfo final
	{
	public:
		std::string logName;
		std::filesystem::path logDirectoryPath;
		std::string logFileName;
		std::string logFormat;
		REX::Enum<LogLevel> logLevel{
#if NDEBUG == 0
			LogLevel::kDebug
#else
			LogLevel::kInformation
#endif
		};
		std::size_t logFileCount{ std::numeric_limits<std::size_t>::max() };
		std::size_t logFileSize{ std::numeric_limits<std::size_t>::max() };
	};

	[[nodiscard]] auto GetDefaultLogger() -> std::shared_ptr<spdlog::logger>;
	[[nodiscard]] auto CreateLogger(LogInitInfo a_info) -> REX::NotNull<std::shared_ptr<spdlog::logger>>;
	auto InitLogger(LogInitInfo a_info) -> REX::NotNull<std::shared_ptr<spdlog::logger>>;

	void Log(LogLevel a_level, std::source_location a_location, std::string_view a_format) noexcept;
	void Log(LogLevel a_level, std::source_location a_location, std::wstring_view a_format) noexcept;

	template <class... Args>
	void Log(LogLevel a_level, REX::FormatStringLocation<Args...> a_formatLocation, Args&&... a_args) noexcept
		requires((REX::formattable<Args, char> && ...))
	{
		try {
			Log(a_level, a_formatLocation.location(), REX::Format(a_formatLocation.format(), std::forward<Args>(a_args)...));
		}
		catch ([[maybe_unused]] const std::bad_alloc& error) {
			REX::AllocationFail();
		}
	}

	template <class... Args>
	void Log(LogLevel a_level, REX::WFormatStringLocation<Args...> a_formatLocation, Args&&... a_args) noexcept
		requires((REX::formattable<Args, wchar_t> && ...))
	{
		try {
			Log(a_level, a_formatLocation.location(), REX::Format(a_formatLocation.format(), std::forward<Args>(a_args)...));
		}
		catch ([[maybe_unused]] const std::bad_alloc& error) {
			REX::AllocationFail();
		}
	}

	inline void LogTrace(std::string_view a_format, std::source_location a_location = std::source_location::current()) noexcept
	{
		Log(LogLevel::kTrace, a_location, a_format);
	}

	inline void LogTrace(std::wstring_view a_format, std::source_location a_location = std::source_location::current()) noexcept
	{
		Log(LogLevel::kTrace, a_location, a_format);
	}

	template <class... Args>
	void LogTrace(REX::FormatStringLocation<Args...> a_formatLocation, Args&&... a_args) noexcept
		requires((REX::formattable<Args, char> && ...))
	{
		Log(LogLevel::kTrace, a_formatLocation, std::forward<Args>(a_args)...);
	}

	template <class... Args>
	void LogTrace(REX::WFormatStringLocation<Args...> a_formatLocation, Args&&... a_args) noexcept
		requires((REX::formattable<Args, wchar_t> && ...))
	{
		Log(LogLevel::kTrace, a_formatLocation, std::forward<Args>(a_args)...);
	}

	inline void LogDebug(std::string_view a_format, std::source_location a_location = std::source_location::current()) noexcept
	{
		Log(LogLevel::kDebug, a_location, a_format);
	}

	inline void LogDebug(std::wstring_view a_format, std::source_location a_location = std::source_location::current()) noexcept
	{
		Log(LogLevel::kDebug, a_location, a_format);
	}

	template <class... Args>
	void LogDebug(REX::FormatStringLocation<Args...> a_formatLocation, Args&&... a_args) noexcept
		requires((REX::formattable<Args, char> && ...))
	{
		Log(LogLevel::kDebug, a_formatLocation, std::forward<Args>(a_args)...);
	}

	template <class... Args>
	void LogDebug(REX::WFormatStringLocation<Args...> a_formatLocation, Args&&... a_args) noexcept
		requires((REX::formattable<Args, wchar_t> && ...))
	{
		Log(LogLevel::kDebug, a_formatLocation, std::forward<Args>(a_args)...);
	}

	inline void LogInformation(std::string_view a_format, std::source_location a_location = std::source_location::current()) noexcept
	{
		Log(LogLevel::kInformation, a_location, a_format);
	}

	inline void LogInformation(std::wstring_view a_format, std::source_location a_location = std::source_location::current()) noexcept
	{
		Log(LogLevel::kInformation, a_location, a_format);
	}

	template <class... Args>
	void LogInformation(REX::FormatStringLocation<Args...> a_formatLocation, Args&&... a_args) noexcept
		requires((REX::formattable<Args, char> && ...))
	{
		Log(LogLevel::kInformation, a_formatLocation, std::forward<Args>(a_args)...);
	}

	template <class... Args>
	void LogInformation(REX::WFormatStringLocation<Args...> a_formatLocation, Args&&... a_args) noexcept
		requires((REX::formattable<Args, wchar_t> && ...))
	{
		Log(LogLevel::kInformation, a_formatLocation, std::forward<Args>(a_args)...);
	}

	inline void LogWarning(std::string_view a_format, std::source_location a_location = std::source_location::current()) noexcept
	{
		Log(LogLevel::kWarning, a_location, a_format);
	}

	inline void LogWarning(std::wstring_view a_format, std::source_location a_location = std::source_location::current()) noexcept
	{
		Log(LogLevel::kWarning, a_location, a_format);
	}

	template <class... Args>
	void LogWarning(REX::FormatStringLocation<Args...> a_formatLocation, Args&&... a_args) noexcept
		requires((REX::formattable<Args, char> && ...))
	{
		Log(LogLevel::kWarning, a_formatLocation, std::forward<Args>(a_args)...);
	}

	template <class... Args>
	void LogWarning(REX::WFormatStringLocation<Args...> a_formatLocation, Args&&... a_args) noexcept
		requires((REX::formattable<Args, wchar_t> && ...))
	{
		Log(LogLevel::kWarning, a_formatLocation, std::forward<Args>(a_args)...);
	}

	inline void LogError(std::string_view a_format, std::source_location a_location = std::source_location::current()) noexcept
	{
		Log(LogLevel::kError, a_location, a_format);
	}

	inline void LogError(std::wstring_view a_format, std::source_location a_location = std::source_location::current()) noexcept
	{
		Log(LogLevel::kError, a_location, a_format);
	}

	template <class... Args>
	void LogError(REX::FormatStringLocation<Args...> a_formatLocation, Args&&... a_args) noexcept
		requires((REX::formattable<Args, char> && ...))
	{
		Log(LogLevel::kError, a_formatLocation, std::forward<Args>(a_args)...);
	}

	template <class... Args>
	void LogError(REX::WFormatStringLocation<Args...> a_formatLocation, Args&&... a_args) noexcept
		requires((REX::formattable<Args, wchar_t> && ...))
	{
		Log(LogLevel::kError, a_formatLocation, std::forward<Args>(a_args)...);
	}

	inline void LogCritical(std::string_view a_format, std::source_location a_location = std::source_location::current()) noexcept
	{
		Log(LogLevel::kCritical, a_location, a_format);
	}

	inline void LogCritical(std::wstring_view a_format, std::source_location a_location = std::source_location::current()) noexcept
	{
		Log(LogLevel::kCritical, a_location, a_format);
	}

	template <class... Args>
	void LogCritical(REX::FormatStringLocation<Args...> a_formatLocation, Args&&... a_args) noexcept
		requires((REX::formattable<Args, char> && ...))
	{
		Log(LogLevel::kCritical, a_formatLocation, std::forward<Args>(a_args)...);
	}

	template <class... Args>
	void LogCritical(REX::WFormatStringLocation<Args...> a_formatLocation, Args&&... a_args) noexcept
		requires((REX::formattable<Args, wchar_t> && ...))
	{
		Log(LogLevel::kCritical, a_formatLocation, std::forward<Args>(a_args)...);
	}
}

namespace REX::Impl
{
	inline constexpr auto THREAD_ID_FLAG = 't';
	inline constexpr auto LOG_LEVEL_FLAG = 'l';
	inline constexpr auto STEM_FILE_NAME_FLAG = 'G';

	class ThreadIdFlagFormatter final
		: public spdlog::custom_flag_formatter
	{
	public:
		ThreadIdFlagFormatter() = default;
		~ThreadIdFlagFormatter() noexcept override = default;

		ThreadIdFlagFormatter(const ThreadIdFlagFormatter&) = delete;
		ThreadIdFlagFormatter(ThreadIdFlagFormatter&&) = delete;

		ThreadIdFlagFormatter& operator=(const ThreadIdFlagFormatter&) = delete;
		ThreadIdFlagFormatter& operator=(ThreadIdFlagFormatter&&) = delete;

		void format(const spdlog::details::log_msg& a_msg, const std::tm& a_time, spdlog::memory_buf_t& a_dest) override;
		auto clone() const -> std::unique_ptr<spdlog::custom_flag_formatter> override;
	};

	class LogLevelFlagFormatter final
		: public spdlog::custom_flag_formatter
	{
	public:
		LogLevelFlagFormatter() = default;
		~LogLevelFlagFormatter() noexcept override = default;

		LogLevelFlagFormatter(const LogLevelFlagFormatter&) = delete;
		LogLevelFlagFormatter(LogLevelFlagFormatter&&) = delete;

		LogLevelFlagFormatter& operator=(const LogLevelFlagFormatter&) = delete;
		LogLevelFlagFormatter& operator=(LogLevelFlagFormatter&&) = delete;

		void format(const spdlog::details::log_msg& a_msg, const std::tm& a_time, spdlog::memory_buf_t& a_dest) override;
		auto clone() const -> std::unique_ptr<spdlog::custom_flag_formatter> override;
	};

	class StemFileNameFlagFormatter final
		: public spdlog::custom_flag_formatter
	{
	public:
		StemFileNameFlagFormatter() = default;
		~StemFileNameFlagFormatter() noexcept override = default;

		StemFileNameFlagFormatter(const StemFileNameFlagFormatter&) = delete;
		StemFileNameFlagFormatter(StemFileNameFlagFormatter&&) = delete;

		StemFileNameFlagFormatter& operator=(const StemFileNameFlagFormatter&) = delete;
		StemFileNameFlagFormatter& operator=(StemFileNameFlagFormatter&&) = delete;

		void format(const spdlog::details::log_msg& a_msg, const std::tm& a_time, spdlog::memory_buf_t& a_dest) override;
		auto clone() const -> std::unique_ptr<spdlog::custom_flag_formatter> override;
	};
}
