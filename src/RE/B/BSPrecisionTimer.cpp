#include "RE/B/BSPrecisionTimer.hpp"

namespace RE
{
	REX::Float32& BSPrecisionTimer::GetFrequencyMS()
	{
		static const auto FREQUENCY_MS = REL::Relocation<REX::Float32*>{ ID::BSPrecisionTimer::FrequencyMS };
		return *FREQUENCY_MS;
	}

	REX::Float32& BSPrecisionTimer::GetFrequencyMSRecip()
	{
		static const auto FREQUENCY_MS_RECIP = REL::Relocation<REX::Float32*>{ ID::BSPrecisionTimer::FrequencyMSRecip };
		return *FREQUENCY_MS_RECIP;
	}

	std::int64_t BSPrecisionTimer::GetTimer() noexcept
	{
		auto counter = static_cast<std::int64_t>(0);
		REX::W32::QueryPerformanceCounter(std::addressof(counter));
		return counter;
	}

	void BSPrecisionTimer::Initialize()
	{
		auto frequency = static_cast<std::int64_t>(0);
		REX::W32::QueryPerformanceFrequency(std::addressof(frequency));

		auto& frequencyMS = GetFrequencyMS();
		auto& frequencyMSRecip = GetFrequencyMSRecip();

		frequencyMS = static_cast<REX::Float32>(frequency) * 0.001_f32;
		frequencyMSRecip = 1.0_f32 / frequencyMS;
	}

	bool BSPrecisionTimer::IsExpired() const noexcept
	{
		return GetTimer() >= endTime;
	}

	std::int64_t BSPrecisionTimer::GetRemainingTime() const noexcept
	{
		return endTime - GetTimer();
	}

	std::int64_t BSPrecisionTimer::GetElapsedTime() const noexcept
	{
		return GetTimer() - startTime;
	}

	BSPrecisionTimer::Seconds BSPrecisionTimer::GetRemainingSeconds() const
	{
		const auto seconds = static_cast<REX::Float32>(GetRemainingTime()) * GetFrequencyMSRecip();
		return static_cast<Seconds>(seconds);
	}

	BSPrecisionTimer::Seconds BSPrecisionTimer::GetElapsedSeconds() const
	{
		const auto seconds = static_cast<REX::Float32>(GetElapsedTime()) * GetFrequencyMSRecip();
		return static_cast<Seconds>(seconds);
	}

	void BSPrecisionTimer::Reset(std::int64_t a_duration) noexcept
	{
		startTime = GetTimer();
		endTime = startTime + a_duration;
	}

	void BSPrecisionTimer::Reset(Seconds a_durationSeconds)
	{
		const auto duration = static_cast<std::int64_t>(a_durationSeconds.count() * GetFrequencyMS());
		Reset(duration);
	}
}
