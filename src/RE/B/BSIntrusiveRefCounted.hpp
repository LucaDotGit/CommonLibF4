#pragma once

#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class BSIntrusiveRefCounted
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSIntrusiveRefCounted;

		GAME_HEAP_REDEFINE_NEW(BSIntrusiveRefCounted);

		[[nodiscard]]
		auto QRefCount() const noexcept -> std::uint32_t;

		auto IncRef() const noexcept -> std::uint32_t;
		auto DecRef() const noexcept -> std::uint32_t;

		// members
		mutable volatile std::uint32_t refCount{0}; // 0x00
	};

	static_assert(sizeof(BSIntrusiveRefCounted) == 0x04);
}
