#pragma once

namespace REX
{
	using ErrorNumber = std::int32_t;

	using PosixErrorCode = std::errc;
	using FutureErrorCode = std::future_errc;
	using IOStreamErrorCode = std::io_errc;

	using PosixError = std::error_condition;
	using SystemError = std::error_code;
	using ErrorCategory = std::error_category;

	static_assert(std::is_error_condition_enum_v<PosixErrorCode>);
	static_assert(std::is_error_code_enum_v<FutureErrorCode>);
	static_assert(std::is_error_code_enum_v<IOStreamErrorCode>);

	inline constexpr auto ERROR_NUMBER_SUCCESS = static_cast<ErrorNumber>(0);

	inline constexpr auto POSIX_ERROR_CODE_SUCCESS = static_cast<PosixErrorCode>(0);
	inline constexpr auto FUTURE_ERROR_CODE_SUCCESS = static_cast<FutureErrorCode>(0);
	inline constexpr auto IO_STREAM_ERROR_CODE_SUCCESS = static_cast<IOStreamErrorCode>(0);

	[[nodiscard]]
	auto GetPosixErrorCategory() noexcept -> const ErrorCategory&;
	[[nodiscard]]
	auto GetSystemErrorCategory() noexcept -> const ErrorCategory&;
	[[nodiscard]]
	auto GetFutureErrorCategory() noexcept -> const ErrorCategory&;
	[[nodiscard]]
	auto GetIOStreamErrorCategory() noexcept -> const ErrorCategory&;

	[[nodiscard]]
	auto GetCurrentStlError() noexcept -> PosixError;
	[[nodiscard]]
	auto GetCurrentSystemError() noexcept -> SystemError;

	[[nodiscard]]
	auto CreatePosixError(ErrorNumber a_errorNumber) noexcept -> PosixError;
	[[nodiscard]]
	auto CreatePosixError(PosixErrorCode a_errorCode) noexcept -> PosixError;
	[[nodiscard]]
	auto CreatePosixError(SystemError a_error) noexcept -> PosixError;

	[[nodiscard]]
	auto CreateSystemError(ErrorNumber a_errorNumber) noexcept -> SystemError;
	[[nodiscard]]
	auto CreateSystemError(PosixErrorCode a_errorCode) noexcept -> SystemError;
	[[nodiscard]]
	auto CreateSystemError(PosixError a_error) noexcept -> SystemError;
	[[nodiscard]]
	auto CreateSystemError(FutureErrorCode a_errorCode) noexcept -> SystemError;
	[[nodiscard]]
	auto CreateSystemError(IOStreamErrorCode a_errorCode) noexcept -> SystemError;
}
