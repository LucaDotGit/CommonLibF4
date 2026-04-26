#pragma once

#include "RE/H/hkHandle.hpp"

namespace RE
{
	class hknpMotionIdBaseDiscriminant
	{
	public:
	};
	static_assert(std::is_empty_v<hknpMotionIdBaseDiscriminant>);

	class hknpMotionId
		: public hkHandle<std::uint32_t, std::numeric_limits<std::int32_t>::max(), hknpMotionIdBaseDiscriminant>
	{
	public:
	};
	static_assert(sizeof(hknpMotionId) == 0x04);
}
