#pragma once

#include "RE/B/BSCRC32.hpp"

namespace RE::PowerUtils
{
	class GridConnection
	{
	public:
		// members
		std::uint32_t connection; // 00 - the powered object
		std::uint32_t connector;  // 04 - how the object is connected
	};
	static_assert(sizeof(GridConnection) == 0x08);
}

namespace RE
{
	template <>
	struct BSCRC32<RE::PowerUtils::GridConnection>
	{
	public:
		[[nodiscard]] constexpr std::uint32_t operator()(const RE::PowerUtils::GridConnection& a_key) const noexcept
		{
			const auto bytes = std::span{ reinterpret_cast<const std::byte*>(std::addressof(a_key)), sizeof(PowerUtils::GridConnection) };
			return RE::Impl::GenerateCRC32Hash(bytes);
		}
	};
}

namespace std
{
	template <>
	struct hash<RE::PowerUtils::GridConnection>
	{
	public:
		[[nodiscard]] std::size_t operator()(const RE::PowerUtils::GridConnection& a_key) const noexcept
		{
			return REX::HashCombine(a_key.connection, a_key.connector);
		}
	};
}
