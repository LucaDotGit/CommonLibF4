#pragma once

#if (COMMONLIB_FEATURE_JSON == 1)

#include "REX/Glaze/Setting.hpp"
#include "REX/Glaze/Utility.hpp"
#include "REX/JSON/Utility.hpp"

namespace REX::JSON
{
	template <class T>
		requires(REX::Glaze::ReadWritable<T, REX::JSON::DEFAULT_OPTIONS>)
	using Setting =
		REX::Glaze::Setting<T, REX::JSON::DEFAULT_OPTIONS, REX::Glaze::DEFAULT_NUMBER_MODE, REX::Glaze::MapType>;
}

#endif
