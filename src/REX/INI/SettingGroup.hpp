#pragma once

#if (COMMONLIB_FEATURE_INI == 1)

#include "REX/Error.hpp"
#include "REX/INI/Utility.hpp"
#include "REX/SettingList.hpp"

namespace REX::INI
{
	class SettingGroup final : public REX::SettingList<REX::INI::EntryType>
	{
	private:
		using super = REX::SettingList<REX::INI::EntryType>;

	public:
		using super::entry_type;

		explicit SettingGroup(std::string a_key) noexcept :
			_key(std::move(a_key))
		{
		}

		~SettingGroup() noexcept override = default;

		SettingGroup(const SettingGroup&) = delete;
		SettingGroup(SettingGroup&&) noexcept = default;

		auto operator=(const SettingGroup&) -> SettingGroup& = delete;
		auto operator=(SettingGroup&&) noexcept -> SettingGroup& = default;

		[[nodiscard]]
		auto GetKey() const noexcept -> std::string_view override
		{
			return _key;
		}

		auto LoadEntry(const entry_type& a_parent) -> REX::SystemError override;
		auto SaveEntry(entry_type& a_parent) const -> REX::SystemError override;

	private:
		std::string _key;
	};
}

#endif
