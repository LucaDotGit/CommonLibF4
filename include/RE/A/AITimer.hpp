#pragma once

namespace RE
{
	class AITimer
	{
	public:
		using Seconds = std::chrono::duration<REX::Float32, std::chrono::seconds::period>;

		[[nodiscard]] static REX::Float32& GetTimer();

		[[nodiscard]] Seconds GetStartTime() const noexcept;
		[[nodiscard]] Seconds GetTargetTime() const noexcept;

		// members
		REX::Float32 startTime;	 // 00
		REX::Float32 targetTime; // 04
	};
	static_assert(sizeof(AITimer) == 0x08);
}
