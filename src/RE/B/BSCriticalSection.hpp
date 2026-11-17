#pragma once

namespace RE
{
	class BSCriticalSection
	{
	public:
		BSCriticalSection() noexcept;
		~BSCriticalSection() noexcept;

		BSCriticalSection(const BSCriticalSection&) = delete;
		BSCriticalSection(BSCriticalSection&&) = delete;

		auto operator=(const BSCriticalSection&) -> BSCriticalSection& = delete;
		auto operator=(BSCriticalSection&&) -> BSCriticalSection& = delete;

		[[nodiscard]]
		auto try_lock() noexcept -> bool;

		void lock() noexcept;
		void unlock() noexcept;

	private:
		// members
		REX::W32::CRITICAL_SECTION _criticalSection; // 0x00
	};

	static_assert(sizeof(BSCriticalSection) == 0x28);
}
