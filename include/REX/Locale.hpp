#pragma once

#include "REX/Concepts.hpp"

namespace REX
{
	using CLocale = std::unique_ptr<std::remove_pointer_t<::_locale_t>, decltype(&::_free_locale)>;
	using CppLocale = std::locale;

	inline constexpr auto DEFAULT_LOCALE_NAME = "en_US.UTF-8"sv;

	template <REX::win32_character T>
	inline constexpr auto MIN_ASCII_CHAR = static_cast<T>(0);

	template <REX::win32_character T>
	inline constexpr auto MAX_ASCII_CHAR = static_cast<T>(std::numeric_limits<char>::max());

	template <REX::win32_character T>
	inline constexpr auto MIN_DIGIT_CHAR = static_cast<T>('0');

	template <REX::win32_character T>
	inline constexpr auto MAX_DIGIT_CHAR = static_cast<T>('9');

	template <REX::win32_character T>
	inline constexpr auto MIN_LOWER_LETTER_CHAR = static_cast<T>('a');

	template <REX::win32_character T>
	inline constexpr auto MAX_LOWER_LETTER_CHAR = static_cast<T>('z');

	template <REX::win32_character T>
	inline constexpr auto MIN_UPPER_LETTER_CHAR = static_cast<T>('A');

	template <REX::win32_character T>
	inline constexpr auto MAX_UPPER_LETTER_CHAR = static_cast<T>('Z');

	template <REX::win32_character T>
	inline constexpr auto MIN_HEXADECIMAL_LOWER_LETTER_CHAR = static_cast<T>('a');

	template <REX::win32_character T>
	inline constexpr auto MAX_HEXADECIMAL_LOWER_LETTER_CHAR = static_cast<T>('f');

	template <REX::win32_character T>
	inline constexpr auto MIN_HEXADECIMAL_UPPER_LETTER_CHAR = static_cast<T>('A');

	template <REX::win32_character T>
	inline constexpr auto MAX_HEXADECIMAL_UPPER_LETTER_CHAR = static_cast<T>('F');

	template <REX::win32_character T>
	inline constexpr auto MIN_CONTROL_CHAR = static_cast<T>(0);

	template <REX::win32_character T>
	inline constexpr auto MAX_CONTROL_CHAR = static_cast<T>(31);

	template <REX::win32_character T>
	inline constexpr auto MIN_GRAPHIC_CHAR = static_cast<T>(33);

	template <REX::win32_character T>
	inline constexpr auto MAX_GRAPHIC_CHAR = static_cast<T>(126);

	template <REX::win32_character T>
	inline constexpr auto MIN_PRINTABLE_CHAR = static_cast<T>(32);

	template <REX::win32_character T>
	inline constexpr auto MAX_PRINTABLE_CHAR = static_cast<T>(126);

	[[nodiscard]] auto CreateCLocale(std::string_view a_localeName, std::int32_t a_localeCategory = LC_ALL) noexcept -> CLocale;
	[[nodiscard]] auto CreateCppLocale(std::string_view a_localeName, std::locale::category a_localeCategory = std::locale::all) noexcept -> std::expected<CppLocale, std::runtime_error>;

	[[nodiscard]] const CLocale& GetDefaultCLocale() noexcept;
	[[nodiscard]] const CppLocale& GetDefaultCppLocale() noexcept;

	[[nodiscard]] constexpr bool IsAscii(char a_value) noexcept
	{
		return a_value >= MIN_ASCII_CHAR<char> && a_value <= MAX_ASCII_CHAR<char>;
	}

	[[nodiscard]] constexpr bool IsAscii(wchar_t a_value) noexcept
	{
		return a_value >= MIN_ASCII_CHAR<wchar_t> && a_value <= MAX_ASCII_CHAR<wchar_t>;
	}

	[[nodiscard]] constexpr bool IsWhiteSpace(char a_value) noexcept
	{
		switch (a_value) {
			case ' ':
			case '\t':
			case '\n':
			case '\v':
			case '\f':
			case '\r': {
				return true;
			}
			default: {
				return false;
			}
		}
	}

	[[nodiscard]] inline bool IsWhiteSpace(wchar_t a_value) noexcept
	{
		return std::isspace(a_value, GetDefaultCppLocale());
	}

	[[nodiscard]] constexpr bool IsBlank(char a_value) noexcept
	{
		switch (a_value) {
			case ' ':
			case '\t': {
				return true;
			}
			default: {
				return false;
			}
		}
	}

	[[nodiscard]] inline bool IsBlank(wchar_t a_value) noexcept
	{
		return std::isblank(a_value, GetDefaultCppLocale());
	}

	[[nodiscard]] constexpr bool IsDigit(char a_value) noexcept
	{
		return a_value >= MIN_DIGIT_CHAR<char> && a_value <= MAX_DIGIT_CHAR<char>;
	}

	[[nodiscard]] inline bool IsDigit(wchar_t a_value) noexcept
	{
		return std::isdigit(a_value, GetDefaultCppLocale());
	}

	[[nodiscard]] constexpr bool IsLetter(char a_value) noexcept
	{
		return (a_value >= MIN_LOWER_LETTER_CHAR<char> && a_value <= MAX_LOWER_LETTER_CHAR<char>) ||
			   (a_value >= MIN_UPPER_LETTER_CHAR<char> && a_value <= MAX_UPPER_LETTER_CHAR<char>);
	}

	[[nodiscard]] inline bool IsLetter(wchar_t a_value) noexcept
	{
		return std::isalpha(a_value, GetDefaultCppLocale());
	}

	[[nodiscard]] constexpr bool IsLetterOrDigit(char a_value) noexcept
	{
		return IsLetter(a_value) || IsDigit(a_value);
	}

	[[nodiscard]] inline bool IsLetterOrDigit(wchar_t a_value) noexcept
	{
		return std::isalnum(a_value, GetDefaultCppLocale());
	}

	[[nodiscard]] constexpr bool IsHexadecimal(char a_value) noexcept
	{
		return (a_value >= MIN_DIGIT_CHAR<char> && a_value <= MAX_DIGIT_CHAR<char>) ||
			   (a_value >= MIN_HEXADECIMAL_LOWER_LETTER_CHAR<char> && a_value <= MAX_HEXADECIMAL_LOWER_LETTER_CHAR<char>) ||
			   (a_value >= MIN_HEXADECIMAL_UPPER_LETTER_CHAR<char> && a_value <= MAX_HEXADECIMAL_UPPER_LETTER_CHAR<char>);
	}

	[[nodiscard]] inline bool IsHexadecimal(wchar_t a_value) noexcept
	{
		return std::isxdigit(a_value, GetDefaultCppLocale());
	}

	[[nodiscard]] constexpr bool IsPunctuation(char a_value) noexcept
	{
		return (a_value >= '!' && a_value <= '/') ||
			   (a_value >= ':' && a_value <= '@') ||
			   (a_value >= '[' && a_value <= '`') ||
			   (a_value >= '{' && a_value <= '~');
	}

	[[nodiscard]] inline bool IsPunctuation(wchar_t a_value) noexcept
	{
		return std::ispunct(a_value, GetDefaultCppLocale());
	}

	[[nodiscard]] constexpr bool IsControl(char a_value) noexcept
	{
		return (a_value >= MIN_CONTROL_CHAR<char> && a_value <= MAX_CONTROL_CHAR<char>) ||
			   (a_value == '\x7F');
	}

	[[nodiscard]] inline bool IsControl(wchar_t a_value) noexcept
	{
		return std::iscntrl(a_value, GetDefaultCppLocale());
	}

	[[nodiscard]] constexpr bool IsGraphic(char a_value) noexcept
	{
		return a_value >= MIN_GRAPHIC_CHAR<char> && a_value <= MAX_GRAPHIC_CHAR<char>;
	}

	[[nodiscard]] inline bool IsGraphic(wchar_t a_value) noexcept
	{
		return std::isgraph(a_value, GetDefaultCppLocale());
	}

	[[nodiscard]] constexpr bool IsPrintable(char a_value) noexcept
	{
		return a_value >= MIN_PRINTABLE_CHAR<char> && a_value <= MAX_PRINTABLE_CHAR<char>;
	}

	[[nodiscard]] inline bool IsPrintable(wchar_t a_value) noexcept
	{
		return std::isprint(a_value, GetDefaultCppLocale());
	}

	[[nodiscard]] constexpr bool IsLower(char a_value) noexcept
	{
		return a_value >= MIN_LOWER_LETTER_CHAR<char> && a_value <= MAX_LOWER_LETTER_CHAR<char>;
	}

	[[nodiscard]] inline bool IsLower(wchar_t a_value) noexcept
	{
		return std::islower(a_value, GetDefaultCppLocale());
	}

	[[nodiscard]] constexpr bool IsUpper(char a_value) noexcept
	{
		return a_value >= MIN_UPPER_LETTER_CHAR<char> && a_value <= MAX_UPPER_LETTER_CHAR<char>;
	}

	[[nodiscard]] inline bool IsUpper(wchar_t a_value) noexcept
	{
		return std::isupper(a_value, GetDefaultCppLocale());
	}

	[[nodiscard]] constexpr char ToLower(char a_value) noexcept
	{
		if (a_value >= MIN_UPPER_LETTER_CHAR<char> && a_value <= MAX_UPPER_LETTER_CHAR<char>) {
			return static_cast<char>(a_value - MIN_UPPER_LETTER_CHAR<char> + MIN_LOWER_LETTER_CHAR<char>);
		}

		return a_value;
	}

	[[nodiscard]] inline wchar_t ToLower(wchar_t a_value) noexcept
	{
		return std::tolower(a_value, GetDefaultCppLocale());
	}

	[[nodiscard]] constexpr char ToUpper(char a_value) noexcept
	{
		if (a_value >= MIN_LOWER_LETTER_CHAR<char> && a_value <= MAX_LOWER_LETTER_CHAR<char>) {
			return static_cast<char>(a_value - MIN_LOWER_LETTER_CHAR<char> + MIN_UPPER_LETTER_CHAR<char>);
		}

		return a_value;
	}

	[[nodiscard]] inline wchar_t ToUpper(wchar_t a_value) noexcept
	{
		return std::toupper(a_value, GetDefaultCppLocale());
	}

	[[nodiscard]] constexpr std::string ToLower(std::string_view a_value)
	{
		auto result = std::string();
		result.resize(a_value.size());

		std::ranges::transform(a_value, result.begin(), [](char a_char) {
			return ToLower(a_char);
		});

		return result;
	}

	[[nodiscard]] inline std::wstring ToLower(std::wstring_view a_value)
	{
		auto result = std::wstring();
		result.resize(a_value.size());

		std::ranges::transform(a_value, result.begin(), [](wchar_t a_char) {
			return ToLower(a_char);
		});

		return result;
	}

	[[nodiscard]] constexpr std::string ToUpper(std::string_view a_value)
	{
		auto result = std::string();
		result.resize(a_value.size());

		std::ranges::transform(a_value, result.begin(), [](char a_char) {
			return ToUpper(a_char);
		});

		return result;
	}

	[[nodiscard]] inline std::wstring ToUpper(std::wstring_view a_value)
	{
		auto result = std::wstring();
		result.resize(a_value.size());

		std::ranges::transform(a_value, result.begin(), [](wchar_t a_char) {
			return ToUpper(a_char);
		});

		return result;
	}
}
