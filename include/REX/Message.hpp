#pragma once

#include "REX/Format.hpp"
#include "REX/SourceLocation.hpp"

namespace REX::W32
{
	// NOLINTBEGIN(cppcoreguidelines-use-enum-class)
	enum MB : std::uint32_t;
	enum MBID : std::int32_t;
	// NOLINTEND(cppcoreguidelines-use-enum-class)
}

namespace REX
{
	enum class LogLevel : std::int32_t;

	using MessageBoxFlags = REX::W32::MB;
	using MessageBoxResult = REX::W32::MBID;
}

namespace REX::Impl
{
	MessageBoxResult ShowBasicMessage(LogLevel a_logLevel, std::string_view a_title, std::string_view a_message, MessageBoxFlags a_messageFlags) noexcept;
	MessageBoxResult ShowBasicMessage(LogLevel a_logLevel, std::wstring_view a_title, std::wstring_view a_message, MessageBoxFlags a_messageFlags) noexcept;

	MessageBoxResult ShowBasicMessage(LogLevel a_logLevel, std::string_view a_message, MessageBoxFlags a_messageFlags) noexcept;
	MessageBoxResult ShowBasicMessage(LogLevel a_logLevel, std::wstring_view a_message, MessageBoxFlags a_messageFlags) noexcept;

	MessageBoxResult ShowSourceMessage(LogLevel a_logLevel, REX::SourceLocation a_location, std::string_view a_format, MessageBoxFlags a_messageFlags) noexcept;
	MessageBoxResult ShowSourceMessage(LogLevel a_logLevel, REX::SourceLocation a_location, std::wstring_view a_format, MessageBoxFlags a_messageFlags) noexcept;

	void Inform(std::string_view a_format) noexcept;
	void Inform(std::wstring_view a_format) noexcept;

	void Warn(REX::SourceLocation a_location, std::string_view a_format) noexcept;
	void Warn(REX::SourceLocation a_location, std::wstring_view a_format) noexcept;

	[[noreturn]] void Fail(REX::SourceLocation a_location, std::string_view a_format) noexcept;
	[[noreturn]] void Fail(REX::SourceLocation a_location, std::wstring_view a_format) noexcept;
}

namespace REX
{
	MessageBoxResult ShowBasicMessage(LogLevel a_logLevel, std::string_view a_title, std::string_view a_message) noexcept;
	MessageBoxResult ShowBasicMessage(LogLevel a_logLevel, std::wstring_view a_title, std::wstring_view a_message) noexcept;

	MessageBoxResult ShowBasicMessage(LogLevel a_logLevel, std::string_view a_message) noexcept;
	MessageBoxResult ShowBasicMessage(LogLevel a_logLevel, std::wstring_view a_message) noexcept;

	MessageBoxResult ShowSourceMessage(LogLevel a_logLevel, REX::SourceLocation a_location, std::string_view a_format) noexcept;
	MessageBoxResult ShowSourceMessage(LogLevel a_logLevel, REX::SourceLocation a_location, std::wstring_view a_format) noexcept;

	template <class... Args>
	MessageBoxResult ShowSourceMessage(LogLevel a_logLevel, REX::FormatStringLocation<Args...> a_formatLocation, Args&&... a_args) noexcept
		requires((REX::formattable<Args, char> && ...))
	{
		const auto formatData = REX::FixedFormat(a_formatLocation.format(), std::forward<Args>(a_args)...);
		return ShowSourceMessage(a_logLevel, a_formatLocation.location(), std::string_view{ formatData.buffer.data(), formatData.size });
	}

	template <class... Args>
	MessageBoxResult ShowSourceMessage(LogLevel a_logLevel, REX::WFormatStringLocation<Args...> a_formatLocation, Args&&... a_args) noexcept
		requires((REX::formattable<Args, wchar_t> && ...))
	{
		const auto formatData = REX::FixedFormat(a_formatLocation.format(), std::forward<Args>(a_args)...);
		return ShowSourceMessage(a_logLevel, a_formatLocation.location(), std::wstring_view{ formatData.buffer.data(), formatData.size });
	}

	inline void Inform(std::string_view a_format) noexcept
	{
		Impl::Inform(a_format);
	}

	inline void Inform(std::wstring_view a_format) noexcept
	{
		Impl::Inform(a_format);
	}

	template <class... Args>
	void Inform(REX::FormatString<Args...> a_format, Args&&... a_args) noexcept
		requires((REX::formattable<Args, char> && ...))
	{
		const auto formatData = REX::FixedFormat(a_format, std::forward<Args>(a_args)...);
		Impl::Inform(std::string_view{ formatData.buffer.data(), formatData.size });
	}

	template <class... Args>
	void Inform(REX::WFormatString<Args...> a_format, Args&&... a_args) noexcept
		requires((REX::formattable<Args, wchar_t> && ...))
	{
		const auto formatData = REX::FixedFormat(a_format, std::forward<Args>(a_args)...);
		Impl::Inform(std::wstring_view{ formatData.buffer.data(), formatData.size });
	}

	inline void Warn(std::string_view a_format, REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept
	{
		Impl::Warn(a_location, a_format);
	}

	inline void Warn(std::wstring_view a_format, REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept
	{
		Impl::Warn(a_location, a_format);
	}

	template <class... Args>
	void Warn(REX::FormatStringLocation<Args...> a_formatLocation, Args&&... a_args) noexcept
		requires((REX::formattable<Args, char> && ...))
	{
		const auto formatData = REX::FixedFormat(a_formatLocation.format(), std::forward<Args>(a_args)...);
		Impl::Warn(a_formatLocation.location(), std::string_view{ formatData.buffer.data(), formatData.size });
	}

	template <class... Args>
	void Warn(REX::WFormatStringLocation<Args...> a_formatLocation, Args&&... a_args) noexcept
		requires((REX::formattable<Args, wchar_t> && ...))
	{
		const auto formatData = REX::FixedFormat(a_formatLocation.format(), std::forward<Args>(a_args)...);
		Impl::Warn(a_formatLocation.location(), std::wstring_view{ formatData.buffer.data(), formatData.size });
	}

	[[noreturn]] inline void Fail(std::string_view a_format, REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept
	{
		Impl::Fail(a_location, a_format);
	}

	[[noreturn]] inline void Fail(std::wstring_view a_format, REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept
	{
		Impl::Fail(a_location, a_format);
	}

	template <class... Args>
	[[noreturn]] void Fail(REX::FormatStringLocation<Args...> a_formatLocation, Args&&... a_args) noexcept
		requires((REX::formattable<Args, char> && ...))
	{
		const auto formatData = REX::FixedFormat(a_formatLocation.format(), std::forward<Args>(a_args)...);
		Impl::Fail(a_formatLocation.location(), std::string_view{ formatData.buffer.data(), formatData.size });
	}

	template <class... Args>
	[[noreturn]] void Fail(REX::WFormatStringLocation<Args...> a_formatLocation, Args&&... a_args) noexcept
		requires((REX::formattable<Args, wchar_t> && ...))
	{
		const auto formatData = REX::FixedFormat(a_formatLocation.format(), std::forward<Args>(a_args)...);
		Impl::Fail(a_formatLocation.location(), std::wstring_view{ formatData.buffer.data(), formatData.size });
	}
}
