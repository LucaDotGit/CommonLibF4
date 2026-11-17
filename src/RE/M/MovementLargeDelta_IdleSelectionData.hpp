#pragma once

#include "RE/M/MovementLargeDelta_CurrentState.hpp"
#include "RE/M/MovementLargeDelta_DesiredState.hpp"

namespace RE::MovementLargeDelta
{
	class IdleSelectionData
	{
	public:
		// members
		CurrentState fromState; // 0x00
		DesiredState toState;	// 0x08
	};

	static_assert(sizeof(IdleSelectionData) == 0x10);
}
