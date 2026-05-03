#include "REX/Log.hpp"

#include "REX/Convert.hpp"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/msvc_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>

namespace REX
{
	auto GetDefaultLogger() -> std::shared_ptr<spdlog::logger>
	{
		return spdlog::default_logger();
	}

	auto CreateLogger(LogInitInfo a_info) -> REX::NotNull<std::shared_ptr<spdlog::logger>>
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
		logFormatter->add_flag<Impl::ThreadIdFlagFormatter>(Impl::THREAD_ID_FLAG);
		logFormatter->add_flag<Impl::LogLevelFlagFormatter>(Impl::LOG_LEVEL_FLAG);
		logFormatter->add_flag<Impl::StemFileNameFlagFormatter>(Impl::STEM_FILE_NAME_FLAG);
		logFormatter->set_pattern(std::move(a_info.logFormat));

		auto logger = std::make_shared<spdlog::logger>(a_info.logName, logSinks.begin(), logSinks.end());
		logger->set_level(static_cast<spdlog::level::level_enum>(a_info.logLevel.get()));
		logger->flush_on(static_cast<spdlog::level::level_enum>(a_info.logLevel.get()));
		logger->set_formatter(std::move(logFormatter));

		return logger;
	}

	auto InitLogger(LogInitInfo a_info) -> REX::NotNull<std::shared_ptr<spdlog::logger>>
	{
		auto logger = CreateLogger(std::move(a_info));
		spdlog::set_default_logger(*logger);
		return logger;
	}

	void Log(LogLevel a_level, std::source_location a_location, std::string_view a_format) noexcept
	{
		const auto location = spdlog::source_loc(
			a_location.file_name(),
			static_cast<std::int32_t>(a_location.line()),
			a_location.function_name());

		try {
			spdlog::log(location, static_cast<spdlog::level::level_enum>(a_level), a_format);
		}
		catch ([[maybe_unused]] const std::bad_alloc& error) {
			REX::AllocationFail("Failed to allocate memory for log message."sv);
		}
	}

	void Log(LogLevel a_level, std::source_location a_location, std::wstring_view a_format) noexcept
	{
		const auto location = spdlog::source_loc(
			a_location.file_name(),
			static_cast<std::int32_t>(a_location.line()),
			a_location.function_name());

		const auto u8Format = REX::Utf16ToUtf8(a_format);
		if (!u8Format) [[unlikely]] {
			REX::QuickFail("Failed to convert log message from UTF-16 to UTF-8."sv);
		}

		try {
			spdlog::log(location, static_cast<spdlog::level::level_enum>(a_level), *u8Format);
		}
		catch ([[maybe_unused]] const std::bad_alloc& error) {
			REX::AllocationFail("Failed to allocate memory for log message."sv);
		}
	}
}

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

	void ThreadIdFlagFormatter::format(const spdlog::details::log_msg& a_msg, [[maybe_unused]] const std::tm& a_time, spdlog::memory_buf_t& a_dest)
	{
		const auto threadId = a_msg.thread_id;
		const auto threadIdString = REX::Format("{:05d}"sv, threadId);
		a_dest.append(threadIdString.data(), threadIdString.data() + threadIdString.size());
	}

	auto ThreadIdFlagFormatter::clone() const -> std::unique_ptr<spdlog::custom_flag_formatter>
	{
		return std::make_unique<ThreadIdFlagFormatter>();
	}

	void LogLevelFlagFormatter::format(const spdlog::details::log_msg& a_msg, [[maybe_unused]] const std::tm& a_time, spdlog::memory_buf_t& a_dest)
	{
		const auto logLevel = static_cast<std::size_t>(a_msg.level);
		const auto& logLevelName = (logLevel < LOG_LEVEL_NAMES.size()) ? LOG_LEVEL_NAMES[logLevel] : UNKOWN_LOG_LEVEL_NAME;
		a_dest.append(logLevelName.data(), logLevelName.data() + logLevelName.size());
	}

	auto LogLevelFlagFormatter::clone() const -> std::unique_ptr<spdlog::custom_flag_formatter>
	{
		return std::make_unique<LogLevelFlagFormatter>();
	}

	void StemFileNameFlagFormatter::format(const spdlog::details::log_msg& a_msg, [[maybe_unused]] const std::tm& a_time, spdlog::memory_buf_t& a_dest)
	{
		const auto filePath = std::filesystem::path(a_msg.source.filename, std::filesystem::path::generic_format);
		const auto fileName = filePath.stem().generic_string();
		a_dest.append(fileName.data(), fileName.data() + fileName.size());
	}

	auto StemFileNameFlagFormatter::clone() const -> std::unique_ptr<spdlog::custom_flag_formatter>
	{
		return std::make_unique<StemFileNameFlagFormatter>();
	}
}
