#pragma once

#include "REX/Format.hpp"
#include "REX/SourceLocation.hpp"

namespace REX::Impl
{
	void Ensure(REX::SourceLocation a_location, std::string_view a_format) noexcept;
	void Ensure(REX::SourceLocation a_location, std::wstring_view a_format) noexcept;

#if NDEBUG == 0
	void Assume(REX::SourceLocation a_location, std::string_view a_format) noexcept;
	void Assume(REX::SourceLocation a_location, std::wstring_view a_format) noexcept;
#endif

#if NDEBUG == 0
	void Assert(REX::SourceLocation a_location, std::string_view a_format) noexcept;
	void Assert(REX::SourceLocation a_location, std::wstring_view a_format) noexcept;
#endif
}

namespace REX
{
	constexpr void Ensure(bool a_condition, REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept
	{
		if (a_condition) [[likely]] {
			return;
		}

		Impl::Ensure(a_location, "Ensurance failed."sv);
	}

	constexpr void Ensure(bool a_condition, std::string_view a_format, REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept
	{
		if (a_condition) [[likely]] {
			return;
		}

		Impl::Ensure(a_location, a_format);
	}

	constexpr void Ensure(bool a_condition, std::wstring_view a_format, REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept
	{
		if (a_condition) [[likely]] {
			return;
		}

		Impl::Ensure(a_location, a_format);
	}

	template <class... Args>
	constexpr void Ensure(bool a_condition, REX::FormatStringLocation<Args...> a_formatLocation, Args&&... a_args) noexcept
		requires((REX::formattable<Args, char> && ...))
	{
		if (a_condition) [[likely]] {
			return;
		}

		const auto formatData = REX::FixedFormat(a_formatLocation.format(), std::forward<Args>(a_args)...);
		Impl::Ensure(a_formatLocation.location(), std::string_view{ formatData.buffer.data(), formatData.size });
	}

	template <class... Args>
	constexpr void Ensure(bool a_condition, REX::WFormatStringLocation<Args...> a_formatLocation, Args&&... a_args) noexcept
		requires((REX::formattable<Args, wchar_t> && ...))
	{
		if (a_condition) [[likely]] {
			return;
		}

		const auto formatData = REX::FixedFormat(a_formatLocation.format(), std::forward<Args>(a_args)...);
		Impl::Ensure(a_formatLocation.location(), std::wstring_view{ formatData.buffer.data(), formatData.size });
	}

#if NDEBUG == 0
	constexpr void Assume(bool a_condition, REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept
	{
		if (a_condition) [[likely]] {
			return;
		}

		Impl::Assume(a_location, "Assumption failed."sv);
	}

	constexpr void Assume(bool a_condition, std::string_view a_format, REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept
	{
		if (a_condition) [[likely]] {
			return;
		}

		Impl::Assume(a_location, a_format);
	}

	constexpr void Assume(bool a_condition, std::wstring_view a_format, REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept
	{
		if (a_condition) [[likely]] {
			return;
		}

		Impl::Assume(a_location, a_format);
	}

	template <class... Args>
	constexpr void Assume(bool a_condition, REX::FormatStringLocation<Args...> a_formatLocation, Args&&... a_args) noexcept
		requires((REX::formattable<Args, char> && ...))
	{
		if (a_condition) [[likely]] {
			return;
		}

		const auto formatData = REX::FixedFormat(a_formatLocation.format(), std::forward<Args>(a_args)...);
		Impl::Assume(a_formatLocation.location(), std::string_view{ formatData.buffer.data(), formatData.size });
	}

	template <class... Args>
	constexpr void Assume(bool a_condition, REX::WFormatStringLocation<Args...> a_formatLocation, Args&&... a_args) noexcept
		requires((REX::formattable<Args, wchar_t> && ...))
	{
		if (a_condition) [[likely]] {
			return;
		}

		const auto formatData = REX::FixedFormat(a_formatLocation.format(), std::forward<Args>(a_args)...);
		Impl::Assume(a_formatLocation.location(), std::wstring_view{ formatData.buffer.data(), formatData.size });
	}
#else
	__forceinline constexpr void Assume(bool a_condition, [[maybe_unused]] REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept
	{
		[[assume(a_condition)]];
	}

	__forceinline constexpr void Assume(bool a_condition, [[maybe_unused]] std::string_view a_format, [[maybe_unused]] REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept
	{
		[[assume(a_condition)]];
	}

	__forceinline constexpr void Assume(bool a_condition, [[maybe_unused]] std::wstring_view a_format, [[maybe_unused]] REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept
	{
		[[assume(a_condition)]];
	}

	template <class... Args>
	__forceinline constexpr void Assume(bool a_condition, [[maybe_unused]] REX::FormatStringLocation<Args...> a_formatLocation, [[maybe_unused]] Args&&... a_args) noexcept
		requires((REX::formattable<Args, char> && ...))
	{
		[[assume(a_condition)]];
	}

	template <class... Args>
	__forceinline constexpr void Assume(bool a_condition, [[maybe_unused]] REX::WFormatStringLocation<Args...> a_formatLocation, [[maybe_unused]] Args&&... a_args) noexcept
		requires((REX::formattable<Args, wchar_t> && ...))
	{
		[[assume(a_condition)]];
	}
#endif

#if NDEBUG == 0
	constexpr void Assert(bool a_condition, REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept
	{
		if (a_condition) [[likely]] {
			return;
		}

		Impl::Assert(a_location, "Assertion failed."sv);
	}

	constexpr void Assert(bool a_condition, std::string_view a_format, REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept
	{
		if (a_condition) [[likely]] {
			return;
		}

		Impl::Assert(a_location, a_format);
	}

	constexpr void Assert(bool a_condition, std::wstring_view a_format, REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept
	{
		if (a_condition) [[likely]] {
			return;
		}

		Impl::Assert(a_location, a_format);
	}

	template <class... Args>
	constexpr void Assert(bool a_condition, REX::FormatStringLocation<Args...> a_formatLocation, Args&&... a_args) noexcept
		requires((REX::formattable<Args, char> && ...))
	{
		if (a_condition) [[likely]] {
			return;
		}

		const auto formatData = REX::FixedFormat(a_formatLocation.format(), std::forward<Args>(a_args)...);
		Impl::Assert(a_formatLocation.location(), std::string_view{ formatData.buffer.data(), formatData.size });
	}

	template <class... Args>
	constexpr void Assert(bool a_condition, REX::WFormatStringLocation<Args...> a_formatLocation, Args&&... a_args) noexcept
		requires((REX::formattable<Args, wchar_t> && ...))
	{
		if (a_condition) [[likely]] {
			return;
		}

		const auto formatData = REX::FixedFormat(a_formatLocation.format(), std::forward<Args>(a_args)...);
		Impl::Assert(a_formatLocation.location(), std::wstring_view{ formatData.buffer.data(), formatData.size });
	}
#else
	constexpr void Assert([[maybe_unused]] bool a_condition, [[maybe_unused]] REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept
	{
		return;
	}

	constexpr void Assert([[maybe_unused]] bool a_condition, [[maybe_unused]] std::string_view a_format, [[maybe_unused]] REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept
	{
		return;
	}

	constexpr void Assert([[maybe_unused]] bool a_condition, [[maybe_unused]] std::wstring_view a_format, [[maybe_unused]] REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept
	{
		return;
	}

	template <class... Args>
	constexpr void Assert([[maybe_unused]] bool a_condition, [[maybe_unused]] REX::FormatStringLocation<Args...> a_formatLocation, [[maybe_unused]] Args&&... a_args) noexcept
		requires((REX::formattable<Args, char> && ...))
	{
		return;
	}

	template <class... Args>
	constexpr void Assert([[maybe_unused]] bool a_condition, [[maybe_unused]] REX::WFormatStringLocation<Args...> a_formatLocation, [[maybe_unused]] Args&&... a_args) noexcept
		requires((REX::formattable<Args, wchar_t> && ...))
	{
		return;
	}
#endif
}
