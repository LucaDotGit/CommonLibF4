#include "REX/Concurrency.hpp"

namespace REX
{
	auto GetCurrentThreadId() noexcept -> std::thread::id
	{
		return std::this_thread::get_id();
	}

	auto GetCurrentNumericThreadId() noexcept -> NumericThreadId
	{
		return GetNumericThreadId(std::this_thread::get_id());
	}

	auto GetMaxThreadCount() noexcept -> std::size_t
	{
		const auto threadCount = std::thread::hardware_concurrency();
		return threadCount > 0 ? threadCount : 1;
	}
}
