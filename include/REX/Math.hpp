#pragma once

#include "REX/Concepts.hpp"
#include "REX/NotAssignable.hpp"

namespace REX::Impl
{
	template <class T>
	concept x64_number = (REX::integer<T> || REX::floating_point<T>) && sizeof(T) == sizeof(std::uint64_t);

	inline constexpr auto LOW_PART_MASK = static_cast<std::uint64_t>(std::numeric_limits<std::uint32_t>::max());
	inline constexpr auto HIGH_PART_SHIFT = static_cast<std::uint64_t>(sizeof(std::int32_t) * CHAR_BIT);

	[[nodiscard]] auto GetLgammaMutex() noexcept
		-> REX::NotAssignable<std::mutex>&;
}

namespace REX
{
	template <REX::floating_point T>
	inline constexpr auto TAU = std::numbers::pi_v<T> * static_cast<T>(2);

	template <REX::integer T>
	inline constexpr auto FIBONACCI_SIZE = static_cast<T>(0);

	template <>
	inline constexpr auto FIBONACCI_SIZE<std::int32_t> = 47i32;
	template <>
	inline constexpr auto FIBONACCI_SIZE<std::uint32_t> = 47ui32;

	template <>
	inline constexpr auto FIBONACCI_SIZE<std::int64_t> = 94i32;
	template <>
	inline constexpr auto FIBONACCI_SIZE<std::uint64_t> = 94ui32;

	inline constexpr auto FIBONACCI_NUMBERS = []() consteval noexcept {
		auto numbers = std::array<std::uint64_t, FIBONACCI_SIZE<std::uint64_t>>();
		numbers[0] = 0ui64;
		numbers[1] = 1ui64;

		for (auto i = 2ui64; i < numbers.size(); i++) {
			numbers[i] = numbers[i - 1] + numbers[i - 2];
		}

		return numbers;
	}();

	inline constexpr auto FACTORIAL_NUMBERS = []() consteval noexcept {
		auto numbers = std::array<std::uint64_t, FIBONACCI_SIZE<std::uint64_t>>();
		auto value = 1ui64;

		for (auto i = 0ui64; i < numbers.size(); i++) {
			numbers[i] = value;
			value *= (i + 1);
		}

		return numbers;
	}();

	template <REX::integer T>
	[[nodiscard]] constexpr T Fib(T a_value) noexcept
	{
		if (a_value < 0 || a_value >= FIBONACCI_SIZE<T>) {
			return 0;
		}

		return static_cast<T>(FIBONACCI_NUMBERS[a_value]);
	}

	extern template std::int32_t Fib(std::int32_t) noexcept;
	extern template std::uint32_t Fib(std::uint32_t) noexcept;
	extern template std::int64_t Fib(std::int64_t) noexcept;
	extern template std::uint64_t Fib(std::uint64_t) noexcept;

	template <REX::integer T>
	[[nodiscard]] constexpr T Fact(T a_value) noexcept
	{
		if (a_value < 0 || a_value >= FIBONACCI_SIZE<T>) {
			return 0;
		}

		return static_cast<T>(FACTORIAL_NUMBERS[a_value]);
	}

	extern template std::int32_t Fact(std::int32_t) noexcept;
	extern template std::uint32_t Fact(std::uint32_t) noexcept;
	extern template std::int64_t Fact(std::int64_t) noexcept;
	extern template std::uint64_t Fact(std::uint64_t) noexcept;

	template <REX::integer T>
	[[nodiscard]] constexpr T Perm(T a_n, T a_r) noexcept
	{
		if (a_n < 0 || a_r < 0 || a_n < a_r) {
			return 0;
		}

		return Fact(a_n) / Fact(a_n - a_r);
	}

	extern template std::int32_t Perm(std::int32_t, std::int32_t) noexcept;
	extern template std::uint32_t Perm(std::uint32_t, std::uint32_t) noexcept;
	extern template std::int64_t Perm(std::int64_t, std::int64_t) noexcept;
	extern template std::uint64_t Perm(std::uint64_t, std::uint64_t) noexcept;

	template <REX::integer T>
	[[nodiscard]] constexpr T Comb(T a_n, T a_r) noexcept
	{
		if (a_n < 0 || a_r < 0 || a_n < a_r) {
			return 0;
		}

		return Fact(a_n) / (Fact(a_r) * Fact(a_n - a_r));
	}

	extern template std::int32_t Comb(std::int32_t, std::int32_t) noexcept;
	extern template std::uint32_t Comb(std::uint32_t, std::uint32_t) noexcept;
	extern template std::int64_t Comb(std::int64_t, std::int64_t) noexcept;
	extern template std::uint64_t Comb(std::uint64_t, std::uint64_t) noexcept;

	template <REX::integer T>
	[[nodiscard]] constexpr T Mod(T a_value, T a_modulus) noexcept
	{
		if (a_modulus == 0) {
			return 0;
		}

		const auto result = a_value % a_modulus;
		return result < 0 ? result + a_modulus : result;
	}

	extern template std::int32_t Mod(std::int32_t, std::int32_t) noexcept;
	extern template std::uint32_t Mod(std::uint32_t, std::uint32_t) noexcept;
	extern template std::int64_t Mod(std::int64_t, std::int64_t) noexcept;
	extern template std::uint64_t Mod(std::uint64_t, std::uint64_t) noexcept;

	template <REX::floating_point T>
	[[nodiscard]] constexpr T Mod(T a_value, T a_modulus) noexcept
	{
		if (a_modulus == 0) {
			return 0;
		}

		const auto result = std::fmod(a_value, a_modulus);
		return result < 0 ? result + a_modulus : result;
	}

	extern template REX::Float32 Mod(REX::Float32, REX::Float32) noexcept;
	extern template REX::Float64 Mod(REX::Float64, REX::Float64) noexcept;
	extern template REX::Float128 Mod(REX::Float128, REX::Float128) noexcept;

	template <REX::floating_point T>
	[[nodiscard]] constexpr T Round(T a_value, std::int32_t a_decimals) noexcept
	{
		constexpr auto MIN_DECIMALS = 0i32;
		constexpr auto MAX_DECIMALS = std::numeric_limits<T>::digits10;

		const auto safeDecimals = std::clamp(a_decimals, MIN_DECIMALS, MAX_DECIMALS);
		if (safeDecimals == 0) {
			return std::round(a_value);
		}

		const auto factor = std::pow(static_cast<T>(10), static_cast<T>(safeDecimals));
		return std::round(a_value * factor) / factor;
	}

	extern template REX::Float32 Round(REX::Float32, std::int32_t) noexcept;
	extern template REX::Float64 Round(REX::Float64, std::int32_t) noexcept;
	extern template REX::Float128 Round(REX::Float128, std::int32_t) noexcept;

	template <REX::floating_point T>
	[[nodiscard]] constexpr T DegToRad(T a_value) noexcept
	{
		return a_value * std::numbers::pi_v<T> / static_cast<T>(180);
	}

	extern template REX::Float32 DegToRad(REX::Float32) noexcept;
	extern template REX::Float64 DegToRad(REX::Float64) noexcept;
	extern template REX::Float128 DegToRad(REX::Float128) noexcept;

	template <REX::floating_point T>
	[[nodiscard]] constexpr T RadToDeg(T a_value) noexcept
	{
		return a_value * static_cast<T>(180) / std::numbers::pi_v<T>;
	}

	extern template REX::Float32 RadToDeg(REX::Float32) noexcept;
	extern template REX::Float64 RadToDeg(REX::Float64) noexcept;
	extern template REX::Float128 RadToDeg(REX::Float128) noexcept;

	template <REX::floating_point T>
	[[nodiscard]] constexpr T ClampDeg(T a_value) noexcept
	{
		if (a_value < static_cast<T>(-180)) {
			a_value += static_cast<T>(360);
		}
		else if (a_value > static_cast<T>(180)) {
			a_value -= static_cast<T>(360);
		}

		return a_value;
	}

	extern template REX::Float32 ClampDeg(REX::Float32) noexcept;
	extern template REX::Float64 ClampDeg(REX::Float64) noexcept;
	extern template REX::Float128 ClampDeg(REX::Float128) noexcept;

	// Source: https://stackoverflow.com/a/253874

	template <REX::floating_point T>
	[[nodiscard]] constexpr bool NearEq(T a_lhs, T a_rhs, T a_epsilon = std::numeric_limits<T>::epsilon()) noexcept
	{
		return std::abs(a_lhs - a_rhs) <= (std::max(std::abs(a_lhs), std::abs(a_rhs)) * a_epsilon);
	}

	extern template bool NearEq(REX::Float32, REX::Float32, REX::Float32) noexcept;
	extern template bool NearEq(REX::Float64, REX::Float64, REX::Float64) noexcept;
	extern template bool NearEq(REX::Float128, REX::Float128, REX::Float128) noexcept;

	template <REX::floating_point T>
	[[nodiscard]] constexpr bool CloseEq(T a_lhs, T a_rhs, T a_epsilon = std::numeric_limits<T>::epsilon()) noexcept
	{
		return std::abs(a_lhs - a_rhs) <= (std::min(std::abs(a_lhs), std::abs(a_rhs)) * a_epsilon);
	}

	extern template bool CloseEq(REX::Float32, REX::Float32, REX::Float32) noexcept;
	extern template bool CloseEq(REX::Float64, REX::Float64, REX::Float64) noexcept;
	extern template bool CloseEq(REX::Float128, REX::Float128, REX::Float128) noexcept;

	template <REX::floating_point T>
	[[nodiscard]] constexpr bool FuzzyGt(T a_lhs, T a_rhs, T a_epsilon = std::numeric_limits<T>::epsilon()) noexcept
	{
		return (a_lhs - a_rhs) > (std::max(std::abs(a_lhs), std::abs(a_rhs)) * a_epsilon);
	}

	extern template bool FuzzyGt(REX::Float32, REX::Float32, REX::Float32) noexcept;
	extern template bool FuzzyGt(REX::Float64, REX::Float64, REX::Float64) noexcept;
	extern template bool FuzzyGt(REX::Float128, REX::Float128, REX::Float128) noexcept;

	template <REX::floating_point T>
	[[nodiscard]] constexpr bool FuzzyLt(T a_lhs, T a_rhs, T a_epsilon = std::numeric_limits<T>::epsilon()) noexcept
	{
		return (a_rhs - a_lhs) > (std::max(std::abs(a_lhs), std::abs(a_rhs)) * a_epsilon);
	}

	extern template bool FuzzyLt(REX::Float32, REX::Float32, REX::Float32) noexcept;
	extern template bool FuzzyLt(REX::Float64, REX::Float64, REX::Float64) noexcept;
	extern template bool FuzzyLt(REX::Float128, REX::Float128, REX::Float128) noexcept;

	template <REX::floating_point T>
	[[nodiscard]] T Lgamma(T a_value) noexcept;

	template <>
	inline REX::Float32 Lgamma(REX::Float32 a_value) noexcept
	{
		const auto lgammaLock = std::scoped_lock(*Impl::GetLgammaMutex());
		return std::lgamma(a_value); // NOLINT(concurrency-mt-unsafe)
	}

	template <>
	inline REX::Float64 Lgamma(REX::Float64 a_value) noexcept
	{
		const auto lgammaLock = std::scoped_lock(*Impl::GetLgammaMutex());
		return std::lgamma(a_value); // NOLINT(concurrency-mt-unsafe)
	}

	template <>
	inline REX::Float128 Lgamma(REX::Float128 a_value) noexcept
	{
		const auto lgammaLock = std::scoped_lock(*Impl::GetLgammaMutex());
		return std::lgamma(a_value); // NOLINT(concurrency-mt-unsafe)
	}

	template <Impl::x64_number T>
	[[nodiscard]] constexpr std::pair<std::uint32_t, std::int32_t> SplitFromX64(T a_value) noexcept
	{
		const auto bits = std::bit_cast<std::uint64_t>(a_value);
		const auto lowPart = static_cast<std::uint32_t>(bits & Impl::LOW_PART_MASK);
		const auto highPart = static_cast<std::int32_t>(bits >> Impl::HIGH_PART_SHIFT);

		return std::make_pair(lowPart, highPart);
	}

	template <Impl::x64_number T>
	[[nodiscard]] constexpr T CombineToX64(std::uint32_t a_lowPart, std::int32_t a_highPart) noexcept
	{
		const auto bits = (static_cast<std::uint64_t>(a_lowPart) & Impl::LOW_PART_MASK) |
						  (static_cast<std::uint64_t>(a_highPart) << Impl::HIGH_PART_SHIFT);

		return std::bit_cast<T>(bits);
	}

	extern template std::pair<std::uint32_t, std::int32_t> SplitFromX64(std::int64_t) noexcept;
	extern template std::int64_t CombineToX64(std::uint32_t, std::int32_t) noexcept;

	extern template std::pair<std::uint32_t, std::int32_t> SplitFromX64(std::uint64_t) noexcept;
	extern template std::uint64_t CombineToX64(std::uint32_t, std::int32_t) noexcept;

	extern template std::pair<std::uint32_t, std::int32_t> SplitFromX64(REX::Float64) noexcept;
	extern template REX::Float64 CombineToX64(std::uint32_t, std::int32_t) noexcept;
}
