#pragma once

#include "RE/B/BSSpinLockPolicy.hpp"

namespace RE
{
	class BSSpinLock
	{
	public:
		BSSpinLock() noexcept = default;
		~BSSpinLock() noexcept = default;

		BSSpinLock(const BSSpinLock&) = delete;
		BSSpinLock(BSSpinLock&&) = delete;

		auto operator=(const BSSpinLock&) -> BSSpinLock& = delete;
		auto operator=(BSSpinLock&&) -> BSSpinLock& = delete;

		[[nodiscard]]
		auto try_lock() noexcept -> bool;

		void lock() noexcept;
		void unlock() noexcept;

	private:
		// members
		REX::W32::THREAD_ID _owningThread{REX::W32::EMPTY_THREAD_ID}; // 0x00
		volatile std::uint32_t _lockCount{0};						  // 0x04
	};

	static_assert(sizeof(BSSpinLock) == 0x08);

	template <class Mutex>
	using BSAutoSpinLock = BSAutoLock<Mutex, BSAutoLockDefaultPolicy>;
	static_assert(sizeof(BSAutoSpinLock<BSSpinLock>) == 0x08);
}
