#pragma once

#include "RE/Havok/hkHandle.hpp"

namespace RE
{
	struct hknpMaterialIdBaseDiscriminant;

	struct hknpMaterialId
		: public hkHandle<std::uint16_t, 0xFFFF, hknpMaterialIdBaseDiscriminant>
	{
	public:
	};
	static_assert(sizeof(hknpMaterialId) == 0x2);
}
