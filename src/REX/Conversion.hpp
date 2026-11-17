#pragma once

#include "REX/Comparison.hpp"
#include "REX/Concepts.hpp"
#include "REX/EnumSet.hpp"
#include "REX/Error.hpp"

namespace REX
{
	enum class BoolFormat : std::uint32_t
	{
		TrueFalse = 1 << 0,
		YesNo = 1 << 1,
		OnOff = 1 << 2,
		OneZero = 1 << 3,

		CaseSensitive = 1 << 8,
		Capitalize = 1 << 9,

		Default = TrueFalse,

		All = TrueFalse | YesNo | OnOff | OneZero
	};

	enum class IntFormat : std::int32_t
	{
		Base02 = 2,
		Base08 = 8,
		Base10 = 10,
		Base16 = 16,
		Base32 = 32,

		Binary = Base02,
		Octal = Base08,
		Decimal = Base10,
		Hexadecimal = Base16,

		Default = Decimal
	};

	enum class FloatFormat : std::uint32_t
	{
		Scientific = static_cast<std::underlying_type_t<FloatFormat>>(std::chars_format::scientific),
		Fixed = static_cast<std::underlying_type_t<FloatFormat>>(std::chars_format::fixed),
		Hexadecimal = static_cast<std::underlying_type_t<FloatFormat>>(std::chars_format::hex),

		Default = static_cast<std::underlying_type_t<FloatFormat>>(std::chars_format::general)
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

	static_assert(TRUE_STRING.size() == CAPITAL_TRUE_STRING.size());
	static_assert(FALSE_STRING.size() == CAPITAL_FALSE_STRING.size());
	static_assert(YES_STRING.size() == CAPITAL_YES_STRING.size());
	static_assert(NO_STRING.size() == CAPITAL_NO_STRING.size());
	static_assert(ON_STRING.size() == CAPITAL_ON_STRING.size());
	static_assert(OFF_STRING.size() == CAPITAL_OFF_STRING.size());

	static_assert(BINARY_PREFIX.size() == CAPITAL_BINARY_PREFIX.size());
	static_assert(OCTAL_PREFIX.size() == CAPITAL_OCTAL_PREFIX.size());
	static_assert(HEXADECIMAL_PREFIX.size() == CAPITAL_HEXADECIMAL_PREFIX.size());

	static_assert(BOOL_FORMAT_STRINGS.size() == CAPITAL_BOOL_FORMAT_STRINGS.size());

	static_assert(
		BOOL_FORMAT_STRINGS[std::countr_zero(std::to_underlying(BoolFormat::TrueFalse))] ==
		std::make_pair(TRUE_STRING, FALSE_STRING));
	static_assert(
		BOOL_FORMAT_STRINGS[std::countr_zero(std::to_underlying(BoolFormat::YesNo))] ==
		std::make_pair(YES_STRING, NO_STRING));
	static_assert(
		BOOL_FORMAT_STRINGS[std::countr_zero(std::to_underlying(BoolFormat::OnOff))] ==
		std::make_pair(ON_STRING, OFF_STRING));
	static_assert(
		BOOL_FORMAT_STRINGS[std::countr_zero(std::to_underlying(BoolFormat::OneZero))] ==
		std::make_pair(ONE_STRING, ZERO_STRING));

	static_assert(
		CAPITAL_BOOL_FORMAT_STRINGS[std::countr_zero(std::to_underlying(BoolFormat::TrueFalse))] ==
		std::make_pair(CAPITAL_TRUE_STRING, CAPITAL_FALSE_STRING));
	static_assert(
		CAPITAL_BOOL_FORMAT_STRINGS[std::countr_zero(std::to_underlying(BoolFormat::YesNo))] ==
		std::make_pair(CAPITAL_YES_STRING, CAPITAL_NO_STRING));
	static_assert(
		CAPITAL_BOOL_FORMAT_STRINGS[std::countr_zero(std::to_underlying(BoolFormat::OnOff))] ==
		std::make_pair(CAPITAL_ON_STRING, CAPITAL_OFF_STRING));
	static_assert(
		CAPITAL_BOOL_FORMAT_STRINGS[std::countr_zero(std::to_underlying(BoolFormat::OneZero))] ==
		std::make_pair(ONE_STRING, ZERO_STRING));

	template <class T, class... Args>
	[[nodiscard]]
	constexpr auto BitsToValue(Args... a_args) noexcept -> T
		requires(sizeof...(Args) > 0 && ((sizeof(Args) == sizeof(std::byte)) && ...))
	{
		constexpr auto ARGS_SIZE = sizeof...(Args);

		auto bits = std::bitset<ARGS_SIZE>();
		auto i = static_cast<std::size_t>(0);
		((bits[i++] = a_args), ...);

		if constexpr (ARGS_SIZE <= std::numeric_limits<std::uint32_t>::digits) {
			return static_cast<T>(bits.to_ulong());
		}
		else if constexpr (ARGS_SIZE <= std::numeric_limits<std::uint64_t>::digits) {
			return static_cast<T>(bits.to_ullong());
		}
		else {
			static_assert(false, "The number of bits exceeds the maximum supported conversion size.");
		}
	}

	static_assert(BitsToValue<std::uint8_t>(static_cast<std::uint8_t>(1)) == static_cast<std::uint8_t>(0b1));
	static_assert(
		BitsToValue<std::uint8_t>(static_cast<std::uint8_t>(1), static_cast<std::uint8_t>(0)) ==
		static_cast<std::uint8_t>(0b01));
	static_assert(
		BitsToValue<std::uint8_t>(
			static_cast<std::uint8_t>(1),
			static_cast<std::uint8_t>(0),
			static_cast<std::uint8_t>(1),
			static_cast<std::uint8_t>(0)) == static_cast<std::uint8_t>(0b0101));
	static_assert(
		BitsToValue<std::uint8_t>(
			static_cast<std::uint8_t>(1),
			static_cast<std::uint8_t>(0),
			static_cast<std::uint8_t>(1),
			static_cast<std::uint8_t>(0),
			static_cast<std::uint8_t>(1),
			static_cast<std::uint8_t>(0),
			static_cast<std::uint8_t>(1),
			static_cast<std::uint8_t>(0)) == static_cast<std::uint8_t>(0b0101'0101));

	[[nodiscard]]
	auto Utf8ToUtf16(std::string_view a_source, std::span<wchar_t> a_buffer) noexcept
		-> std::expected<std::size_t, REX::SystemError>;

	[[nodiscard]]
	auto Utf8ToUtf16(std::u8string_view a_source, std::span<char16_t> a_buffer) noexcept
		-> std::expected<std::size_t, REX::SystemError>;

	[[nodiscard]]
	auto Utf16ToUtf8(std::wstring_view a_source, std::span<char> a_buffer) noexcept
		-> std::expected<std::size_t, REX::SystemError>;

	[[nodiscard]]
	auto Utf16ToUtf8(std::u16string_view a_source, std::span<char8_t> a_buffer) noexcept
		-> std::expected<std::size_t, REX::SystemError>;

	[[nodiscard]]
	auto Utf8ToUtf16(std::string_view a_source) noexcept -> std::expected<std::wstring, REX::SystemError>;

	[[nodiscard]]
	auto Utf8ToUtf16(std::u8string_view a_source) noexcept -> std::expected<std::u16string, REX::SystemError>;

	[[nodiscard]]
	auto Utf16ToUtf8(std::wstring_view a_source) noexcept -> std::expected<std::string, REX::SystemError>;

	[[nodiscard]]
	auto Utf16ToUtf8(std::u16string_view a_source) noexcept -> std::expected<std::u8string, REX::SystemError>;

	template <class T>
	[[nodiscard]]
	constexpr auto FromString(std::string_view a_value, BoolFormat a_format = BoolFormat::Default) noexcept
		-> std::expected<T, REX::PosixErrorCode>
		requires(REX::boolean<T>)
	{
		if (a_value.empty()) [[unlikely]] {
			return std::unexpected(REX::PosixErrorCode::invalid_argument);
		}

		const auto formatSet = REX::EnumSet(a_format);
		if (formatSet.none(BoolFormat::All)) [[unlikely]] {
			return std::unexpected(REX::PosixErrorCode::invalid_argument);
		}

		const auto& formatTable =
			formatSet.any(BoolFormat::Capitalize) ? CAPITAL_BOOL_FORMAT_STRINGS : BOOL_FORMAT_STRINGS;

		const auto formatComparer =
			[formatSet](std::string_view a_value, std::string_view a_formatString) noexcept -> bool {
			if (formatSet.any(BoolFormat::CaseSensitive)) {
				return REX::Equals(a_value, a_formatString);
			}

			return REX::EqualsIgnoreCase(a_value, a_formatString);
		};

		for (auto formatIndex = static_cast<std::underlying_type_t<decltype(a_format)>>(0);
			 formatIndex < formatTable.size();
			 formatIndex++) {
			const auto formatBit = static_cast<std::underlying_type_t<decltype(a_format)>>(1) << formatIndex;
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
	[[nodiscard]]
	constexpr auto FromString(std::string_view a_value) noexcept -> std::expected<T, REX::PosixErrorCode>
		requires(std::same_as<T, char>)
	{
		if (a_value.size() != 1) [[unlikely]] {
			return std::unexpected(REX::PosixErrorCode::invalid_argument);
		}

		return a_value.front();
	}

	template <class T>
	[[nodiscard]]
	constexpr auto FromString(std::string_view a_value, IntFormat a_format = IntFormat::Default) noexcept
		-> std::expected<T, REX::PosixErrorCode>
		requires(REX::integer<T> && !std::same_as<T, char>)
	{
		switch (a_format) {
			case IntFormat::Binary: {
				if (REX::StartsWithIgnoreCase(a_value, BINARY_PREFIX)) {
					a_value.remove_prefix(BINARY_PREFIX.size());
				}

				break;
			}
			case IntFormat::Octal: {
				if (REX::StartsWithIgnoreCase(a_value, OCTAL_PREFIX)) {
					a_value.remove_prefix(OCTAL_PREFIX.size());
				}

				break;
			}
			case IntFormat::Hexadecimal: {
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
		if (conversionResult.ec != REX::POSIX_ERROR_CODE_SUCCESS) [[unlikely]] {
			return std::unexpected(conversionResult.ec);
		}

		if (conversionResult.ptr != a_value.data() + a_value.size()) [[unlikely]] {
			return std::unexpected(REX::PosixErrorCode::result_out_of_range);
		}

		return result;
	}

	template <class T>
	[[nodiscard]]
	constexpr auto FromString(std::string_view a_value, FloatFormat a_format = FloatFormat::Default) noexcept
		-> std::expected<T, REX::PosixErrorCode>
		requires(REX::floating_point<T>)
	{
		auto result = T();

		const auto conversionResult = std::from_chars(
			a_value.data(),
			a_value.data() + a_value.size(),
			result,
			static_cast<std::chars_format>(a_format));
		if (conversionResult.ec != REX::POSIX_ERROR_CODE_SUCCESS) [[unlikely]] {
			return std::unexpected(conversionResult.ec);
		}

		if (conversionResult.ptr != a_value.data() + a_value.size()) [[unlikely]] {
			return std::unexpected(REX::PosixErrorCode::result_out_of_range);
		}

		return result;
	}

	static_assert(FromString<bool>(TRUE_STRING, BoolFormat::TrueFalse).value());
	static_assert(!FromString<bool>(FALSE_STRING, BoolFormat::TrueFalse).value());
	static_assert(FromString<bool>(YES_STRING, BoolFormat::YesNo).value());
	static_assert(!FromString<bool>(NO_STRING, BoolFormat::YesNo).value());
	static_assert(FromString<bool>(ON_STRING, BoolFormat::OnOff).value());
	static_assert(!FromString<bool>(OFF_STRING, BoolFormat::OnOff).value());
	static_assert(FromString<bool>(ONE_STRING, BoolFormat::OneZero).value());
	static_assert(!FromString<bool>(ZERO_STRING, BoolFormat::OneZero).value());

	static_assert(FromString<char>("A"sv).value() == 'A');
	static_assert(FromString<char>("z"sv).value() == 'z');
	static_assert(FromString<char>("0"sv).value() == '0');
	static_assert(FromString<char>("9"sv).value() == '9');

	static_assert(
		FromString<std::int8_t>("-10000000"sv, IntFormat::Binary).value() == std::numeric_limits<std::int8_t>::min());
	static_assert(
		FromString<std::uint8_t>("11111111"sv, IntFormat::Binary).value() == std::numeric_limits<std::uint8_t>::max());
	static_assert(
		FromString<std::int16_t>("-1000000000000000"sv, IntFormat::Binary).value() ==
		std::numeric_limits<std::int16_t>::min());
	static_assert(
		FromString<std::uint16_t>("1111111111111111"sv, IntFormat::Binary).value() ==
		std::numeric_limits<std::uint16_t>::max());
	static_assert(
		FromString<std::int32_t>("-10000000000000000000000000000000"sv, IntFormat::Binary).value() ==
		std::numeric_limits<std::int32_t>::min());
	static_assert(
		FromString<std::uint32_t>("11111111111111111111111111111111"sv, IntFormat::Binary).value() ==
		std::numeric_limits<std::uint32_t>::max());
	static_assert(
		FromString<std::int64_t>(
			"-1000000000000000000000000000000000000000000000000000000000000000"sv,
			IntFormat::Binary)
			.value() == std::numeric_limits<std::int64_t>::min());
	static_assert(
		FromString<std::uint64_t>(
			"1111111111111111111111111111111111111111111111111111111111111111"sv,
			IntFormat::Binary)
			.value() == std::numeric_limits<std::uint64_t>::max());

	template <class T>
	[[nodiscard]]
	constexpr auto ToString(T a_value, BoolFormat a_format = BoolFormat::Default) noexcept
		-> std::expected<std::string, REX::PosixErrorCode>
		requires(REX::boolean<T>)
	{
		const auto formatSet = REX::EnumSet(a_format);

		const auto formatMask = formatSet & BoolFormat::All;
		if (formatMask.empty()) [[unlikely]] {
			return std::unexpected(REX::PosixErrorCode::invalid_argument);
		}

		const auto& formatTable =
			formatSet.any(BoolFormat::Capitalize) ? CAPITAL_BOOL_FORMAT_STRINGS : BOOL_FORMAT_STRINGS;

		const auto formatIndex = static_cast<std::size_t>(std::countr_zero(formatMask.underlying()));
		const auto& [trueString, falseString] = formatTable[formatIndex];
		const auto& valueString = a_value ? trueString : falseString;

		try {
			return std::string(valueString);
		}
		catch (const std::bad_alloc& error) {
			std::ignore = error;
			return std::unexpected(REX::PosixErrorCode::not_enough_memory);
		}
	}

	template <class T>
	[[nodiscard]]
	constexpr auto ToString(T a_value) noexcept -> std::expected<std::string, REX::PosixErrorCode>
		requires(std::same_as<T, char>)
	{
		try {
			return std::string(1, a_value);
		}
		catch (const std::bad_alloc& error) {
			std::ignore = error;
			return std::unexpected(REX::PosixErrorCode::not_enough_memory);
		}
	}

	template <class T>
	[[nodiscard]]
	constexpr auto ToString(T a_value, IntFormat a_format = IntFormat::Default) noexcept
		-> std::expected<std::string, REX::PosixErrorCode>
		requires(REX::integer<T> && !std::same_as<T, char>)
	{
		auto buffer = std::array<char, REX::buffer_traits<T>::buffer_size::value>();

		const auto conversionResult =
			std::to_chars(buffer.data(), buffer.data() + buffer.size(), a_value, static_cast<std::int32_t>(a_format));
		if (conversionResult.ec != REX::POSIX_ERROR_CODE_SUCCESS) [[unlikely]] {
			return std::unexpected(conversionResult.ec);
		}

		try {
			return std::string{
				buffer.data(),
				static_cast<std::size_t>(std::distance(buffer.data(), conversionResult.ptr))
			};
		}
		catch (const std::bad_alloc& error) {
			std::ignore = error;
			return std::unexpected(REX::PosixErrorCode::not_enough_memory);
		}
	}

	template <class T>
	[[nodiscard]]
	constexpr auto ToString(T a_value, FloatFormat a_format = FloatFormat::Default, std::int32_t a_precision = -1)
		noexcept -> std::expected<std::string, REX::PosixErrorCode>
		requires(REX::floating_point<T>)
	{
		auto buffer = std::array<char, REX::buffer_traits<T>::buffer_size::value>();

		const auto conversionResult = std::to_chars(
			buffer.data(),
			buffer.data() + buffer.size(),
			a_value,
			static_cast<std::chars_format>(a_format),
			a_precision);
		if (conversionResult.ec != REX::POSIX_ERROR_CODE_SUCCESS) [[unlikely]] {
			return std::unexpected(conversionResult.ec);
		}

		try {
			return std::string{
				buffer.data(),
				static_cast<std::size_t>(std::distance(buffer.data(), conversionResult.ptr))
			};
		}
		catch (const std::bad_alloc& error) {
			std::ignore = error;
			return std::unexpected(REX::PosixErrorCode::not_enough_memory);
		}
	}

	static_assert(ToString(true, BoolFormat::TrueFalse).value() == TRUE_STRING);
	static_assert(ToString(false, BoolFormat::TrueFalse).value() == FALSE_STRING);
	static_assert(ToString(true, BoolFormat::YesNo).value() == YES_STRING);
	static_assert(ToString(false, BoolFormat::YesNo).value() == NO_STRING);
	static_assert(ToString(true, BoolFormat::OnOff).value() == ON_STRING);
	static_assert(ToString(false, BoolFormat::OnOff).value() == OFF_STRING);
	static_assert(ToString(true, BoolFormat::OneZero).value() == ONE_STRING);
	static_assert(ToString(false, BoolFormat::OneZero).value() == ZERO_STRING);

	static_assert(
		ToString(true, REX::EnumSet(BoolFormat::TrueFalse, BoolFormat::Capitalize).get()).value() ==
		CAPITAL_TRUE_STRING);
	static_assert(
		ToString(false, REX::EnumSet(BoolFormat::TrueFalse, BoolFormat::Capitalize).get()).value() ==
		CAPITAL_FALSE_STRING);
	static_assert(
		ToString(true, REX::EnumSet(BoolFormat::YesNo, BoolFormat::Capitalize).get()).value() == CAPITAL_YES_STRING);
	static_assert(
		ToString(false, REX::EnumSet(BoolFormat::YesNo, BoolFormat::Capitalize).get()).value() == CAPITAL_NO_STRING);
	static_assert(
		ToString(true, REX::EnumSet(BoolFormat::OnOff, BoolFormat::Capitalize).get()).value() == CAPITAL_ON_STRING);
	static_assert(
		ToString(false, REX::EnumSet(BoolFormat::OnOff, BoolFormat::Capitalize).get()).value() == CAPITAL_OFF_STRING);
	static_assert(
		ToString(true, REX::EnumSet(BoolFormat::OneZero, BoolFormat::Capitalize).get()).value() == ONE_STRING);
	static_assert(
		ToString(false, REX::EnumSet(BoolFormat::OneZero, BoolFormat::Capitalize).get()).value() == ZERO_STRING);

	static_assert(ToString('A').value() == "A"sv);
	static_assert(ToString('z').value() == "z"sv);
	static_assert(ToString('0').value() == "0"sv);
	static_assert(ToString('9').value() == "9"sv);

	static_assert(ToString(std::numeric_limits<std::int8_t>::min(), IntFormat::Binary).value() == "-10000000"sv);
	static_assert(ToString(std::numeric_limits<std::uint8_t>::max(), IntFormat::Binary).value() == "11111111"sv);
	static_assert(
		ToString(std::numeric_limits<std::int16_t>::min(), IntFormat::Binary).value() == "-1000000000000000"sv);
	static_assert(
		ToString(std::numeric_limits<std::uint16_t>::max(), IntFormat::Binary).value() == "1111111111111111"sv);
	static_assert(
		ToString(std::numeric_limits<std::int32_t>::min(), IntFormat::Binary).value() ==
		"-10000000000000000000000000000000"sv);
	static_assert(
		ToString(std::numeric_limits<std::uint32_t>::max(), IntFormat::Binary).value() ==
		"11111111111111111111111111111111"sv);
	static_assert(
		ToString(std::numeric_limits<std::int64_t>::min(), IntFormat::Binary).value() ==
		"-1000000000000000000000000000000000000000000000000000000000000000"sv);
	static_assert(
		ToString(std::numeric_limits<std::uint64_t>::max(), IntFormat::Binary).value() ==
		"1111111111111111111111111111111111111111111111111111111111111111"sv);
}

#if __has_include(<glaze/glaze.hpp>)
namespace glz
{
	template <>
	struct meta<std::wstring>
	{
	public:
		using self_type = std::wstring;
		using other_type = std::string;

		inline static constexpr auto read_fn =
			[](self_type& a_self, const other_type& a_value, glz::context& a_context) -> void {
			using namespace std::string_view_literals;

			auto result = REX::Utf8ToUtf16(a_value);
			if (!result.has_value()) {
				a_context.error = glz::error_code::constraint_violated;
				a_context.custom_error_message = "Invalid UTF-8 string"sv;
				return;
			}

			a_self = std::move(result).value();
		};

		inline static constexpr auto write_fn =
			[](const self_type& a_self, other_type& a_other, glz::context& a_context) -> void {
			using namespace std::string_view_literals;

			auto result = REX::Utf16ToUtf8(a_self);
			if (!result.has_value()) {
				a_context.error = glz::error_code::constraint_violated;
				a_context.custom_error_message = "Invalid UTF-16 string"sv;
				return;
			}

			a_other = std::move(result).value();
		};

		inline static constexpr auto value = glz::custom<read_fn, write_fn>;
	};

	template <>
	struct meta<std::u16string>
	{
	public:
		using self_type = std::u16string;
		using other_type = std::u8string;

		inline static constexpr auto read_fn =
			[](self_type& a_self, const other_type& a_value, glz::context& a_context) -> void {
			using namespace std::string_view_literals;

			auto result = REX::Utf8ToUtf16(a_value);
			if (!result.has_value()) {
				a_context.error = glz::error_code::constraint_violated;
				a_context.custom_error_message = "Invalid UTF-8 string"sv;
				return;
			}

			a_self = std::move(result).value();
		};

		inline static constexpr auto write_fn =
			[](const self_type& a_self, other_type& a_other, glz::context& a_context) -> void {
			using namespace std::string_view_literals;

			auto result = REX::Utf16ToUtf8(a_self);
			if (!result.has_value()) {
				a_context.error = glz::error_code::constraint_violated;
				a_context.custom_error_message = "Invalid UTF-16 string"sv;
				return;
			}

			a_other = std::move(result).value();
		};

		inline static constexpr auto value = glz::custom<read_fn, write_fn>;
	};
}
#endif
