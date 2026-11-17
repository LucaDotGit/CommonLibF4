#pragma once

#include "REX/Unit.hpp"

namespace REX
{
	inline constexpr auto BASE_ONE_THOUSAND = static_cast<std::intmax_t>(1'000);
	inline constexpr auto BASE_ONE_KIBI = static_cast<std::intmax_t>(1'024);

	using Byte = Unit<1, 1>;

	using Kilobyte = Unit<BASE_ONE_THOUSAND, 1>;
	using Megabyte = Unit<BASE_ONE_THOUSAND, 2>;
	using Gigabyte = Unit<BASE_ONE_THOUSAND, 3>;
	using Terabyte = Unit<BASE_ONE_THOUSAND, 4>;
	using Petabyte = Unit<BASE_ONE_THOUSAND, 5>;
	using Exabyte = Unit<BASE_ONE_THOUSAND, 6>;

	using Kibibyte = Unit<BASE_ONE_KIBI, 1>;
	using Mebibyte = Unit<BASE_ONE_KIBI, 2>;
	using Gibibyte = Unit<BASE_ONE_KIBI, 3>;
	using Tebibyte = Unit<BASE_ONE_KIBI, 4>;
	using Pebibyte = Unit<BASE_ONE_KIBI, 5>;
	using Exbibyte = Unit<BASE_ONE_KIBI, 6>;
}

namespace REX::Literals::inline NumericLiterals
{
	[[nodiscard]]
	constexpr auto operator""_B(std::uintmax_t a_value) noexcept -> Byte
	{
		return Byte(static_cast<Byte::value_type>(a_value));
	}

	[[nodiscard]]
	constexpr auto operator""_KB(std::uintmax_t a_value) noexcept -> Kilobyte
	{
		return Kilobyte(static_cast<Kilobyte::value_type>(a_value));
	}

	[[nodiscard]]
	constexpr auto operator""_MB(std::uintmax_t a_value) noexcept -> Megabyte
	{
		return Megabyte(static_cast<Megabyte::value_type>(a_value));
	}

	[[nodiscard]]
	constexpr auto operator""_GB(std::uintmax_t a_value) noexcept -> Gigabyte
	{
		return Gigabyte(static_cast<Gigabyte::value_type>(a_value));
	}

	[[nodiscard]]
	constexpr auto operator""_TB(std::uintmax_t a_value) noexcept -> Terabyte
	{
		return Terabyte(static_cast<Terabyte::value_type>(a_value));
	}

	[[nodiscard]]
	constexpr auto operator""_PB(std::uintmax_t a_value) noexcept -> Petabyte
	{
		return Petabyte(static_cast<Petabyte::value_type>(a_value));
	}

	[[nodiscard]]
	constexpr auto operator""_EB(std::uintmax_t a_value) noexcept -> Exabyte
	{
		return Exabyte(static_cast<Exabyte::value_type>(a_value));
	}

	[[nodiscard]]
	constexpr auto operator""_KiB(std::uintmax_t a_value) noexcept -> Kibibyte
	{
		return Kibibyte(static_cast<Kibibyte::value_type>(a_value));
	}

	[[nodiscard]]
	constexpr auto operator""_MiB(std::uintmax_t a_value) noexcept -> Mebibyte
	{
		return Mebibyte(static_cast<Mebibyte::value_type>(a_value));
	}

	[[nodiscard]]
	constexpr auto operator""_GiB(std::uintmax_t a_value) noexcept -> Gibibyte
	{
		return Gibibyte(static_cast<Gibibyte::value_type>(a_value));
	}

	[[nodiscard]]
	constexpr auto operator""_TiB(std::uintmax_t a_value) noexcept -> Tebibyte
	{
		return Tebibyte(static_cast<Tebibyte::value_type>(a_value));
	}

	[[nodiscard]]
	constexpr auto operator""_PiB(std::uintmax_t a_value) noexcept -> Pebibyte
	{
		return Pebibyte(static_cast<Pebibyte::value_type>(a_value));
	}

	[[nodiscard]]
	constexpr auto operator""_EiB(std::uintmax_t a_value) noexcept -> Exbibyte
	{
		return Exbibyte(static_cast<Exbibyte::value_type>(a_value));
	}
}
