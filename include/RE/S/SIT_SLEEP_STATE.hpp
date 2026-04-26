#pragma once

namespace RE
{
	enum class SIT_SLEEP_STATE : std::uint32_t
	{
		kNormal = 0,
		kWantToSit = 1,
		kWaitingForSitAnim = 2,
		kIsSitting = 3,
		kWantToStand = 4,
		kWantToSleep = 5,
		kWaitingForSleepAnim = 6,
		kIsSleeping = 7,
		kWantToWakeUp = 8
	};
}
