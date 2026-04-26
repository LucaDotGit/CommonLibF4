#pragma once

namespace Scaleform
{
	using ThreadId = std::uintptr_t;

	[[nodiscard]] inline ThreadId GetCurrentThreadId() noexcept
	{
		return REX::W32::GetCurrentThreadId();
	}
}
