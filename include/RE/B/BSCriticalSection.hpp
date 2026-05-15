#pragma once

#include "RE/B/BSSpinLockPolicy.hpp"

namespace RE
{
	class BSCriticalSection
	{
	public:
		BSCriticalSection() noexcept;
		~BSCriticalSection() noexcept;

		BSCriticalSection(const BSCriticalSection&) = delete;
		BSCriticalSection(BSCriticalSection&&) = delete;

		BSCriticalSection& operator=(const BSCriticalSection&) = delete;
		BSCriticalSection& operator=(BSCriticalSection&&) = delete;

		[[nodiscard]] bool try_lock() noexcept;

		void lock() noexcept;
		void unlock() noexcept;

	private:
		// members
		REX::W32::CRITICAL_SECTION _criticalSection; // 00
	};
	static_assert(sizeof(BSCriticalSection) == 0x28);

	extern template class BSAutoLockDefaultPolicy<BSCriticalSection>;
	extern template class BSAutoLock<BSCriticalSection, BSAutoLockDefaultPolicy>;
}
