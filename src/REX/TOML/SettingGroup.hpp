#pragma once

#if (COMMONLIB_FEATURE_TOML == 1)

#include "REX/Glaze/SettingGroup.hpp"
#include "REX/Glaze/Utility.hpp"

namespace REX::TOML
{
	using SettingGroup = REX::Glaze::SettingGroup<REX::Glaze::DEFAULT_NUMBER_MODE, REX::Glaze::MapType>;
}

#endif
