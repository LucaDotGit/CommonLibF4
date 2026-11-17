#include "REX/INI/Utility.hpp"

#if (COMMONLIB_FEATURE_INI == 1)

#include "REX/Error.hpp"

namespace REX::INI
{
	auto CreatePosixError(ErrorNumber a_errorCode) noexcept -> REX::PosixError
	{
		if (a_errorCode == ::SI_FAIL) {
			return REX::CreatePosixError(REX::PosixErrorCode::bad_message);
		}

		if (a_errorCode == ::SI_NOMEM) {
			return REX::CreatePosixError(REX::PosixErrorCode::not_enough_memory);
		}

		if (a_errorCode == ::SI_FILE) {
			return REX::CreatePosixError(REX::PosixErrorCode::io_error);
		}

		return REX::CreatePosixError(REX::POSIX_ERROR_CODE_SUCCESS);
	}
}

#endif
