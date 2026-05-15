#include "REX/TomlUtility.hpp"

#if COMMONLIB_OPTION_TOML == 1

namespace REX::Toml
{
	auto SplitSetting(std::string_view a_setting)
		-> std::pair<std::string_view, std::string_view>
	{
		const auto separatorPos = a_setting.rfind(REX::Toml::KEY_SEPARATOR);
		if (separatorPos == std::string_view::npos) {
			return std::make_pair(std::string_view(), a_setting);
		}

		const auto section = a_setting.substr(0, separatorPos);
		const auto key = a_setting.substr(separatorPos + 1);
		return std::make_pair(section, key);
	}

	template auto GetPointer(toml::basic_value<toml::type_config>&, std::string_view)
		-> toml::basic_value<toml::type_config>*;
	template auto GetPointer(const toml::basic_value<toml::type_config>&, std::string_view)
		-> const toml::basic_value<toml::type_config>*;
	template auto GetOrCreatePointer(toml::basic_value<toml::type_config>&, std::string_view)
		-> toml::basic_value<toml::type_config>*;
	template auto Flatten(const toml::basic_value<toml::type_config>&)
		-> std::optional<toml::basic_value<toml::type_config>>;
}

#endif
