#include "REX/ErrorCode.hpp"

#include "REX/W32/KERNEL32.hpp"

namespace REX
{
	const ErrorCategory& GetSystemErrorCategory() noexcept
	{
		return std::system_category();
	}

	const ErrorCategory& GetPosixErrorCategory() noexcept
	{
		return std::generic_category();
	}

	const ErrorCategory& GetFutureErrorCategory() noexcept
	{
		return std::future_category();
	}

	const ErrorCategory& GetIOStreamErrorCategory() noexcept
	{
		return std::iostream_category();
	}

	SystemError GetCurrentSystemError() noexcept
	{
		return CreateSystemError(static_cast<ErrorNumber>(REX::W32::GetLastError()));
	}

	PosixError GetCurrentPosixError() noexcept
	{
		return CreatePosixError(static_cast<PosixErrorCode>(errno));
	}

	SystemError CreateSystemError(ErrorNumber a_errorNumber) noexcept
	{
		return { a_errorNumber, GetSystemErrorCategory() };
	}

	SystemError CreateSystemError(PosixErrorCode a_errorCode) noexcept
	{
		return { static_cast<ErrorNumber>(a_errorCode), GetSystemErrorCategory() };
	}

	SystemError CreateSystemError(PosixError a_error) noexcept
	{
		return { a_error.value(), GetSystemErrorCategory() };
	}

	PosixError CreatePosixError(ErrorNumber a_errorNumber) noexcept
	{
		return { a_errorNumber, GetPosixErrorCategory() };
	}

	PosixError CreatePosixError(PosixErrorCode a_errorCode) noexcept
	{
		return { static_cast<ErrorNumber>(a_errorCode), GetPosixErrorCategory() };
	}

	PosixError CreatePosixError(SystemError a_error) noexcept
	{
		return a_error.default_error_condition();
	}

	SystemError CreateFutureError(ErrorNumber a_errorNumber) noexcept
	{
		return { a_errorNumber, GetFutureErrorCategory() };
	}

	SystemError CreateFutureError(FutureErrorCode a_errorCode) noexcept
	{
		return { static_cast<ErrorNumber>(a_errorCode), GetFutureErrorCategory() };
	}

	SystemError CreateIOStreamError(ErrorNumber a_errorNumber) noexcept
	{
		return { a_errorNumber, GetIOStreamErrorCategory() };
	}

	SystemError CreateIOStreamError(IOStreamErrorCode a_errorCode) noexcept
	{
		return { static_cast<ErrorNumber>(a_errorCode), GetIOStreamErrorCategory() };
	}
}
