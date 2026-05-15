#pragma once

#include "REX/Format.hpp"
#include "REX/Message.hpp"
#include "REX/SourceLocation.hpp"

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
		REX::FormatString<std::string_view> a_format = "A function threw an exception during execution.\nError: {}"sv,
		REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) //
		noexcept(std::is_nothrow_invocable_v<TryFunc>)
			-> std::invoke_result_t<TryFunc>
		requires(std::derived_from<Error, std::exception> &&
				 std::is_invocable_v<TryFunc>)
	{
		try {
			return std::invoke(std::forward<TryFunc>(a_tryFunc));
		}
		catch (const Error& error) {
			const auto formatData = REX::FixedFormat(a_format, std::string_view(error.what()));
			REX::Fail(std::string_view{ formatData.buffer.data(), formatData.size }, a_location);
		}
	}

	template <class Error, class TryFunc>
	[[nodiscard]] constexpr auto TryOrFailW(
		TryFunc&& a_tryFunc,
		REX::WFormatString<std::wstring_view> a_format = L"A function threw an exception during execution.\nError: {}"sv,
		REX::SourceLocation a_location = REX::SourceLocation::GetCurrent()) //
		noexcept(std::is_nothrow_invocable_v<TryFunc>)
			-> std::invoke_result_t<TryFunc>
		requires(std::derived_from<Error, std::exception> &&
				 std::is_invocable_v<TryFunc>)
	{
		try {
			return std::invoke(std::forward<TryFunc>(a_tryFunc));
		}
		catch (const Error& error) {
			const auto formatData = REX::FixedFormat(a_format, std::wstring_view(error.what()));
			REX::Fail(std::wstring_view{ formatData.buffer.data(), formatData.size }, a_location);
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
		catch ([[maybe_unused]] const Error& error) {
			std::terminate();
		}
	}
}
