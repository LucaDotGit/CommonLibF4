#pragma once

#if (COMMONLIB_FEATURE_YAML == 1)

#include "REX/Glaze/SettingList.hpp"
#include "REX/Glaze/Utility.hpp"

namespace REX::YAML
{
	using SettingList = REX::Glaze::SettingList<REX::Glaze::DEFAULT_NUMBER_MODE, REX::Glaze::MapType>;
}

#endif
