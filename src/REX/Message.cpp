#include "REX/Message.hpp"

#include "REX/Concepts.hpp"
#include "REX/Contract.hpp"
#include "REX/Conversion.hpp"
#include "REX/EnumSet.hpp"
#include "REX/Error.hpp"
#include "REX/Formatting.hpp"
#include "REX/Logging/Level.hpp"
#include "REX/Macros.hpp"
#include "REX/Path.hpp"
#include "REX/SourceLocation.hpp"
#include "REX/System.hpp"
#include "REX/Version.hpp"
#include "REX/W32/CORE.hpp"
#include "REX/W32/USER32.hpp"

namespace REX::Impl
{
	namespace
	{
		template <REX::win32_character CharT>
		constexpr auto EXCLUDED_DIRECTORY_NAMES =
			std::array{REX_STRING_LITERAL(CharT, "src"sv), REX_STRING_LITERAL(CharT, "include"sv)};

		template <REX::win32_character CharT>
		constexpr auto MESSAGE_TITLE_FORMAT = REX_STRING_LITERAL(CharT, "{:s} v{:s}"sv);

		template <REX::win32_character CharT>
		constexpr auto MESSAGE_BODY_FORMAT = REX_STRING_LITERAL(CharT, "[{:s}@{:s}#{:0>5d}]\n\n{:s}"sv);

		constexpr auto DEFAULT_MESSAGE_FLAGS = REX::EnumSet(
			MessageBoxFlags::MB_SYSTEMMODAL,
			MessageBoxFlags::MB_SETFOREGROUND,
			MessageBoxFlags::MB_TOPMOST,
			MessageBoxFlags::MB_OK);

		template <REX::win32_character CharT>
		[[nodiscard]]
		auto GetRelativeFilePath(std::basic_string_view<CharT> a_filePath) noexcept -> std::basic_string_view<CharT>
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
		[[nodiscard]]
		auto GetCurrentModuleFileName(std::span<CharT> a_buffer) noexcept
			-> std::expected<std::basic_string_view<CharT>, REX::SystemError>
		{
			const auto moduleFilePath = REX::GetModuleFilePath<CharT>(REX::GetCurrentModuleHandle(), a_buffer);
			if (!moduleFilePath.has_value()) [[unlikely]] {
				return std::unexpected(moduleFilePath.error());
			}

			return REX::GetFileName(moduleFilePath.value());
		}

		template <REX::win32_character CharT>
		[[nodiscard]]
		auto GetCurrentModuleVersionString(std::basic_string_view<CharT> a_moduleName, std::span<CharT> a_buffer)
			noexcept -> std::expected<std::basic_string_view<CharT>, REX::SystemError>
		{
			const auto version = REX::GetModuleFileVersion(a_moduleName);
			if (!version.has_value()) [[unlikely]] {
				return std::unexpected(version.error());
			}

			return version->template ToString<CharT>(a_buffer);
		}

		template <REX::win32_character CharT>
		[[nodiscard]]
		auto FormatMessageTitle(std::span<CharT> a_buffer) noexcept
			-> std::expected<std::basic_string_view<CharT>, REX::SystemError>
		{
			auto moduleFileNameBuffer = std::array<CharT, REX::W32::MAX_FNAME>();

			const auto moduleFileNameView = GetCurrentModuleFileName<CharT>(moduleFileNameBuffer);
			if (!moduleFileNameView.has_value()) [[unlikely]] {
				return std::unexpected(moduleFileNameView.error());
			}

			auto moduleVersionStringBuffer = std::array<CharT, REX::Version::MAX_STRING_SIZE>();

			const auto moduleVersionStringView =
				GetCurrentModuleVersionString<CharT>(moduleFileNameView.value(), moduleVersionStringBuffer);
			if (!moduleVersionStringView.has_value()) [[unlikely]] {
				return std::unexpected(moduleVersionStringView.error());
			}

			const auto formatResult = REX::FormatToN(
				a_buffer.data(),
				static_cast<std::ptrdiff_t>(a_buffer.size()),
				MESSAGE_TITLE_FORMAT<CharT>,
				moduleFileNameView.value(),
				moduleVersionStringView.value());

			return std::basic_string_view<CharT>{a_buffer.data(), formatResult.size};
		}

		template <REX::win32_character CharT>
		[[nodiscard]]
		auto FormatMessageBody(
			std::span<CharT> a_buffer,
			REX::SourceLocation a_location,
			std::basic_string_view<CharT> a_format) noexcept
			-> std::expected<std::basic_string_view<CharT>, REX::SystemError>;

		template <>
		[[nodiscard]]
		auto FormatMessageBody(std::span<char> a_buffer, REX::SourceLocation a_location, std::string_view a_format)
			noexcept -> std::expected<std::string_view, REX::SystemError>
		{
			const auto relativeFilePath = GetRelativeFilePath(a_location.GetFilePath());

			const auto formatResult = REX::FormatToN(
				a_buffer.data(),
				static_cast<std::ptrdiff_t>(a_buffer.size()),
				MESSAGE_BODY_FORMAT<char>,
				relativeFilePath,
				a_location.GetFunctionName(),
				a_location.GetLineNumber(),
				a_format);

			return std::string_view{a_buffer.data(), formatResult.size};
		}

		template <>
		[[nodiscard]]
		auto FormatMessageBody(std::span<wchar_t> a_buffer, REX::SourceLocation a_location, std::wstring_view a_format)
			noexcept -> std::expected<std::wstring_view, REX::SystemError>
		{
			auto filePathBuffer = std::array<wchar_t, REX::W32::MAX_FNAME>();

			const auto filePathSize = REX::Utf8ToUtf16(a_location.GetFilePath(), filePathBuffer);
			if (filePathSize.has_value()) [[unlikely]] {
				return std::unexpected(filePathSize.error());
			}

			auto functionNameBuffer = std::array<wchar_t, REX::W32::MAX_FNAME>();

			const auto functionNameSize = REX::Utf8ToUtf16(a_location.GetFunctionName(), functionNameBuffer);
			if (!functionNameSize.has_value()) [[unlikely]] {
				return std::unexpected(functionNameSize.error());
			}

			const auto relativeFilePath =
				GetRelativeFilePath(std::wstring_view{filePathBuffer.data(), filePathSize.value()});

			const auto formatResult = REX::FormatToN(
				a_buffer.data(),
				static_cast<std::ptrdiff_t>(a_buffer.size()),
				MESSAGE_BODY_FORMAT<wchar_t>,
				relativeFilePath,
				std::wstring_view{functionNameBuffer.data(), functionNameSize.value()},
				a_location.GetLineNumber(),
				a_format);

			return std::wstring_view{a_buffer.data(), formatResult.size};
		}

		[[nodiscard]]
		constexpr auto GetMessageSeverityByLogLevel(REX::Logging::Level a_logLevel) noexcept -> MessageBoxFlags
		{
			switch (a_logLevel) {
				case REX::Logging::Level::Warning: {
					return MessageBoxFlags::MB_ICONWARNING;
				}
				case REX::Logging::Level::Error:
				case REX::Logging::Level::Critical: {
					return MessageBoxFlags::MB_ICONERROR;
				}
				default: {
					return MessageBoxFlags::MB_ICONINFORMATION;
				}
			}
		}
	}
}

namespace REX
{
	auto ShowBasicMessage(
		REX::Logging::Level a_logLevel,
		std::string_view a_title,
		std::string_view a_message,
		MessageBoxFlags a_messageFlags) noexcept -> MessageBoxResult
	{
		constexpr auto WINDOW_HANDLE = static_cast<REX::W32::HWND>(0);

		const auto messageBoxFlags = REX::EnumSet(a_messageFlags, Impl::GetMessageSeverityByLogLevel(a_logLevel));
		return static_cast<MessageBoxResult>(
			REX::W32::MessageBoxA(WINDOW_HANDLE, a_message.data(), a_title.data(), messageBoxFlags.get()));
	}

	auto ShowBasicMessage(
		REX::Logging::Level a_logLevel,
		std::wstring_view a_title,
		std::wstring_view a_message,
		MessageBoxFlags a_messageFlags) noexcept -> MessageBoxResult
	{
		constexpr auto WINDOW_HANDLE = static_cast<REX::W32::HWND>(0);

		const auto messageBoxFlags = REX::EnumSet(a_messageFlags, Impl::GetMessageSeverityByLogLevel(a_logLevel));
		return static_cast<MessageBoxResult>(
			REX::W32::MessageBoxW(WINDOW_HANDLE, a_message.data(), a_title.data(), messageBoxFlags.get()));
	}

	auto ShowBasicMessage(REX::Logging::Level a_logLevel, std::string_view a_title, std::string_view a_message) noexcept
		-> MessageBoxResult
	{
		return ShowBasicMessage(a_logLevel, a_title, a_message, Impl::DEFAULT_MESSAGE_FLAGS.get());
	}

	auto ShowBasicMessage(REX::Logging::Level a_logLevel, std::wstring_view a_title, std::wstring_view a_message)
		noexcept -> MessageBoxResult
	{
		return ShowBasicMessage(a_logLevel, a_title, a_message, Impl::DEFAULT_MESSAGE_FLAGS.get());
	}

	auto ShowBasicMessage(REX::Logging::Level a_logLevel, std::string_view a_message, MessageBoxFlags a_messageFlags)
		noexcept -> MessageBoxResult
	{
		auto titleBuffer = std::array<char, REX::TITLE_BUFFER_SIZE>();

		const auto messageTitle = Impl::FormatMessageTitle<char>(titleBuffer);
		if (!messageTitle.has_value()) [[unlikely]] {
			REX::Assert(false);
			return MessageBoxResult::IDABORT;
		}

		return ShowBasicMessage(a_logLevel, messageTitle.value(), a_message, a_messageFlags);
	}

	auto ShowBasicMessage(REX::Logging::Level a_logLevel, std::wstring_view a_message, MessageBoxFlags a_messageFlags)
		noexcept -> MessageBoxResult
	{
		auto titleBuffer = std::array<wchar_t, REX::TITLE_BUFFER_SIZE>();

		const auto messageTitle = Impl::FormatMessageTitle<wchar_t>(titleBuffer);
		if (!messageTitle.has_value()) [[unlikely]] {
			REX::Assert(false);
			return MessageBoxResult::IDABORT;
		}

		return ShowBasicMessage(a_logLevel, messageTitle.value(), a_message, a_messageFlags);
	}

	auto ShowBasicMessage(REX::Logging::Level a_logLevel, std::string_view a_message) noexcept -> MessageBoxResult
	{
		return ShowBasicMessage(a_logLevel, a_message, Impl::DEFAULT_MESSAGE_FLAGS.get());
	}

	auto ShowBasicMessage(REX::Logging::Level a_logLevel, std::wstring_view a_message) noexcept -> MessageBoxResult
	{
		return ShowBasicMessage(a_logLevel, a_message, Impl::DEFAULT_MESSAGE_FLAGS.get());
	}

	auto ShowSourceMessage(
		REX::Logging::Level a_logLevel,
		std::string_view a_format,
		MessageBoxFlags a_messageFlags,
		REX::SourceLocation a_location) noexcept -> MessageBoxResult
	{
		auto titleBuffer = std::array<char, REX::TITLE_BUFFER_SIZE>();

		const auto messageTitle = Impl::FormatMessageTitle<char>(titleBuffer);
		if (!messageTitle.has_value()) [[unlikely]] {
			REX::Assert(false);
			return MessageBoxResult::IDABORT;
		}

		auto messageBuffer = std::array<char, REX::MESSAGE_BUFFER_SIZE>();

		const auto messageBody = Impl::FormatMessageBody<char>(messageBuffer, a_location, a_format);
		if (!messageBody.has_value()) [[unlikely]] {
			REX::Assert(false);
			return MessageBoxResult::IDABORT;
		}

		return ShowBasicMessage(a_logLevel, messageTitle.value(), messageBody.value(), a_messageFlags);
	}

	auto ShowSourceMessage(
		REX::Logging::Level a_logLevel,
		std::wstring_view a_format,
		MessageBoxFlags a_messageFlags,
		REX::SourceLocation a_location) noexcept -> MessageBoxResult
	{
		auto titleBuffer = std::array<wchar_t, REX::TITLE_BUFFER_SIZE>();

		const auto messageTitle = Impl::FormatMessageTitle<wchar_t>(titleBuffer);
		if (!messageTitle.has_value()) [[unlikely]] {
			REX::Assert(false);
			return MessageBoxResult::IDABORT;
		}

		auto messageBuffer = std::array<wchar_t, REX::MESSAGE_BUFFER_SIZE>();

		const auto messageBody = Impl::FormatMessageBody<wchar_t>(messageBuffer, a_location, a_format);
		if (!messageBody.has_value()) [[unlikely]] {
			REX::Assert(false);
			return MessageBoxResult::IDABORT;
		}

		return ShowBasicMessage(a_logLevel, messageTitle.value(), messageBody.value(), a_messageFlags);
	}

	auto ShowSourceMessage(REX::Logging::Level a_logLevel, std::string_view a_format, REX::SourceLocation a_location)
		noexcept -> MessageBoxResult
	{
		return ShowSourceMessage(a_logLevel, a_format, Impl::DEFAULT_MESSAGE_FLAGS.get(), a_location);
	}

	auto ShowSourceMessage(REX::Logging::Level a_logLevel, std::wstring_view a_format, REX::SourceLocation a_location)
		noexcept -> MessageBoxResult
	{
		return ShowSourceMessage(a_logLevel, a_format, Impl::DEFAULT_MESSAGE_FLAGS.get(), a_location);
	}

	void Inform(std::string_view a_format, REX::SourceLocation a_location) noexcept
	{
		ShowSourceMessage(REX::Logging::Level::Information, a_format, Impl::DEFAULT_MESSAGE_FLAGS.get(), a_location);
	}

	void Inform(std::wstring_view a_format, REX::SourceLocation a_location) noexcept
	{
		ShowSourceMessage(REX::Logging::Level::Information, a_format, Impl::DEFAULT_MESSAGE_FLAGS.get(), a_location);
	}

	void Warn(std::string_view a_format, REX::SourceLocation a_location) noexcept
	{
		ShowSourceMessage(REX::Logging::Level::Warning, a_format, Impl::DEFAULT_MESSAGE_FLAGS.get(), a_location);
	}

	void Warn(std::wstring_view a_format, REX::SourceLocation a_location) noexcept
	{
		ShowSourceMessage(REX::Logging::Level::Warning, a_format, Impl::DEFAULT_MESSAGE_FLAGS.get(), a_location);
	}

	void Fail(std::string_view a_format, REX::SourceLocation a_location) noexcept
	{
		ShowSourceMessage(REX::Logging::Level::Critical, a_format, Impl::DEFAULT_MESSAGE_FLAGS.get(), a_location);

		REX::Terminate(EXIT_FAILURE);
	}

	void Fail(std::wstring_view a_format, REX::SourceLocation a_location) noexcept
	{
		ShowSourceMessage(REX::Logging::Level::Critical, a_format, Impl::DEFAULT_MESSAGE_FLAGS.get(), a_location);

		REX::Terminate(EXIT_FAILURE);
	}
}
