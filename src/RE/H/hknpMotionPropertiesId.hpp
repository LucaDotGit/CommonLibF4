#pragma once

#include "RE/H/hkHandle.hpp"

namespace RE
{
	class hknpMotionPropertiesIdBaseDiscriminant
	{
	public:
	};

	static_assert(std::is_empty_v<hknpMotionPropertiesIdBaseDiscriminant>);

	class hknpMotionPropertiesId :
		public hkHandle<
			std::uint16_t,
			std::numeric_limits<std::uint16_t>::max(),
			hknpMotionPropertiesIdBaseDiscriminant>
	{
	public:
		using hkHandle::hkHandle;

		enum class Preset : std::uint16_t
		{
			Invalid = std::numeric_limits<std::uint16_t>::max(),
			Static = 0,
			Dynamic = 1,
			Keyframed = 2,
			Frozen = 3,
			Debris = 4,

			_Count = 5
		};
	};

	static_assert(sizeof(hknpMotionPropertiesId) == 0x02);
}
