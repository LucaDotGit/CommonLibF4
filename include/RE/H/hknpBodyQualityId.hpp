#pragma once

#include "RE/H/hkHandle.hpp"

namespace RE
{
	class hknpBodyQualityIdBaseDiscriminant
	{
	public:
	};
	static_assert(std::is_empty_v<hknpBodyQualityIdBaseDiscriminant>);

	class hknpBodyQualityId
		: public hkHandle<std::uint8_t, std::numeric_limits<std::uint8_t>::max(), hknpBodyQualityIdBaseDiscriminant> // 00
	{
	public:
		using hkHandle::hkHandle;
	};
	static_assert(sizeof(hknpBodyQualityId) == 0x01);
}
