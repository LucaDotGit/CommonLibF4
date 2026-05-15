#include "REX/Message.hpp"

#include "REX/Concepts.hpp"
#include "REX/Contract.hpp"
#include "REX/EnumSet.hpp"
#include "REX/Error.hpp"
#include "REX/Path.hpp"
#include "REX/Version.hpp"
#include "REX/W32/CORE.hpp"
#include "REX/W32/KERNEL32.hpp"
#include "REX/W32/USER32.hpp"
#include "REX/Windows.hpp"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/msvc_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>

namespace REX::Impl
{
	template <REX::win32_character CharT>
	static constexpr auto EXCLUDED_DIRECTORY_NAMES = std::false_type();

	template <>
	constexpr auto EXCLUDED_DIRECTORY_NAMES<char> = std::array{
		"include"sv,
		"src"sv,
		"source"sv
	};

	template <>
	constexpr auto EXCLUDED_DIRECTORY_NAMES<wchar_t> = std::array{
		L"include"sv,
		L"src"sv,
		L"source"sv
	};

	template <REX::win32_character CharT>
	static constexpr auto MESSAGE_TITLE_FORMAT = std::false_type();

	template <>
	constexpr auto MESSAGE_TITLE_FORMAT<char> = "{:s} v{:s}"sv;

	template <>
	constexpr auto MESSAGE_TITLE_FORMAT<wchar_t> = L"{:s} v{:s}"sv;

	template <REX::win32_character CharT>
	static constexpr auto MESSAGE_BODY_FORMAT = std::false_type();

	template <>
	constexpr auto MESSAGE_BODY_FORMAT<char> = "[{:s}#{:d}@{:s}]\n\n{}"sv;

	template <>
	constexpr auto MESSAGE_BODY_FORMAT<wchar_t> = L"[{:s}#{:d}@{:s}]\n\n{}"sv;

	static constexpr auto DEFAULT_MESSAGE_FLAGS =
		REX::EnumSet(
			MessageBoxFlags::MB_SYSTEMMODAL,
			MessageBoxFlags::MB_SETFOREGROUND,
			MessageBoxFlags::MB_TOPMOST,
			MessageBoxFlags::MB_OK);

	template <REX::win32_character CharT>
	[[nodiscard]] static auto GetRelativeFilePath(std::basic_string_view<CharT> a_filePath) noexcept
		-> std::basic_string_view<CharT>
	{
		auto currentFilePath = a_filePath;
		do {
			currentFilePath = REX::GetDirectoryPath(currentFilePath);
			for (const auto excludedDirectoryName : EXCLUDED_DIRECTORY_NAMES<CharT>) {
				const auto currentDirectoryName = REX::GetFileName(currentFilePath);
				if (currentDirectoryName == excludedDirectoryName) {
					return a_filePath.substr(currentFilePath.size() + 1);
				}
			}
		}
		while (!currentFilePath.empty());

		return a_filePath;
	}

	template <REX::win32_character CharT>
	[[nodiscard]] static auto GetCurrentModuleFileName(std::span<CharT> a_buffer) noexcept
		-> std::expected<std::basic_string_view<CharT>, REX::SystemError>
	{
		return REX::GetCurrentModuleFileName<CharT>(a_buffer);
	}

	template <REX::win32_character CharT>
	[[nodiscard]] static auto GetCurrentModuleVersionString(std::basic_string_view<CharT> a_moduleName, std::span<CharT> a_buffer) noexcept
		-> std::expected<std::basic_string_view<CharT>, REX::SystemError>
	{
		const auto version = REX::GetModuleFileVersion(a_moduleName);
		if (!version) {
			return std::unexpected(version.error());
		}

		return version->template ToString<CharT>(a_buffer);
	}

	template <REX::win32_character CharT>
	[[nodiscard]] static auto FormatMessageTitle(std::span<CharT> a_buffer) noexcept
		-> std::expected<std::basic_string_view<CharT>, REX::SystemError>
	{
		auto moduleFileNameBuffer = std::array<CharT, REX::W32::MAX_FNAME>();

		const auto moduleFileNameView = GetCurrentModuleFileName<CharT>(moduleFileNameBuffer);
		if (!moduleFileNameView) {
			return std::unexpected(moduleFileNameView.error());
		}

		auto moduleVersionStringBuffer = std::array<CharT, REX::Version::MAX_BUFFER_SIZE>();

		const auto moduleVersionStringView = GetCurrentModuleVersionString<CharT>(*moduleFileNameView, moduleVersionStringBuffer);
		if (!moduleVersionStringView) {
			return std::unexpected(moduleVersionStringView.error());
		}

		return REX::FixedFormat(
			a_buffer,
			MESSAGE_TITLE_FORMAT<CharT>,
			*moduleFileNameView,
			*moduleVersionStringView);
	}

	template <REX::win32_character CharT>
	[[nodiscard]] static auto FormatMessageBody(std::span<CharT> a_buffer, REX::SourceLocation a_location, std::basic_string_view<CharT> a_format) noexcept
		-> std::expected<std::basic_string_view<CharT>, REX::SystemError>;

	template <>
	[[nodiscard]] auto FormatMessageBody(std::span<char> a_buffer, REX::SourceLocation a_location, std::string_view a_format) noexcept
		-> std::expected<std::string_view, REX::SystemError>
	{
		const auto relativeFilePath = GetRelativeFilePath(a_location.GetFilePath());
		return REX::FixedFormat(
			a_buffer,
			MESSAGE_BODY_FORMAT<char>,
			relativeFilePath,
			a_location.GetLineNumber(),
			a_location.GetFunctionName(),
			a_format);
	}

	template <>
	[[nodiscard]] auto FormatMessageBody(std::span<wchar_t> a_buffer, REX::SourceLocation a_location, std::wstring_view a_format) noexcept
		-> std::expected<std::wstring_view, REX::SystemError>
	{
		auto filePathBuffer = std::array<wchar_t, REX::W32::MAX_FNAME>();

		const auto filePathView = REX::Utf8ToUtf16(a_location.GetFilePath(), filePathBuffer);
		if (!filePathView) {
			return std::unexpected(filePathView.error());
		}

		auto functionNameBuffer = std::array<wchar_t, REX::W32::MAX_FNAME>();

		const auto functionNameView = REX::Utf8ToUtf16(a_location.GetFunctionName(), functionNameBuffer);
		if (!functionNameView) {
			return std::unexpected(functionNameView.error());
		}

		const auto relativeFilePath = GetRelativeFilePath(*filePathView);
		return REX::FixedFormat(
			a_buffer,
			MESSAGE_BODY_FORMAT<wchar_t>,
			relativeFilePath,
			a_location.GetLineNumber(),
			*functionNameView,
			a_format);
	}

	[[nodiscard]] static constexpr MessageBoxFlags GetMessageSeverityByLogLevel(LogLevel a_logLevel) noexcept
	{
		switch (a_logLevel) {
			case LogLevel::kWarning: {
				return MessageBoxFlags::MB_ICONWARNING;
			}
			case LogLevel::kError:
			case LogLevel::kCritical: {
				return MessageBoxFlags::MB_ICONERROR;
			}
			default: {
				return MessageBoxFlags::MB_ICONINFORMATION;
			}
		}
	}

	MessageBoxResult ShowBasicMessage(LogLevel a_logLevel, std::string_view a_title, std::string_view a_message, MessageBoxFlags a_messageFlags) noexcept
	{
		constexpr auto WINDOW_HANDLE = static_cast<REX::W32::HWND>(0);

		const auto messageBoxFlags = REX::EnumSet(a_messageFlags, GetMessageSeverityByLogLevel(a_logLevel));
		return static_cast<MessageBoxResult>(REX::W32::MessageBoxA(
			WINDOW_HANDLE,
			a_message.data(),
			a_title.data(),
			messageBoxFlags.get()));
	}

	MessageBoxResult ShowBasicMessage(LogLevel a_logLevel, std::wstring_view a_title, std::wstring_view a_message, MessageBoxFlags a_messageFlags) noexcept
	{
		constexpr auto WINDOW_HANDLE = static_cast<REX::W32::HWND>(0);

		const auto messageBoxFlags = REX::EnumSet(a_messageFlags, GetMessageSeverityByLogLevel(a_logLevel));
		return static_cast<MessageBoxResult>(REX::W32::MessageBoxW(
			WINDOW_HANDLE,
			a_message.data(),
			a_title.data(),
			messageBoxFlags.get()));
	}

	MessageBoxResult ShowBasicMessage(LogLevel a_logLevel, std::string_view a_message, MessageBoxFlags a_messageFlags) noexcept
	{
		auto titleBuffer = std::array<char, REX::TITLE_BUFFER_SIZE>();

		const auto messageTitle = FormatMessageTitle<char>(titleBuffer);
		if (!messageTitle) [[unlikely]] {
			REX::Assert(false);
			return MessageBoxResult::IDABORT;
		}

		return ShowBasicMessage(a_logLevel, *messageTitle, a_message, a_messageFlags);
	}

	MessageBoxResult ShowBasicMessage(LogLevel a_logLevel, std::wstring_view a_message, MessageBoxFlags a_messageFlags) noexcept
	{
		auto titleBuffer = std::array<wchar_t, REX::TITLE_BUFFER_SIZE>();

		const auto messageTitle = FormatMessageTitle<wchar_t>(titleBuffer);
		if (!messageTitle) [[unlikely]] {
			REX::Assert(false);
			return MessageBoxResult::IDABORT;
		}

		return ShowBasicMessage(a_logLevel, *messageTitle, a_message, a_messageFlags);
	}

	MessageBoxResult ShowSourceMessage(LogLevel a_logLevel, REX::SourceLocation a_location, std::string_view a_format, MessageBoxFlags a_messageFlags) noexcept
	{
		auto titleBuffer = std::array<char, REX::TITLE_BUFFER_SIZE>();

		const auto messageTitle = FormatMessageTitle<char>(titleBuffer);
		if (!messageTitle) [[unlikely]] {
			REX::Assert(false);
			return MessageBoxResult::IDABORT;
		}

		auto messageBuffer = std::array<char, REX::MESSAGE_BUFFER_SIZE>();

		const auto messageBody = FormatMessageBody<char>(messageBuffer, a_location, a_format);
		if (!messageBody) [[unlikely]] {
			REX::Assert(false);
			return MessageBoxResult::IDABORT;
		}

		Log(a_logLevel, a_location, a_format);

		return ShowBasicMessage(a_logLevel, *messageTitle, *messageBody, a_messageFlags);
	}

	MessageBoxResult ShowSourceMessage(LogLevel a_logLevel, REX::SourceLocation a_location, std::wstring_view a_format, MessageBoxFlags a_messageFlags) noexcept
	{
		auto titleBuffer = std::array<wchar_t, REX::TITLE_BUFFER_SIZE>();

		const auto messageTitle = FormatMessageTitle<wchar_t>(titleBuffer);
		if (!messageTitle) [[unlikely]] {
			REX::Assert(false);
			return MessageBoxResult::IDABORT;
		}

		auto messageBuffer = std::array<wchar_t, REX::MESSAGE_BUFFER_SIZE>();

		const auto messageBody = FormatMessageBody<wchar_t>(messageBuffer, a_location, a_format);
		if (!messageBody) [[unlikely]] {
			REX::Assert(false);
			return MessageBoxResult::IDABORT;
		}

		Log(a_logLevel, a_location, a_format);

		return ShowBasicMessage(a_logLevel, *messageTitle, *messageBody, a_messageFlags);
	}

	void Inform(std::string_view a_format) noexcept
	{
		ShowBasicMessage(LogLevel::kInformation, a_format, DEFAULT_MESSAGE_FLAGS.get());
	}

	void Inform(std::wstring_view a_format) noexcept
	{
		ShowBasicMessage(LogLevel::kInformation, a_format, DEFAULT_MESSAGE_FLAGS.get());
	}

	void Warn(REX::SourceLocation a_location, std::string_view a_format) noexcept
	{
		ShowSourceMessage(LogLevel::kWarning, a_location, a_format, DEFAULT_MESSAGE_FLAGS.get());
	}

	void Warn(REX::SourceLocation a_location, std::wstring_view a_format) noexcept
	{
		ShowSourceMessage(LogLevel::kWarning, a_location, a_format, DEFAULT_MESSAGE_FLAGS.get());
	}

	void Fail(REX::SourceLocation a_location, std::string_view a_format) noexcept
	{
		ShowSourceMessage(LogLevel::kCritical, a_location, a_format, DEFAULT_MESSAGE_FLAGS.get());

		if (REX::W32::IsDebuggerPresent()) {
			REX::W32::DebugBreak();
		}

		REX::W32::TerminateCurrentProcess(EXIT_FAILURE);
	}

	void Fail(REX::SourceLocation a_location, std::wstring_view a_format) noexcept
	{
		ShowSourceMessage(LogLevel::kCritical, a_location, a_format, DEFAULT_MESSAGE_FLAGS.get());

		if (REX::W32::IsDebuggerPresent()) {
			REX::W32::DebugBreak();
		}

		REX::W32::TerminateCurrentProcess(EXIT_FAILURE);
	}
}

namespace REX
{
	MessageBoxResult ShowBasicMessage(LogLevel a_logLevel, std::string_view a_title, std::string_view a_message) noexcept
	{
		return Impl::ShowBasicMessage(a_logLevel, a_title, a_message, Impl::DEFAULT_MESSAGE_FLAGS.get());
	}

	MessageBoxResult ShowBasicMessage(LogLevel a_logLevel, std::wstring_view a_title, std::wstring_view a_message) noexcept
	{
		return Impl::ShowBasicMessage(a_logLevel, a_title, a_message, Impl::DEFAULT_MESSAGE_FLAGS.get());
	}

	MessageBoxResult ShowBasicMessage(LogLevel a_logLevel, std::string_view a_message) noexcept
	{
		return Impl::ShowBasicMessage(a_logLevel, a_message, Impl::DEFAULT_MESSAGE_FLAGS.get());
	}

	MessageBoxResult ShowBasicMessage(LogLevel a_logLevel, std::wstring_view a_message) noexcept
	{
		return Impl::ShowBasicMessage(a_logLevel, a_message, Impl::DEFAULT_MESSAGE_FLAGS.get());
	}

	MessageBoxResult ShowSourceMessage(LogLevel a_logLevel, REX::SourceLocation a_location, std::string_view a_format) noexcept
	{
		return Impl::ShowSourceMessage(a_logLevel, a_location, a_format, Impl::DEFAULT_MESSAGE_FLAGS.get());
	}

	MessageBoxResult ShowSourceMessage(LogLevel a_logLevel, REX::SourceLocation a_location, std::wstring_view a_format) noexcept
	{
		return Impl::ShowSourceMessage(a_logLevel, a_location, a_format, Impl::DEFAULT_MESSAGE_FLAGS.get());
	}
}
