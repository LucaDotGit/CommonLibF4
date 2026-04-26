#include "REX/Message.hpp"

#include "REX/W32/CORE.hpp"
#include "REX/W32/KERNEL32.hpp"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/msvc_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>

namespace REX::Impl
{
	template <REX::win32_character CharT>
	static constexpr auto DIRECTORIES = std::array<std::basic_string_view<CharT>, 2>();

	template <>
	constexpr auto DIRECTORIES<char> = std::array{
		"include/"sv,
		"src/"sv
	};

	template <>
	constexpr auto DIRECTORIES<wchar_t> = std::array{
		L"include/"sv,
		L"src/"sv
	};

	template <REX::win32_character T>
	[[nodiscard]] static auto FormatHeaderImpl() noexcept -> std::expected<std::basic_string<T>, REX::SystemError>
	{
		try {
			auto buffer = std::vector<T>();
			buffer.reserve(REX::W32::MAX_PATH);
			buffer.resize(REX::W32::MAX_PATH / 2);

			auto fileNameLength = 0ui32;

			do {
				buffer.resize(buffer.size() * 2);

				if constexpr (std::same_as<T, char>) {
					fileNameLength = REX::W32::GetModuleFileNameA(
						REX::W32::GetCurrentModule(),
						buffer.data(),
						static_cast<std::uint32_t>(buffer.size()));
				}
				else {
					fileNameLength = REX::W32::GetModuleFileNameW(
						REX::W32::GetCurrentModule(),
						buffer.data(),
						static_cast<std::uint32_t>(buffer.size()));
				}

				if (fileNameLength == 0) {
					return std::unexpected(REX::GetCurrentSystemError());
				}
			}
			while (fileNameLength != 0 && fileNameLength == buffer.size() && buffer.size() <= std::numeric_limits<std::uint32_t>::max());

			if (fileNameLength == 0 || fileNameLength == buffer.size()) {
				return {};
			}

			const auto path = std::filesystem::path(buffer.data(), buffer.data() + fileNameLength, std::filesystem::path::generic_format);
			return path.filename().generic_string<T>();
		}
		catch ([[maybe_unused]] const std::bad_alloc& error) {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::not_enough_memory));
		}
	}

	template <>
	auto FormatHeader() noexcept -> std::expected<std::string, REX::SystemError>
	{
		return FormatHeaderImpl<char>();
	}

	template <>
	auto FormatHeader() noexcept -> std::expected<std::wstring, REX::SystemError>
	{
		return FormatHeaderImpl<wchar_t>();
	}

	template <REX::win32_character T>
	[[nodiscard]] static auto FormatBodyImpl(std::source_location a_location, std::basic_string_view<T> a_format) noexcept -> std::expected<std::basic_string<T>, REX::SystemError>
	{
		try {
			const auto filePath = std::filesystem::path(a_location.file_name(), std::filesystem::path::generic_format);
			const auto filePathString = filePath.generic_string<T>();

			auto filePathView = std::basic_string_view<T>(filePathString.data(), filePathString.size());
			auto filePosition = std::basic_string<T>::npos;
			auto fileOffset = static_cast<std::size_t>(0);

			for (const auto& directory : DIRECTORIES<T>) {
				filePosition = filePathView.find(directory);
				if (filePosition != std::basic_string<T>::npos) {
					fileOffset = directory.size();
					break;
				}
			}

			if (filePosition != std::basic_string<T>::npos) {
				filePathView = filePathView.substr(filePosition + fileOffset);
			}

			if constexpr (std::same_as<T, char>) {
				return Format(R"("{}" ({}): {})"sv,
					filePathView, a_location.line(), a_format);
			}
			else {
				return Format(LR"("{}" ({}): {})"sv,
					filePathView, a_location.line(), a_format);
			}
		}
		catch ([[maybe_unused]] const std::bad_alloc& error) {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::not_enough_memory));
		}
	}

	template <>
	auto FormatBody(std::source_location a_location, std::string_view a_format) noexcept -> std::expected<std::string, REX::SystemError>
	{
		return FormatBodyImpl<char>(a_location, a_format);
	}

	template <>
	auto FormatBody(std::source_location a_location, std::wstring_view a_format) noexcept -> std::expected<std::wstring, REX::SystemError>
	{
		return FormatBodyImpl<wchar_t>(a_location, a_format);
	}

	REX::W32::MB GetMessageSeverityByLogLevel(LogLevel a_logLevel) noexcept
	{
		switch (a_logLevel) {
			case LogLevel::kWarning: {
				return REX::W32::MB::MB_ICONWARNING;
			}
			case LogLevel::kError:
			case LogLevel::kCritical: {
				return REX::W32::MB::MB_ICONERROR;
			}
			default: {
				return REX::W32::MB::MB_ICONINFORMATION;
			}
		}
	}

	REX::W32::MBID ShowBasicMessage(LogLevel a_logLevel, REX::zstring_view a_title, REX::zstring_view a_message, REX::W32::MB a_messageFlags) noexcept
	{
		const auto windowHandle = static_cast<REX::W32::HWND>(0);
		const auto messageBoxFlags = REX::EnumSet(a_messageFlags, GetMessageSeverityByLogLevel(a_logLevel));

		return static_cast<REX::W32::MBID>(REX::W32::MessageBoxA(
			windowHandle,
			a_message.data(),
			a_title.data(),
			messageBoxFlags.get()));
	}

	REX::W32::MBID ShowBasicMessage(LogLevel a_logLevel, REX::zwstring_view a_title, REX::zwstring_view a_message, REX::W32::MB a_messageFlags) noexcept
	{
		const auto windowHandle = static_cast<REX::W32::HWND>(0);
		const auto messageBoxFlags = REX::EnumSet(a_messageFlags, GetMessageSeverityByLogLevel(a_logLevel));

		return static_cast<REX::W32::MBID>(REX::W32::MessageBoxW(
			windowHandle,
			a_message.data(),
			a_title.data(),
			messageBoxFlags.get()));
	}

	REX::W32::MBID ShowSourceMessage(LogLevel a_logLevel, std::source_location a_location, std::string_view a_format, REX::W32::MB a_messageFlags) noexcept
	{
		const auto messageBody = FormatBody(a_location, a_format);
		if (!messageBody) [[unlikely]] {
			REX::QuickFail("Failed to format source message body."sv);
		}

		const auto messageHeader = FormatHeader<char>();
		if (!messageHeader) [[unlikely]] {
			REX::QuickFail("Failed to format source message header."sv);
		}

		Log(a_logLevel, a_location, a_format);

		return Impl::ShowBasicMessage(a_logLevel, *messageHeader, *messageBody, a_messageFlags);
	}

	REX::W32::MBID ShowSourceMessage(LogLevel a_logLevel, std::source_location a_location, std::wstring_view a_format, REX::W32::MB a_messageFlags) noexcept
	{
		const auto messageBody = FormatBody(a_location, a_format);
		if (!messageBody) [[unlikely]] {
			REX::QuickFail("Failed to format wide source message body."sv);
		}

		const auto messageHeader = FormatHeader<wchar_t>();
		if (!messageHeader) [[unlikely]] {
			REX::QuickFail("Failed to format wide source message header."sv);
		}

		Log(a_logLevel, a_location, a_format);

		return Impl::ShowBasicMessage(a_logLevel, *messageHeader, *messageBody, a_messageFlags);
	}

	void Inform(std::source_location a_location, std::string_view a_format) noexcept
	{
		Impl::ShowSourceMessage(LogLevel::kInformation, a_location, a_format);
	}

	void Inform(std::source_location a_location, std::wstring_view a_format) noexcept
	{
		Impl::ShowSourceMessage(LogLevel::kInformation, a_location, a_format);
	}

	void Warn(std::source_location a_location, std::string_view a_format) noexcept
	{
		Impl::ShowSourceMessage(LogLevel::kWarning, a_location, a_format);
	}

	void Warn(std::source_location a_location, std::wstring_view a_format) noexcept
	{
		Impl::ShowSourceMessage(LogLevel::kWarning, a_location, a_format);
	}

	void Fail(std::source_location a_location, std::string_view a_format) noexcept
	{
		Impl::ShowSourceMessage(LogLevel::kCritical, a_location, a_format);

		if (REX::W32::IsDebuggerPresent()) {
			REX::W32::DebugBreak();
		}

		REX::W32::TerminateCurrentProcess(EXIT_FAILURE);
	}

	void Fail(std::source_location a_location, std::wstring_view a_format) noexcept
	{
		Impl::ShowSourceMessage(LogLevel::kCritical, a_location, a_format);

		if (REX::W32::IsDebuggerPresent()) {
			REX::W32::DebugBreak();
		}

		REX::W32::TerminateCurrentProcess(EXIT_FAILURE);
	}
}