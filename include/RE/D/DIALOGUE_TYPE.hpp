#pragma once

namespace RE
{
	enum class DIALOGUE_TYPE : std::int32_t
	{
		kPlayerDialogue = 0,
		kCommandDialogue = 1,
		kSceneDialogue = 2,
		kCombat = 3,
		kFavors = 4,
		kDetection = 5,
		kService = 6,
		kMiscellaneous = 7
	};
}
