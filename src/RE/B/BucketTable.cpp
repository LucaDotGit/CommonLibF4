#include "RE/B/BucketTable.hpp"

namespace RE
{
	bool BucketTable::AlignedLock::try_lock_shared() noexcept
	{
		auto atomicLock = REX::AtomicRef(_lock);

		auto expectedLock = atomicLock.load(std::memory_order_acquire);
		return expectedLock < READ_WRITE_LOCK_ACQUIRED_VALUE &&
			   atomicLock.compare_exchange_strong(expectedLock, expectedLock + 1,
				   std::memory_order_acq_rel, std::memory_order_relaxed);
	}

	bool BucketTable::AlignedLock::try_lock() noexcept
	{
		auto atomicLock = REX::AtomicRef(_lock);

		auto expectedLock = 0ui32;
		return atomicLock.compare_exchange_strong(expectedLock, READ_WRITE_LOCK_ACQUIRED_VALUE,
			std::memory_order_acq_rel, std::memory_order_relaxed);
	}

	void BucketTable::AlignedLock::lock_shared() noexcept
	{
		auto atomicLock = REX::AtomicRef(_lock);
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

	void BucketTable::AlignedLock::lock() noexcept
	{
		auto atomicLock = REX::AtomicRef(_lock);
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
	}

	void BucketTable::AlignedLock::unlock_shared() noexcept
	{
		auto atomicLock = REX::AtomicRef(_lock);
		atomicLock.fetch_sub(1, std::memory_order_acq_rel);
	}

	void BucketTable::AlignedLock::unlock() noexcept
	{
		auto atomicLock = REX::AtomicRef(_lock);

		auto expectedLock = READ_WRITE_LOCK_ACQUIRED_VALUE;
		if (!atomicLock.compare_exchange_strong(expectedLock, 0,
				std::memory_order_acq_rel, std::memory_order_relaxed)) {
			atomicLock.fetch_sub(1, std::memory_order_acq_rel);
			return;
		}
	}

	BucketTable& BucketTable::GetSingleton()
	{
		using FuncType = decltype(&BucketTable::GetSingleton);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BucketTable::Singleton };
		return std::invoke(FUNC);
	}

	template class BSAutoLockReadLockPolicy<BucketTable::AlignedLock>;
	static_assert(std::is_empty_v<BSAutoLockReadLockPolicy<BucketTable::AlignedLock>>);

	template class BSAutoLockWriteLockPolicy<BucketTable::AlignedLock>;
	static_assert(std::is_empty_v<BSAutoLockWriteLockPolicy<BucketTable::AlignedLock>>);
}
