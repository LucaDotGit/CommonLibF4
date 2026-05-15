#include "REX/Log.hpp"

#include "REX/Convert.hpp"
#include "REX/Message.hpp"
#include "REX/Path.hpp"

#include <spdlog/logger.h>
#include <spdlog/pattern_formatter.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/msvc_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>

namespace REX::Impl
{
	static constexpr auto LOG_LEVEL_NAMES = std::array{
		"Trace"sv,
		"Debug"sv,
		"Information"sv,
		"Warning"sv,
		"Error"sv,
		"Critical"sv,
		"Off"sv
	};

	static constexpr auto UNKOWN_LOG_LEVEL_NAME = "Unknown"sv;

	static_assert(LOG_LEVEL_NAMES.size() == static_cast<std::size_t>(LogLevel::kTotal));

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

		void format(const spdlog::details::log_msg& a_msg, [[maybe_unused]] const std::tm& a_time, spdlog::memory_buf_t& a_dest) override
		{
			constexpr auto BUFFER_SIZE = REX::buffer_traits<std::uint16_t>::buffer_size::value;

			const auto formatData = REX::FixedFormat<BUFFER_SIZE>("{:05d}"sv, a_msg.thread_id);
			a_dest.append(formatData.buffer.data(), formatData.buffer.data() + formatData.size);
		}

		auto clone() const
			-> std::unique_ptr<spdlog::custom_flag_formatter> override
		{
			return std::make_unique<ThreadIdFlagFormatter>();
		}
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

		void format(const spdlog::details::log_msg& a_msg, [[maybe_unused]] const std::tm& a_time, spdlog::memory_buf_t& a_dest) override
		{
			const auto logLevel = static_cast<std::size_t>(a_msg.level);
			const auto& logLevelName = (logLevel < LOG_LEVEL_NAMES.size()) ? LOG_LEVEL_NAMES[logLevel] : UNKOWN_LOG_LEVEL_NAME;
			a_dest.append(logLevelName.data(), logLevelName.data() + logLevelName.size());
		}

		auto clone() const
			-> std::unique_ptr<spdlog::custom_flag_formatter> override
		{
			return std::make_unique<LogLevelFlagFormatter>();
		}
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

		void format(const spdlog::details::log_msg& a_msg, [[maybe_unused]] const std::tm& a_time, spdlog::memory_buf_t& a_dest) override
		{
			const auto fileName = REX::GetFileNameWithoutExtension(std::string_view(a_msg.source.filename));
			a_dest.append(fileName.data(), fileName.data() + fileName.size());
		}

		auto clone() const
			-> std::unique_ptr<spdlog::custom_flag_formatter> override
		{
			return std::make_unique<StemFileNameFlagFormatter>();
		}
	};
}

namespace REX
{
	static_assert(std::to_underlying(LogLevel::kTrace) == std::to_underlying(spdlog::level::trace));
	static_assert(std::to_underlying(LogLevel::kDebug) == std::to_underlying(spdlog::level::debug));
	static_assert(std::to_underlying(LogLevel::kInformation) == std::to_underlying(spdlog::level::info));
	static_assert(std::to_underlying(LogLevel::kWarning) == std::to_underlying(spdlog::level::warn));
	static_assert(std::to_underlying(LogLevel::kError) == std::to_underlying(spdlog::level::err));
	static_assert(std::to_underlying(LogLevel::kCritical) == std::to_underlying(spdlog::level::critical));
	static_assert(std::to_underlying(LogLevel::kNone) == std::to_underlying(spdlog::level::off));

	auto CreateLogger(LogInitInfo a_info)
		-> REX::NotNull<std::shared_ptr<spdlog::logger>>
	{
		constexpr auto REPLACE_EXISTING_FILES = true;
		constexpr auto MAX_SIZE_VALUE = std::numeric_limits<std::size_t>::max();

		const auto logFileName = REX::Format("{}.log"sv, a_info.logFileName);
		const auto logFilePath = a_info.logDirectoryPath / logFileName;

		const auto logFileCount = a_info.logFileCount;
		const auto logFileSize = a_info.logFileSize;

		auto mainLogSink =
			(logFileCount == MAX_SIZE_VALUE && logFileSize == MAX_SIZE_VALUE) ?
				static_cast<spdlog::sink_ptr>(
					std::make_shared<spdlog::sinks::basic_file_sink_mt>(
						logFilePath.generic_string(), REPLACE_EXISTING_FILES)) :
				static_cast<spdlog::sink_ptr>(
					std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
						logFilePath.generic_string(), logFileSize, logFileCount, REPLACE_EXISTING_FILES));

		auto windowsSink =
			static_cast<spdlog::sink_ptr>(
				std::make_shared<spdlog::sinks::msvc_sink_mt>());

		const auto logSinks = std::array{
			std::move(mainLogSink),
			std::move(windowsSink)
		};

		auto logFormatter = std::make_unique<spdlog::pattern_formatter>();
		logFormatter->add_flag<Impl::ThreadIdFlagFormatter>(LOG_THREAD_ID_FLAG);
		logFormatter->add_flag<Impl::LogLevelFlagFormatter>(LOG_LEVEL_FLAG);
		logFormatter->add_flag<Impl::StemFileNameFlagFormatter>(LOG_STEM_FILE_NAME_FLAG);
		logFormatter->set_pattern(std::move(a_info.logFormat));

		auto logger = std::make_shared<spdlog::logger>(a_info.logName, logSinks.begin(), logSinks.end());
		logger->set_level(static_cast<spdlog::level::level_enum>(a_info.logLevel.get()));
		logger->flush_on(static_cast<spdlog::level::level_enum>(a_info.logLevel.get()));
		logger->set_formatter(std::move(logFormatter));

		logger->set_error_handler([](const std::string& a_message) -> void {
			REX::PrintLine(stderr, "{}"sv, a_message);
		});

		return logger;
	}

	auto GetDefaultLogger()
		-> std::shared_ptr<spdlog::logger>
	{
		return spdlog::default_logger();
	}

	void SetDefaultLogger(
		REX::NotNull<std::shared_ptr<spdlog::logger>> a_logger)
	{
		spdlog::set_default_logger(*std::move(a_logger));
	}

	auto InitDefaultLogger(LogInitInfo a_info)
		-> REX::NotNull<std::shared_ptr<spdlog::logger>>
	{
		auto logger = CreateLogger(std::move(a_info));
		spdlog::set_default_logger(*logger);
		return logger;
	}

	void Log(LogLevel a_level, REX::SourceLocation a_location, std::string_view a_format) noexcept
	{
		const auto location = spdlog::source_loc(
			a_location.GetFilePath().data(),
			static_cast<std::int32_t>(a_location.GetLineNumber()),
			a_location.GetFunctionName().data());

		GetDefaultLogger()->log(location, static_cast<spdlog::level::level_enum>(a_level), a_format);
	}

	void Log(LogLevel a_level, REX::SourceLocation a_location, std::wstring_view a_format) noexcept
	{
		const auto location = spdlog::source_loc(
			a_location.GetFilePath().data(),
			static_cast<std::int32_t>(a_location.GetLineNumber()),
			a_location.GetFunctionName().data());

		const auto u8Format = REX::Utf16ToUtf8(a_format);
		const auto finalFormat = u8Format ? std::string_view(*u8Format) : "<Invalid UTF-16 format string>"sv;

		GetDefaultLogger()->log(location, static_cast<spdlog::level::level_enum>(a_level), finalFormat);
	}
}
