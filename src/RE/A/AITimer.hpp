#pragma once

namespace RE
{
	class AITimer
	{
	public:
		using Duration = std::chrono::duration<REX::Float32, std::chrono::seconds::period>;

		[[nodiscard]]
		static auto GetTimer() noexcept -> REX::Float32&;

		// members
		Duration startTime;	 // 0x00
		Duration targetTime; // 0x04
	};

	static_assert(sizeof(AITimer) == 0x08);
}
