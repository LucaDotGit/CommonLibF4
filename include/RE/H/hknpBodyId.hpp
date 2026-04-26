#pragma once

#include "RE/B/BSCRC32.hpp"
#include "RE/H/hkHandle.hpp"

namespace RE
{
	class hknpBodyIdBaseDiscriminant
	{
	public:
	};
	static_assert(std::is_empty_v<hknpBodyIdBaseDiscriminant>);

	class hknpBodyId
		: public hkHandle<std::uint32_t, std::numeric_limits<std::int32_t>::max(), hknpBodyIdBaseDiscriminant>
	{
	public:
	};
	static_assert(sizeof(hknpBodyId) == 0x04);
}

namespace RE
{
	template <>
	struct BSCRC32<RE::hknpBodyId>
	{
	public:
		[[nodiscard]] constexpr std::uint32_t operator()(const RE::hknpBodyId& a_key) const noexcept
		{
			return RE::HashCRC32(a_key.value_or(0));
		}
	};
}

namespace std
{
	template <>
	struct hash<RE::hknpBodyId>
	{
	public:
		[[nodiscard]] std::size_t operator()(const RE::hknpBodyId& a_key) const noexcept
		{
			return REX::Hash(a_key.value_or(0));
		}
	};
}
