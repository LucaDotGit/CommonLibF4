#pragma once

namespace RE
{
	class BSPrecisionTimer
	{
	public:
		using Seconds = std::chrono::duration<REX::Float32, std::chrono::seconds::period>;

		[[nodiscard]] static REX::Float32& GetFrequencyMS();
		[[nodiscard]] static REX::Float32& GetFrequencyMSRecip();

		[[nodiscard]] static std::int64_t GetTimer() noexcept;

		static void Initialize();

		[[nodiscard]] bool IsExpired() const noexcept;

		[[nodiscard]] std::int64_t GetRemainingTime() const noexcept;
		[[nodiscard]] std::int64_t GetElapsedTime() const noexcept;

		[[nodiscard]] Seconds GetRemainingSeconds() const;
		[[nodiscard]] Seconds GetElapsedSeconds() const;

		void Reset(std::int64_t a_duration) noexcept;
		void Reset(Seconds a_durationSeconds);

		// members
		std::int64_t startTime; // 00
		std::int64_t endTime;	// 08
	};
	static_assert(sizeof(BSPrecisionTimer) == 0x10);
}
