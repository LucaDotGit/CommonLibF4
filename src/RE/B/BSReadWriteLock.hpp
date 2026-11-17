#pragma once

#include "RE/B/BSSpinLockPolicy.hpp"

namespace RE
{
	class BSReadWriteLock
	{
	public:
		BSReadWriteLock() noexcept = default;
		~BSReadWriteLock() noexcept = default;

		BSReadWriteLock(const BSReadWriteLock&) = delete;
		BSReadWriteLock(BSReadWriteLock&&) = delete;

		auto operator=(const BSReadWriteLock&) -> BSReadWriteLock& = delete;
		auto operator=(BSReadWriteLock&&) -> BSReadWriteLock& = delete;

		[[nodiscard]]
		auto try_lock_shared() noexcept -> bool;
		[[nodiscard]]
		auto try_lock() noexcept -> bool;

		void lock_shared() noexcept;
		void lock() noexcept;

		void unlock_shared() noexcept;
		void unlock() noexcept;

	private:
		inline static constexpr auto READ_WRITE_LOCK_ACQUIRED_VALUE = static_cast<std::uint32_t>(0x8000'0001);

		// members
		REX::W32::THREAD_ID _writerThread{REX::W32::EMPTY_THREAD_ID}; // 0x00
		volatile std::uint32_t _lock{0};							  // 0x04
	};

	static_assert(sizeof(BSReadWriteLock) == 0x08);

	template <class Mutex>
	using BSAutoReadLock = BSAutoLock<Mutex, BSAutoLockReadLockPolicy>;
	static_assert(sizeof(BSAutoReadLock<BSReadWriteLock>) == 0x08);

	template <class Mutex>
	using BSAutoWriteLock = BSAutoLock<Mutex, BSAutoLockWriteLockPolicy>;
	static_assert(sizeof(BSAutoWriteLock<BSReadWriteLock>) == 0x08);
}
