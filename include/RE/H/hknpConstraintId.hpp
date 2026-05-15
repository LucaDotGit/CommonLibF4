#pragma once

#include "RE/H/hkHandle.hpp"

namespace RE
{
	class hknpConstraintIdBaseDiscriminant
	{
	public:
	};
	static_assert(std::is_empty_v<hknpConstraintIdBaseDiscriminant>);

	class hknpConstraintId
		: public hkHandle<std::uint32_t, std::numeric_limits<std::int32_t>::max(), hknpConstraintIdBaseDiscriminant>
	{
	public:
		using hkHandle::hkHandle;
	};
	static_assert(sizeof(hknpConstraintId) == 0x04);
}
