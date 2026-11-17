#pragma once

namespace RE::TESAudio
{
	enum class CategoryDuckingType : std::int32_t
	{
		HolotapeProgram = 0,
		HolotapeScene = 1,
		DialogueMenu = 2,
		SemiDialogue = 3,
		DialogueCamera = 4,
		InterestingNonDialogue = 5,
		HighlightNearby = 6
	};
}
