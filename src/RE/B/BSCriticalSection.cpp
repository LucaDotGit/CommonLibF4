#include "RE/B/BSCriticalSection.hpp"

namespace RE
{
	BSCriticalSection::BSCriticalSection() noexcept :
		_criticalSection()
	{
		REX::W32::InitializeCriticalSection(std::addressof(_criticalSection));
	}

	BSCriticalSection::~BSCriticalSection() noexcept
	{
		REX::W32::DeleteCriticalSection(std::addressof(_criticalSection));
	}

	auto BSCriticalSection::try_lock() noexcept -> bool
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
}
