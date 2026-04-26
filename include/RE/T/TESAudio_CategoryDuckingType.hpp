#pragma once

namespace RE::TESAudio
{
	enum class CategoryDuckingType : std::int32_t
	{
		kHolotapeProgram = 0,
		kHolotapeScene = 1,
		kDialogueMenu = 2,
		kSemiDialogue = 3,
		kDialogueCamera = 4,
		kInterestingNonDialogue = 5,
		kHighlightNearby = 6
	};
}
