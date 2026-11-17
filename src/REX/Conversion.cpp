#include "REX/Conversion.hpp"

#include "REX/Casting.hpp"
#include "REX/Concepts.hpp"
#include "REX/Container.hpp"
#include "REX/Error.hpp"
#include "REX/W32/KERNEL32.hpp"

namespace REX::Impl
{
	namespace
	{
		template <REX::character To, REX::character From>
		[[nodiscard]]
		auto Utf8ToUtf16(std::basic_string_view<From> a_source, std::span<To> a_target) noexcept
			-> std::expected<std::size_t, REX::SystemError>
		{
			if (a_source.empty()) {
				return 0;
			}

			constexpr auto FLAGS = static_cast<std::uint32_t>(0);

			const auto writeSize = REX::W32::MultiByteToWideChar(
				REX::W32::CP_UTF8,
				FLAGS,
				REX::CheckedReinterpretCast<const char*>(a_source.data()),
				static_cast<std::int32_t>(a_source.size()),
				REX::CheckedReinterpretCast<wchar_t*>(a_target.data()),
				static_cast<std::int32_t>(a_target.size()));
			if (writeSize == 0) [[unlikely]] {
				return std::unexpected(REX::GetCurrentSystemError());
			}

			return static_cast<std::size_t>(writeSize);
		}

		template <REX::character To, REX::character From>
		[[nodiscard]]
		auto Utf16ToUtf8(std::basic_string_view<From> a_source, std::span<To> a_target) noexcept
			-> std::expected<std::size_t, REX::SystemError>
		{
			if (a_source.empty()) {
				return 0;
			}

			constexpr auto FLAGS = static_cast<std::uint32_t>(0);
			constexpr auto DEFAULT_VALUE = static_cast<const char*>(nullptr);
			constexpr auto DEFAULT_SIZE = static_cast<std::int32_t*>(nullptr);

			const auto writeSize = REX::W32::WideCharToMultiByte(
				REX::W32::CP_UTF8,
				FLAGS,
				REX::CheckedReinterpretCast<const wchar_t*>(a_source.data()),
				static_cast<std::int32_t>(a_source.size()),
				REX::CheckedReinterpretCast<char*>(a_target.data()),
				static_cast<std::int32_t>(a_target.size()),
				DEFAULT_VALUE,
				DEFAULT_SIZE);
			if (writeSize == 0) [[unlikely]] {
				return std::unexpected(REX::GetCurrentSystemError());
			}

			return static_cast<std::size_t>(writeSize);
		}

		template <REX::character To, REX::character From>
		[[nodiscard]]
		auto Utf8ToUtf16(std::basic_string_view<From> a_source) noexcept
			-> std::expected<std::basic_string<To>, REX::SystemError>
		{
			if (a_source.empty()) {
				return std::basic_string<To>();
			}

			const auto readSize = Utf8ToUtf16<To>(a_source, {});
			if (!readSize.has_value()) [[unlikely]] {
				return std::unexpected(REX::GetCurrentSystemError());
			}

			auto result = std::basic_string<To>();

			try {
				REX::ResizeForOverwrite(result, readSize.value());
			}
			catch (const std::bad_alloc& error) {
				std::ignore = error;
				return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::not_enough_memory));
			}

			const auto writeSize = Utf8ToUtf16(a_source, std::span{result.data(), result.size()});
			if (!writeSize.has_value()) [[unlikely]] {
				return std::unexpected(REX::GetCurrentSystemError());
			}

			if (readSize.value() != writeSize.value()) [[unlikely]] {
				return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
			}

			return result;
		}

		template <REX::character To, REX::character From>
		[[nodiscard]]
		auto Utf16ToUtf8(std::basic_string_view<From> a_source) noexcept
			-> std::expected<std::basic_string<To>, REX::SystemError>
		{
			if (a_source.empty()) {
				return std::basic_string<To>();
			}

			const auto readSize = Utf16ToUtf8<To>(a_source, {});
			if (!readSize.has_value()) [[unlikely]] {
				return std::unexpected(REX::GetCurrentSystemError());
			}

			auto result = std::basic_string<To>();

			try {
				REX::ResizeForOverwrite(result, readSize.value());
			}
			catch (const std::bad_alloc& error) {
				std::ignore = error;
				return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::not_enough_memory));
			}

			const auto writeSize = Utf16ToUtf8(a_source, std::span{result.data(), result.size()});
			if (!writeSize.has_value()) [[unlikely]] {
				return std::unexpected(REX::GetCurrentSystemError());
			}

			if (readSize.value() != writeSize.value()) [[unlikely]] {
				return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::invalid_argument));
			}

			return result;
		}
	}
}

namespace REX
{
	auto Utf8ToUtf16(std::string_view a_source, std::span<wchar_t> a_buffer) noexcept
		-> std::expected<std::size_t, REX::SystemError>
	{
		return Impl::Utf8ToUtf16(a_source, a_buffer);
	}

	auto Utf8ToUtf16(std::u8string_view a_source, std::span<char16_t> a_buffer) noexcept
		-> std::expected<std::size_t, REX::SystemError>
	{
		return Impl::Utf8ToUtf16(a_source, a_buffer);
	}

	auto Utf16ToUtf8(std::wstring_view a_source, std::span<char> a_buffer) noexcept
		-> std::expected<std::size_t, REX::SystemError>
	{
		return Impl::Utf16ToUtf8(a_source, a_buffer);
	}

	auto Utf16ToUtf8(std::u16string_view a_source, std::span<char8_t> a_buffer) noexcept
		-> std::expected<std::size_t, REX::SystemError>
	{
		return Impl::Utf16ToUtf8(a_source, a_buffer);
	}

	auto Utf8ToUtf16(std::string_view a_source) noexcept -> std::expected<std::wstring, REX::SystemError>
	{
		return Impl::Utf8ToUtf16<wchar_t>(a_source);
	}

	auto Utf8ToUtf16(std::u8string_view a_source) noexcept -> std::expected<std::u16string, REX::SystemError>
	{
		return Impl::Utf8ToUtf16<char16_t>(a_source);
	}

	auto Utf16ToUtf8(std::wstring_view a_source) noexcept -> std::expected<std::string, REX::SystemError>
	{
		return Impl::Utf16ToUtf8<char>(a_source);
	}

	auto Utf16ToUtf8(std::u16string_view a_source) noexcept -> std::expected<std::u8string, REX::SystemError>
	{
		return Impl::Utf16ToUtf8<char8_t>(a_source);
	}
}
