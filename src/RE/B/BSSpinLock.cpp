#include "RE/B/BSSpinLock.hpp"

namespace RE
{
	auto BSSpinLock::try_lock() noexcept -> bool
	{
		const auto atomicLock = REX::AtomicRef(_lockCount);

		const auto currentThreadID = REX::W32::GetCurrentThreadId();
		if (_owningThread == currentThreadID) {
			atomicLock.fetch_add(1, std::memory_order_acq_rel);
			return true;
		}

		auto expectedLock = static_cast<std::uint32_t>(0);
		if (!atomicLock.compare_exchange_strong(
				expectedLock,
				1,
				std::memory_order_acq_rel,
				std::memory_order_relaxed)) {
			return false;
		}

		_owningThread = currentThreadID;
		std::atomic_thread_fence(std::memory_order_seq_cst);

		return true;
	}

	void BSSpinLock::lock() noexcept
	{
		const auto atomicLock = REX::AtomicRef(_lockCount);

		const auto currentThreadID = REX::W32::GetCurrentThreadId();
		if (_owningThread == currentThreadID) {
			atomicLock.fetch_add(1, std::memory_order_acq_rel);
			return;
		}

		auto spinCount = static_cast<std::uint32_t>(0);

		while (true) {
			auto expectedLock = static_cast<std::uint32_t>(0);
			if (!atomicLock.compare_exchange_weak(
					expectedLock,
					1,
					std::memory_order_acq_rel,
					std::memory_order_relaxed)) {
				if (++spinCount < Impl::SPIN_LOCK_YIELD_COUNT) {
					std::this_thread::yield();
					continue;
				}

				std::this_thread::sleep_for(Impl::SPIN_LOCK_SLEEP_DURATION);
				continue;
			}

			break;
		}

		_owningThread = currentThreadID;
		std::atomic_thread_fence(std::memory_order_seq_cst);
	}

	void BSSpinLock::unlock() noexcept
	{
		const auto atomicLock = REX::AtomicRef(_lockCount);

		auto expectedLock = static_cast<std::uint32_t>(1);
		if (!atomicLock.compare_exchange_strong(
				expectedLock,
				0,
				std::memory_order_acq_rel,
				std::memory_order_relaxed)) {
			atomicLock.fetch_sub(1, std::memory_order_acq_rel);
			return;
		}

		_owningThread = REX::W32::EMPTY_THREAD_ID;
		std::atomic_thread_fence(std::memory_order_seq_cst);
	}
}
