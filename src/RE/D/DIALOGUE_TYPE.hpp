#pragma once

namespace RE
{
	enum class DIALOGUE_TYPE : std::int32_t
	{
		PlayerDialogue = 0,
		CommandDialogue = 1,
		SceneDialogue = 2,
		Combat = 3,
		Favors = 4,
		Detection = 5,
		Service = 6,
		Miscellaneous = 7
	};
}
