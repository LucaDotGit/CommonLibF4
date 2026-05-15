#include "REX/Error.hpp"

#include "REX/W32/KERNEL32.hpp"

namespace REX
{
	const ErrorCategory& GetPosixErrorCategory() noexcept
	{
		return std::generic_category();
	}

	const ErrorCategory& GetSystemErrorCategory() noexcept
	{
		return std::system_category();
	}

	const ErrorCategory& GetFutureErrorCategory() noexcept
	{
		return std::future_category();
	}

	const ErrorCategory& GetIOStreamErrorCategory() noexcept
	{
		return std::iostream_category();
	}

	PosixError GetCurrentPosixError() noexcept
	{
		return CreatePosixError(static_cast<PosixErrorCode>(errno));
	}

	SystemError GetCurrentSystemError() noexcept
	{
		return CreateSystemError(static_cast<ErrorNumber>(REX::W32::GetLastError()));
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
		return { a_error.value(), GetSystemErrorCategory() };
	}

	SystemError CreateSystemError(ErrorNumber a_errorNumber) noexcept
	{
		return { a_errorNumber, GetSystemErrorCategory() };
	}

	SystemError CreateSystemError(PosixErrorCode a_errorCode) noexcept
	{
		return { static_cast<ErrorNumber>(a_errorCode), GetPosixErrorCategory() };
	}

	SystemError CreateSystemError(PosixError a_error) noexcept
	{
		return { a_error.value(), GetPosixErrorCategory() };
	}

	SystemError CreateSystemError(FutureErrorCode a_errorCode) noexcept
	{
		return { static_cast<ErrorNumber>(a_errorCode), GetFutureErrorCategory() };
	}

	SystemError CreateSystemError(IOStreamErrorCode a_errorCode) noexcept
	{
		return { static_cast<ErrorNumber>(a_errorCode), GetIOStreamErrorCategory() };
	}
}
