#pragma once

namespace RE
{
	class hkCriticalSection
	{
	public:
		hkCriticalSection() noexcept;
		explicit hkCriticalSection(std::uint32_t a_spinCount) noexcept;

		~hkCriticalSection() noexcept;

		hkCriticalSection(const hkCriticalSection&) = delete;
		hkCriticalSection(hkCriticalSection&&) = delete;

		auto operator=(const hkCriticalSection&) -> hkCriticalSection& = delete;
		auto operator=(hkCriticalSection&&) -> hkCriticalSection& = delete;

		[[nodiscard]]
		auto try_lock() noexcept -> bool;

		void lock() noexcept;
		void unlock() noexcept;

	private:
		// members
		REX::W32::CRITICAL_SECTION _criticalSection; // 0x00
	};

	static_assert(sizeof(hkCriticalSection) == 0x28);

	class hkCriticalSectionLock
	{
	public:
		explicit hkCriticalSectionLock(hkCriticalSection& a_section) :
			_criticalSection(std::addressof(a_section))
		{
			_criticalSection->lock();
		}

		~hkCriticalSectionLock()
		{
			_criticalSection->unlock();
		}

		hkCriticalSectionLock(const hkCriticalSectionLock&) = delete;
		hkCriticalSectionLock(hkCriticalSectionLock&&) noexcept = default;

		auto operator=(const hkCriticalSectionLock&) -> hkCriticalSectionLock& = delete;
		auto operator=(hkCriticalSectionLock&&) noexcept -> hkCriticalSectionLock& = default;

	private:
		// members
		hkCriticalSection* _criticalSection; // 0x00
	};

	static_assert(sizeof(hkCriticalSectionLock) == 0x08);
}
