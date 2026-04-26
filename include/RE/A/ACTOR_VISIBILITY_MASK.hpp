#pragma once

namespace RE
{
	enum class ACTOR_VISIBILITY_MASK : std::uint32_t
	{
		kFrustum = 1 << 0,
		kOcclusion = 1 << 1,
		kFaded = 1 << 2,

		kAll = kFrustum |
			   kOcclusion |
			   kFaded
	};
}
