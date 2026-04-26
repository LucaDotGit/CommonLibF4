#pragma once

#include "RE/B/BSSpinLockPolicy.hpp"

namespace RE
{
	class BSNonReentrantSpinLock
	{
	public:
		BSNonReentrantSpinLock() noexcept = default;
		~BSNonReentrantSpinLock() noexcept = default;

		BSNonReentrantSpinLock(const BSNonReentrantSpinLock&) = delete;
		BSNonReentrantSpinLock(BSNonReentrantSpinLock&&) = delete;

		BSNonReentrantSpinLock& operator=(const BSNonReentrantSpinLock&) = delete;
		BSNonReentrantSpinLock& operator=(BSNonReentrantSpinLock&&) = delete;

		[[nodiscard]] bool try_lock() noexcept;

		void lock() noexcept;
		void unlock() noexcept;

	private:
		// members
		volatile std::uint32_t _lock{ 0 }; // 00
	};
	static_assert(sizeof(BSNonReentrantSpinLock) == 0x04);

	class BSSpinLock
	{
	public:
		BSSpinLock() noexcept = default;
		~BSSpinLock() noexcept = default;

		BSSpinLock(const BSSpinLock&) = delete;
		BSSpinLock(BSSpinLock&&) = delete;

		BSSpinLock& operator=(const BSSpinLock&) = delete;
		BSSpinLock& operator=(BSSpinLock&&) = delete;

		[[nodiscard]] bool try_lock() noexcept;

		void lock() noexcept;
		void unlock() noexcept;

	private:
		// members
		REX::W32::THREAD_ID _owningThread{ REX::W32::EMPTY_THREAD_ID }; // 00
		volatile std::uint32_t _lockCount{ 0 };							// 04
	};
	static_assert(sizeof(BSSpinLock) == 0x08);

	class BSReadWriteLock
	{
	public:
		BSReadWriteLock() noexcept = default;
		~BSReadWriteLock() noexcept = default;

		BSReadWriteLock(const BSReadWriteLock&) = delete;
		BSReadWriteLock(BSReadWriteLock&&) = delete;

		BSReadWriteLock& operator=(const BSReadWriteLock&) = delete;
		BSReadWriteLock& operator=(BSReadWriteLock&&) = delete;

		[[nodiscard]] bool try_lock_shared() noexcept;
		[[nodiscard]] bool try_lock() noexcept;

		void lock_shared() noexcept;
		void lock() noexcept;

		void unlock_shared() noexcept;
		void unlock() noexcept;

	private:
		inline static constexpr auto READ_WRITE_LOCK_ACQUIRED_VALUE = 0x80000001ui32;

		// members
		REX::W32::THREAD_ID _writerThread{ REX::W32::EMPTY_THREAD_ID }; // 00
		volatile std::uint32_t _lock{ 0 };								// 04
	};
	static_assert(sizeof(BSReadWriteLock) == 0x08);

	extern template class BSAutoLockDefaultPolicy<BSNonReentrantSpinLock>;
	extern template class BSAutoLockDefaultPolicy<BSSpinLock>;
	extern template class BSAutoLockReadLockPolicy<BSReadWriteLock>;
	extern template class BSAutoLockWriteLockPolicy<BSReadWriteLock>;

	extern template class BSAutoLock<BSNonReentrantSpinLock, BSAutoLockDefaultPolicy>;
	extern template class BSAutoLock<BSSpinLock, BSAutoLockDefaultPolicy>;
	extern template class BSAutoLock<BSReadWriteLock, BSAutoLockReadLockPolicy>;
	extern template class BSAutoLock<BSReadWriteLock, BSAutoLockWriteLockPolicy>;

	using BSAutoReadLock = BSAutoLock<BSReadWriteLock, BSAutoLockReadLockPolicy>;
	using BSAutoWriteLock = BSAutoLock<BSReadWriteLock, BSAutoLockWriteLockPolicy>;
}
