#pragma once

#include "REX/Contract.hpp"
#include "REX/Format.hpp"
#include "REX/Message.hpp"

namespace REX
{
	template <class Error, class TryFunc, class CatchFunc>
	[[nodiscard]] constexpr auto TryCatch(
		TryFunc&& a_tryFunc,
		CatchFunc&& a_catchFunc) //
		noexcept(std::is_nothrow_invocable_v<TryFunc> &&
				 std::is_nothrow_invocable_v<CatchFunc, const Error&>)
			-> std::invoke_result_t<TryFunc>
		requires(std::derived_from<Error, std::exception> &&
				 std::is_invocable_v<TryFunc> &&
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
	[[nodiscard]] constexpr auto TryOrFail(
		TryFunc&& a_tryFunc,
		REX::FormatString<const char*> a_format = "A function threw an exception during execution.\nError: {}"sv,
		std::source_location a_location = std::source_location::current()) //
		noexcept(std::is_nothrow_invocable_v<TryFunc>)
			-> std::invoke_result_t<TryFunc>
		requires(std::derived_from<Error, std::exception> &&
				 std::is_invocable_v<TryFunc>)
	{
		try {
			return std::invoke(std::forward<TryFunc>(a_tryFunc));
		}
		catch (const Error& error) {
			REX::Impl::Fail(a_location, a_format, error.what());
		}
	}

	template <class Error, class TryFunc>
	[[nodiscard]] constexpr auto TryOrQuickFail(
		TryFunc&& a_tryFunc,
		std::string_view a_format = "A function threw an exception during execution."sv) //
		noexcept(std::is_nothrow_invocable_v<TryFunc>)
			-> std::invoke_result_t<TryFunc>
		requires(std::derived_from<Error, std::exception> &&
				 std::is_invocable_v<TryFunc>)
	{
		try {
			return std::invoke(std::forward<TryFunc>(a_tryFunc));
		}
		catch (const Error& error) {
			REX::Impl::QuickFail(a_format);
		}
	}

	template <class Error, class TryFunc>
	[[nodiscard]] constexpr auto TryOrTerminate(TryFunc&& a_tryFunc) //
		noexcept(std::is_nothrow_invocable_v<TryFunc>)
			-> std::invoke_result_t<TryFunc>
		requires(std::derived_from<Error, std::exception> &&
				 std::is_invocable_v<TryFunc>)
	{
		try {
			return std::invoke(std::forward<TryFunc>(a_tryFunc));
		}
		catch (const Error& error) {
			std::terminate();
		}
	}
}
