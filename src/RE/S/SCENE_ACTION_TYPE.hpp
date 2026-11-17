#pragma once

namespace RE
{
	enum class SCENE_ACTION_TYPE : std::int32_t
	{
		Dialogue = 0,
		Package = 1,
		Timer = 2,
		PlayerDialogue = 3,
		StartScene = 4,
		NPCResponse = 5,
		Radio = 6
	};
}
