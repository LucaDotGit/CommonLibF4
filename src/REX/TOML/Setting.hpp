#pragma once

#if (COMMONLIB_FEATURE_TOML == 1)

#include "REX/Glaze/Setting.hpp"
#include "REX/Glaze/Utility.hpp"
#include "REX/TOML/Utility.hpp"

namespace REX::TOML
{
	template <class T>
		requires(REX::Glaze::ReadWritable<T, REX::TOML::DEFAULT_OPTIONS>)
	using Setting =
		REX::Glaze::Setting<T, REX::TOML::DEFAULT_OPTIONS, REX::Glaze::DEFAULT_NUMBER_MODE, REX::Glaze::MapType>;
}

#endif
