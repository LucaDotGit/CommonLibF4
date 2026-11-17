#include "RE/B/BSPrecisionTimer.hpp"

namespace RE
{
	auto BSPrecisionTimer::GetFrequencyMS() noexcept -> REX::Float32&
	{
		static const auto FREQUENCY_MS = REL::Relocation<REX::Float32*>(ID::BSPrecisionTimer::FrequencyMS);
		return *FREQUENCY_MS;
	}

	auto BSPrecisionTimer::GetFrequencyMSRecip() noexcept -> REX::Float32&
	{
		static const auto FREQUENCY_MS_RECIP = REL::Relocation<REX::Float32*>(ID::BSPrecisionTimer::FrequencyMSRecip);
		return *FREQUENCY_MS_RECIP;
	}

	auto BSPrecisionTimer::IsExpired() const noexcept -> bool
	{
		return Clock::now() >= endTime;
	}

	auto BSPrecisionTimer::GetRemainingTime() const noexcept -> BSPrecisionTimer::Duration
	{
		const auto currentTime = Clock::now();
		if (currentTime >= endTime) {
			return Duration::zero();
		}

		return endTime - currentTime;
	}

	auto BSPrecisionTimer::GetElapsedTime() const noexcept -> BSPrecisionTimer::Duration
	{
		const auto currentTime = Clock::now();
		if (currentTime <= startTime) {
			return Duration::zero();
		}

		return currentTime - startTime;
	}

	void BSPrecisionTimer::Start(TimePoint a_endTime) noexcept
	{
		startTime = Clock::now();
		endTime = a_endTime;
	}
}
