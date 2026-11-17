#pragma once

namespace RE
{
	enum class SIT_SLEEP_STATE : std::uint32_t
	{
		Normal = 0,
		WantToSit = 1,
		WaitingForSitAnim = 2,
		IsSitting = 3,
		WantToStand = 4,
		WantToSleep = 5,
		WaitingForSleepAnim = 6,
		IsSleeping = 7,
		WantToWakeUp = 8
	};
}
