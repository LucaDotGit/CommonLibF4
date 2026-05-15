#pragma once

#include "REX/Enum.hpp"
#include "REX/Format.hpp"
#include "REX/NotNull.hpp"
#include "REX/SourceLocation.hpp"

namespace spdlog
{
	class logger;
}

namespace REX
{
	inline constexpr auto LOG_THREAD_ID_FLAG = 't';
	inline constexpr auto LOG_LEVEL_FLAG = 'l';
	inline constexpr auto LOG_STEM_FILE_NAME_FLAG = 'G';

	inline constexpr auto DEFAULT_LOGGER_NAME = "Default Logger"sv;
	inline constexpr auto DEFAULT_LOGGER_FORMAT = "[%Y-%m-%d %H:%M:%S.%e] [Thread: %t] [%l] [%G] %v"sv;

	enum class LogLevel : std::int32_t
	{
		kTrace = 0,
		kDebug = 1,
		kInformation = 2,
		kWarning = 3,
		kError = 4,
		kCritical = 5,
		kNone = 6,

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

	[[nodiscard]] auto CreateLogger(LogInitInfo a_info)
		-> REX::NotNull<std::shared_ptr<spdlog::logger>>;
	[[nodiscard]] auto GetDefaultLogger()
		-> std::shared_ptr<spdlog::logger>;
	void SetDefaultLogger(
		REX::NotNull<std::shared_ptr<spdlog::logger>> a_logger);
	auto InitDefaultLogger(LogInitInfo a_info)
		-> REX::NotNull<std::shared_ptr<spdlog::logger>>;

	void Log(LogLevel a_level, REX::SourceLocation a_location, std::string_view a_format) noexcept;
	void Log(LogLevel a_level, REX::SourceLocation a_location, std::wstring_view a_format) noexcept;

	template <class... Args>
	void Log(LogLevel a_level, REX::FormatStringLocation<Args...> a_formatLocation, Args&&... a_args) noexcept
		requires((REX::formattable<Args, char> && ...))
	{
		const auto formatData = REX::FixedFormat(a_formatLocation.format(), std::forward<Args>(a_args)...);
		Log(a_level, a_formatLocation.location(), std::string_view{ formatData.buffer.data(), formatData.size });
	}

	template <class... Args>
	void Log(LogLevel a_level, REX::WFormatStringLocation<Args...> a_formatLocation, Args&&... a_args) noexcept
		requires((REX::formattable<Args, wchar_t> && ...))
	{
		const auto formatData = REX::FixedFormat(a_formatLocation.format(), std::forward<Args>(a_args)...);
		Log(a_level, a_formatLocation.location(), std::wstring_view{ formatData.buffer.data(), formatData.size });
	}

	inline void LogTrace(std::string_view a_format, REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept
	{
		Log(LogLevel::kTrace, a_location, a_format);
	}

	inline void LogTrace(std::wstring_view a_format, REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept
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

	inline void LogDebug(std::string_view a_format, REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept
	{
		Log(LogLevel::kDebug, a_location, a_format);
	}

	inline void LogDebug(std::wstring_view a_format, REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept
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

	inline void LogInformation(std::string_view a_format, REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept
	{
		Log(LogLevel::kInformation, a_location, a_format);
	}

	inline void LogInformation(std::wstring_view a_format, REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept
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

	inline void LogWarning(std::string_view a_format, REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept
	{
		Log(LogLevel::kWarning, a_location, a_format);
	}

	inline void LogWarning(std::wstring_view a_format, REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept
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

	inline void LogError(std::string_view a_format, REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept
	{
		Log(LogLevel::kError, a_location, a_format);
	}

	inline void LogError(std::wstring_view a_format, REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept
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

	inline void LogCritical(std::string_view a_format, REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept
	{
		Log(LogLevel::kCritical, a_location, a_format);
	}

	inline void LogCritical(std::wstring_view a_format, REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept
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
