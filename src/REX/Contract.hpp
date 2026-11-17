#pragma once

#include "REX/Concepts.hpp"
#include "REX/Formatting.hpp"
#include "REX/SourceLocation.hpp"

#if (NDEBUG == 1)
#include "REX/Macros.hpp"
#endif

namespace REX::Impl
{
	[[noreturn]]
	void EnsureFail(std::string_view a_format, REX::SourceLocation a_location) noexcept;
	[[noreturn]]
	void EnsureFail(std::wstring_view a_format, REX::SourceLocation a_location) noexcept;

#if (NDEBUG == 0)
	[[noreturn]]
	void AssumeFail(std::string_view a_format, REX::SourceLocation a_location) noexcept;
	[[noreturn]]
	void AssumeFail(std::wstring_view a_format, REX::SourceLocation a_location) noexcept;
#endif

#if (NDEBUG == 0)
	void AssertFail(std::string_view a_format, REX::SourceLocation a_location) noexcept;
	void AssertFail(std::wstring_view a_format, REX::SourceLocation a_location) noexcept;
#endif
}

namespace REX
{
	constexpr void Ensure(bool a_condition, REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept
	{
		if (a_condition) [[likely]] {
			return;
		}

		Impl::EnsureFail("Ensurance failed."sv, a_location);
	}

	constexpr void Ensure(
		bool a_condition,
		std::string_view a_format,
		REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept
	{
		if (a_condition) [[likely]] {
			return;
		}

		Impl::EnsureFail(a_format, a_location);
	}

	constexpr void Ensure(
		bool a_condition,
		std::wstring_view a_format,
		REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept
	{
		if (a_condition) [[likely]] {
			return;
		}

		Impl::EnsureFail(a_format, a_location);
	}

	template <class... Args>
	constexpr void Ensure(bool a_condition, REX::FormatStringLocation<Args...> a_formatLocation, Args&&... a_args)
		noexcept
		requires((REX::formattable<Args, char> && ...))
	{
		if (a_condition) [[likely]] {
			return;
		}

		auto formatBuffer = std::array<char, REX::MESSAGE_BUFFER_SIZE>();
		const auto formatResult = REX::FormatToN(
			formatBuffer.data(),
			static_cast<std::ptrdiff_t>(formatBuffer.size()),
			a_formatLocation.format(),
			std::forward<Args>(a_args)...);

		Impl::EnsureFail(std::string_view{formatBuffer.data(), formatResult.size}, a_formatLocation.location());
	}

	template <class... Args>
	constexpr void Ensure(bool a_condition, REX::WFormatStringLocation<Args...> a_formatLocation, Args&&... a_args)
		noexcept
		requires((REX::formattable<Args, wchar_t> && ...))
	{
		if (a_condition) [[likely]] {
			return;
		}

		auto formatBuffer = std::array<wchar_t, REX::MESSAGE_BUFFER_SIZE>();
		const auto formatResult = REX::FormatToN(
			formatBuffer.data(),
			static_cast<std::ptrdiff_t>(formatBuffer.size()),
			a_formatLocation.format(),
			std::forward<Args>(a_args)...);

		Impl::EnsureFail(std::wstring_view{formatBuffer.data(), formatResult.size}, a_formatLocation.location());
	}

#if (NDEBUG == 0)
	constexpr void Assume(bool a_condition, REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept
	{
		if (a_condition) [[likely]] {
			return;
		}

		Impl::AssumeFail("Assumption failed."sv, a_location);
	}

	constexpr void Assume(
		bool a_condition,
		std::string_view a_format,
		REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept
	{
		if (a_condition) [[likely]] {
			return;
		}

		Impl::AssumeFail(a_format, a_location);
	}

	constexpr void Assume(
		bool a_condition,
		std::wstring_view a_format,
		REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept
	{
		if (a_condition) [[likely]] {
			return;
		}

		Impl::AssumeFail(a_format, a_location);
	}

	template <class... Args>
	constexpr void Assume(bool a_condition, REX::FormatStringLocation<Args...> a_formatLocation, Args&&... a_args)
		noexcept
		requires((REX::formattable<Args, char> && ...))
	{
		if (a_condition) [[likely]] {
			return;
		}

		auto formatBuffer = std::array<char, REX::MESSAGE_BUFFER_SIZE>();
		const auto formatResult = REX::FormatToN(
			formatBuffer.data(),
			static_cast<std::ptrdiff_t>(formatBuffer.size()),
			a_formatLocation.format(),
			std::forward<Args>(a_args)...);

		Impl::AssumeFail(std::string_view{formatBuffer.data(), formatResult.size}, a_formatLocation.location());
	}

	template <class... Args>
	constexpr void Assume(bool a_condition, REX::WFormatStringLocation<Args...> a_formatLocation, Args&&... a_args)
		noexcept
		requires((REX::formattable<Args, wchar_t> && ...))
	{
		if (a_condition) [[likely]] {
			return;
		}

		auto formatBuffer = std::array<wchar_t, REX::MESSAGE_BUFFER_SIZE>();
		const auto formatResult = REX::FormatToN(
			formatBuffer.data(),
			static_cast<std::ptrdiff_t>(formatBuffer.size()),
			a_formatLocation.format(),
			std::forward<Args>(a_args)...);

		Impl::AssumeFail(std::wstring_view{formatBuffer.data(), formatResult.size}, a_formatLocation.location());
	}
#else
	[[REX_ALWAYS_INLINE]]
	constexpr void Assume(
		bool a_condition,
		[[maybe_unused]] REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept
	{
		[[assume(a_condition)]];
	}

	[[REX_ALWAYS_INLINE]]
	constexpr void Assume(
		bool a_condition,
		[[maybe_unused]] std::string_view a_format,
		[[maybe_unused]] REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept
	{
		[[assume(a_condition)]];
	}

	[[REX_ALWAYS_INLINE]]
	constexpr void Assume(
		bool a_condition,
		[[maybe_unused]] std::wstring_view a_format,
		[[maybe_unused]] REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept
	{
		[[assume(a_condition)]];
	}

	template <class... Args>
	[[REX_ALWAYS_INLINE]]
	constexpr void Assume(
		bool a_condition,
		[[maybe_unused]] REX::FormatStringLocation<Args...> a_formatLocation,
		[[maybe_unused]] Args&&... a_args) noexcept
		requires((REX::formattable<Args, char> && ...))
	{
		[[assume(a_condition)]];
	}

	template <class... Args>
	[[REX_ALWAYS_INLINE]]
	constexpr void Assume(
		bool a_condition,
		[[maybe_unused]] REX::WFormatStringLocation<Args...> a_formatLocation,
		[[maybe_unused]] Args&&... a_args) noexcept
		requires((REX::formattable<Args, wchar_t> && ...))
	{
		[[assume(a_condition)]];
	}
#endif

#if (NDEBUG == 0)
	constexpr void Assert(bool a_condition, REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept
	{
		if (a_condition) [[likely]] {
			return;
		}

		Impl::AssertFail("Assertion failed."sv, a_location);
	}

	constexpr void Assert(
		bool a_condition,
		std::string_view a_format,
		REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept
	{
		if (a_condition) [[likely]] {
			return;
		}

		Impl::AssertFail(a_format, a_location);
	}

	constexpr void Assert(
		bool a_condition,
		std::wstring_view a_format,
		REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept
	{
		if (a_condition) [[likely]] {
			return;
		}

		Impl::AssertFail(a_format, a_location);
	}

	template <class... Args>
	constexpr void Assert(bool a_condition, REX::FormatStringLocation<Args...> a_formatLocation, Args&&... a_args)
		noexcept
		requires((REX::formattable<Args, char> && ...))
	{
		if (a_condition) [[likely]] {
			return;
		}

		auto formatBuffer = std::array<char, REX::MESSAGE_BUFFER_SIZE>();
		const auto formatResult = REX::FormatToN(
			formatBuffer.data(),
			static_cast<std::ptrdiff_t>(formatBuffer.size()),
			a_formatLocation.format(),
			std::forward<Args>(a_args)...);

		Impl::AssertFail(std::string_view{formatBuffer.data(), formatResult.size}, a_formatLocation.location());
	}

	template <class... Args>
	constexpr void Assert(bool a_condition, REX::WFormatStringLocation<Args...> a_formatLocation, Args&&... a_args)
		noexcept
		requires((REX::formattable<Args, wchar_t> && ...))
	{
		if (a_condition) [[likely]] {
			return;
		}

		auto formatBuffer = std::array<wchar_t, REX::MESSAGE_BUFFER_SIZE>();
		const auto formatResult = REX::FormatToN(
			formatBuffer.data(),
			static_cast<std::ptrdiff_t>(formatBuffer.size()),
			a_formatLocation.format(),
			std::forward<Args>(a_args)...);

		Impl::AssertFail(std::wstring_view{formatBuffer.data(), formatResult.size}, a_formatLocation.location());
	}
#else
	constexpr void Assert(
		[[maybe_unused]] bool a_condition,
		[[maybe_unused]] REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept
	{
		return;
	}

	constexpr void Assert(
		[[maybe_unused]] bool a_condition,
		[[maybe_unused]] std::string_view a_format,
		[[maybe_unused]] REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept
	{
		return;
	}

	constexpr void Assert(
		[[maybe_unused]] bool a_condition,
		[[maybe_unused]] std::wstring_view a_format,
		[[maybe_unused]] REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept
	{
		return;
	}

	template <class... Args>
	constexpr void Assert(
		[[maybe_unused]] bool a_condition,
		[[maybe_unused]] REX::FormatStringLocation<Args...> a_formatLocation,
		[[maybe_unused]] Args&&... a_args) noexcept
		requires((REX::formattable<Args, char> && ...))
	{
		return;
	}

	template <class... Args>
	constexpr void Assert(
		[[maybe_unused]] bool a_condition,
		[[maybe_unused]] REX::WFormatStringLocation<Args...> a_formatLocation,
		[[maybe_unused]] Args&&... a_args) noexcept
		requires((REX::formattable<Args, wchar_t> && ...))
	{
		return;
	}
#endif
}
