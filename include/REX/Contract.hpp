#pragma once

#include "REX/Format.hpp"
#include "REX/ZString.hpp"

namespace REX::Impl
{
	[[noreturn]] void QuickFail(std::string_view a_format) noexcept;
	[[noreturn]] void QuickFail(std::wstring_view a_format) noexcept;
}

namespace REX
{
	[[noreturn]] inline void QuickFail(REX::zstring_view a_format) noexcept
	{
		Impl::QuickFail(a_format);
	}

	[[noreturn]] inline void QuickFail(REX::zwstring_view a_format) noexcept
	{
		Impl::QuickFail(a_format);
	}

	[[noreturn]] inline void AllocationFail() noexcept
	{
		Impl::QuickFail("The application failed to allocate memory."sv);
	}

	[[noreturn]] inline void AllocationFail(REX::zstring_view a_format) noexcept
	{
		Impl::QuickFail(a_format);
	}

	[[noreturn]] inline void AllocationFail(REX::zwstring_view a_format) noexcept
	{
		Impl::QuickFail(a_format);
	}

	[[noreturn]] inline void DeallocationFail() noexcept
	{
		Impl::QuickFail("The application failed to deallocate memory."sv);
	}

	[[noreturn]] inline void DeallocationFail(REX::zstring_view a_format) noexcept
	{
		Impl::QuickFail(a_format);
	}

	[[noreturn]] inline void DeallocationFail(REX::zwstring_view a_format) noexcept
	{
		Impl::QuickFail(a_format);
	}
}

namespace REX::Impl
{
	void Ensure(std::source_location a_location, std::string_view a_format) noexcept;
	void Ensure(std::source_location a_location, std::wstring_view a_format) noexcept;

#if NDEBUG == 0
	void Assume(std::source_location a_location, std::string_view a_format) noexcept;
	void Assume(std::source_location a_location, std::wstring_view a_format) noexcept;
#endif

#if NDEBUG == 0
	void Assert(std::source_location a_location, std::string_view a_format) noexcept;
	void Assert(std::source_location a_location, std::wstring_view a_format) noexcept;
#endif
}

namespace REX
{
	constexpr void Ensure(bool a_condition, std::source_location a_location = std::source_location::current()) noexcept
	{
		if (a_condition) [[likely]] {
			return;
		}

		Impl::Ensure(a_location, "Ensurance failed."sv);
	}

	constexpr void Ensure(bool a_condition, std::string_view a_format, std::source_location a_location = std::source_location::current()) noexcept
	{
		if (a_condition) [[likely]] {
			return;
		}

		Impl::Ensure(a_location, a_format);
	}

	constexpr void Ensure(bool a_condition, std::wstring_view a_format, std::source_location a_location = std::source_location::current()) noexcept
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

		try {
			Impl::Ensure(a_formatLocation.location(), REX::Format(a_formatLocation.format(), std::forward<Args>(a_args)...));
		}
		catch ([[maybe_unused]] const std::bad_alloc& error) {
			REX::AllocationFail();
		}
	}

	template <class... Args>
	constexpr void Ensure(bool a_condition, REX::WFormatStringLocation<Args...> a_formatLocation, Args&&... a_args) noexcept
		requires((REX::formattable<Args, wchar_t> && ...))
	{
		if (a_condition) [[likely]] {
			return;
		}

		try {
			Impl::Ensure(a_formatLocation.location(), REX::Format(a_formatLocation.format(), std::forward<Args>(a_args)...));
		}
		catch ([[maybe_unused]] const std::bad_alloc& error) {
			REX::AllocationFail();
		}
	}

#if NDEBUG == 0
	constexpr void Assume(bool a_condition, std::source_location a_location = std::source_location::current()) noexcept
	{
		if (a_condition) [[likely]] {
			return;
		}

		Impl::Assume(a_location, "Assumption failed."sv);
	}

	constexpr void Assume(bool a_condition, std::string_view a_format, std::source_location a_location = std::source_location::current()) noexcept
	{
		if (a_condition) [[likely]] {
			return;
		}

		Impl::Assume(a_location, a_format);
	}

	constexpr void Assume(bool a_condition, std::wstring_view a_format, std::source_location a_location = std::source_location::current()) noexcept
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

		try {
			Impl::Assume(a_formatLocation.location(), REX::Format(a_formatLocation.format(), std::forward<Args>(a_args)...));
		}
		catch ([[maybe_unused]] const std::bad_alloc& error) {
			REX::AllocationFail();
		}
	}

	template <class... Args>
	constexpr void Assume(bool a_condition, REX::WFormatStringLocation<Args...> a_formatLocation, Args&&... a_args) noexcept
		requires((REX::formattable<Args, wchar_t> && ...))
	{
		if (a_condition) [[likely]] {
			return;
		}

		try {
			Impl::Assume(a_formatLocation.location(), REX::Format(a_formatLocation.format(), std::forward<Args>(a_args)...));
		}
		catch ([[maybe_unused]] const std::bad_alloc& error) {
			REX::AllocationFail();
		}
	}
#else
	__forceinline constexpr void Assume(bool a_condition, [[maybe_unused]] std::source_location a_location = std::source_location::current()) noexcept
	{
		[[assume(a_condition)]];
	}

	__forceinline constexpr void Assume(bool a_condition, [[maybe_unused]] std::string_view a_format, [[maybe_unused]] std::source_location a_location = std::source_location::current()) noexcept
	{
		[[assume(a_condition)]];
	}

	__forceinline constexpr void Assume(bool a_condition, [[maybe_unused]] std::wstring_view a_format, [[maybe_unused]] std::source_location a_location = std::source_location::current()) noexcept
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
	constexpr void Assert(bool a_condition, std::source_location a_location = std::source_location::current()) noexcept
	{
		if (a_condition) [[likely]] {
			return;
		}

		Impl::Assert(a_location, "Assertion failed."sv);
	}

	constexpr void Assert(bool a_condition, std::string_view a_format, std::source_location a_location = std::source_location::current()) noexcept
	{
		if (a_condition) [[likely]] {
			return;
		}

		Impl::Assert(a_location, a_format);
	}

	constexpr void Assert(bool a_condition, std::wstring_view a_format, std::source_location a_location = std::source_location::current()) noexcept
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

		try {
			Impl::Assert(a_formatLocation.location(), REX::Format(a_formatLocation.format(), std::forward<Args>(a_args)...));
		}
		catch ([[maybe_unused]] const std::bad_alloc& error) {
			REX::AllocationFail();
		}
	}

	template <class... Args>
	constexpr void Assert(bool a_condition, REX::WFormatStringLocation<Args...> a_formatLocation, Args&&... a_args) noexcept
		requires((REX::formattable<Args, wchar_t> && ...))
	{
		if (a_condition) [[likely]] {
			return;
		}

		try {
			Impl::Assert(a_formatLocation.location(), REX::Format(a_formatLocation.format(), std::forward<Args>(a_args)...));
		}
		catch ([[maybe_unused]] const std::bad_alloc& error) {
			REX::AllocationFail();
		}
	}
#else
	constexpr void Assert([[maybe_unused]] bool a_condition, [[maybe_unused]] std::source_location a_location = std::source_location::current()) noexcept
	{
		return;
	}

	constexpr void Assert([[maybe_unused]] bool a_condition, [[maybe_unused]] std::string_view a_format, [[maybe_unused]] std::source_location a_location = std::source_location::current()) noexcept
	{
		return;
	}

	constexpr void Assert([[maybe_unused]] bool a_condition, [[maybe_unused]] std::wstring_view a_format, [[maybe_unused]] std::source_location a_location = std::source_location::current()) noexcept
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
