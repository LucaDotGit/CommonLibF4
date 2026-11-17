#include "REX/Error.hpp"

#include "REX/W32/KERNEL32.hpp"

namespace REX
{
	auto GetPosixErrorCategory() noexcept -> const ErrorCategory&
	{
		return std::generic_category();
	}

	auto GetSystemErrorCategory() noexcept -> const ErrorCategory&
	{
		return std::system_category();
	}

	auto GetFutureErrorCategory() noexcept -> const ErrorCategory&
	{
		return std::future_category();
	}

	auto GetIOStreamErrorCategory() noexcept -> const ErrorCategory&
	{
		return std::iostream_category();
	}

	auto GetCurrentStlError() noexcept -> PosixError
	{
		return CreatePosixError(static_cast<PosixErrorCode>(errno));
	}

	auto GetCurrentSystemError() noexcept -> SystemError
	{
		return CreateSystemError(static_cast<ErrorNumber>(REX::W32::GetLastError()));
	}

	auto CreatePosixError(ErrorNumber a_errorNumber) noexcept -> PosixError
	{
		return {a_errorNumber, GetPosixErrorCategory()};
	}

	auto CreatePosixError(PosixErrorCode a_errorCode) noexcept -> PosixError
	{
		return {static_cast<ErrorNumber>(a_errorCode), GetPosixErrorCategory()};
	}

	auto CreatePosixError(SystemError a_error) noexcept -> PosixError
	{
		return {a_error.value(), GetSystemErrorCategory()};
	}

	auto CreateSystemError(ErrorNumber a_errorNumber) noexcept -> SystemError
	{
		return {a_errorNumber, GetSystemErrorCategory()};
	}

	auto CreateSystemError(PosixErrorCode a_errorCode) noexcept -> SystemError
	{
		return {static_cast<ErrorNumber>(a_errorCode), GetPosixErrorCategory()};
	}

	auto CreateSystemError(PosixError a_error) noexcept -> SystemError
	{
		return {a_error.value(), GetPosixErrorCategory()};
	}

	auto CreateSystemError(FutureErrorCode a_errorCode) noexcept -> SystemError
	{
		return {static_cast<ErrorNumber>(a_errorCode), GetFutureErrorCategory()};
	}

	auto CreateSystemError(IOStreamErrorCode a_errorCode) noexcept -> SystemError
	{
		return {static_cast<ErrorNumber>(a_errorCode), GetIOStreamErrorCategory()};
	}
}
