#pragma once

namespace RE::BSRandom
{
	[[nodiscard]]
	auto GetGenerator() noexcept -> std::mt19937&;

	[[nodiscard]]
	auto NextBool() noexcept -> bool;

	[[nodiscard]]
	auto NextInt() noexcept -> std::int32_t;
	[[nodiscard]]
	auto NextInt(std::int32_t a_maxInclusive) noexcept -> std::int32_t;
	[[nodiscard]]
	auto NextInt(std::int32_t a_minInclusive, std::int32_t a_maxInclusive) noexcept -> std::int32_t;

	[[nodiscard]]
	auto NextUInt() noexcept -> std::uint32_t;
	[[nodiscard]]
	auto NextUInt(std::uint32_t a_maxInclusive) noexcept -> std::uint32_t;
	[[nodiscard]]
	auto NextUInt(std::uint32_t a_minInclusive, std::uint32_t a_maxInclusive) noexcept -> std::uint32_t;

	[[nodiscard]]
	auto NextFloat() noexcept -> REX::Float32;
	[[nodiscard]]
	auto NextFloat(REX::Float32 a_maxExclusive) noexcept -> REX::Float32;
	[[nodiscard]]
	auto NextFloat(REX::Float32 a_minInclusive, REX::Float32 a_maxExclusive) noexcept -> REX::Float32;

	[[nodiscard]]
	auto NextFloat0To1() noexcept -> REX::Float32;
	[[nodiscard]]
	auto NextFloatNegative01To01() noexcept -> REX::Float32;
	[[nodiscard]]
	auto NextFloatTwoPi() noexcept -> REX::Float32;
	[[nodiscard]]
	auto NextFloatNegativePiToPi() noexcept -> REX::Float32;
}
