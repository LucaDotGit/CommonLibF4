#include "RE/B/BSReadWriteLock.hpp"

namespace RE
{
	auto BSReadWriteLock::try_lock_shared() noexcept -> bool
	{
		const auto atomicLock = REX::AtomicRef(_lock);

		const auto currentThreadID = REX::W32::GetCurrentThreadId();
		if (_writerThread == currentThreadID) {
			atomicLock.fetch_add(1, std::memory_order_acq_rel);
			return true;
		}

		auto expectedLock = atomicLock.load(std::memory_order_acquire);
		return expectedLock < READ_WRITE_LOCK_ACQUIRED_VALUE && atomicLock.compare_exchange_strong(
																	expectedLock,
																	expectedLock + 1,
																	std::memory_order_acq_rel,
																	std::memory_order_relaxed);
	}

	auto BSReadWriteLock::try_lock() noexcept -> bool
	{
		const auto atomicLock = REX::AtomicRef(_lock);

		const auto currentThreadID = REX::W32::GetCurrentThreadId();
		if (_writerThread == currentThreadID) {
			atomicLock.fetch_add(1, std::memory_order_acq_rel);
			return true;
		}

		auto expectedLock = static_cast<std::uint32_t>(0);
		if (!atomicLock.compare_exchange_strong(
				expectedLock,
				READ_WRITE_LOCK_ACQUIRED_VALUE,
				std::memory_order_acq_rel,
				std::memory_order_relaxed)) {
			return false;
		}

		_writerThread = currentThreadID;
		std::atomic_thread_fence(std::memory_order_seq_cst);

		return true;
	}

	void BSReadWriteLock::lock_shared() noexcept
	{
		const auto atomicLock = REX::AtomicRef(_lock);

		const auto currentThreadID = REX::W32::GetCurrentThreadId();
		if (_writerThread == currentThreadID) {
			atomicLock.fetch_add(1, std::memory_order_acq_rel);
			return;
		}

		auto spinCount = static_cast<std::uint32_t>(0);

		while (true) {
			auto expectedLock = atomicLock.load(std::memory_order_acquire);
			if (expectedLock >= READ_WRITE_LOCK_ACQUIRED_VALUE || !atomicLock.compare_exchange_weak(
																	  expectedLock,
																	  expectedLock + 1,
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
	}

	void BSReadWriteLock::lock() noexcept
	{
		const auto atomicLock = REX::AtomicRef(_lock);

		const auto currentThreadID = REX::W32::GetCurrentThreadId();
		if (_writerThread == currentThreadID) {
			atomicLock.fetch_add(1, std::memory_order_acq_rel);
			return;
		}

		auto spinCount = static_cast<std::uint32_t>(0);

		while (true) {
			auto expectedLock = static_cast<std::uint32_t>(0);
			if (!atomicLock.compare_exchange_weak(
					expectedLock,
					READ_WRITE_LOCK_ACQUIRED_VALUE,
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

		_writerThread = currentThreadID;
		std::atomic_thread_fence(std::memory_order_seq_cst);
	}

	void BSReadWriteLock::unlock_shared() noexcept
	{
		const auto atomicLock = REX::AtomicRef(_lock);
		atomicLock.fetch_sub(1, std::memory_order_acq_rel);
	}

	void BSReadWriteLock::unlock() noexcept
	{
		const auto atomicLock = REX::AtomicRef(_lock);

		auto expectedLock = READ_WRITE_LOCK_ACQUIRED_VALUE;
		if (!atomicLock.compare_exchange_strong(
				expectedLock,
				0,
				std::memory_order_acq_rel,
				std::memory_order_relaxed)) {
			atomicLock.fetch_sub(1, std::memory_order_acq_rel);
			return;
		}

		_writerThread = REX::W32::EMPTY_THREAD_ID;
		std::atomic_thread_fence(std::memory_order_seq_cst);
	}
}
