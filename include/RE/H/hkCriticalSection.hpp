#pragma once

namespace RE
{
	class hkCriticalSection
	{
	public:
		explicit hkCriticalSection() noexcept;
		explicit hkCriticalSection(std::uint32_t a_spinCount) noexcept;

		~hkCriticalSection() noexcept;

		hkCriticalSection(const hkCriticalSection&) = delete;
		hkCriticalSection(hkCriticalSection&&) = delete;

		hkCriticalSection& operator=(const hkCriticalSection&) = delete;
		hkCriticalSection& operator=(hkCriticalSection&&) = delete;

		[[nodiscard]] bool try_lock() noexcept;

		void lock() noexcept;
		void unlock() noexcept;

	private:
		// members
		REX::W32::CRITICAL_SECTION _criticalSection; // 00
	};
	static_assert(sizeof(hkCriticalSection) == 0x28);

	class hkCriticalSectionLock
	{
	public:
		hkCriticalSectionLock(hkCriticalSection& a_section)
			: _criticalSection(std::addressof(a_section))
		{
			_criticalSection->lock();
		}

		~hkCriticalSectionLock()
		{
			_criticalSection->unlock();
		}

	protected:
		// members
		hkCriticalSection* _criticalSection; // 00
	};
	static_assert(sizeof(hkCriticalSectionLock) == 0x08);
}
