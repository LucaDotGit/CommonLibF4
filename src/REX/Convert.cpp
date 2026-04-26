#include "REX/Convert.hpp"

#include "REX/W32/KERNEL32.hpp"

namespace REX
{
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

	static_assert(BOOL_FORMAT_STRINGS[std::countr_zero(std::to_underlying(BoolFormat::kTrueFalse))] == std::make_pair(TRUE_STRING, FALSE_STRING));
	static_assert(BOOL_FORMAT_STRINGS[std::countr_zero(std::to_underlying(BoolFormat::kYesNo))] == std::make_pair(YES_STRING, NO_STRING));
	static_assert(BOOL_FORMAT_STRINGS[std::countr_zero(std::to_underlying(BoolFormat::kOnOff))] == std::make_pair(ON_STRING, OFF_STRING));
	static_assert(BOOL_FORMAT_STRINGS[std::countr_zero(std::to_underlying(BoolFormat::kOneZero))] == std::make_pair(ONE_STRING, ZERO_STRING));

	static_assert(CAPITAL_BOOL_FORMAT_STRINGS[std::countr_zero(std::to_underlying(BoolFormat::kTrueFalse))] == std::make_pair(CAPITAL_TRUE_STRING, CAPITAL_FALSE_STRING));
	static_assert(CAPITAL_BOOL_FORMAT_STRINGS[std::countr_zero(std::to_underlying(BoolFormat::kYesNo))] == std::make_pair(CAPITAL_YES_STRING, CAPITAL_NO_STRING));
	static_assert(CAPITAL_BOOL_FORMAT_STRINGS[std::countr_zero(std::to_underlying(BoolFormat::kOnOff))] == std::make_pair(CAPITAL_ON_STRING, CAPITAL_OFF_STRING));
	static_assert(CAPITAL_BOOL_FORMAT_STRINGS[std::countr_zero(std::to_underlying(BoolFormat::kOneZero))] == std::make_pair(ONE_STRING, ZERO_STRING));

	auto Utf8ToUtf16(std::string_view a_value) noexcept -> std::expected<std::wstring, REX::SystemError>
	{
		if (a_value.empty()) {
			return std::wstring();
		}

		const auto doConvert = [a_value](wchar_t* a_target, std::size_t a_length) -> std::int32_t {
			return REX::W32::MultiByteToWideChar(
				REX::W32::CP_UTF8,
				0,
				a_value.data(),
				static_cast<std::int32_t>(a_value.size()),
				a_target,
				static_cast<std::int32_t>(a_length));
		};

		const auto readSize = doConvert(nullptr, 0);
		if (readSize == 0) {
			return std::unexpected(REX::GetCurrentSystemError());
		}

		auto result = std::wstring();

		try {
			result.resize(readSize);
		}
		catch ([[maybe_unused]] const std::bad_alloc& error) {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::not_enough_memory));
		}

		const auto writeSize = doConvert(result.data(), result.size());
		if (writeSize == 0) {
			return std::unexpected(REX::GetCurrentSystemError());
		}

		try {
			result.resize(writeSize);
		}
		catch ([[maybe_unused]] const std::bad_alloc& error) {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::not_enough_memory));
		}

		return result;
	}

	auto Utf16ToUtf8(std::wstring_view a_value) noexcept -> std::expected<std::string, REX::SystemError>
	{
		if (a_value.empty()) {
			return std::string();
		}

		const auto doConvert = [a_value](char* a_target, std::size_t a_length) -> std::int32_t {
			constexpr auto FLAGS = static_cast<std::uint32_t>(0);
			constexpr auto DEFAULT_STRING = static_cast<const char*>(nullptr);
			constexpr auto DEFAULT_LENGTH = static_cast<std::int32_t*>(nullptr);

			return REX::W32::WideCharToMultiByte(
				REX::W32::CP_UTF8,
				FLAGS,
				a_value.data(),
				static_cast<std::int32_t>(a_value.size()),
				a_target,
				static_cast<std::int32_t>(a_length),
				DEFAULT_STRING,
				DEFAULT_LENGTH);
		};

		const auto readSize = doConvert(nullptr, 0);
		if (readSize == 0) {
			return std::unexpected(REX::GetCurrentSystemError());
		}

		auto result = std::string();

		try {
			result.resize(readSize);
		}
		catch ([[maybe_unused]] const std::bad_alloc& error) {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::not_enough_memory));
		}

		const auto writeSize = doConvert(result.data(), result.size());
		if (writeSize == 0) {
			return std::unexpected(REX::GetCurrentSystemError());
		}

		try {
			result.resize(writeSize);
		}
		catch ([[maybe_unused]] const std::bad_alloc& error) {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::not_enough_memory));
		}

		return result;
	}

	template auto FromString<bool>(std::string_view, BoolFormat) noexcept -> std::expected<bool, REX::PosixErrorCode>;
	template auto FromString<char>(std::string_view) noexcept -> std::expected<char, REX::PosixErrorCode>;
	template auto FromString<std::int8_t>(std::string_view, IntFormat) noexcept -> std::expected<std::int8_t, REX::PosixErrorCode>;
	template auto FromString<std::uint8_t>(std::string_view, IntFormat) noexcept -> std::expected<std::uint8_t, REX::PosixErrorCode>;
	template auto FromString<std::int16_t>(std::string_view, IntFormat) noexcept -> std::expected<std::int16_t, REX::PosixErrorCode>;
	template auto FromString<std::uint16_t>(std::string_view, IntFormat) noexcept -> std::expected<std::uint16_t, REX::PosixErrorCode>;
	template auto FromString<std::int32_t>(std::string_view, IntFormat) noexcept -> std::expected<std::int32_t, REX::PosixErrorCode>;
	template auto FromString<std::uint32_t>(std::string_view, IntFormat) noexcept -> std::expected<std::uint32_t, REX::PosixErrorCode>;
	template auto FromString<std::int64_t>(std::string_view, IntFormat) noexcept -> std::expected<std::int64_t, REX::PosixErrorCode>;
	template auto FromString<std::uint64_t>(std::string_view, IntFormat) noexcept -> std::expected<std::uint64_t, REX::PosixErrorCode>;
	template auto FromString<REX::Float32>(std::string_view, FloatFormat) noexcept -> std::expected<REX::Float32, REX::PosixErrorCode>;
	template auto FromString<REX::Float64>(std::string_view, FloatFormat) noexcept -> std::expected<REX::Float64, REX::PosixErrorCode>;
	template auto FromString<REX::Float128>(std::string_view, FloatFormat) noexcept -> std::expected<REX::Float128, REX::PosixErrorCode>;

	static_assert(FromString<bool>(TRUE_STRING, BoolFormat::kTrueFalse).value());
	static_assert(!FromString<bool>(FALSE_STRING, BoolFormat::kTrueFalse).value());
	static_assert(FromString<bool>(YES_STRING, BoolFormat::kYesNo).value());
	static_assert(!FromString<bool>(NO_STRING, BoolFormat::kYesNo).value());
	static_assert(FromString<bool>(ON_STRING, BoolFormat::kOnOff).value());
	static_assert(!FromString<bool>(OFF_STRING, BoolFormat::kOnOff).value());
	static_assert(FromString<bool>(ONE_STRING, BoolFormat::kOneZero).value());
	static_assert(!FromString<bool>(ZERO_STRING, BoolFormat::kOneZero).value());

	static_assert(FromString<char>("A"sv).value() == 'A');
	static_assert(FromString<char>("z"sv).value() == 'z');
	static_assert(FromString<char>("0"sv).value() == '0');
	static_assert(FromString<char>("9"sv).value() == '9');

	static_assert(FromString<std::int8_t>("-10000000"sv, IntFormat::kBinary).value() == std::numeric_limits<std::int8_t>::min());
	static_assert(FromString<std::uint8_t>("11111111"sv, IntFormat::kBinary).value() == std::numeric_limits<std::uint8_t>::max());
	static_assert(FromString<std::int16_t>("-1000000000000000"sv, IntFormat::kBinary).value() == std::numeric_limits<std::int16_t>::min());
	static_assert(FromString<std::uint16_t>("1111111111111111"sv, IntFormat::kBinary).value() == std::numeric_limits<std::uint16_t>::max());
	static_assert(FromString<std::int32_t>("-10000000000000000000000000000000"sv, IntFormat::kBinary).value() == std::numeric_limits<std::int32_t>::min());
	static_assert(FromString<std::uint32_t>("11111111111111111111111111111111"sv, IntFormat::kBinary).value() == std::numeric_limits<std::uint32_t>::max());
	static_assert(FromString<std::int64_t>("-1000000000000000000000000000000000000000000000000000000000000000"sv, IntFormat::kBinary).value() == std::numeric_limits<std::int64_t>::min());
	static_assert(FromString<std::uint64_t>("1111111111111111111111111111111111111111111111111111111111111111"sv, IntFormat::kBinary).value() == std::numeric_limits<std::uint64_t>::max());

	template auto ToString<bool>(bool, BoolFormat) noexcept -> std::expected<std::string, REX::PosixErrorCode>;
	template auto ToString<char>(char) noexcept -> std::expected<std::string, REX::PosixErrorCode>;
	template auto ToString<std::int8_t>(std::int8_t, IntFormat) noexcept -> std::expected<std::string, REX::PosixErrorCode>;
	template auto ToString<std::uint8_t>(std::uint8_t, IntFormat) noexcept -> std::expected<std::string, REX::PosixErrorCode>;
	template auto ToString<std::int16_t>(std::int16_t, IntFormat) noexcept -> std::expected<std::string, REX::PosixErrorCode>;
	template auto ToString<std::uint16_t>(std::uint16_t, IntFormat) noexcept -> std::expected<std::string, REX::PosixErrorCode>;
	template auto ToString<std::int32_t>(std::int32_t, IntFormat) noexcept -> std::expected<std::string, REX::PosixErrorCode>;
	template auto ToString<std::uint32_t>(std::uint32_t, IntFormat) noexcept -> std::expected<std::string, REX::PosixErrorCode>;
	template auto ToString<std::int64_t>(std::int64_t, IntFormat) noexcept -> std::expected<std::string, REX::PosixErrorCode>;
	template auto ToString<std::uint64_t>(std::uint64_t, IntFormat) noexcept -> std::expected<std::string, REX::PosixErrorCode>;
	template auto ToString<REX::Float32>(REX::Float32, FloatFormat, std::int32_t) noexcept -> std::expected<std::string, REX::PosixErrorCode>;
	template auto ToString<REX::Float64>(REX::Float64, FloatFormat, std::int32_t) noexcept -> std::expected<std::string, REX::PosixErrorCode>;
	template auto ToString<REX::Float128>(REX::Float128, FloatFormat, std::int32_t) noexcept -> std::expected<std::string, REX::PosixErrorCode>;

	static_assert(ToString(true, BoolFormat::kTrueFalse).value() == TRUE_STRING);
	static_assert(ToString(false, BoolFormat::kTrueFalse).value() == FALSE_STRING);
	static_assert(ToString(true, BoolFormat::kYesNo).value() == YES_STRING);
	static_assert(ToString(false, BoolFormat::kYesNo).value() == NO_STRING);
	static_assert(ToString(true, BoolFormat::kOnOff).value() == ON_STRING);
	static_assert(ToString(false, BoolFormat::kOnOff).value() == OFF_STRING);
	static_assert(ToString(true, BoolFormat::kOneZero).value() == ONE_STRING);
	static_assert(ToString(false, BoolFormat::kOneZero).value() == ZERO_STRING);

	static_assert(ToString(true, EnumSet(BoolFormat::kTrueFalse, BoolFormat::kCapitalize).get()).value() == CAPITAL_TRUE_STRING);
	static_assert(ToString(false, EnumSet(BoolFormat::kTrueFalse, BoolFormat::kCapitalize).get()).value() == CAPITAL_FALSE_STRING);
	static_assert(ToString(true, EnumSet(BoolFormat::kYesNo, BoolFormat::kCapitalize).get()).value() == CAPITAL_YES_STRING);
	static_assert(ToString(false, EnumSet(BoolFormat::kYesNo, BoolFormat::kCapitalize).get()).value() == CAPITAL_NO_STRING);
	static_assert(ToString(true, EnumSet(BoolFormat::kOnOff, BoolFormat::kCapitalize).get()).value() == CAPITAL_ON_STRING);
	static_assert(ToString(false, EnumSet(BoolFormat::kOnOff, BoolFormat::kCapitalize).get()).value() == CAPITAL_OFF_STRING);
	static_assert(ToString(true, EnumSet(BoolFormat::kOneZero, BoolFormat::kCapitalize).get()).value() == ONE_STRING);
	static_assert(ToString(false, EnumSet(BoolFormat::kOneZero, BoolFormat::kCapitalize).get()).value() == ZERO_STRING);

	static_assert(ToString('A').value() == "A"sv);
	static_assert(ToString('z').value() == "z"sv);
	static_assert(ToString('0').value() == "0"sv);
	static_assert(ToString('9').value() == "9"sv);

	static_assert(ToString(std::numeric_limits<std::int8_t>::min(), IntFormat::kBinary).value() == "-10000000"sv);
	static_assert(ToString(std::numeric_limits<std::uint8_t>::max(), IntFormat::kBinary).value() == "11111111"sv);
	static_assert(ToString(std::numeric_limits<std::int16_t>::min(), IntFormat::kBinary).value() == "-1000000000000000"sv);
	static_assert(ToString(std::numeric_limits<std::uint16_t>::max(), IntFormat::kBinary).value() == "1111111111111111"sv);
	static_assert(ToString(std::numeric_limits<std::int32_t>::min(), IntFormat::kBinary).value() == "-10000000000000000000000000000000"sv);
	static_assert(ToString(std::numeric_limits<std::uint32_t>::max(), IntFormat::kBinary).value() == "11111111111111111111111111111111"sv);
	static_assert(ToString(std::numeric_limits<std::int64_t>::min(), IntFormat::kBinary).value() == "-1000000000000000000000000000000000000000000000000000000000000000"sv);
	static_assert(ToString(std::numeric_limits<std::uint64_t>::max(), IntFormat::kBinary).value() == "1111111111111111111111111111111111111111111111111111111111111111"sv);
}
