#pragma once

#include "RE/H/hkHandle.hpp"

namespace RE
{
	class hknpMaterialIdBaseDiscriminant
	{
	public:
	};
	static_assert(std::is_empty_v<hknpMaterialIdBaseDiscriminant>);

	class hknpMaterialId
		: public hkHandle<std::uint16_t, std::numeric_limits<std::uint16_t>::max(), hknpMaterialIdBaseDiscriminant>
	{
	public:
		using hkHandle::hkHandle;
	};
	static_assert(sizeof(hknpMaterialId) == 0x02);
}
