#include "RE/B/BSNonReentrantSpinLock.hpp"

namespace RE
{
	auto BSNonReentrantSpinLock::try_lock() noexcept -> bool
	{
		const auto atomicLock = REX::AtomicRef(_lock);

		auto expectedLock = static_cast<std::uint32_t>(0);
		return atomicLock.compare_exchange_strong(
			expectedLock,
			1,
			std::memory_order_acq_rel,
			std::memory_order_relaxed);
	}

	void BSNonReentrantSpinLock::lock() noexcept
	{
		const auto atomicLock = REX::AtomicRef(_lock);
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
	}

	void BSNonReentrantSpinLock::unlock() noexcept
	{
		const auto atomicLock = REX::AtomicRef(_lock);

		auto expectedLock = static_cast<std::uint32_t>(1);
		std::ignore =
			atomicLock.compare_exchange_strong(expectedLock, 0, std::memory_order_acq_rel, std::memory_order_relaxed);
	}
}
