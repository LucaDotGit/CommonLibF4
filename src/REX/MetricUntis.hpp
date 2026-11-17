#pragma once

#include "REX/Unit.hpp"

namespace REX
{
	inline constexpr auto BASE_TEN = static_cast<std::intmax_t>(10);

	using Deci = Unit<BASE_TEN, -1>;
	using Centi = Unit<BASE_TEN, -2>;
	using Milli = Unit<BASE_TEN, -3>;
	using Micro = Unit<BASE_TEN, -6>;
	using Nano = Unit<BASE_TEN, -9>;
	using Pico = Unit<BASE_TEN, -12>;
	using Femto = Unit<BASE_TEN, -15>;
	using Atto = Unit<BASE_TEN, -18>;

	using Deca = Unit<BASE_TEN, 1>;
	using Hecto = Unit<BASE_TEN, 2>;
	using Kilo = Unit<BASE_TEN, 3>;
	using Mega = Unit<BASE_TEN, 6>;
	using Giga = Unit<BASE_TEN, 9>;
	using Tera = Unit<BASE_TEN, 12>;
	using Peta = Unit<BASE_TEN, 15>;
	using Exa = Unit<BASE_TEN, 18>;
}

namespace REX::Literals::inline NumericLiterals
{
	[[nodiscard]]
	constexpr auto operator""_d(std::uintmax_t a_value) noexcept -> Deci
	{
		return Deci(static_cast<Deci::value_type>(a_value));
	}

	[[nodiscard]]
	constexpr auto operator""_c(std::uintmax_t a_value) noexcept -> Centi
	{
		return Centi(static_cast<Centi::value_type>(a_value));
	}

	[[nodiscard]]
	constexpr auto operator""_m(std::uintmax_t a_value) noexcept -> Milli
	{
		return Milli(static_cast<Milli::value_type>(a_value));
	}

	[[nodiscard]]
	constexpr auto operator""_u(std::uintmax_t a_value) noexcept -> Micro
	{
		return Micro(static_cast<Micro::value_type>(a_value));
	}

	[[nodiscard]]
	constexpr auto operator""_n(std::uintmax_t a_value) noexcept -> Nano
	{
		return Nano(static_cast<Nano::value_type>(a_value));
	}

	[[nodiscard]]
	constexpr auto operator""_p(std::uintmax_t a_value) noexcept -> Pico
	{
		return Pico(static_cast<Pico::value_type>(a_value));
	}

	[[nodiscard]]
	constexpr auto operator""_f(std::uintmax_t a_value) noexcept -> Femto
	{
		return Femto(static_cast<Femto::value_type>(a_value));
	}

	[[nodiscard]]
	constexpr auto operator""_a(std::uintmax_t a_value) noexcept -> Atto
	{
		return Atto(static_cast<Atto::value_type>(a_value));
	}

	[[nodiscard]]
	constexpr auto operator""_da(std::uintmax_t a_value) noexcept -> Deca
	{
		return Deca(static_cast<Deca::value_type>(a_value));
	}

	[[nodiscard]]
	constexpr auto operator""_h(std::uintmax_t a_value) noexcept -> Hecto
	{
		return Hecto(static_cast<Hecto::value_type>(a_value));
	}

	[[nodiscard]]
	constexpr auto operator""_k(std::uintmax_t a_value) noexcept -> Kilo
	{
		return Kilo(static_cast<Kilo::value_type>(a_value));
	}

	[[nodiscard]]
	constexpr auto operator""_M(std::uintmax_t a_value) noexcept -> Mega
	{
		return Mega(static_cast<Mega::value_type>(a_value));
	}

	[[nodiscard]]
	constexpr auto operator""_G(std::uintmax_t a_value) noexcept -> Giga
	{
		return Giga(static_cast<Giga::value_type>(a_value));
	}

	[[nodiscard]]
	constexpr auto operator""_T(std::uintmax_t a_value) noexcept -> Tera
	{
		return Tera(static_cast<Tera::value_type>(a_value));
	}

	[[nodiscard]]
	constexpr auto operator""_P(std::uintmax_t a_value) noexcept -> Peta
	{
		return Peta(static_cast<Peta::value_type>(a_value));
	}

	[[nodiscard]]
	constexpr auto operator""_E(std::uintmax_t a_value) noexcept -> Exa
	{
		return Exa(static_cast<Exa::value_type>(a_value));
	}
}
