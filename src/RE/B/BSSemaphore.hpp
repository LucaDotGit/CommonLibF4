#pragma once

namespace RE
{
	class BSSemaphore
	{
	public:
		using Milliseconds = std::chrono::duration<std::uint32_t, std::chrono::milliseconds::period>;
		using TimePoint = std::chrono::time_point<std::chrono::steady_clock, Milliseconds>;

		BSSemaphore() noexcept;
		BSSemaphore(std::int32_t a_initialCount, std::int32_t a_maxCount) noexcept;

		~BSSemaphore() noexcept;

		BSSemaphore(const BSSemaphore&) = delete;
		BSSemaphore(BSSemaphore&&) = delete;

		auto operator=(const BSSemaphore&) -> BSSemaphore& = delete;
		auto operator=(BSSemaphore&&) -> BSSemaphore& = delete;

		[[nodiscard]]
		auto try_acquire() noexcept -> bool;
		[[nodiscard]]
		auto try_acquire_for(Milliseconds a_delay) noexcept -> bool;
		[[nodiscard]]
		auto try_acquire_until(TimePoint a_timePoint) noexcept -> bool;

		void acquire() noexcept;
		void acquire_for(Milliseconds a_delay) noexcept;
		void release(std::int32_t a_releaseCount = 1) noexcept;

	private:
		// members
		REX::W32::HANDLE _semaphoreHandle; // 0x00
	};

	static_assert(sizeof(BSSemaphore) == 0x08);
}
