#pragma once

#include "REX/Concepts.hpp"
#include "REX/Contract.hpp"
#include "REX/EnumSet.hpp"
#include "REX/ErrorCode.hpp"
#include "REX/Format.hpp"
#include "REX/ZString.hpp"

#include "REX/W32/USER32.hpp"

namespace REX
{
	enum class LogLevel : std::int32_t;

	inline constexpr auto DEFAULT_MESSAGE_FLAGS =
		REX::EnumSet(
			REX::W32::MB::MB_SYSTEMMODAL,
			REX::W32::MB::MB_SETFOREGROUND,
			REX::W32::MB::MB_TOPMOST);
}

namespace REX::Impl
{
	template <REX::win32_character T>
	[[nodiscard]] auto FormatHeader() noexcept -> std::expected<std::basic_string<T>, REX::SystemError>;

	template <>
	auto FormatHeader() noexcept -> std::expected<std::string, REX::SystemError>;

	template <>
	auto FormatHeader() noexcept -> std::expected<std::wstring, REX::SystemError>;

	template <REX::win32_character T>
	[[nodiscard]] auto FormatBody(std::source_location a_location, std::basic_string_view<T> a_format) noexcept -> std::expected<std::basic_string<T>, REX::SystemError>;

	template <>
	auto FormatBody(std::source_location a_location, std::string_view a_format) noexcept -> std::expected<std::string, REX::SystemError>;

	template <>
	auto FormatBody(std::source_location a_location, std::wstring_view a_format) noexcept -> std::expected<std::wstring, REX::SystemError>;

	[[nodiscard]] REX::W32::MB GetMessageSeverityByLogLevel(LogLevel a_logLevel) noexcept;

	REX::W32::MBID ShowBasicMessage(LogLevel a_logLevel, REX::zstring_view a_title, REX::zstring_view a_message, REX::W32::MB a_messageFlags = DEFAULT_MESSAGE_FLAGS.get()) noexcept;
	REX::W32::MBID ShowBasicMessage(LogLevel a_logLevel, REX::zwstring_view a_title, REX::zwstring_view a_message, REX::W32::MB a_messageFlags = DEFAULT_MESSAGE_FLAGS.get()) noexcept;

	REX::W32::MBID ShowSourceMessage(LogLevel a_logLevel, std::source_location a_location, std::string_view a_format, REX::W32::MB a_messageFlags = DEFAULT_MESSAGE_FLAGS.get()) noexcept;
	REX::W32::MBID ShowSourceMessage(LogLevel a_logLevel, std::source_location a_location, std::wstring_view a_format, REX::W32::MB a_messageFlags = DEFAULT_MESSAGE_FLAGS.get()) noexcept;

	template <class... Args>
	REX::W32::MBID ShowSourceMessage(LogLevel a_logLevel, std::source_location a_location, REX::FormatString<Args...> a_format, Args&&... a_args) noexcept
		requires((REX::formattable<Args, char> && ...))
	{
		try {
			return ShowSourceMessage(a_logLevel, a_location, REX::Format(a_format, std::forward<Args>(a_args)...));
		}
		catch ([[maybe_unused]] const std::bad_alloc& error) {
			REX::AllocationFail();
		}
	}

	template <class... Args>
	REX::W32::MBID ShowSourceMessage(LogLevel a_logLevel, std::source_location a_location, REX::WFormatString<Args...> a_format, Args&&... a_args) noexcept
		requires((REX::formattable<Args, wchar_t> && ...))
	{
		try {
			return ShowSourceMessage(a_logLevel, a_location, REX::Format(a_format, std::forward<Args>(a_args)...));
		}
		catch ([[maybe_unused]] const std::bad_alloc& error) {
			REX::AllocationFail();
		}
	}

	void Inform(std::source_location a_location, std::string_view a_format) noexcept;
	void Inform(std::source_location a_location, std::wstring_view a_format) noexcept;

	template <class... Args>
	[[noreturn]] void Inform(std::source_location a_location, REX::FormatString<Args...> a_format, Args&&... a_args) noexcept
		requires((REX::formattable<Args, char> && ...))
	{
		try {
			Inform(a_location, REX::Format(a_format, std::forward<Args>(a_args)...));
		}
		catch ([[maybe_unused]] const std::bad_alloc& error) {
			REX::AllocationFail();
		}
	}

	template <class... Args>
	[[noreturn]] void Inform(std::source_location a_location, REX::WFormatString<Args...> a_format, Args&&... a_args) noexcept
		requires((REX::formattable<Args, wchar_t> && ...))
	{
		try {
			Inform(a_location, REX::Format(a_format, std::forward<Args>(a_args)...));
		}
		catch ([[maybe_unused]] const std::bad_alloc& error) {
			REX::AllocationFail();
		}
	}

	void Warn(std::source_location a_location, std::string_view a_format) noexcept;
	void Warn(std::source_location a_location, std::wstring_view a_format) noexcept;

	template <class... Args>
	[[noreturn]] void Warn(std::source_location a_location, REX::FormatString<Args...> a_format, Args&&... a_args) noexcept
		requires((REX::formattable<Args, char> && ...))
	{
		try {
			Warn(a_location, REX::Format(a_format, std::forward<Args>(a_args)...));
		}
		catch ([[maybe_unused]] const std::bad_alloc& error) {
			REX::AllocationFail();
		}
	}

	template <class... Args>
	[[noreturn]] void Warn(std::source_location a_location, REX::WFormatString<Args...> a_format, Args&&... a_args) noexcept
		requires((REX::formattable<Args, wchar_t> && ...))
	{
		try {
			Warn(a_location, REX::Format(a_format, std::forward<Args>(a_args)...));
		}
		catch ([[maybe_unused]] const std::bad_alloc& error) {
			REX::AllocationFail();
		}
	}

	[[noreturn]] void Fail(std::source_location a_location, std::string_view a_format) noexcept;
	[[noreturn]] void Fail(std::source_location a_location, std::wstring_view a_format) noexcept;

	template <class... Args>
	[[noreturn]] void Fail(std::source_location a_location, REX::FormatString<Args...> a_format, Args&&... a_args) noexcept
		requires((REX::formattable<Args, char> && ...))
	{
		try {
			Fail(a_location, REX::Format(a_format, std::forward<Args>(a_args)...));
		}
		catch ([[maybe_unused]] const std::bad_alloc& error) {
			REX::AllocationFail();
		}
	}

	template <class... Args>
	[[noreturn]] void Fail(std::source_location a_location, REX::WFormatString<Args...> a_format, Args&&... a_args) noexcept
		requires((REX::formattable<Args, wchar_t> && ...))
	{
		try {
			Fail(a_location, REX::Format(a_format, std::forward<Args>(a_args)...));
		}
		catch ([[maybe_unused]] const std::bad_alloc& error) {
			REX::AllocationFail();
		}
	}
}

namespace REX
{
	inline REX::W32::MBID ShowBasicMessage(LogLevel a_logLevel, std::string_view a_title, std::string_view a_message, REX::W32::MB a_messageFlags = DEFAULT_MESSAGE_FLAGS.get()) noexcept
	{
		return Impl::ShowBasicMessage(a_logLevel, a_title, a_message, a_messageFlags);
	}

	inline REX::W32::MBID ShowBasicMessage(LogLevel a_logLevel, std::wstring_view a_title, std::wstring_view a_message, REX::W32::MB a_messageFlags = DEFAULT_MESSAGE_FLAGS.get()) noexcept
	{
		return Impl::ShowBasicMessage(a_logLevel, a_title, a_message, a_messageFlags);
	}

	inline REX::W32::MBID ShowSourceMessage(LogLevel a_logLevel, std::source_location a_location, std::string_view a_format, REX::W32::MB a_messageFlags = DEFAULT_MESSAGE_FLAGS.get()) noexcept
	{
		return Impl::ShowSourceMessage(a_logLevel, a_location, a_format, a_messageFlags);
	}

	inline REX::W32::MBID ShowSourceMessage(LogLevel a_logLevel, std::source_location a_location, std::wstring_view a_format, REX::W32::MB a_messageFlags = DEFAULT_MESSAGE_FLAGS.get()) noexcept
	{
		return Impl::ShowSourceMessage(a_logLevel, a_location, a_format, a_messageFlags);
	}

	template <class... Args>
	REX::W32::MBID ShowSourceMessage(LogLevel a_logLevel, REX::FormatStringLocation<Args...> a_formatLocation, Args&&... a_args) noexcept
		requires((REX::formattable<Args, char> && ...))
	{
		Impl::ShowSourceMessage(a_logLevel, a_formatLocation.location(), a_formatLocation.format(), std::forward<Args>(a_args)...);
	}

	template <class... Args>
	REX::W32::MBID ShowSourceMessage(LogLevel a_logLevel, REX::WFormatStringLocation<Args...> a_formatLocation, Args&&... a_args) noexcept
		requires((REX::formattable<Args, wchar_t> && ...))
	{
		Impl::ShowSourceMessage(a_logLevel, a_formatLocation.location(), a_formatLocation.format(), std::forward<Args>(a_args)...);
	}

	inline void Inform(std::string_view a_format, std::source_location a_location = std::source_location::current()) noexcept
	{
		Impl::Inform(a_location, a_format);
	}

	inline void Inform(std::wstring_view a_format, std::source_location a_location = std::source_location::current()) noexcept
	{
		Impl::Inform(a_location, a_format);
	}

	template <class... Args>
	void Inform(REX::FormatStringLocation<Args...> a_formatLocation, Args&&... a_args) noexcept
		requires((REX::formattable<Args, char> && ...))
	{
		Impl::Inform(a_formatLocation.location(), a_formatLocation.format(), std::forward<Args>(a_args)...);
	}

	template <class... Args>
	void Inform(REX::WFormatStringLocation<Args...> a_formatLocation, Args&&... a_args) noexcept
		requires((REX::formattable<Args, wchar_t> && ...))
	{
		Impl::Inform(a_formatLocation.location(), a_formatLocation.format(), std::forward<Args>(a_args)...);
	}

	inline void Warn(std::string_view a_format, std::source_location a_location = std::source_location::current()) noexcept
	{
		Impl::Warn(a_location, a_format);
	}

	inline void Warn(std::wstring_view a_format, std::source_location a_location = std::source_location::current()) noexcept
	{
		Impl::Warn(a_location, a_format);
	}

	template <class... Args>
	void Warn(REX::FormatStringLocation<Args...> a_formatLocation, Args&&... a_args) noexcept
		requires((REX::formattable<Args, char> && ...))
	{
		Impl::Warn(a_formatLocation.location(), a_formatLocation.format(), std::forward<Args>(a_args)...);
	}

	template <class... Args>
	void Warn(REX::WFormatStringLocation<Args...> a_formatLocation, Args&&... a_args) noexcept
		requires((REX::formattable<Args, wchar_t> && ...))
	{
		Impl::Warn(a_formatLocation.location(), a_formatLocation.format(), std::forward<Args>(a_args)...);
	}

	[[noreturn]] inline void Fail(std::string_view a_format, std::source_location a_location = std::source_location::current()) noexcept
	{
		Impl::Fail(a_location, a_format);
	}

	[[noreturn]] inline void Fail(std::wstring_view a_format, std::source_location a_location = std::source_location::current()) noexcept
	{
		Impl::Fail(a_location, a_format);
	}

	template <class... Args>
	[[noreturn]] void Fail(REX::FormatStringLocation<Args...> a_formatLocation, Args&&... a_args) noexcept
		requires((REX::formattable<Args, char> && ...))
	{
		Impl::Fail(a_formatLocation.location(), a_formatLocation.format(), std::forward<Args>(a_args)...);
	}

	template <class... Args>
	[[noreturn]] void Fail(REX::WFormatStringLocation<Args...> a_formatLocation, Args&&... a_args) noexcept
		requires((REX::formattable<Args, wchar_t> && ...))
	{
		Impl::Fail(a_formatLocation.location(), a_formatLocation.format(), std::forward<Args>(a_args)...);
	}
}
