#pragma once

#include "RE/H/hkHandle.hpp"

namespace RE
{
	class hknpShapeInstanceIdDiscriminant
	{
	public:
	};
	static_assert(std::is_empty_v<hknpShapeInstanceIdDiscriminant>);

	class hknpShapeInstanceId
		: public hkHandle<std::int16_t, std::numeric_limits<std::int16_t>::max(), hknpShapeInstanceIdDiscriminant>
	{
	public:
		using hkHandle::hkHandle;
	};
	static_assert(sizeof(hknpShapeInstanceId) == 0x02);
}
