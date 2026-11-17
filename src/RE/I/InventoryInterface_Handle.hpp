#pragma once

#include "RE/B/BSCRC32.hpp"

namespace RE::InventoryInterface
{
	class Handle
	{
	public:
		inline static constexpr auto EMPTY_HANDLE = std::numeric_limits<std::uint32_t>::max();

		// members
		std::uint32_t id; // 0x00
	};

	static_assert(sizeof(Handle) == 0x04);
}

namespace RE
{
	template <>
	struct BSCRC32<RE::InventoryInterface::Handle>
	{
		[[nodiscard]]
		constexpr auto operator()(const RE::InventoryInterface::Handle& a_key) const noexcept -> std::uint32_t
		{
			return RE::HashCRC32(a_key.id);
		}
	};
}

namespace std
{
	template <>
	struct hash<RE::InventoryInterface::Handle>
	{
	public:
		[[nodiscard]]
		auto operator()(const RE::InventoryInterface::Handle& a_key) const noexcept -> std::size_t
		{
			return REX::Hash(a_key.id);
		}
	};
}
