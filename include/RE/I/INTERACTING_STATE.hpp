#pragma once

namespace RE
{
	enum class INTERACTING_STATE : std::uint32_t
	{
		kNotInteracting = 0,
		kWaitingToInteract = 1,
		kInteracting = 2,
		kWaitingToStopInteracting = 3
	};
}
