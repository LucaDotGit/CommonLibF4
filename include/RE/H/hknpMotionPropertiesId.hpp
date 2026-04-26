#pragma once

#include "RE/H/hkHandle.hpp"

namespace RE
{
	class hknpMotionPropertiesIdBaseDiscriminant
	{
	public:
	};
	static_assert(std::is_empty_v<hknpMotionPropertiesIdBaseDiscriminant>);

	class hknpMotionPropertiesId
		: public hkHandle<std::uint16_t, std::numeric_limits<std::uint16_t>::max(), hknpMotionPropertiesIdBaseDiscriminant>
	{
	public:
		enum class Preset : std::uint16_t
		{
			kInvalid = std::numeric_limits<std::uint16_t>::max(),
			kStatic = 0,
			kDynamic = 1,
			kKeyframed = 2,
			kFrozen = 3,
			kDebris = 4,

			kTotal = 5
		};
	};
	static_assert(sizeof(hknpMotionPropertiesId) == 0x02);
}
