#pragma once

#include "RE/B/BGSEntryPoint.hpp"

namespace RE
{
	class hknpActivationMode
	{
	public:
		using Enum = BGSEntryPoint::ENTRY_POINT;
	};
	static_assert(std::is_empty_v<hknpActivationMode>);
}
