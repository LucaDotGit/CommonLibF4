#pragma once

#include "REX/W32/CORE.hpp"

namespace REX
{
	using NumericThreadId = REX::W32::THREAD_ID;

	static_assert(
		sizeof(NumericThreadId) == sizeof(std::thread::id) && alignof(NumericThreadId) == alignof(std::thread::id));

	[[nodiscard]]
	constexpr auto GetThreadId(NumericThreadId a_threadId) noexcept -> std::thread::id
	{
		return {std::bit_cast<std::thread::id>(a_threadId)};
	}

	[[nodiscard]]
	constexpr auto GetNumericThreadId(std::thread::id a_threadId) noexcept -> NumericThreadId
	{
		return std::bit_cast<NumericThreadId>(a_threadId);
	}

	[[nodiscard]]
	auto GetCurrentThreadId() noexcept -> std::thread::id;

	[[nodiscard]]
	auto GetCurrentNumericThreadId() noexcept -> NumericThreadId;

	[[nodiscard]]
	auto GetMaxThreadCount() noexcept -> std::size_t;
}
