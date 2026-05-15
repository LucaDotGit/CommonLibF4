#include "RE/B/BSSpinLock.hpp"

namespace RE
{
	bool BSNonReentrantSpinLock::try_lock() noexcept
	{
		auto atomicLock = REX::AtomicRef(_lock);

		auto expectedLock = 0ui32;
		return atomicLock.compare_exchange_strong(expectedLock, 1,
			std::memory_order_acq_rel, std::memory_order_relaxed);
	}

	void BSNonReentrantSpinLock::lock() noexcept
	{
		auto atomicLock = REX::AtomicRef(_lock);
		auto spinCount = 0ui32;

		while (true) {
			auto expectedLock = 0ui32;
			if (!atomicLock.compare_exchange_weak(expectedLock, 1,
					std::memory_order_acq_rel, std::memory_order_relaxed)) {
				REX::W32::Sleep(++spinCount < Impl::SPIN_LOCK_YIELD_COUNT ? Impl::SPIN_LOCK_YIELD_DURATION_MS : Impl::SPIN_LOCK_SLEEP_DURATION_MS);
				continue;
			}

			break;
		}
	}

	void BSNonReentrantSpinLock::unlock() noexcept
	{
		auto atomicLock = REX::AtomicRef(_lock);

		auto expectedLock = 1ui32;
		std::ignore = atomicLock.compare_exchange_strong(expectedLock, 0,
			std::memory_order_acq_rel, std::memory_order_relaxed);
	}

	bool BSSpinLock::try_lock() noexcept
	{
		auto atomicLock = REX::AtomicRef(_lockCount);

		const auto currentThreadID = REX::W32::GetCurrentThreadId();
		if (_owningThread == currentThreadID) {
			atomicLock.fetch_add(1, std::memory_order_acq_rel);
			return true;
		}

		auto expectedLock = 0ui32;
		if (!atomicLock.compare_exchange_strong(expectedLock, 1,
				std::memory_order_acq_rel, std::memory_order_relaxed)) {
			return false;
		}

		_owningThread = currentThreadID;
		std::atomic_thread_fence(std::memory_order_seq_cst);

		return true;
	}

	void BSSpinLock::lock() noexcept
	{
		auto atomicLock = REX::AtomicRef(_lockCount);

		const auto currentThreadID = REX::W32::GetCurrentThreadId();
		if (_owningThread == currentThreadID) {
			atomicLock.fetch_add(1, std::memory_order_acq_rel);
			return;
		}

		auto spinCount = 0ui32;

		while (true) {
			auto expectedLock = 0ui32;
			if (!atomicLock.compare_exchange_weak(expectedLock, 1,
					std::memory_order_acq_rel, std::memory_order_relaxed)) {
				REX::W32::Sleep(++spinCount < Impl::SPIN_LOCK_YIELD_COUNT ? Impl::SPIN_LOCK_YIELD_DURATION_MS : Impl::SPIN_LOCK_SLEEP_DURATION_MS);
				continue;
			}

			break;
		}

		_owningThread = currentThreadID;
		std::atomic_thread_fence(std::memory_order_seq_cst);
	}

	void BSSpinLock::unlock() noexcept
	{
		auto atomicLock = REX::AtomicRef(_lockCount);

		auto expectedLock = 1ui32;
		if (!atomicLock.compare_exchange_strong(expectedLock, 0,
				std::memory_order_acq_rel, std::memory_order_relaxed)) {
			atomicLock.fetch_sub(1, std::memory_order_acq_rel);
			return;
		}

		_owningThread = REX::W32::EMPTY_THREAD_ID;
		std::atomic_thread_fence(std::memory_order_seq_cst);
	}

	bool BSReadWriteLock::try_lock_shared() noexcept
	{
		auto atomicLock = REX::AtomicRef(_lock);

		const auto currentThreadID = REX::W32::GetCurrentThreadId();
		if (_writerThread == currentThreadID) {
			atomicLock.fetch_add(1, std::memory_order_acq_rel);
			return true;
		}

		auto expectedLock = atomicLock.load(std::memory_order_acquire);
		return expectedLock < READ_WRITE_LOCK_ACQUIRED_VALUE &&
			   atomicLock.compare_exchange_strong(expectedLock, expectedLock + 1,
				   std::memory_order_acq_rel, std::memory_order_relaxed);
	}

	bool BSReadWriteLock::try_lock() noexcept
	{
		auto atomicLock = REX::AtomicRef(_lock);

		const auto currentThreadID = REX::W32::GetCurrentThreadId();
		if (_writerThread == currentThreadID) {
			atomicLock.fetch_add(1, std::memory_order_acq_rel);
			return true;
		}

		auto expectedLock = 0ui32;
		if (!atomicLock.compare_exchange_strong(expectedLock, READ_WRITE_LOCK_ACQUIRED_VALUE,
				std::memory_order_acq_rel, std::memory_order_relaxed)) {
			return false;
		}

		_writerThread = currentThreadID;
		std::atomic_thread_fence(std::memory_order_seq_cst);

		return true;
	}

	void BSReadWriteLock::lock_shared() noexcept
	{
		auto atomicLock = REX::AtomicRef(_lock);

		const auto currentThreadID = REX::W32::GetCurrentThreadId();
		if (_writerThread == currentThreadID) {
			atomicLock.fetch_add(1, std::memory_order_acq_rel);
			return;
		}

		auto spinCount = 0ui32;

		while (true) {
			auto expectedLock = atomicLock.load(std::memory_order_acquire);
			if (expectedLock >= READ_WRITE_LOCK_ACQUIRED_VALUE ||
				!atomicLock.compare_exchange_weak(expectedLock, expectedLock + 1,
					std::memory_order_acq_rel, std::memory_order_relaxed)) {
				REX::W32::Sleep(++spinCount < Impl::SPIN_LOCK_YIELD_COUNT ? Impl::SPIN_LOCK_YIELD_DURATION_MS : Impl::SPIN_LOCK_SLEEP_DURATION_MS);
				continue;
			}

			break;
		}
	}

	void BSReadWriteLock::lock() noexcept
	{
		auto atomicLock = REX::AtomicRef(_lock);

		const auto currentThreadID = REX::W32::GetCurrentThreadId();
		if (_writerThread == currentThreadID) {
			atomicLock.fetch_add(1, std::memory_order_acq_rel);
			return;
		}

		auto spinCount = 0ui32;

		while (true) {
			auto expectedLock = 0ui32;
			if (!atomicLock.compare_exchange_weak(expectedLock, READ_WRITE_LOCK_ACQUIRED_VALUE,
					std::memory_order_acq_rel, std::memory_order_relaxed)) {
				REX::W32::Sleep(++spinCount < Impl::SPIN_LOCK_YIELD_COUNT ? Impl::SPIN_LOCK_YIELD_DURATION_MS : Impl::SPIN_LOCK_SLEEP_DURATION_MS);
				continue;
			}

			break;
		}

		_writerThread = currentThreadID;
		std::atomic_thread_fence(std::memory_order_seq_cst);
	}

	void BSReadWriteLock::unlock_shared() noexcept
	{
		auto atomicLock = REX::AtomicRef(_lock);
		atomicLock.fetch_sub(1, std::memory_order_acq_rel);
	}

	void BSReadWriteLock::unlock() noexcept
	{
		auto atomicLock = REX::AtomicRef(_lock);

		auto expectedLock = READ_WRITE_LOCK_ACQUIRED_VALUE;
		if (!atomicLock.compare_exchange_strong(expectedLock, 0,
				std::memory_order_acq_rel, std::memory_order_relaxed)) {
			atomicLock.fetch_sub(1, std::memory_order_acq_rel);
			return;
		}

		_writerThread = REX::W32::EMPTY_THREAD_ID;
		std::atomic_thread_fence(std::memory_order_seq_cst);
	}

	template class BSAutoLockDefaultPolicy<BSNonReentrantSpinLock>;
	static_assert(std::is_empty_v<BSAutoLockDefaultPolicy<BSNonReentrantSpinLock>>);

	template class BSAutoLockDefaultPolicy<BSSpinLock>;
	static_assert(std::is_empty_v<BSAutoLockDefaultPolicy<BSSpinLock>>);

	template class BSAutoLockWriteLockPolicy<BSReadWriteLock>;
	static_assert(std::is_empty_v<BSAutoLockWriteLockPolicy<BSReadWriteLock>>);

	template class BSAutoLockReadLockPolicy<BSReadWriteLock>;
	static_assert(std::is_empty_v<BSAutoLockReadLockPolicy<BSReadWriteLock>>);

	template class BSAutoLock<BSNonReentrantSpinLock, BSAutoLockDefaultPolicy>;
	static_assert(sizeof(BSAutoLock<BSNonReentrantSpinLock, BSAutoLockDefaultPolicy>) == 0x08);

	template class BSAutoLock<BSReadWriteLock, BSAutoLockReadLockPolicy>;
	static_assert(sizeof(BSAutoLock<BSReadWriteLock, BSAutoLockReadLockPolicy>) == 0x08);

	template class BSAutoLock<BSReadWriteLock, BSAutoLockWriteLockPolicy>;
	static_assert(sizeof(BSAutoLock<BSReadWriteLock, BSAutoLockWriteLockPolicy>) == 0x08);

	template class BSAutoLock<BSSpinLock, BSAutoLockDefaultPolicy>;
	static_assert(sizeof(BSAutoLock<BSSpinLock, BSAutoLockDefaultPolicy>) == 0x08);
}
