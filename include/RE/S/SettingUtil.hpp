#pragma once

namespace RE
{
	class Setting;

	Setting* GetINISetting(std::string_view a_name);
	Setting* GetGameSetting(std::string_view a_name);
}
