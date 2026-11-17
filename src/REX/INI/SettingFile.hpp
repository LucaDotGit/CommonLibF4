#pragma once

#if (COMMONLIB_FEATURE_INI == 1)

#include "REX/Error.hpp"
#include "REX/INI/Utility.hpp"
#include "REX/SettingFile.hpp"

namespace REX::INI
{
	class SettingFile final : public REX::SettingFile<REX::INI::EntryType>
	{
	private:
		using super = REX::SettingFile<REX::INI::EntryType>;

	public:
		using super::entry_type;

		explicit SettingFile(std::filesystem::path a_filePath) noexcept :
			super(std::move(a_filePath))
		{
		}

		~SettingFile() noexcept override = default;

		SettingFile(const SettingFile&) = delete;
		SettingFile(SettingFile&&) noexcept = default;

		auto operator=(const SettingFile&) -> SettingFile& = delete;
		auto operator=(SettingFile&&) noexcept -> SettingFile& = default;

		auto LoadEntry(const entry_type& a_parent) -> REX::SystemError override;
		auto SaveEntry(entry_type& a_parent) const -> REX::SystemError override;

		auto Load() -> REX::SystemError override;
		auto Save() const -> REX::SystemError override;
	};
}

#endif
