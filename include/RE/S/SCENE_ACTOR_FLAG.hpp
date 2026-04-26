#pragma once

namespace RE
{
	enum class SCENE_ACTOR_FLAG : std::uint32_t
	{
		kNone = 0,
		kNoPlayerActivation = 1 << 0,
		kOptional = 1 << 1,
		kRunOnlyScenePackages = 1 << 2,
		kNoCommandState = 1 << 3
	};
}
