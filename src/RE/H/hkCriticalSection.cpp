#include "RE/H/hkCriticalSection.hpp"

#include "RE/H/hkHardwareInfo.hpp"

namespace RE
{
	hkCriticalSection::hkCriticalSection() noexcept :
		_criticalSection()
	{
		REX::W32::InitializeCriticalSection(std::addressof(_criticalSection));
	}

	hkCriticalSection::hkCriticalSection(std::uint32_t a_spinCount) noexcept :
		_criticalSection()
	{
		const auto finalSpinCount =
			static_cast<std::uint32_t>(a_spinCount == 0 ? 0 : 1'000 * hkHardwareInfo::CalcNumHardwareThreads());
		REX::W32::InitializeCriticalSectionAndSpinCount(std::addressof(_criticalSection), finalSpinCount);
	}

	hkCriticalSection::~hkCriticalSection() noexcept
	{
		REX::W32::DeleteCriticalSection(std::addressof(_criticalSection));
	}

	auto hkCriticalSection::try_lock() noexcept -> bool
	{
		return REX::W32::TryEnterCriticalSection(std::addressof(_criticalSection));
	}

	void hkCriticalSection::lock() noexcept
	{
		REX::W32::EnterCriticalSection(std::addressof(_criticalSection));
	}

	void hkCriticalSection::unlock() noexcept
	{
		REX::W32::LeaveCriticalSection(std::addressof(_criticalSection));
	}
}
