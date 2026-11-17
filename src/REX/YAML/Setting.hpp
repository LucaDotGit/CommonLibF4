#pragma once

#if (COMMONLIB_FEATURE_YAML == 1)

#include "REX/Glaze/Setting.hpp"
#include "REX/Glaze/Utility.hpp"
#include "REX/YAML/Utility.hpp"

namespace REX::YAML
{
	template <class T>
		requires(REX::Glaze::ReadWritable<T, REX::YAML::DEFAULT_OPTIONS>)
	using Setting =
		REX::Glaze::Setting<T, REX::YAML::DEFAULT_OPTIONS, REX::Glaze::DEFAULT_NUMBER_MODE, REX::Glaze::MapType>;
}

#endif
