#include "RE/A/AITimer.hpp"

namespace RE
{
	REX::Float32& AITimer::GetTimer()
	{
		static const auto TIMER = REL::Relocation<REX::Float32*>{ ID::AITimer::Timer };
		return *TIMER;
	}

	AITimer::Seconds AITimer::GetStartTime() const noexcept
	{
		return Seconds(startTime);
	}

	AITimer::Seconds AITimer::GetTargetTime() const noexcept
	{
		return Seconds(targetTime);
	}
}
