#pragma once

namespace RE
{
	class BSNonReentrantSpinLock
	{
	public:
		BSNonReentrantSpinLock() noexcept = default;
		~BSNonReentrantSpinLock() noexcept = default;

		BSNonReentrantSpinLock(const BSNonReentrantSpinLock&) = delete;
		BSNonReentrantSpinLock(BSNonReentrantSpinLock&&) = delete;

		auto operator=(const BSNonReentrantSpinLock&) -> BSNonReentrantSpinLock& = delete;
		auto operator=(BSNonReentrantSpinLock&&) -> BSNonReentrantSpinLock& = delete;

		[[nodiscard]]
		auto try_lock() noexcept -> bool;

		void lock() noexcept;
		void unlock() noexcept;

	private:
		// members
		volatile std::uint32_t _lock{0}; // 0x00
	};

	static_assert(sizeof(BSNonReentrantSpinLock) == 0x04);
}
