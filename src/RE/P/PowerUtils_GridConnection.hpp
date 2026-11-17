#pragma once

#include "RE/B/BSCRC32.hpp"

namespace RE::PowerUtils
{
	class GridConnection
	{
	public:
		// members
		std::uint32_t connection; // 0x00 - the powered object
		std::uint32_t connector;  // 0x04 - how the object is connected
	};

	static_assert(sizeof(GridConnection) == 0x08);
}

namespace RE
{
	template <>
	struct BSCRC32<RE::PowerUtils::GridConnection>
	{
	public:
		[[nodiscard]]
		auto operator()(const RE::PowerUtils::GridConnection& a_key) const noexcept -> std::uint32_t
		{
			const auto bytes = std::as_bytes(std::span{std::addressof(a_key), sizeof(RE::PowerUtils::GridConnection)});
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
		[[nodiscard]]
		auto operator()(const RE::PowerUtils::GridConnection& a_key) const noexcept -> std::size_t
		{
			return REX::HashCombine(a_key.connection, a_key.connector);
		}
	};
}
