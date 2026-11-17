#pragma once

namespace RE
{
	class Setting;

	auto GetINISetting(std::string_view a_name) -> Setting*;
	auto GetGameSetting(std::string_view a_name) -> Setting*;
}
