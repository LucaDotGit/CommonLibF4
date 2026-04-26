#pragma once

namespace REX
{
	using ErrorNumber = std::int32_t;

	using PosixErrorCode = std::errc;
	using FutureErrorCode = std::future_errc;
	using IOStreamErrorCode = std::io_errc;

	using SystemError = std::error_code;
	using PosixError = std::error_condition;
	using ErrorCategory = std::error_category;

	inline constexpr auto ERROR_NUMBER_SUCCESS = static_cast<ErrorNumber>(0);

	inline constexpr auto POSIX_ERROR_CODE_SUCCESS = static_cast<PosixErrorCode>(0);
	inline constexpr auto FUTURE_ERROR_CODE_SUCCESS = static_cast<FutureErrorCode>(0);
	inline constexpr auto IO_STREAM_ERROR_CODE_SUCCESS = static_cast<IOStreamErrorCode>(0);

	[[nodiscard]] const ErrorCategory& GetSystemErrorCategory() noexcept;
	[[nodiscard]] const ErrorCategory& GetPosixErrorCategory() noexcept;
	[[nodiscard]] const ErrorCategory& GetFutureErrorCategory() noexcept;
	[[nodiscard]] const ErrorCategory& GetIOStreamErrorCategory() noexcept;

	[[nodiscard]] SystemError GetCurrentSystemError() noexcept;
	[[nodiscard]] PosixError GetCurrentPosixError() noexcept;

	[[nodiscard]] SystemError CreateSystemError(ErrorNumber a_errorNumber) noexcept;
	[[nodiscard]] SystemError CreateSystemError(PosixErrorCode a_errorCode) noexcept;
	[[nodiscard]] SystemError CreateSystemError(PosixError a_error) noexcept;

	[[nodiscard]] PosixError CreatePosixError(ErrorNumber a_errorNumber) noexcept;
	[[nodiscard]] PosixError CreatePosixError(PosixErrorCode a_errorCode) noexcept;
	[[nodiscard]] PosixError CreatePosixError(SystemError a_error) noexcept;

	[[nodiscard]] SystemError CreateFutureError(ErrorNumber a_errorNumber) noexcept;
	[[nodiscard]] SystemError CreateFutureError(FutureErrorCode a_errorCode) noexcept;

	[[nodiscard]] SystemError CreateIOStreamError(ErrorNumber a_errorNumber) noexcept;
	[[nodiscard]] SystemError CreateIOStreamError(IOStreamErrorCode a_errorCode) noexcept;
}
