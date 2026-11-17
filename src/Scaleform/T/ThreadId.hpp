#pragma once

namespace Scaleform
{
	using ThreadId = std::uintptr_t;

	[[nodiscard]]
	inline auto GetCurrentThreadId() noexcept -> ThreadId
	{
		return REX::W32::GetCurrentThreadId();
	}
}
