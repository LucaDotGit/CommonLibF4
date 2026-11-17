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

namespace REX::Literals::inline NumericLiterals
{
	[[nodiscard]]
	constexpr auto operator""_f32(Float128 a_value) noexcept -> Float32
	{
		return static_cast<Float32>(a_value);
	}

	[[nodiscard]]
	constexpr auto operator""_F32(Float128 a_value) noexcept -> Float32
	{
		return static_cast<Float32>(a_value);
	}

	[[nodiscard]]
	constexpr auto operator""_f64(Float128 a_value) noexcept -> Float64
	{
		return static_cast<Float64>(a_value);
	}

	[[nodiscard]]
	constexpr auto operator""_F64(Float128 a_value) noexcept -> Float64
	{
		return static_cast<Float64>(a_value);
	}

	[[nodiscard]]
	constexpr auto operator""_f128(Float128 a_value) noexcept -> Float128
	{
		return a_value;
	}

	[[nodiscard]]
	constexpr auto operator""_F128(Float128 a_value) noexcept -> Float128
	{
		return a_value;
	}
}
