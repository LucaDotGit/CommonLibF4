#pragma once

#if (COMMONLIB_FEATURE_INI == 1)

#include "REX/Error.hpp"
#include "REX/INI/Utility.hpp"
#include "REX/SettingList.hpp"

namespace REX::INI
{
	class SettingList final : public REX::SettingList<REX::INI::EntryType>
	{
	private:
		using super = REX::SettingList<REX::INI::EntryType>;

	public:
		using super::entry_type;

		SettingList() noexcept = default;
		~SettingList() noexcept override = default;

		SettingList(const SettingList&) = delete;
		SettingList(SettingList&&) noexcept = default;

		auto operator=(const SettingList&) -> SettingList& = delete;
		auto operator=(SettingList&&) noexcept -> SettingList& = default;

		[[nodiscard]]
		auto GetKey() const noexcept -> std::string_view override
		{
			return {};
		}

		auto LoadEntry(const entry_type& a_parent) -> REX::SystemError override;
		auto SaveEntry(entry_type& a_parent) const -> REX::SystemError override;
	};
}

#endif
