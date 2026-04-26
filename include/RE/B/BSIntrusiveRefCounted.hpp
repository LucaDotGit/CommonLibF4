#pragma once

#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class BSIntrusiveRefCounted
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSIntrusiveRefCounted };

		GAME_HEAP_REDEFINE_NEW(BSIntrusiveRefCounted);

		[[nodiscard]] std::uint32_t QRefCount() const noexcept;

		std::uint32_t IncRef() noexcept;
		std::uint32_t DecRef() noexcept;

		// members
		volatile std::uint32_t refCount{ 0 }; // 00
	};
	static_assert(sizeof(BSIntrusiveRefCounted) == 0x04);
}
