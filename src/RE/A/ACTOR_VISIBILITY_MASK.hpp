#pragma once

namespace RE
{
	enum class ACTOR_VISIBILITY_MASK : std::uint32_t
	{
		Frustum = 1 << 0,
		Occlusion = 1 << 1,
		Faded = 1 << 2,

		All = Frustum | Occlusion | Faded
	};
}
