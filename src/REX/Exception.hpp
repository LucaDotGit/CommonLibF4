#pragma once

#include "REX/Concepts.hpp"
#include "REX/Formatting.hpp"
#include "REX/Macros.hpp"
#include "REX/Message.hpp"
#include "REX/SourceLocation.hpp"

namespace REX
{
	template <class Error, class TryFunc, class CatchFunc>
	[[nodiscard]] [[REX_EXCEPTION_INLINE]]
	constexpr auto TryCatch(TryFunc&& a_tryFunc, CatchFunc&& a_catchFunc)
		noexcept(std::is_nothrow_invocable_v<CatchFunc, const Error&>) -> std::invoke_result_t<TryFunc>
		requires(
			std::derived_from<Error, std::exception> &&
			std::is_invocable_v<TryFunc> &&
			!std::is_nothrow_invocable_v<TryFunc> &&
			std::is_invocable_v<CatchFunc, const Error&> &&
			std::same_as<std::invoke_result_t<TryFunc>, std::invoke_result_t<CatchFunc, const Error&>>)
	{
		try {
			return std::invoke(std::forward<TryFunc>(a_tryFunc));
		}
		catch (const Error& error) {
			return std::invoke(std::forward<CatchFunc>(a_catchFunc), error);
		}
	}

	template <class Error, class TryFunc>
	[[nodiscard]] [[REX_EXCEPTION_INLINE]]
	constexpr auto TryOrFail(
		TryFunc&& a_tryFunc,
		REX::FormatString<std::string_view> a_format,
		REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) noexcept -> std::invoke_result_t<TryFunc>
		requires(
			std::derived_from<Error, std::exception> &&
			std::is_invocable_v<TryFunc> &&
			!std::is_nothrow_invocable_v<TryFunc>)
	{
		try {
			return std::invoke(std::forward<TryFunc>(a_tryFunc));
		}
		catch (const Error& error) {
			auto formatBuffer = std::array<char, REX::MESSAGE_BUFFER_SIZE>();
			const auto formatResult = REX::FormatToN(
				formatBuffer.data(),
				static_cast<std::ptrdiff_t>(formatBuffer.size()),
				a_format,
				std::string_view(error.what()));

			REX::Fail(std::string_view{formatBuffer.data(), formatResult.size}, a_location);
		}
	}

	template <class Error, class TryFunc>
	[[nodiscard]] [[REX_EXCEPTION_INLINE]]
	constexpr auto TryOrFail(TryFunc&& a_tryFunc, REX::SourceLocation a_location = REX::SourceLocation::GetCurrent())
		noexcept -> std::invoke_result_t<TryFunc>
		requires(
			std::derived_from<Error, std::exception> &&
			std::is_invocable_v<TryFunc> &&
			!std::is_nothrow_invocable_v<TryFunc>)
	{
		return REX::TryOrFail<Error>(
			std::forward<TryFunc>(a_tryFunc),
			"A function threw an exception during execution.\n"
			"Error: {}"sv,
			a_location);
	}

	template <class Error>
	[[noreturn]] [[REX_EXCEPTION_INLINE]]
	constexpr void Throw() noexcept(false)
		requires(std::derived_from<Error, std::exception> && !std::is_constructible_v<Error, const char*>)
	{
		throw Error();
	}

	template <class Error, class... Args>
	[[noreturn]]
	constexpr void Throw(REX::FormatString<Args...> a_format, Args&&... a_args) noexcept(false)
		requires(std::derived_from<Error, std::exception> && std::is_constructible_v<Error, const char*>)
	{
		auto formatBuffer = std::array<char, REX::MESSAGE_BUFFER_SIZE>();
		const auto formatResult = REX::FormatToN(
			formatBuffer.data(),
			static_cast<std::ptrdiff_t>(formatBuffer.size()),
			a_format,
			std::forward<Args>(a_args)...);

		throw Error(formatBuffer.data());
	}

	template <class Error, class... Args>
	[[noreturn]] [[REX_EXCEPTION_INLINE]]
	constexpr void Throw(Args&&... a_args) noexcept(false)
		requires(std::derived_from<Error, std::exception> && std::is_constructible_v<Error, Args...>)
	{
		throw Error(std::forward<Args>(a_args)...);
	}

	template <class Error>
	[[REX_EXCEPTION_INLINE]]
	constexpr void ThrowIf(bool a_condition) noexcept(false)
		requires(std::derived_from<Error, std::exception> && !std::is_constructible_v<Error, const char*>)
	{
		if (!a_condition) [[likely]] {
			return;
		}

		Throw<Error>();
	}

	template <class Error, class... Args>
	[[REX_EXCEPTION_INLINE]]
	constexpr void ThrowIf(bool a_condition, REX::FormatString<Args...> a_format, Args&&... a_args) noexcept(false)
		requires(std::derived_from<Error, std::exception> && std::is_constructible_v<Error, const char*>)
	{
		if (!a_condition) [[likely]] {
			return;
		}

		Throw<Error>(a_format, std::forward<Args>(a_args)...);
	}

	template <class Error, class... Args>
	[[REX_EXCEPTION_INLINE]]
	constexpr void ThrowIf(bool a_condition, Args&&... a_args) noexcept(false)
		requires(std::derived_from<Error, std::exception> && std::is_constructible_v<Error, Args...>)
	{
		if (!a_condition) [[likely]] {
			return;
		}

		Throw<Error>(std::forward<Args>(a_args)...);
	}
}
