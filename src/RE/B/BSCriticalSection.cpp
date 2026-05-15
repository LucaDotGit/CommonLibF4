#include "RE/B/BSCriticalSection.hpp"

namespace RE
{
	BSCriticalSection::BSCriticalSection() noexcept
		: _criticalSection()
	{
		REX::W32::InitializeCriticalSection(std::addressof(_criticalSection));
	}

	BSCriticalSection::~BSCriticalSection() noexcept
	{
		REX::W32::DeleteCriticalSection(std::addressof(_criticalSection));
	}

	bool BSCriticalSection::try_lock() noexcept
	{
		return REX::W32::TryEnterCriticalSection(std::addressof(_criticalSection));
	}

	void BSCriticalSection::lock() noexcept
	{
		REX::W32::EnterCriticalSection(std::addressof(_criticalSection));
	}

	void BSCriticalSection::unlock() noexcept
	{
		REX::W32::LeaveCriticalSection(std::addressof(_criticalSection));
	}

	template class BSAutoLockDefaultPolicy<BSCriticalSection>;
	static_assert(std::is_empty_v<BSAutoLockDefaultPolicy<BSCriticalSection>>);

	template class BSAutoLock<BSCriticalSection, BSAutoLockDefaultPolicy>;
	static_assert(sizeof(BSAutoLock<BSCriticalSection, BSAutoLockDefaultPolicy>) == 0x08);
}
