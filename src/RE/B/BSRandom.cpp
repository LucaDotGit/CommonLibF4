#include "RE/B/BSRandom.hpp"

namespace RE::BSRandom
{
	auto GetGenerator() noexcept -> std::mt19937&
	{
		static const auto GENERATOR = REL::Relocation<std::mt19937*>(ID::BSRandom::Generator);
		return *GENERATOR;
	}

	auto NextBool() noexcept -> bool
	{
		auto distributor = std::bernoulli_distribution();
		return static_cast<bool>(distributor(GetGenerator()));
	}

	auto NextInt() noexcept -> std::int32_t
	{
		auto distributor =
			std::uniform_int_distribution(static_cast<std::int32_t>(0), std::numeric_limits<std::int32_t>::max());
		return distributor(GetGenerator());
	}

	auto NextInt(std::int32_t a_maxInclusive) noexcept -> std::int32_t
	{
		auto distributor = std::uniform_int_distribution(static_cast<std::int32_t>(0), a_maxInclusive);
		return distributor(GetGenerator());
	}

	auto NextInt(std::int32_t a_minInclusive, std::int32_t a_maxInclusive) noexcept -> std::int32_t
	{
		auto distributor = std::uniform_int_distribution(a_minInclusive, a_maxInclusive);
		return distributor(GetGenerator());
	}

	auto NextUInt() noexcept -> std::uint32_t
	{
		auto distributor =
			std::uniform_int_distribution(static_cast<std::uint32_t>(0), std::numeric_limits<std::uint32_t>::max());
		return distributor(GetGenerator());
	}

	auto NextUInt(std::uint32_t a_maxInclusive) noexcept -> std::uint32_t
	{
		auto distributor = std::uniform_int_distribution(static_cast<std::uint32_t>(0), a_maxInclusive);
		return distributor(GetGenerator());
	}

	auto NextUInt(std::uint32_t a_minInclusive, std::uint32_t a_maxInclusive) noexcept -> std::uint32_t
	{
		auto distributor = std::uniform_int_distribution(a_minInclusive, a_maxInclusive);
		return distributor(GetGenerator());
	}

	auto NextFloat() noexcept -> REX::Float32
	{
		auto distributor =
			std::uniform_real_distribution(static_cast<REX::Float32>(0.0), std::numeric_limits<REX::Float32>::max());
		return distributor(GetGenerator());
	}

	auto NextFloat(REX::Float32 a_maxExclusive) noexcept -> REX::Float32
	{
		auto distributor = std::uniform_real_distribution(static_cast<REX::Float32>(0.0), a_maxExclusive);
		return distributor(GetGenerator());
	}

	auto NextFloat(REX::Float32 a_minInclusive, REX::Float32 a_maxExclusive) noexcept -> REX::Float32
	{
		auto distributor = std::uniform_real_distribution(a_minInclusive, a_maxExclusive);
		return distributor(GetGenerator());
	}

	auto NextFloat0To1() noexcept -> REX::Float32
	{
		auto distributor =
			std::uniform_real_distribution(static_cast<REX::Float32>(0.0), static_cast<REX::Float32>(1.0));
		return distributor(GetGenerator());
	}

	auto NextFloatNegative01To01() noexcept -> REX::Float32
	{
		auto distributor =
			std::uniform_real_distribution(static_cast<REX::Float32>(-1.0), static_cast<REX::Float32>(1.0));
		return distributor(GetGenerator());
	}

	auto NextFloatTwoPi() noexcept -> REX::Float32
	{
		auto distributor = std::uniform_real_distribution(static_cast<REX::Float32>(0.0), REX::TAU<REX::Float32>);
		return distributor(GetGenerator());
	}

	auto NextFloatNegativePiToPi() noexcept -> REX::Float32
	{
		auto distributor =
			std::uniform_real_distribution(-std::numbers::pi_v<REX::Float32>, std::numbers::pi_v<REX::Float32>);
		return distributor(GetGenerator());
	}
}
