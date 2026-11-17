#pragma once

#if (COMMONLIB_FEATURE_JSON == 1)

#include "REX/Glaze/SettingFile.hpp"
#include "REX/Glaze/Utility.hpp"
#include "REX/JSON/Utility.hpp"

namespace REX::JSON
{
	using SettingFile =
		REX::Glaze::SettingFile<REX::JSON::DEFAULT_OPTIONS, REX::Glaze::DEFAULT_NUMBER_MODE, REX::Glaze::MapType>;
}

#endif
