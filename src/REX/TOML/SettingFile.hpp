#pragma once

#if (COMMONLIB_FEATURE_TOML == 1)

#include "REX/Glaze/SettingFile.hpp"
#include "REX/Glaze/Utility.hpp"
#include "REX/TOML/Utility.hpp"

namespace REX::TOML
{
	using SettingFile =
		REX::Glaze::SettingFile<REX::TOML::DEFAULT_OPTIONS, REX::Glaze::DEFAULT_NUMBER_MODE, REX::Glaze::MapType>;
}

#endif
