#pragma once

#include "REX/Compare.hpp"
#include "REX/Concepts.hpp"
#include "REX/EnumSet.hpp"
#include "REX/Error.hpp"

namespace REX
{
	enum class BoolFormat : std::uint32_t
	{
		kNone = 0,
		kTrueFalse = 1 << 0,
		kYesNo = 1 << 1,
		kOnOff = 1 << 2,
		kOneZero = 1 << 3,

		kCaseSensitive = 1 << 8,
		kCapitalize = 1 << 9,

		kDefault = kTrueFalse,

		kAll = kTrueFalse | kYesNo | kOnOff | kOneZero
	};

	enum class IntFormat : std::uint32_t
	{
		kNone = 0,
		kBase02 = 2,
		kBase08 = 8,
		kBase10 = 10,
		kBase16 = 16,
		kBase32 = 32,

		kBinary = kBase02,
		kOctal = kBase08,
		kDecimal = kBase10,
		kHexadecimal = kBase16,

		kDefault = kDecimal
	};

	enum class FloatFormat : std::uint32_t
	{
		kNone = 0,
		kScientific = static_cast<std::underlying_type_t<FloatFormat>>(std::chars_format::scientific),
		kFixed = static_cast<std::underlying_type_t<FloatFormat>>(std::chars_format::fixed),
		kHexadecimal = static_cast<std::underlying_type_t<FloatFormat>>(std::chars_format::hex),

		kDefault = static_cast<std::underlying_type_t<FloatFormat>>(std::chars_format::general)
	};

	inline constexpr auto TRUE_STRING = "true"sv;
	inline constexpr auto CAPITAL_TRUE_STRING = "True"sv;

	inline constexpr auto FALSE_STRING = "false"sv;
	inline constexpr auto CAPITAL_FALSE_STRING = "False"sv;

	inline constexpr auto YES_STRING = "yes"sv;
	inline constexpr auto CAPITAL_YES_STRING = "Yes"sv;

	inline constexpr auto NO_STRING = "no"sv;
	inline constexpr auto CAPITAL_NO_STRING = "No"sv;

	inline constexpr auto ON_STRING = "on"sv;
	inline constexpr auto CAPITAL_ON_STRING = "On"sv;

	inline constexpr auto OFF_STRING = "off"sv;
	inline constexpr auto CAPITAL_OFF_STRING = "Off"sv;

	inline constexpr auto ONE_STRING = "1"sv;
	inline constexpr auto ZERO_STRING = "0"sv;

	inline constexpr auto BINARY_PREFIX = "0b"sv;
	inline constexpr auto CAPITAL_BINARY_PREFIX = "0B"sv;

	inline constexpr auto OCTAL_PREFIX = "0o"sv;
	inline constexpr auto CAPITAL_OCTAL_PREFIX = "0O"sv;

	inline constexpr auto HEXADECIMAL_PREFIX = "0x"sv;
	inline constexpr auto CAPITAL_HEXADECIMAL_PREFIX = "0X"sv;

	inline constexpr auto BOOL_FORMAT_STRINGS = std::array{
		std::make_pair(TRUE_STRING, FALSE_STRING),
		std::make_pair(YES_STRING, NO_STRING),
		std::make_pair(ON_STRING, OFF_STRING),
		std::make_pair(ONE_STRING, ZERO_STRING)
	};

	inline constexpr auto CAPITAL_BOOL_FORMAT_STRINGS = std::array{
		std::make_pair(CAPITAL_TRUE_STRING, CAPITAL_FALSE_STRING),
		std::make_pair(CAPITAL_YES_STRING, CAPITAL_NO_STRING),
		std::make_pair(CAPITAL_ON_STRING, CAPITAL_OFF_STRING),
		std::make_pair(ONE_STRING, ZERO_STRING)
	};

	template <class U, class... T>
	[[nodiscard]] constexpr U BitsToValue(T... a_args) noexcept
		requires((std::same_as<std::remove_cv_t<T>, bool> && ...))
	{
		constexpr auto ARGC = sizeof...(T);

		auto bits = std::bitset<ARGC>();
		auto i = static_cast<std::size_t>(0);
		((bits[i++] = a_args), ...);

		if constexpr (ARGC <= std::numeric_limits<std::uint32_t>::digits) {
			return static_cast<U>(bits.to_ulong());
		}
		else if constexpr (ARGC <= std::numeric_limits<std::uint64_t>::digits) {
			return static_cast<U>(bits.to_ullong());
		}
		else {
			static_assert(false, "The number of arguments exceeds the maximum supported size.");
		}
	}

	[[nodiscard]] auto Utf8ToUtf16(std::string_view a_source, std::span<wchar_t> a_buffer) noexcept
		-> std::expected<std::wstring_view, REX::SystemError>;
	[[nodiscard]] auto Utf16ToUtf8(std::wstring_view a_source, std::span<char> a_buffer) noexcept
		-> std::expected<std::string_view, REX::SystemError>;

	[[nodiscard]] auto Utf8ToUtf16(std::string_view a_source) noexcept
		-> std::expected<std::wstring, REX::SystemError>;
	[[nodiscard]] auto Utf16ToUtf8(std::wstring_view a_source) noexcept
		-> std::expected<std::string, REX::SystemError>;

	template <class T>
	[[nodiscard]] constexpr auto FromString(std::string_view a_value, BoolFormat a_format = BoolFormat::kDefault) noexcept
		-> std::expected<T, REX::PosixErrorCode>
		requires(std::same_as<T, bool>)
	{
		if (a_value.empty()) {
			return std::unexpected(REX::PosixErrorCode::invalid_argument);
		}

		const auto formatSet = REX::EnumSet<BoolFormat>(a_format);
		if (formatSet.none(BoolFormat::kAll)) {
			return std::unexpected(REX::PosixErrorCode::invalid_argument);
		}

		const auto& formatTable = formatSet.any(BoolFormat::kCapitalize) ?
									  CAPITAL_BOOL_FORMAT_STRINGS :
									  BOOL_FORMAT_STRINGS;

		const auto formatComparer = [formatSet](std::string_view a_value, std::string_view a_formatString) -> bool {
			if (formatSet.any(BoolFormat::kCaseSensitive)) {
				return REX::Equals(a_value, a_formatString);
			}

			return REX::EqualsIgnoreCase(a_value, a_formatString);
		};

		for (auto formatIndex = static_cast<std::underlying_type_t<BoolFormat>>(0); formatIndex < formatTable.size(); formatIndex++) {
			const auto formatBit = static_cast<std::underlying_type_t<BoolFormat>>(1) << formatIndex;
			if (formatSet.none(formatBit)) {
				continue;
			}

			const auto& [trueString, falseString] = formatTable[formatIndex];

			if (formatComparer(a_value, trueString)) {
				return true;
			}

			if (formatComparer(a_value, falseString)) {
				return false;
			}
		}

		return std::unexpected(REX::PosixErrorCode::invalid_argument);
	}

	template <class T>
	[[nodiscard]] constexpr auto FromString(std::string_view a_value) noexcept
		-> std::expected<T, REX::PosixErrorCode>
		requires(std::same_as<T, char>)
	{
		if (a_value.size() != 1) {
			return std::unexpected(REX::PosixErrorCode::invalid_argument);
		}

		return a_value.front();
	}

	template <class T>
	[[nodiscard]] constexpr auto FromString(std::string_view a_value, IntFormat a_format = IntFormat::kDefault) noexcept
		-> std::expected<T, REX::PosixErrorCode>
		requires(REX::integer<T> && !std::same_as<T, char>)
	{
		switch (a_format) {
			case IntFormat::kBinary: {
				if (REX::StartsWithIgnoreCase(a_value, BINARY_PREFIX)) {
					a_value.remove_prefix(BINARY_PREFIX.size());
				}

				break;
			}
			case IntFormat::kOctal: {
				if (REX::StartsWithIgnoreCase(a_value, OCTAL_PREFIX)) {
					a_value.remove_prefix(OCTAL_PREFIX.size());
				}

				break;
			}
			case IntFormat::kHexadecimal: {
				if (REX::StartsWithIgnoreCase(a_value, HEXADECIMAL_PREFIX)) {
					a_value.remove_prefix(HEXADECIMAL_PREFIX.size());
				}

				break;
			}
			default: {
				break;
			}
		}

		auto result = T();

		const auto conversionResult = std::from_chars(
			a_value.data(),
			a_value.data() + a_value.size(),
			result,
			static_cast<std::int32_t>(a_format));
		if (conversionResult.ec != REX::POSIX_ERROR_CODE_SUCCESS) {
			return std::unexpected(conversionResult.ec);
		}

		if (conversionResult.ptr != a_value.data() + a_value.size()) {
			return std::unexpected(REX::PosixErrorCode::invalid_argument);
		}

		return result;
	}

	template <class T>
	[[nodiscard]] constexpr auto FromString(std::string_view a_value, FloatFormat a_format = FloatFormat::kDefault) noexcept
		-> std::expected<T, REX::PosixErrorCode>
		requires(REX::floating_point<T>)
	{
		auto result = T();

		const auto conversionResult = std::from_chars(
			a_value.data(),
			a_value.data() + a_value.size(),
			result,
			static_cast<std::chars_format>(a_format));
		if (conversionResult.ec != REX::POSIX_ERROR_CODE_SUCCESS) {
			return std::unexpected(conversionResult.ec);
		}

		if (conversionResult.ptr != a_value.data() + a_value.size()) {
			return std::unexpected(REX::PosixErrorCode::invalid_argument);
		}

		return result;
	}

	extern template auto FromString<bool>(std::string_view, BoolFormat) noexcept
		-> std::expected<bool, REX::PosixErrorCode>;
	extern template auto FromString<char>(std::string_view) noexcept
		-> std::expected<char, REX::PosixErrorCode>;
	extern template auto FromString<std::int8_t>(std::string_view, IntFormat) noexcept
		-> std::expected<std::int8_t, REX::PosixErrorCode>;
	extern template auto FromString<std::uint8_t>(std::string_view, IntFormat) noexcept
		-> std::expected<std::uint8_t, REX::PosixErrorCode>;
	extern template auto FromString<std::int16_t>(std::string_view, IntFormat) noexcept
		-> std::expected<std::int16_t, REX::PosixErrorCode>;
	extern template auto FromString<std::uint16_t>(std::string_view, IntFormat) noexcept
		-> std::expected<std::uint16_t, REX::PosixErrorCode>;
	extern template auto FromString<std::int32_t>(std::string_view, IntFormat) noexcept
		-> std::expected<std::int32_t, REX::PosixErrorCode>;
	extern template auto FromString<std::uint32_t>(std::string_view, IntFormat) noexcept
		-> std::expected<std::uint32_t, REX::PosixErrorCode>;
	extern template auto FromString<std::int64_t>(std::string_view, IntFormat) noexcept
		-> std::expected<std::int64_t, REX::PosixErrorCode>;
	extern template auto FromString<std::uint64_t>(std::string_view, IntFormat) noexcept
		-> std::expected<std::uint64_t, REX::PosixErrorCode>;
	extern template auto FromString<REX::Float32>(std::string_view, FloatFormat) noexcept
		-> std::expected<REX::Float32, REX::PosixErrorCode>;
	extern template auto FromString<REX::Float64>(std::string_view, FloatFormat) noexcept
		-> std::expected<REX::Float64, REX::PosixErrorCode>;
	extern template auto FromString<REX::Float128>(std::string_view, FloatFormat) noexcept
		-> std::expected<REX::Float128, REX::PosixErrorCode>;

	template <class T>
	[[nodiscard]] constexpr auto ToString(T a_value, BoolFormat a_format = BoolFormat::kDefault) noexcept
		-> std::expected<std::string, REX::PosixErrorCode>
		requires(std::same_as<T, bool>)
	{
		const auto formatSet = REX::EnumSet(a_format);

		const auto formatMask = formatSet & BoolFormat::kAll;
		if (formatMask.empty()) {
			return std::unexpected(REX::PosixErrorCode::invalid_argument);
		}

		const auto& formatTable = formatSet.any(BoolFormat::kCapitalize) ?
									  CAPITAL_BOOL_FORMAT_STRINGS :
									  BOOL_FORMAT_STRINGS;

		const auto formatIndex = static_cast<std::size_t>(std::countr_zero(formatMask.underlying()));
		const auto& [trueString, falseString] = formatTable[formatIndex];
		const auto& valueString = a_value ? trueString : falseString;

		try {
			return std::string(valueString);
		}
		catch ([[maybe_unused]] const std::bad_alloc& error) {
			return std::unexpected(REX::PosixErrorCode::not_enough_memory);
		}
	}

	template <class T>
	[[nodiscard]] constexpr auto ToString(T a_value) noexcept
		-> std::expected<std::string, REX::PosixErrorCode>
		requires(std::same_as<T, char>)
	{
		try {
			return std::string(1, a_value);
		}
		catch ([[maybe_unused]] const std::bad_alloc& error) {
			return std::unexpected(REX::PosixErrorCode::not_enough_memory);
		}
	}

	template <class T>
	[[nodiscard]] constexpr auto ToString(T a_value, IntFormat a_format = IntFormat::kDefault) noexcept
		-> std::expected<std::string, REX::PosixErrorCode>
		requires(REX::integer<T> && !std::same_as<T, char>)
	{
		auto buffer = std::array<char, REX::buffer_traits<T>::buffer_size::value>();

		const auto conversionResult = std::to_chars(
			buffer.data(),
			buffer.data() + buffer.size(),
			a_value,
			static_cast<std::int32_t>(a_format));
		if (conversionResult.ec != REX::POSIX_ERROR_CODE_SUCCESS) {
			return std::unexpected(conversionResult.ec);
		}

		try {
			return std::string{ buffer.data(), static_cast<std::size_t>(std::distance(buffer.data(), conversionResult.ptr)) };
		}
		catch ([[maybe_unused]] const std::bad_alloc& error) {
			return std::unexpected(REX::PosixErrorCode::not_enough_memory);
		}
	}

	template <class T>
	[[nodiscard]] constexpr auto ToString(T a_value, FloatFormat a_format = FloatFormat::kDefault, std::int32_t a_precision = -1) noexcept
		-> std::expected<std::string, REX::PosixErrorCode>
		requires(REX::floating_point<T>)
	{
		auto buffer = std::array<char, REX::buffer_traits<T>::buffer_size::value>();

		const auto conversionResult = std::to_chars(
			buffer.data(),
			buffer.data() + buffer.size(),
			a_value,
			static_cast<std::chars_format>(a_format),
			a_precision);
		if (conversionResult.ec != REX::POSIX_ERROR_CODE_SUCCESS) {
			return std::unexpected(conversionResult.ec);
		}

		try {
			return std::string{ buffer.data(), static_cast<std::size_t>(std::distance(buffer.data(), conversionResult.ptr)) };
		}
		catch ([[maybe_unused]] const std::bad_alloc& error) {
			return std::unexpected(REX::PosixErrorCode::not_enough_memory);
		}
	}

	extern template auto ToString<bool>(bool, BoolFormat) noexcept
		-> std::expected<std::string, REX::PosixErrorCode>;
	extern template auto ToString<char>(char) noexcept
		-> std::expected<std::string, REX::PosixErrorCode>;
	extern template auto ToString<std::int8_t>(std::int8_t, IntFormat) noexcept
		-> std::expected<std::string, REX::PosixErrorCode>;
	extern template auto ToString<std::uint8_t>(std::uint8_t, IntFormat) noexcept
		-> std::expected<std::string, REX::PosixErrorCode>;
	extern template auto ToString<std::int16_t>(std::int16_t, IntFormat) noexcept
		-> std::expected<std::string, REX::PosixErrorCode>;
	extern template auto ToString<std::uint16_t>(std::uint16_t, IntFormat) noexcept
		-> std::expected<std::string, REX::PosixErrorCode>;
	extern template auto ToString<std::int32_t>(std::int32_t, IntFormat) noexcept
		-> std::expected<std::string, REX::PosixErrorCode>;
	extern template auto ToString<std::uint32_t>(std::uint32_t, IntFormat) noexcept
		-> std::expected<std::string, REX::PosixErrorCode>;
	extern template auto ToString<std::int64_t>(std::int64_t, IntFormat) noexcept
		-> std::expected<std::string, REX::PosixErrorCode>;
	extern template auto ToString<std::uint64_t>(std::uint64_t, IntFormat) noexcept
		-> std::expected<std::string, REX::PosixErrorCode>;
	extern template auto ToString<REX::Float32>(REX::Float32, FloatFormat, std::int32_t) noexcept
		-> std::expected<std::string, REX::PosixErrorCode>;
	extern template auto ToString<REX::Float64>(REX::Float64, FloatFormat, std::int32_t) noexcept
		-> std::expected<std::string, REX::PosixErrorCode>;
	extern template auto ToString<REX::Float128>(REX::Float128, FloatFormat, std::int32_t) noexcept
		-> std::expected<std::string, REX::PosixErrorCode>;
}
