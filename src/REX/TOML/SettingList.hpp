#pragma once

#if (COMMONLIB_FEATURE_TOML == 1)

#include "REX/Glaze/SettingList.hpp"
#include "REX/Glaze/Utility.hpp"

namespace REX::TOML
{
	using SettingList = REX::Glaze::SettingList<REX::Glaze::DEFAULT_NUMBER_MODE, REX::Glaze::MapType>;
}

#endif
