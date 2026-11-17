#pragma once

#if (COMMONLIB_FEATURE_YAML == 1)

#include "REX/Glaze/SettingFile.hpp"
#include "REX/Glaze/Utility.hpp"
#include "REX/YAML/Utility.hpp"

namespace REX::YAML
{
	using SettingFile =
		REX::Glaze::SettingFile<REX::YAML::DEFAULT_OPTIONS, REX::Glaze::DEFAULT_NUMBER_MODE, REX::Glaze::MapType>;
}

#endif
