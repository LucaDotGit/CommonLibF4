#include "RE/S/SettingUtil.hpp"

#include "RE/G/GameSettingCollection.hpp"
#include "RE/I/INIPrefSettingCollection.hpp"
#include "RE/I/INISettingCollection.hpp"
#include "RE/S/Setting.hpp"

namespace RE
{
	Setting* GetINISetting(std::string_view a_name)
	{
		const auto* settings = INISettingCollection::GetSingleton();
		if (!settings) {
			return nullptr;
		}

		auto* setting = settings->GetSetting(a_name);
		if (setting) {
			return setting;
		}

		const auto* prefSettings = INIPrefSettingCollection::GetSingleton();
		if (!prefSettings) {
			return nullptr;
		}

		return prefSettings->GetSetting(a_name);
	}

	Setting* GetGameSetting(std::string_view a_name)
	{
		const auto* settings = GameSettingCollection::GetSingleton();
		if (!settings) {
			return nullptr;
		}

		return settings->GetSetting(a_name);
	}
}
