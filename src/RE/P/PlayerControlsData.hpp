#pragma once

#include "RE/B/BSSpring_SpringState.hpp"
#include "RE/N/NiPoint2.hpp"
#include "RE/N/NiPoint3.hpp"

namespace RE
{
	class NiPoint3;

	class PlayerControlsData
	{
	public:
		// members
		NiPoint2 moveInputVec;								 // 0x00
		NiPoint2 lookInputVec;								 // 0x08
		NiPoint2 lookInputVecNormalized;					 // 0x10
		NiPoint2 prevMoveVec;								 // 0x18
		NiPoint2 prevLookVec;								 // 0x20
		BSSpring::SpringState<NiPoint3> rotationSpeedSpring; // 0x28
		bool autoMove;										 // 0x44
		bool running;										 // 0x45
		bool togglePOV;										 // 0x46
		bool vanityModeEnabled;								 // 0x47
		bool checkHeldStates;								 // 0x48
		bool setupHeldStatesForRelease;						 // 0x49
	};

	static_assert(sizeof(PlayerControlsData) == 0x4C);
}
