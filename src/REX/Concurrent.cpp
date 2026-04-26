#include "REX/Concurrent.hpp"

namespace REX
{
	static_assert(sizeof(std::thread::id) == sizeof(NumericThreadId));

	std::thread::id GetCurrentThreadId() noexcept
	{
		return std::this_thread::get_id();
	}

	NumericThreadId GetCurrentNumericThreadId() noexcept
	{
		return std::bit_cast<NumericThreadId>(std::this_thread::get_id());
	}

	std::size_t GetMaxThreadCount() noexcept
	{
		const auto threadCount = std::thread::hardware_concurrency();
		return threadCount > 0 ? threadCount : 1;
	}
}
