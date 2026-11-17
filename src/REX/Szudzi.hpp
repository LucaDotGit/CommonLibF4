#pragma once

namespace REX
{
	[[nodiscard]]
	constexpr auto SzudziPair(std::uint32_t a_x, std::uint32_t a_y) noexcept -> std::uint64_t
	{
		const auto a = static_cast<std::uint64_t>(a_x);
		const auto b = static_cast<std::uint64_t>(a_y);

		if (a >= b) {
			return (a * a) + a + b;
		}

		return (b * b) + a;
	}

	[[nodiscard]]
	constexpr auto SzudziUnpair(std::uint64_t a_z) noexcept -> std::pair<std::uint32_t, std::uint32_t>
	{
		const auto a = static_cast<std::uint64_t>(std::floor(std::sqrt(static_cast<REX::Float64>(a_z))));
		const auto b = a_z - (a * a);

		if (b < a) {
			return std::make_pair(static_cast<std::uint32_t>(b), static_cast<std::uint32_t>(a));
		}

		return std::make_pair(static_cast<std::uint32_t>(a), static_cast<std::uint32_t>(b - a));
	}
}
