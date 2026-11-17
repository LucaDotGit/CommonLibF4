#pragma once

namespace RE
{
	enum class INTERACTING_STATE : std::uint32_t
	{
		NotInteracting = 0,
		WaitingToInteract = 1,
		Interacting = 2,
		WaitingToStopInteracting = 3
	};
}
