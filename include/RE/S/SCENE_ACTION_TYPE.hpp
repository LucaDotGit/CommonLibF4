#pragma once

namespace RE
{
	enum class SCENE_ACTION_TYPE : std::int32_t
	{
		kDialogue = 0,
		kPackage = 1,
		kTimer = 2,
		kPlayerDialogue = 3,
		kStartScene = 4,
		kNPCResponse = 5,
		kRadio = 6
	};
}
