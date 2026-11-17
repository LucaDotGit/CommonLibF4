#pragma once

namespace RE
{
	enum class SCENE_ACTOR_FLAG : std::uint32_t
	{
		None = 0,
		NoPlayerActivation = 1 << 0,
		Optional = 1 << 1,
		RunOnlyScenePackages = 1 << 2,
		NoCommandState = 1 << 3
	};
}
