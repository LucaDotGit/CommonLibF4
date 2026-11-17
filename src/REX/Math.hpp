#pragma once

#include "REX/Concepts.hpp"

namespace REX::Impl
{
	template <class T>
	concept x64_number = REX::number<T> && sizeof(T) == sizeof(std::uint64_t);

	inline constexpr auto LOW_PART_MASK = static_cast<std::uint64_t>(std::numeric_limits<std::uint32_t>::max());
	inline constexpr auto HIGH_PART_SHIFT =
		static_cast<std::uint64_t>(sizeof(std::int32_t) * std::numeric_limits<std::uint8_t>::digits);
}

namespace REX
{
	template <REX::floating_point T>
	inline constexpr auto TAU = std::numbers::pi_v<T> * static_cast<T>(2);

	template <REX::integer T>
	inline constexpr auto FIBONACCI_SIZE = static_cast<T>(0);

	template <>
	inline constexpr auto FIBONACCI_SIZE<std::int32_t> = 46;
	template <>
	inline constexpr auto FIBONACCI_SIZE<std::uint32_t> = 47;

	template <>
	inline constexpr auto FIBONACCI_SIZE<std::int64_t> = 92;
	template <>
	inline constexpr auto FIBONACCI_SIZE<std::uint64_t> = 93;

	template <REX::integer T>
	inline constexpr auto FACTORIAL_SIZE = static_cast<T>(0);

	template <>
	inline constexpr auto FACTORIAL_SIZE<std::int32_t> = 13;

	template <>
	inline constexpr auto FACTORIAL_SIZE<std::uint32_t> = 13;

	template <>
	inline constexpr auto FACTORIAL_SIZE<std::int64_t> = 21;

	template <>
	inline constexpr auto FACTORIAL_SIZE<std::uint64_t> = 21;

	inline constexpr auto FIBONACCI_NUMBERS =
		[]() consteval noexcept -> std::array<std::uint64_t, FIBONACCI_SIZE<std::uint64_t>> {
		auto numbers = std::array<std::uint64_t, FIBONACCI_SIZE<std::uint64_t>>();
		numbers[0] = static_cast<std::uint64_t>(0);
		numbers[1] = static_cast<std::uint64_t>(1);

		for (auto i = static_cast<std::size_t>(2); i < numbers.size(); i++) {
			numbers[i] = numbers[i - 1] + numbers[i - 2];
		}

		return numbers;
	}();

	inline constexpr auto FACTORIAL_NUMBERS =
		[]() consteval noexcept -> std::array<std::uint64_t, FACTORIAL_SIZE<std::uint64_t>> {
		auto numbers = std::array<std::uint64_t, FACTORIAL_SIZE<std::uint64_t>>();
		auto value = static_cast<std::uint64_t>(1);

		for (auto i = static_cast<std::size_t>(0); i < numbers.size(); i++) {
			numbers[i] = value;
			value *= (i + 1);
		}

		return numbers;
	}();

	template <class T>
	[[nodiscard]]
	constexpr auto Abs(T a_value) noexcept -> T
		requires(REX::signed_integer<T> || REX::floating_point<T>)
	{
		return a_value < 0 ? -a_value : a_value;
	}

	static_assert(Abs(-1) == 1);
	static_assert(Abs(1) == 1);
	static_assert(Abs(static_cast<REX::Float32>(-1.0)) == static_cast<REX::Float32>(1.0));
	static_assert(Abs(static_cast<REX::Float32>(1.0)) == static_cast<REX::Float32>(1.0));

	template <REX::integer T>
	[[nodiscard]]
	constexpr auto Mod(T a_value, T a_modulus) noexcept -> T
	{
		if (a_modulus == 0) {
			return 0;
		}

		const auto result = a_value % a_modulus;
		return result < 0 ? result + a_modulus : result;
	}

	static_assert(Mod(5, 3) == 2);
	static_assert(Mod(-5, 3) == 1);

	template <REX::floating_point T>
	[[nodiscard]]
	constexpr auto Mod(T a_value, T a_modulus) noexcept -> T
	{
		if (a_modulus == 0) {
			return 0;
		}

		const auto result = std::fmod(a_value, a_modulus);
		return result < 0 ? result + a_modulus : result;
	}

	/*
	static_assert(
		Mod(static_cast<REX::Float32>(5.0), static_cast<REX::Float32>(3.0)) == static_cast<REX::Float32>(2.0));
	static_assert(
		Mod(static_cast<REX::Float32>(-5.0), static_cast<REX::Float32>(3.0)) == static_cast<REX::Float32>(1.0));
	*/

	// Source: https://stackoverflow.com/a/253874

	template <REX::floating_point T>
	[[nodiscard]]
	constexpr auto NearEq(T a_lhs, T a_rhs, T a_epsilon = std::numeric_limits<T>::epsilon()) noexcept -> bool
	{
		if (a_lhs == a_rhs) {
			return true;
		}

		if (!(a_epsilon >= 0) || !std::isfinite(a_lhs) || !std::isfinite(a_rhs)) {
			return false;
		}

		const auto difference = Abs(a_lhs - a_rhs);
		const auto scale = std::max(Abs(a_lhs), Abs(a_rhs));
		return difference <= std::max(a_epsilon, scale * a_epsilon);
	}

	static_assert(
		NearEq(static_cast<REX::Float32>(1.0), static_cast<REX::Float32>(1.0), static_cast<REX::Float32>(0.0001)));

	template <REX::floating_point T>
	[[nodiscard]]
	constexpr auto CloseEq(T a_lhs, T a_rhs, T a_epsilon = std::numeric_limits<T>::epsilon()) noexcept -> bool
	{
		return NearEq(a_lhs, a_rhs, a_epsilon);
	}

	static_assert(
		CloseEq(static_cast<REX::Float32>(1.0), static_cast<REX::Float32>(1.0), static_cast<REX::Float32>(0.0001)));

	template <REX::floating_point T>
	[[nodiscard]]
	constexpr auto FuzzyGt(T a_lhs, T a_rhs, T a_epsilon = std::numeric_limits<T>::epsilon()) noexcept -> bool
	{
		if (!(a_epsilon >= 0) || a_lhs == a_rhs) {
			return false;
		}

		if (!std::isfinite(a_lhs) || !std::isfinite(a_rhs)) {
			return a_lhs > a_rhs;
		}

		const auto difference = a_lhs - a_rhs;
		const auto scale = std::max(Abs(a_lhs), Abs(a_rhs));
		return difference > std::max(a_epsilon, scale * a_epsilon);
	}

	/*
	static_assert(
		FuzzyGt(static_cast<REX::Float32>(1.0), static_cast<REX::Float32>(0.9999), static_cast<REX::Float32>(0.0001)));
	*/

	template <REX::floating_point T>
	[[nodiscard]]
	constexpr auto FuzzyLt(T a_lhs, T a_rhs, T a_epsilon = std::numeric_limits<T>::epsilon()) noexcept -> bool
	{
		if (!(a_epsilon >= 0) || a_lhs == a_rhs) {
			return false;
		}

		if (!std::isfinite(a_lhs) || !std::isfinite(a_rhs)) {
			return a_lhs < a_rhs;
		}

		const auto difference = a_rhs - a_lhs;
		const auto scale = std::max(Abs(a_lhs), Abs(a_rhs));
		return difference > std::max(a_epsilon, scale * a_epsilon);
	}

	/*
	static_assert(
		FuzzyLt(static_cast<REX::Float32>(0.9999), static_cast<REX::Float32>(1.0), static_cast<REX::Float32>(0.0001)));
	*/

	template <REX::number T>
	[[nodiscard]]
	constexpr auto Sign(T a_value) noexcept -> std::int32_t
	{
		if (a_value > 0) {
			return 1;
		}

		if (a_value < 0) {
			return -1;
		}

		return 0;
	}

	static_assert(Sign(0) == 0);
	static_assert(Sign(1) == 1);
	static_assert(Sign(-1) == -1);

	template <REX::floating_point T>
	[[nodiscard]]
	constexpr auto Ceil(T a_value) noexcept -> T
	{
		const auto intValue = static_cast<T>(static_cast<std::int64_t>(a_value));
		return static_cast<T>(intValue) - static_cast<T>(a_value < intValue);
	}

	template <REX::floating_point T>
	[[nodiscard]]
	constexpr auto Floor(T a_value) noexcept -> T
	{
		const auto intValue = static_cast<T>(static_cast<std::int64_t>(a_value));
		return static_cast<T>(intValue) + static_cast<T>(a_value > intValue);
	}

	template <REX::floating_point T>
	[[nodiscard]]
	constexpr auto Trunc(T a_value) noexcept -> T
	{
		return a_value < 0 ? Ceil(a_value) : Floor(a_value);
	}

	template <REX::floating_point T>
	[[nodiscard]]
	constexpr auto Round(T a_value, std::int32_t a_decimals) noexcept -> T
	{
		constexpr auto MIN_DECIMALS = static_cast<std::int32_t>(0);
		constexpr auto MAX_DECIMALS = std::numeric_limits<T>::digits10;

		const auto safeDecimals = std::clamp(a_decimals, MIN_DECIMALS, MAX_DECIMALS);
		if (safeDecimals == 0) {
			return std::round(a_value);
		}

		const auto factor = std::pow(static_cast<T>(10), static_cast<T>(safeDecimals));
		return std::round(a_value * factor) / factor;
	}

	/*
	static_assert(Round(static_cast<REX::Float32>(5.12345), 2) == static_cast<REX::Float32>(5.12));
	*/

	template <REX::number T>
	[[nodiscard]]
	constexpr auto Pow(T a_base, T a_exponent) noexcept -> T
	{
		if (std::is_constant_evaluated()) [[unlikely]] {
			if (a_exponent == 0) {
				return static_cast<T>(1);
			}

			if (a_exponent < 0) {
				return static_cast<T>(1) / Pow(a_base, static_cast<T>(-a_exponent));
			}

			// NOLINTBEGIN(bugprone-float-loop-counter)

			auto result = static_cast<T>(1);
			for (auto i = static_cast<T>(0); i < a_exponent; i++) {
				result *= a_base;
			}

			// NOLINTEND(bugprone-float-loop-counter)

			return result;
		}

		return static_cast<T>(std::pow(a_base, a_exponent));
	}

	static_assert(Pow(2, 3) == 8);
	static_assert(
		Pow(static_cast<REX::Float32>(2.0), static_cast<REX::Float32>(3.0)) == static_cast<REX::Float32>(8.0));

	template <REX::number T>
	[[nodiscard]]
	constexpr auto Sqrt(T a_value) noexcept -> T
	{
		if (std::is_constant_evaluated()) [[unlikely]] {
			if (a_value < 0) {
				return static_cast<T>(0);
			}

			auto result = static_cast<T>(1);
			auto lastResult = static_cast<T>(0);

			while (result != lastResult) {
				lastResult = result;
				result = (result + (a_value / result)) / static_cast<T>(2);
			}

			return result;
		}

		return static_cast<T>(std::sqrt(a_value));
	}

	static_assert(Sqrt(4) == 2);
	static_assert(Sqrt(static_cast<REX::Float32>(4.0)) == static_cast<REX::Float32>(2.0));

	template <REX::floating_point T>
	[[nodiscard]]
	constexpr auto DegToRad(T a_value) noexcept -> T
	{
		return a_value * std::numbers::pi_v<T> / static_cast<T>(180);
	}

	static_assert(DegToRad(static_cast<REX::Float32>(180.0)) == std::numbers::pi_v<REX::Float32>);

	template <REX::floating_point T>
	[[nodiscard]]
	constexpr auto RadToDeg(T a_value) noexcept -> T
	{
		return a_value * static_cast<T>(180) / std::numbers::pi_v<T>;
	}

	static_assert(RadToDeg(std::numbers::pi_v<REX::Float32>) == static_cast<REX::Float32>(180.0));

	template <REX::floating_point T>
	[[nodiscard]]
	constexpr auto ClampDeg(T a_value) noexcept -> T
	{
		if (a_value < static_cast<T>(-180)) {
			return a_value + static_cast<T>(360);
		}

		if (a_value > static_cast<T>(180)) {
			return a_value - static_cast<T>(360);
		}

		return a_value;
	}

	static_assert(ClampDeg(static_cast<REX::Float32>(90.0)) == static_cast<REX::Float32>(90.0));
	static_assert(ClampDeg(static_cast<REX::Float32>(-90.0)) == static_cast<REX::Float32>(-90.0));
	static_assert(ClampDeg(static_cast<REX::Float32>(270.0)) == static_cast<REX::Float32>(-90.0));
	static_assert(ClampDeg(static_cast<REX::Float32>(-270.0)) == static_cast<REX::Float32>(90.0));

	template <REX::integer T>
	[[nodiscard]]
	constexpr auto Fib(T a_value) noexcept -> T
	{
		if (a_value < 0 || a_value >= FIBONACCI_SIZE<T>) {
			return 0;
		}

		return static_cast<T>(FIBONACCI_NUMBERS[a_value]);
	}

	template <REX::integer T>
	[[nodiscard]]
	constexpr auto Fact(T a_value) noexcept -> T
	{
		if (a_value < 0 || a_value >= FACTORIAL_SIZE<T>) {
			return 0;
		}

		return static_cast<T>(FACTORIAL_NUMBERS[a_value]);
	}

	template <REX::integer T>
	[[nodiscard]]
	constexpr auto Perm(T a_n, T a_r) noexcept -> T
	{
		if (a_n < 0 || a_r < 0 || a_n < a_r) {
			return 0;
		}

		return Fact(a_n) / Fact(a_n - a_r);
	}

	template <REX::integer T>
	[[nodiscard]]
	constexpr auto Comb(T a_n, T a_r) noexcept -> T
	{
		if (a_n < 0 || a_r < 0 || a_n < a_r) {
			return 0;
		}

		return Fact(a_n) / (Fact(a_r) * Fact(a_n - a_r));
	}

	template <Impl::x64_number T>
	[[nodiscard]]
	constexpr auto SplitX64(T a_value) noexcept -> std::pair<std::uint32_t, std::int32_t>
	{
		const auto bits = std::bit_cast<std::uint64_t>(a_value);
		const auto lowPart = static_cast<std::uint32_t>(bits & Impl::LOW_PART_MASK);
		const auto highPart = static_cast<std::int32_t>(bits >> Impl::HIGH_PART_SHIFT);

		return std::make_pair(lowPart, highPart);
	}

	static_assert(
		SplitX64(static_cast<std::int64_t>(0x1122'3344'5566'7788)) ==
		std::make_pair(static_cast<std::uint32_t>(0x5566'7788), static_cast<std::int32_t>(0x1122'3344)));

	template <Impl::x64_number T>
	[[nodiscard]]
	constexpr auto JoinX64(std::pair<std::uint32_t, std::int32_t> a_split) noexcept -> T
	{
		const auto bits = (static_cast<std::uint64_t>(a_split.first) & Impl::LOW_PART_MASK) |
						  (static_cast<std::uint64_t>(a_split.second) << Impl::HIGH_PART_SHIFT);

		return std::bit_cast<T>(bits);
	}

	static_assert(
		JoinX64<std::uint64_t>(
			std::make_pair(static_cast<std::uint32_t>(0x5566'7788), static_cast<std::int32_t>(0x1122'3344))) ==
		static_cast<std::uint64_t>(0x1122'3344'5566'7788));
}
