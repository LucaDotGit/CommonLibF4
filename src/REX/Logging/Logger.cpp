#include "REX/Logging/Logger.hpp"

#include "REX/Concepts.hpp"
#include "REX/Container.hpp"
#include "REX/Conversion.hpp"
#include "REX/Formatting.hpp"
#include "REX/Logging/Context.hpp"
#include "REX/Logging/Formatter.hpp"
#include "REX/Logging/IFormatter.hpp"
#include "REX/Logging/ISink.hpp"
#include "REX/Logging/Level.hpp"
#include "REX/NotNull.hpp"
#include "REX/SourceLocation.hpp"

namespace REX::Logging
{
	Logger::Logger(std::string a_name) :
		Logger(std::move(a_name), std::make_unique<const REX::Logging::Formatter>())
	{
	}

	Logger::Logger(std::string a_name, REX::NotNull<std::unique_ptr<const REX::Logging::IFormatter>> a_formatter) :
		Logger(std::move(a_name), std::move(a_formatter), DefaultErrorHandler)
	{
	}

	Logger::Logger(
		std::string a_name,
		REX::NotNull<std::unique_ptr<const REX::Logging::IFormatter>> a_formatter,
		REX::NotNull<std::move_only_function<ErrorHandler>> a_errorHandler) noexcept :
		_name(std::move(a_name)),
		_minLevel(Level::Information),
		_flushLevel(Level::Error),
		_formatter(std::move(a_formatter)),
		_errorHandler(std::move(a_errorHandler))
	{
	}

	Logger::~Logger() noexcept = default;

	void Logger::AddSink(REX::NotNull<std::shared_ptr<REX::Logging::ISink>> a_sink)
	{
		const auto lock = std::scoped_lock(_sinkMutex);
		_sinks.push_back(std::move(a_sink));
	}

	void Logger::AddSinkRange(std::span<const REX::NotNull<std::shared_ptr<REX::Logging::ISink>>> a_sinks)
	{
		const auto lock = std::scoped_lock(_sinkMutex);
		_sinks.append_range(a_sinks);
	}

	void Logger::LogContext(const REX::Logging::Context& a_context)
	{
		if (GetMinLevel() > a_context.GetLevel()) {
			return;
		}

		auto currentError = std::exception_ptr();
		auto currentErrorMessage = std::string_view();

		auto formatStorage = std::array<char, REX::MESSAGE_BUFFER_SIZE>();
		auto formatRessource = std::pmr::monotonic_buffer_resource{formatStorage.data(), formatStorage.size()};
		auto formatBuffer = std::pmr::string(std::addressof(formatRessource));

		try {
			_formatter->Format(a_context, formatBuffer);

			const auto doFlush = GetFlushLevel() <= a_context.GetLevel();
			const auto sinkLock = std::scoped_lock(_sinkMutex);

			for (const auto& sink : _sinks) {
				sink->Log(a_context, formatBuffer);

				if (doFlush) {
					sink->Flush();
				}
			}
		}
		catch (const std::exception& error) {
			currentError = std::current_exception();
			currentErrorMessage = error.what();
		}
		catch (...) {
			currentError = std::current_exception();
			currentErrorMessage = "An unknown error occurred while logging a message."sv;
		}

		if (!currentError) [[likely]] {
			return;
		}

		std::invoke(_errorHandler.get(), a_context, currentError, currentErrorMessage);
	}

	void Logger::LogMessage(REX::Logging::Level a_level, std::string_view a_message, REX::SourceLocation a_location)
	{
		if (GetMinLevel() > a_level) {
			return;
		}

		const auto currentSystemTime = std::chrono::system_clock::now();
		const auto currentThreadId = std::this_thread::get_id();
		const auto context =
			REX::Logging::Context(_name, a_level, currentSystemTime, currentThreadId, a_location, a_message);

		LogContext(context);
	}

	void Logger::LogMessage(REX::Logging::Level a_level, std::wstring_view a_message, REX::SourceLocation a_location)
	{
		if (GetMinLevel() > a_level) {
			return;
		}

		constexpr auto ERROR_MESSAGE = "<Failed to convert log message from UTF-16 to UTF-8>"sv;

		const auto conversionSize = REX::Utf16ToUtf8(a_message, {});
		if (!conversionSize.has_value()) [[unlikely]] {
			LogMessage(a_level, ERROR_MESSAGE, a_location);
			return;
		}

		auto formatStorage = std::array<char, REX::MESSAGE_BUFFER_SIZE>();
		auto formatRessource = std::pmr::monotonic_buffer_resource{formatStorage.data(), formatStorage.size()};
		auto formatBuffer = std::pmr::string(std::addressof(formatRessource));

		REX::ResizeForOverwrite(formatBuffer, conversionSize.value());

		const auto conversionResult = REX::Utf16ToUtf8(a_message, std::span<char>(formatBuffer));
		if (!conversionResult.has_value()) [[unlikely]] {
			LogMessage(a_level, ERROR_MESSAGE, a_location);
			return;
		}

		LogMessage(a_level, formatBuffer, a_location);
	}

	void Logger::LogFormat(
		REX::Logging::Level a_level,
		std::string_view a_format,
		REX::FormatArgs a_args,
		REX::SourceLocation a_location)
	{
		if (GetMinLevel() > a_level) {
			return;
		}

		auto formatStorage = std::array<char, REX::MESSAGE_BUFFER_SIZE>();
		auto formatRessource = std::pmr::monotonic_buffer_resource{formatStorage.data(), formatStorage.size()};
		auto formatBuffer = std::pmr::string(std::addressof(formatRessource));

		REX::VFormatTo(std::back_inserter(formatBuffer), a_format, a_args);
		LogMessage(a_level, formatBuffer, a_location);
	}

	void Logger::LogFormat(
		REX::Logging::Level a_level,
		std::wstring_view a_format,
		REX::WFormatArgs a_args,
		REX::SourceLocation a_location)
	{
		if (GetMinLevel() > a_level) {
			return;
		}

		auto formatStorage = std::array<wchar_t, REX::MESSAGE_BUFFER_SIZE>();
		auto formatRessource = std::pmr::monotonic_buffer_resource{formatStorage.data(), formatStorage.size()};
		auto formatBuffer = std::pmr::wstring(std::addressof(formatRessource));

		REX::VFormatTo(std::back_inserter(formatBuffer), a_format, a_args);
		LogMessage(a_level, formatBuffer, a_location);
	}

	void Logger::DefaultErrorHandler(
		[[maybe_unused]] const REX::Logging::Context& a_context,
		[[maybe_unused]] const std::exception_ptr& a_error,
		std::string_view a_errorMessage)
	{
		REX::PrintLine(std::cerr, "{}"sv, a_errorMessage);
	}
}
