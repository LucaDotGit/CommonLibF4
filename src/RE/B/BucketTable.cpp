#include "RE/B/BucketTable.hpp"

#include "RE/B/BSSpinLockPolicy.hpp"

namespace RE
{
	auto BucketTable::AlignedLock::try_lock_shared() noexcept -> bool
	{
		const auto atomicLock = REX::AtomicRef(_lock);

		auto expectedLock = atomicLock.load(std::memory_order_acquire);
		return expectedLock < READ_WRITE_LOCK_ACQUIRED_VALUE && atomicLock.compare_exchange_strong(
																	expectedLock,
																	expectedLock + 1,
																	std::memory_order_acq_rel,
																	std::memory_order_relaxed);
	}

	auto BucketTable::AlignedLock::try_lock() noexcept -> bool
	{
		const auto atomicLock = REX::AtomicRef(_lock);

		auto expectedLock = static_cast<std::uint32_t>(0);
		return atomicLock.compare_exchange_strong(
			expectedLock,
			READ_WRITE_LOCK_ACQUIRED_VALUE,
			std::memory_order_acq_rel,
			std::memory_order_relaxed);
	}

	void BucketTable::AlignedLock::lock_shared() noexcept
	{
		const auto atomicLock = REX::AtomicRef(_lock);
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

	void BucketTable::AlignedLock::lock() noexcept
	{
		const auto atomicLock = REX::AtomicRef(_lock);
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
	}

	void BucketTable::AlignedLock::unlock_shared() noexcept
	{
		const auto atomicLock = REX::AtomicRef(_lock);
		atomicLock.fetch_sub(1, std::memory_order_acq_rel);
	}

	void BucketTable::AlignedLock::unlock() noexcept
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
	}

	auto BucketTable::GetSingleton() -> BucketTable&
	{
		using FuncType = decltype(&BucketTable::GetSingleton);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BucketTable::Singleton);
		return std::invoke(FUNC);
	}
}
