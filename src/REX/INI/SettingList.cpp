#include "REX/INI/SettingList.hpp"

#if (COMMONLIB_FEATURE_INI == 1)

#include "REX/Error.hpp"
#include "REX/INI/Utility.hpp" // IWYU pragma: keep

namespace REX::INI
{
	auto SettingList::LoadEntry(const entry_type& a_parent) -> REX::SystemError
	{
		for (auto&& [_, value] : _settings) {
			const auto loadError = value->LoadEntry(a_parent);
			if (loadError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
				return loadError;
			}
		}

		return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
	}

	auto SettingList::SaveEntry(entry_type& a_parent) const -> REX::SystemError
	{
		for (auto&& [_, value] : _settings) {
			const auto saveValueError = value->SaveEntry(a_parent);
			if (saveValueError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
				return saveValueError;
			}
		}

		return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
	}
}

#endif
