#pragma once

namespace RE
{
	enum class CameraStates : std::int32_t
	{
		kFirstPerson = 0,
		kAutoVanity = 1,
		kVATS = 2,
		kFree = 3,
		kIronSights = 4,
		kPCTransition = 5,
		kTween = 6,
		kAnimated = 7,
		kThirdPerson = 8,
		kFurniture = 9,
		kMount = 10,
		kBleedout = 11,
		kDialogue = 12,

		kMin = kFirstPerson,
		kMax = kDialogue,
		kTotal = (kMax - kMin) + 1
	};
}
