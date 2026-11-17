#pragma once

#if (COMMONLIB_FEATURE_JSON == 1)

#include "REX/Glaze/SettingGroup.hpp"
#include "REX/Glaze/Utility.hpp"

namespace REX::JSON
{
	using SettingGroup = REX::Glaze::SettingGroup<REX::Glaze::DEFAULT_NUMBER_MODE, REX::Glaze::MapType>;
}

#endif
