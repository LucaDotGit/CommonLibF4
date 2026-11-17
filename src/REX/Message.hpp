#pragma once

#include "REX/Concepts.hpp"
#include "REX/Formatting.hpp"
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
	using MessageBoxFlags = REX::W32::MB;
	using MessageBoxResult = REX::W32::MBID;
}

namespace REX::Logging
{
	enum class Level : std::int32_t;
}

namespace REX
{
	auto ShowBasicMessage(
		REX::Logging::Level a_logLevel,
		std::string_view a_title,
		std::string_view a_message,
		MessageBoxFlags a_messageFlags) noexcept -> MessageBoxResult;
	auto ShowBasicMessage(
		REX::Logging::Level a_logLevel,
		std::wstring_view a_title,
		std::wstring_view a_message,
		MessageBoxFlags a_messageFlags) noexcept -> MessageBoxResult;

	auto ShowBasicMessage(REX::Logging::Level a_logLevel, std::string_view a_title, std::string_view a_message) noexcept
		-> MessageBoxResult;
	auto ShowBasicMessage(REX::Logging::Level a_logLevel, std::wstring_view a_title, std::wstring_view a_message)
		noexcept -> MessageBoxResult;

	auto ShowBasicMessage(REX::Logging::Level a_logLevel, std::string_view a_message, MessageBoxFlags a_messageFlags)
		noexcept -> MessageBoxResult;
	auto ShowBasicMessage(REX::Logging::Level a_logLevel, std::wstring_view a_message, MessageBoxFlags a_messageFlags)
		noexcept -> MessageBoxResult;

	auto ShowBasicMessage(REX::Logging::Level a_logLevel, std::string_view a_message) noexcept -> MessageBoxResult;
	auto ShowBasicMessage(REX::Logging::Level a_logLevel, std::wstring_view a_message) noexcept -> MessageBoxResult;

	auto ShowSourceMessage(
		REX::Logging::Level a_logLevel,
		std::string_view a_format,
		MessageBoxFlags a_messageFlags,
		REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept -> MessageBoxResult;
	auto ShowSourceMessage(
		REX::Logging::Level a_logLevel,
		std::wstring_view a_format,
		MessageBoxFlags a_messageFlags,
		REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept -> MessageBoxResult;

	auto ShowSourceMessage(
		REX::Logging::Level a_logLevel,
		std::string_view a_format,
		REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept -> MessageBoxResult;
	auto ShowSourceMessage(
		REX::Logging::Level a_logLevel,
		std::wstring_view a_format,
		REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept -> MessageBoxResult;

	template <class... Args>
	auto ShowSourceMessage(
		REX::Logging::Level a_logLevel,
		REX::FormatStringLocation<Args...> a_formatLocation,
		Args&&... a_args) noexcept -> MessageBoxResult
		requires((REX::formattable<Args, char> && ...))
	{
		auto formatBuffer = std::array<char, REX::MESSAGE_BUFFER_SIZE>();
		const auto formatResult = REX::FormatToN(
			formatBuffer.data(),
			static_cast<std::ptrdiff_t>(formatBuffer.size()),
			a_formatLocation.format(),
			std::forward<Args>(a_args)...);

		return ShowSourceMessage(
			a_logLevel,
			std::string_view{formatBuffer.data(), formatResult.size},
			a_formatLocation.location());
	}

	template <class... Args>
	auto ShowSourceMessage(
		REX::Logging::Level a_logLevel,
		REX::WFormatStringLocation<Args...> a_formatLocation,
		Args&&... a_args) noexcept -> MessageBoxResult
		requires((REX::formattable<Args, wchar_t> && ...))
	{
		auto formatBuffer = std::array<wchar_t, REX::MESSAGE_BUFFER_SIZE>();
		const auto formatResult = REX::FormatToN(
			formatBuffer.data(),
			static_cast<std::ptrdiff_t>(formatBuffer.size()),
			a_formatLocation.format(),
			std::forward<Args>(a_args)...);

		return ShowSourceMessage(
			a_logLevel,
			std::wstring_view{formatBuffer.data(), formatResult.size},
			a_formatLocation.location());
	}

	void Inform(std::string_view a_format, REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept;
	void Inform(std::wstring_view a_format, REX::SourceLocation a_location = REX::SourceLocation::GetCurrent())
		noexcept;

	template <class... Args>
	void Inform(REX::FormatStringLocation<Args...> a_formatLocation, Args&&... a_args) noexcept
		requires((REX::formattable<Args, char> && ...))
	{
		auto formatBuffer = std::array<char, REX::MESSAGE_BUFFER_SIZE>();
		const auto formatResult = REX::FormatToN(
			formatBuffer.data(),
			static_cast<std::ptrdiff_t>(formatBuffer.size()),
			a_formatLocation.format(),
			std::forward<Args>(a_args)...);

		Inform(std::string_view{formatBuffer.data(), formatResult.size}, a_formatLocation.location());
	}

	template <class... Args>
	void Inform(REX::WFormatStringLocation<Args...> a_formatLocation, Args&&... a_args) noexcept
		requires((REX::formattable<Args, wchar_t> && ...))
	{
		auto formatBuffer = std::array<wchar_t, REX::MESSAGE_BUFFER_SIZE>();
		const auto formatResult = REX::FormatToN(
			formatBuffer.data(),
			static_cast<std::ptrdiff_t>(formatBuffer.size()),
			a_formatLocation.format(),
			std::forward<Args>(a_args)...);

		Inform(std::wstring_view{formatBuffer.data(), formatResult.size}, a_formatLocation.location());
	}

	void Warn(std::string_view a_format, REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept;
	void Warn(std::wstring_view a_format, REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept;

	template <class... Args>
	void Warn(REX::FormatStringLocation<Args...> a_formatLocation, Args&&... a_args) noexcept
		requires((REX::formattable<Args, char> && ...))
	{
		auto formatBuffer = std::array<char, REX::MESSAGE_BUFFER_SIZE>();
		const auto formatResult = REX::FormatToN(
			formatBuffer.data(),
			static_cast<std::ptrdiff_t>(formatBuffer.size()),
			a_formatLocation.format(),
			std::forward<Args>(a_args)...);

		Warn(std::string_view{formatBuffer.data(), formatResult.size}, a_formatLocation.location());
	}

	template <class... Args>
	void Warn(REX::WFormatStringLocation<Args...> a_formatLocation, Args&&... a_args) noexcept
		requires((REX::formattable<Args, wchar_t> && ...))
	{
		auto formatBuffer = std::array<wchar_t, REX::MESSAGE_BUFFER_SIZE>();
		const auto formatResult = REX::FormatToN(
			formatBuffer.data(),
			static_cast<std::ptrdiff_t>(formatBuffer.size()),
			a_formatLocation.format(),
			std::forward<Args>(a_args)...);

		Warn(std::wstring_view{formatBuffer.data(), formatResult.size}, a_formatLocation.location());
	}

	[[noreturn]]
	void Fail(std::string_view a_format, REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept;
	[[noreturn]]
	void Fail(std::wstring_view a_format, REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept;

	template <class... Args>
	[[noreturn]]
	void Fail(REX::FormatStringLocation<Args...> a_formatLocation, Args&&... a_args) noexcept
		requires((REX::formattable<Args, char> && ...))
	{
		auto formatBuffer = std::array<char, REX::MESSAGE_BUFFER_SIZE>();
		const auto formatResult = REX::FormatToN(
			formatBuffer.data(),
			static_cast<std::ptrdiff_t>(formatBuffer.size()),
			a_formatLocation.format(),
			std::forward<Args>(a_args)...);

		Fail(std::string_view{formatBuffer.data(), formatResult.size}, a_formatLocation.location());
	}

	template <class... Args>
	[[noreturn]]
	void Fail(REX::WFormatStringLocation<Args...> a_formatLocation, Args&&... a_args) noexcept
		requires((REX::formattable<Args, wchar_t> && ...))
	{
		auto formatBuffer = std::array<wchar_t, REX::MESSAGE_BUFFER_SIZE>();
		const auto formatResult = REX::FormatToN(
			formatBuffer.data(),
			static_cast<std::ptrdiff_t>(formatBuffer.size()),
			a_formatLocation.format(),
			std::forward<Args>(a_args)...);

		Fail(std::wstring_view{formatBuffer.data(), formatResult.size}, a_formatLocation.location());
	}
}
