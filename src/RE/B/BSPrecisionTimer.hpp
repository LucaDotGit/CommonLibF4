#pragma once

namespace RE
{
	class BSPrecisionTimer
	{
	public:
		using Clock = std::chrono::steady_clock;
		using Duration = Clock::duration;
		using TimePoint = Clock::time_point;

		[[nodiscard]]
		static auto GetFrequencyMS() noexcept -> REX::Float32&;
		[[nodiscard]]
		static auto GetFrequencyMSRecip() noexcept -> REX::Float32&;

		[[nodiscard]]
		auto IsExpired() const noexcept -> bool;

		[[nodiscard]]
		auto GetRemainingTime() const noexcept -> Duration;
		[[nodiscard]]
		auto GetElapsedTime() const noexcept -> Duration;

		void Start(TimePoint a_endTime) noexcept;

		// members
		TimePoint startTime; // 0x00
		TimePoint endTime;	 // 0x08
	};

	static_assert(sizeof(BSPrecisionTimer) == 0x10);
}
