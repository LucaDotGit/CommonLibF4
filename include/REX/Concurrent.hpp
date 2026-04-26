#pragma once

#include "REX/W32/CORE.hpp"

namespace REX
{
	using NumericThreadId = REX::W32::THREAD_ID;

	[[nodiscard]] constexpr std::thread::id GetThreadId(NumericThreadId a_threadId) noexcept
	{
		return { std::bit_cast<std::thread::id>(a_threadId) };
	}

	[[nodiscard]] constexpr NumericThreadId GetNumericThreadId(std::thread::id a_threadId) noexcept
	{
		return std::bit_cast<NumericThreadId>(a_threadId);
	}

	[[nodiscard]] std::thread::id GetCurrentThreadId() noexcept;
	[[nodiscard]] NumericThreadId GetCurrentNumericThreadId() noexcept;

	[[nodiscard]] std::size_t GetMaxThreadCount() noexcept;
}
