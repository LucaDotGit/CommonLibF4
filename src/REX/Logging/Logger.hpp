#pragma once

#include "REX/Enum.hpp"
#include "REX/Formatting.hpp"
#include "REX/Logging/ILogger.hpp"
#include "REX/NotNull.hpp"
#include "REX/SourceLocation.hpp"

namespace REX::Logging
{
	enum class Level : std::int32_t;

	class Context;
	class ISink;
	class IFormatter;

	class Logger final : public REX::Logging::ILogger
	{
	public:
		using ErrorHandler = void(
			const REX::Logging::Context& a_context,
			const std::exception_ptr& a_error,
			std::string_view a_errorMessage) const;

		explicit Logger(std::string a_name);

		Logger(std::string a_name, REX::NotNull<std::unique_ptr<const REX::Logging::IFormatter>> a_formatter);

		Logger(
			std::string a_name,
			REX::NotNull<std::unique_ptr<const REX::Logging::IFormatter>> a_formatter,
			REX::NotNull<std::move_only_function<ErrorHandler>> a_errorHandler) noexcept;

		~Logger() noexcept override;

		Logger(const Logger&) = delete;
		Logger(Logger&&) = delete;

		auto operator=(const Logger&) -> Logger& = delete;
		auto operator=(Logger&&) -> Logger& = delete;

		[[nodiscard]]
		auto GetName() const noexcept -> std::string_view override
		{
			return std::string_view(_name);
		}

		[[nodiscard]]
		auto GetMinLevel() const noexcept -> REX::Logging::Level override
		{
			return _minLevel.get_atomic();
		}

		void SetMinLevel(REX::Logging::Level a_minLevel) noexcept override
		{
			_minLevel.store_atomic(a_minLevel);
		}

		[[nodiscard]]
		auto GetFlushLevel() const noexcept -> REX::Logging::Level override
		{
			return _flushLevel.get_atomic();
		}

		void SetFlushLevel(REX::Logging::Level a_flushLevel) noexcept override
		{
			_flushLevel.store_atomic(a_flushLevel);
		}

		void AddSink(REX::NotNull<std::shared_ptr<REX::Logging::ISink>> a_sink) override;

		void AddSinkRange(std::span<const REX::NotNull<std::shared_ptr<REX::Logging::ISink>>> a_sinks) override;

		void LogContext(const REX::Logging::Context& a_context) override;

		void LogMessage(
			REX::Logging::Level a_level,
			std::string_view a_message,
			REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) override;

		void LogMessage(
			REX::Logging::Level a_level,
			std::wstring_view a_message,
			REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) override;

		void LogFormat(
			REX::Logging::Level a_level,
			std::string_view a_format,
			REX::FormatArgs a_args,
			REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) override;

		void LogFormat(
			REX::Logging::Level a_level,
			std::wstring_view a_format,
			REX::WFormatArgs a_args,
			REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) override;

		static void DefaultErrorHandler(
			const REX::Logging::Context& a_context,
			const std::exception_ptr& a_error,
			std::string_view a_errorMessage);

	private:
		std::string _name;
		REX::Enum<REX::Logging::Level> _minLevel;
		REX::Enum<REX::Logging::Level> _flushLevel;
		REX::NotNull<std::unique_ptr<const REX::Logging::IFormatter>> _formatter;
		REX::NotNull<std::move_only_function<ErrorHandler>> _errorHandler;
		mutable std::mutex _sinkMutex;
		std::vector<REX::NotNull<std::shared_ptr<REX::Logging::ISink>>> _sinks;
	};
}
