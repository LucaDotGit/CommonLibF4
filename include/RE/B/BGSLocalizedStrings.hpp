#pragma once

#include "RE/M/MemoryManager.hpp"

namespace RE::BGSLocalizedStrings
{
	class ScrapStringBuffer
	{
	public:
		ScrapStringBuffer() noexcept = default;
		~ScrapStringBuffer() noexcept = default;

		ScrapStringBuffer(const ScrapStringBuffer&) = delete;
		ScrapStringBuffer(ScrapStringBuffer&&) noexcept = default;

		ScrapStringBuffer& operator=(const ScrapStringBuffer&) = delete;
		ScrapStringBuffer& operator=(ScrapStringBuffer&&) noexcept = default;

		[[nodiscard]] explicit operator bool() const noexcept { return static_cast<bool>(buffer); }

		[[nodiscard]] const char* data() const noexcept { return reinterpret_cast<const char*>(buffer.data()) + offset; }

		// members
		MemoryManager::AutoScrapBuffer buffer; // 00
		std::size_t offset{ 0 };			   // 08
	};
	static_assert(sizeof(ScrapStringBuffer) == 0x10);
}
