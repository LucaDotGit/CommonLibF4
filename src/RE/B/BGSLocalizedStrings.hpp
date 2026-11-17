#pragma once

#include "RE/M/MemoryManager.hpp"

namespace RE::BGSLocalizedStrings
{
	class ScrapStringBuffer
	{
	public:
		using value_type = char;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using pointer = value_type*;
		using const_pointer = const value_type*;

		ScrapStringBuffer() noexcept = default;
		~ScrapStringBuffer() noexcept = default;

		ScrapStringBuffer(const ScrapStringBuffer&) = delete;
		ScrapStringBuffer(ScrapStringBuffer&&) noexcept = default;

		auto operator=(const ScrapStringBuffer&) -> ScrapStringBuffer& = delete;
		auto operator=(ScrapStringBuffer&&) noexcept -> ScrapStringBuffer& = default;

		[[nodiscard]]
		explicit operator bool() const noexcept
		{
			return static_cast<bool>(buffer);
		}

		[[nodiscard]]
		auto data() noexcept -> pointer
		{
			return reinterpret_cast<pointer>(buffer.data()) + offset;
		}

		[[nodiscard]]
		auto data() const noexcept -> const_pointer
		{
			return reinterpret_cast<const_pointer>(buffer.data()) + offset;
		}

		// members
		MemoryManager::AutoScrapBuffer buffer; // 0x00
		size_type offset{0};				   // 0x08
	};

	static_assert(sizeof(ScrapStringBuffer) == 0x10);
}
