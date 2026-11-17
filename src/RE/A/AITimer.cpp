#include "RE/A/AITimer.hpp"

namespace RE
{
	auto AITimer::GetTimer() noexcept -> REX::Float32&
	{
		static const auto TIMER = REL::Relocation<REX::Float32*>(ID::AITimer::Timer);
		return *TIMER;
	}
}
