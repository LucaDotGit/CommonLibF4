#pragma once

namespace REX
{
	using Float32 = float;
	using Float64 = double;
	using Float128 = long double;

	static_assert(std::numeric_limits<Float32>::is_iec559);
	static_assert(std::numeric_limits<Float64>::is_iec559);
	static_assert(std::numeric_limits<Float128>::is_iec559);
}

namespace REX::Literals
{
	[[nodiscard]] constexpr REX::Float32 operator""_f32(long double a_value) noexcept
	{
		return static_cast<REX::Float32>(a_value);
	}

	[[nodiscard]] constexpr REX::Float32 operator""_F32(long double a_value) noexcept
	{
		return static_cast<REX::Float32>(a_value);
	}

	[[nodiscard]] constexpr REX::Float64 operator""_f64(long double a_value) noexcept
	{
		return static_cast<REX::Float64>(a_value);
	}

	[[nodiscard]] constexpr REX::Float64 operator""_F64(long double a_value) noexcept
	{
		return static_cast<REX::Float64>(a_value);
	}

	[[nodiscard]] constexpr REX::Float128 operator""_f128(long double a_value) noexcept
	{
		return static_cast<REX::Float128>(a_value);
	}

	[[nodiscard]] constexpr REX::Float128 operator""_F128(long double a_value) noexcept
	{
		return static_cast<REX::Float128>(a_value);
	}
}

using namespace REX::Literals;
