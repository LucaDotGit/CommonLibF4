#include "REX/INI/SettingGroup.hpp"

#if (COMMONLIB_FEATURE_INI == 1)

#include "REX/Error.hpp"
#include "REX/INI/Utility.hpp" // IWYU pragma: keep

namespace REX::INI
{
	auto SettingGroup::LoadEntry(const entry_type& a_parent) -> REX::SystemError
	{
		auto tempEntryPair = entry_type{a_parent.first, _key};

		for (auto&& [_, value] : _settings) {
			const auto loadError = value->LoadEntry(tempEntryPair);
			if (loadError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
				return loadError;
			}
		}

		return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
	}

	auto SettingGroup::SaveEntry(entry_type& a_parent) const -> REX::SystemError
	{
		auto tempEntryPair = entry_type{a_parent.first, _key};

		for (auto&& [_, value] : _settings) {
			const auto saveValueError = value->SaveEntry(tempEntryPair);
			if (saveValueError.value() != REX::ERROR_NUMBER_SUCCESS) [[unlikely]] {
				return saveValueError;
			}
		}

		return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
	}
}

#endif
