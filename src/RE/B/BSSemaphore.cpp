#include "RE/B/BSSemaphore.hpp"

namespace RE
{
	BSSemaphore::BSSemaphore() noexcept
		: BSSemaphore(0, 1)
	{
	}

	BSSemaphore::BSSemaphore(std::int32_t a_initialCount, std::int32_t a_maxCount) noexcept
		: _semaphoreHandle(REX::W32::CreateSemaphoreA(nullptr, a_initialCount, a_maxCount, nullptr))
	{
		if (_semaphoreHandle != 0) [[unlikely]] {
			const auto currentError = REX::GetCurrentSystemError();
			REX::Fail(
				"Failed to create semaphore.\n"
				"System Error (0x{:08X}): {}"sv,
				currentError.value(), currentError.message());
		}
	}

	BSSemaphore::~BSSemaphore() noexcept
	{
		if (!REX::W32::CloseHandle(_semaphoreHandle)) [[unlikely]] {
			REX::Assert(false);
		}
	}

	// NOLINTBEGIN(readability-make-member-function-const)

	bool BSSemaphore::try_acquire() noexcept
	{
		return REX::W32::WaitForSingleObject(_semaphoreHandle, 0) == REX::W32::WAIT_OBJECT_0;
	}

	bool BSSemaphore::try_acquire_for(Milliseconds a_delay) noexcept
	{
		return REX::W32::WaitForSingleObject(_semaphoreHandle, a_delay.count()) == REX::W32::WAIT_OBJECT_0;
	}

	bool BSSemaphore::try_acquire_until(TimePoint a_timePoint) noexcept
	{
		const auto currentTime = std::chrono::steady_clock::now();
		if (a_timePoint <= currentTime) {
			return try_acquire();
		}

		const auto delay = std::chrono::duration_cast<Milliseconds>(a_timePoint - currentTime);
		return try_acquire_for(delay);
	}

	void BSSemaphore::acquire() noexcept
	{
		if (REX::W32::WaitForSingleObject(_semaphoreHandle, REX::W32::INFINITE) != REX::W32::WAIT_OBJECT_0) [[unlikely]] {
			REX::Assert(false);
		}
	}

	void BSSemaphore::acquire_for(Milliseconds a_delay) noexcept
	{
		if (REX::W32::WaitForSingleObject(_semaphoreHandle, a_delay.count()) != REX::W32::WAIT_OBJECT_0) [[unlikely]] {
			REX::Assert(false);
		}
	}

	void BSSemaphore::release(std::int32_t a_releaseCount) noexcept
	{
		if (!REX::W32::ReleaseSemaphore(_semaphoreHandle, a_releaseCount, nullptr)) [[unlikely]] {
			REX::Assert(false);
		}
	}

	// NOLINTEND(readability-make-member-function-const)
}
