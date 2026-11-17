#pragma once

#include "REX/Concepts.hpp"
#include "REX/ZString.hpp"

namespace REX
{
	template <REX::character CharT>
	inline constexpr auto MIN_ASCII_CHAR = static_cast<CharT>(0);

	template <REX::character CharT>
	inline constexpr auto MAX_ASCII_CHAR = static_cast<CharT>(std::numeric_limits<std::int8_t>::max());

	template <REX::character CharT>
	inline constexpr auto MIN_DIGIT_CHAR = static_cast<CharT>('0');

	template <REX::character CharT>
	inline constexpr auto MAX_DIGIT_CHAR = static_cast<CharT>('9');

	template <REX::character CharT>
	inline constexpr auto MIN_LOWER_LETTER_CHAR = static_cast<CharT>('a');

	template <REX::character CharT>
	inline constexpr auto MAX_LOWER_LETTER_CHAR = static_cast<CharT>('z');

	template <REX::character CharT>
	inline constexpr auto MIN_UPPER_LETTER_CHAR = static_cast<CharT>('A');

	template <REX::character CharT>
	inline constexpr auto MAX_UPPER_LETTER_CHAR = static_cast<CharT>('Z');

	template <REX::character CharT>
	inline constexpr auto MIN_LOWER_HEXADECIMAL_LETTER_CHAR = static_cast<CharT>('a');

	template <REX::character CharT>
	inline constexpr auto MAX_LOWER_HEXADECIMAL_LETTER_CHAR = static_cast<CharT>('f');

	template <REX::character CharT>
	inline constexpr auto MIN_UPPER_HEXADECIMAL_LETTER_CHAR = static_cast<CharT>('A');

	template <REX::character CharT>
	inline constexpr auto MAX_UPPER_HEXADECIMAL_LETTER_CHAR = static_cast<CharT>('F');

	template <REX::character CharT>
	inline constexpr auto MIN_CONTROL_CHAR = static_cast<CharT>(0);

	template <REX::character CharT>
	inline constexpr auto MAX_CONTROL_CHAR = static_cast<CharT>(31);

	template <REX::character CharT>
	inline constexpr auto MIN_GRAPHIC_CHAR = static_cast<CharT>(33);

	template <REX::character CharT>
	inline constexpr auto MAX_GRAPHIC_CHAR = static_cast<CharT>(126);

	template <REX::character CharT>
	inline constexpr auto MIN_PRINTABLE_CHAR = static_cast<CharT>(32);

	template <REX::character CharT>
	inline constexpr auto MAX_PRINTABLE_CHAR = static_cast<CharT>(126);

	template <REX::character CharT>
	inline constexpr auto EMPTY_CHAR = static_cast<CharT>('\0');

	template <REX::character CharT>
	inline constexpr auto SPACE_CHAR = static_cast<CharT>(' ');

	template <REX::character CharT>
	inline constexpr auto TAB_CHAR = static_cast<CharT>('\t');

	template <REX::character CharT>
	inline constexpr auto NEWLINE_CHAR = static_cast<CharT>('\n');

	template <REX::character CharT>
	inline constexpr auto CARRIAGE_RETURN_CHAR = static_cast<CharT>('\r');

	inline constexpr auto UTF8_BOM =
		std::array{static_cast<std::uint8_t>(0xEF), static_cast<std::uint8_t>(0xBB), static_cast<std::uint8_t>(0xBF)};

	inline constexpr auto UTF16_BOM = std::array{static_cast<std::uint8_t>(0xFF), static_cast<std::uint8_t>(0xFE)};

	inline constexpr auto UTF32_BOM = std::array{
		static_cast<std::uint8_t>(0xFF),
		static_cast<std::uint8_t>(0xFE),
		static_cast<std::uint8_t>(0x00),
		static_cast<std::uint8_t>(0x00)
	};

	inline constexpr auto DEFAULT_LOCALE_NAMES = std::array{".UTF-8"sv, "en_US.UTF-8"sv, "C.UTF-8"sv, "POSIX.UTF-8"sv};

	template <REX::character CharT>
	inline constexpr auto ALPHANUMERIC_CHARACTERS = []() consteval noexcept -> auto {
		constexpr auto LOWER_LETTER_CHAR_COUNT =
			REX::MAX_LOWER_LETTER_CHAR<CharT> - REX::MIN_LOWER_LETTER_CHAR<CharT> + 1;
		constexpr auto UPPER_LETTER_CHAR_COUNT =
			REX::MAX_UPPER_LETTER_CHAR<CharT> - REX::MIN_UPPER_LETTER_CHAR<CharT> + 1;
		constexpr auto DIGIT_CHAR_COUNT = REX::MAX_DIGIT_CHAR<CharT> - REX::MIN_DIGIT_CHAR<CharT> + 1;

		constexpr auto CHAR_SIZE = LOWER_LETTER_CHAR_COUNT + UPPER_LETTER_CHAR_COUNT + DIGIT_CHAR_COUNT;

		auto result = std::array<CharT, CHAR_SIZE>();

		for (auto i = static_cast<std::size_t>(0); i < LOWER_LETTER_CHAR_COUNT; i++) {
			result[i] = static_cast<CharT>(REX::MIN_LOWER_LETTER_CHAR<CharT> + i);
		}

		for (auto i = static_cast<std::size_t>(0); i < UPPER_LETTER_CHAR_COUNT; i++) {
			result[i + LOWER_LETTER_CHAR_COUNT] = static_cast<CharT>(REX::MIN_UPPER_LETTER_CHAR<CharT> + i);
		}

		for (auto i = static_cast<std::size_t>(0); i < DIGIT_CHAR_COUNT; i++) {
			result[i + LOWER_LETTER_CHAR_COUNT + UPPER_LETTER_CHAR_COUNT] =
				static_cast<CharT>(REX::MIN_DIGIT_CHAR<CharT> + i);
		}

		return result;
	}();

	template <REX::character CharT>
	inline constexpr auto HEXADECIMAL_CHARACTERS = []() consteval noexcept -> auto {
		constexpr auto LOWER_HEXADECIMAL_LETTER_CHAR_COUNT =
			REX::MAX_LOWER_HEXADECIMAL_LETTER_CHAR<CharT> - REX::MIN_LOWER_HEXADECIMAL_LETTER_CHAR<CharT> + 1;
		constexpr auto UPPER_HEXADECIMAL_LETTER_CHAR_COUNT =
			REX::MAX_UPPER_HEXADECIMAL_LETTER_CHAR<CharT> - REX::MIN_UPPER_HEXADECIMAL_LETTER_CHAR<CharT> + 1;
		constexpr auto DIGIT_CHAR_COUNT = REX::MAX_DIGIT_CHAR<CharT> - REX::MIN_DIGIT_CHAR<CharT> + 1;

		constexpr auto CHAR_SIZE =
			LOWER_HEXADECIMAL_LETTER_CHAR_COUNT + UPPER_HEXADECIMAL_LETTER_CHAR_COUNT + DIGIT_CHAR_COUNT;

		auto result = std::array<CharT, CHAR_SIZE>();

		for (auto i = static_cast<std::size_t>(0); i < LOWER_HEXADECIMAL_LETTER_CHAR_COUNT; i++) {
			result[i] = static_cast<CharT>(REX::MIN_LOWER_HEXADECIMAL_LETTER_CHAR<CharT> + i);
		}

		for (auto i = static_cast<std::size_t>(0); i < UPPER_HEXADECIMAL_LETTER_CHAR_COUNT; i++) {
			result[i + LOWER_HEXADECIMAL_LETTER_CHAR_COUNT] =
				static_cast<CharT>(REX::MIN_UPPER_HEXADECIMAL_LETTER_CHAR<CharT> + i);
		}

		for (auto i = static_cast<std::size_t>(0); i < DIGIT_CHAR_COUNT; i++) {
			result[i + LOWER_HEXADECIMAL_LETTER_CHAR_COUNT + UPPER_HEXADECIMAL_LETTER_CHAR_COUNT] =
				static_cast<CharT>(REX::MIN_DIGIT_CHAR<CharT> + i);
		}

		return result;
	}();

	[[nodiscard]]
	auto CreateLocale(REX::ZStringView a_localeName, std::locale::category a_localeCategory = std::locale::all) noexcept
		-> std::expected<std::locale, std::exception>;

	[[nodiscard]]
	auto CreateLocaleForLanguage(std::string_view a_language, std::locale::category a_localeCategory = std::locale::all)
		noexcept -> std::expected<std::locale, std::exception>;

	[[nodiscard]]
	auto GetOrCreateDefaultLocale() noexcept -> std::locale;

	[[nodiscard]]
	auto GetLocaleForLanguageOrDefault(
		std::string_view a_language,
		std::locale::category a_localeCategory = std::locale::all) noexcept -> std::locale;

#if (__clang__ == 1)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-type-limit-compare"
#pragma clang diagnostic ignored "-Wtautological-unsigned-zero-compare"
#endif

	[[nodiscard]]
	constexpr auto IsAscii(char a_value) noexcept -> bool
	{
		return a_value >= MIN_ASCII_CHAR<char> && a_value <= MAX_ASCII_CHAR<char>;
	}

	[[nodiscard]]
	constexpr auto IsAscii(wchar_t a_value) noexcept -> bool
	{
		return a_value >= MIN_ASCII_CHAR<wchar_t> && a_value <= MAX_ASCII_CHAR<wchar_t>;
	}

#if (__clang__ == 1)
#pragma clang diagnostic pop
#endif

	[[nodiscard]]
	constexpr auto IsWhiteSpace(char a_value) noexcept -> bool
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

	[[nodiscard]]
	inline auto IsWhiteSpace(wchar_t a_value) noexcept -> bool
	{
		return std::isspace(a_value, GetOrCreateDefaultLocale());
	}

	[[nodiscard]]
	constexpr auto IsBlank(char a_value) noexcept -> bool
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

	[[nodiscard]]
	inline auto IsBlank(wchar_t a_value) noexcept -> bool
	{
		return std::isblank(a_value, GetOrCreateDefaultLocale());
	}

	[[nodiscard]]
	constexpr auto IsDigit(char a_value) noexcept -> bool
	{
		return a_value >= MIN_DIGIT_CHAR<char> && a_value <= MAX_DIGIT_CHAR<char>;
	}

	[[nodiscard]]
	inline auto IsDigit(wchar_t a_value) noexcept -> bool
	{
		return std::isdigit(a_value, GetOrCreateDefaultLocale());
	}

	[[nodiscard]]
	constexpr auto IsLetter(char a_value) noexcept -> bool
	{
		return (a_value >= MIN_LOWER_LETTER_CHAR<char> && a_value <= MAX_LOWER_LETTER_CHAR<char>) ||
			   (a_value >= MIN_UPPER_LETTER_CHAR<char> && a_value <= MAX_UPPER_LETTER_CHAR<char>);
	}

	[[nodiscard]]
	inline auto IsLetter(wchar_t a_value) noexcept -> bool
	{
		return std::isalpha(a_value, GetOrCreateDefaultLocale());
	}

	[[nodiscard]]
	constexpr auto IsLetterOrDigit(char a_value) noexcept -> bool
	{
		return IsLetter(a_value) || IsDigit(a_value);
	}

	[[nodiscard]]
	inline auto IsLetterOrDigit(wchar_t a_value) noexcept -> bool
	{
		return std::isalnum(a_value, GetOrCreateDefaultLocale());
	}

	[[nodiscard]]
	constexpr auto IsHexadecimal(char a_value) noexcept -> bool
	{
		return (a_value >= MIN_DIGIT_CHAR<char> && a_value <= MAX_DIGIT_CHAR<char>) ||
			   (a_value >= MIN_LOWER_HEXADECIMAL_LETTER_CHAR<char> &&
				a_value <= MAX_LOWER_HEXADECIMAL_LETTER_CHAR<char>) ||
			   (a_value >= MIN_UPPER_HEXADECIMAL_LETTER_CHAR<char> &&
				a_value <= MAX_UPPER_HEXADECIMAL_LETTER_CHAR<char>);
	}

	[[nodiscard]]
	inline auto IsHexadecimal(wchar_t a_value) noexcept -> bool
	{
		return std::isxdigit(a_value, GetOrCreateDefaultLocale());
	}

	[[nodiscard]]
	constexpr auto IsPunctuation(char a_value) noexcept -> bool
	{
		return (a_value >= '!' && a_value <= '/') ||
			   (a_value >= ':' && a_value <= '@') ||
			   (a_value >= '[' && a_value <= '`') ||
			   (a_value >= '{' && a_value <= '~');
	}

	[[nodiscard]]
	inline auto IsPunctuation(wchar_t a_value) noexcept -> bool
	{
		return std::ispunct(a_value, GetOrCreateDefaultLocale());
	}

	[[nodiscard]]
	constexpr auto IsControl(char a_value) noexcept -> bool
	{
		return (a_value >= MIN_CONTROL_CHAR<char> && a_value <= MAX_CONTROL_CHAR<char>) || (a_value == '\x7F');
	}

	[[nodiscard]]
	inline auto IsControl(wchar_t a_value) noexcept -> bool
	{
		return std::iscntrl(a_value, GetOrCreateDefaultLocale());
	}

	[[nodiscard]]
	constexpr auto IsGraphic(char a_value) noexcept -> bool
	{
		return a_value >= MIN_GRAPHIC_CHAR<char> && a_value <= MAX_GRAPHIC_CHAR<char>;
	}

	[[nodiscard]]
	inline auto IsGraphic(wchar_t a_value) noexcept -> bool
	{
		return std::isgraph(a_value, GetOrCreateDefaultLocale());
	}

	[[nodiscard]]
	constexpr auto IsPrintable(char a_value) noexcept -> bool
	{
		return a_value >= MIN_PRINTABLE_CHAR<char> && a_value <= MAX_PRINTABLE_CHAR<char>;
	}

	[[nodiscard]]
	inline auto IsPrintable(wchar_t a_value) noexcept -> bool
	{
		return std::isprint(a_value, GetOrCreateDefaultLocale());
	}

	[[nodiscard]]
	constexpr auto IsLower(char a_value) noexcept -> bool
	{
		return a_value >= MIN_LOWER_LETTER_CHAR<char> && a_value <= MAX_LOWER_LETTER_CHAR<char>;
	}

	[[nodiscard]]
	inline auto IsLower(wchar_t a_value) noexcept -> bool
	{
		return std::islower(a_value, GetOrCreateDefaultLocale());
	}

	[[nodiscard]]
	constexpr auto IsUpper(char a_value) noexcept -> bool
	{
		return a_value >= MIN_UPPER_LETTER_CHAR<char> && a_value <= MAX_UPPER_LETTER_CHAR<char>;
	}

	[[nodiscard]]
	inline auto IsUpper(wchar_t a_value) noexcept -> bool
	{
		return std::isupper(a_value, GetOrCreateDefaultLocale());
	}

	[[nodiscard]]
	constexpr auto ToLower(char a_value) noexcept -> char
	{
		if (a_value >= MIN_UPPER_LETTER_CHAR<char> && a_value <= MAX_UPPER_LETTER_CHAR<char>) {
			return static_cast<char>(a_value - MIN_UPPER_LETTER_CHAR<char> + MIN_LOWER_LETTER_CHAR<char>);
		}

		return a_value;
	}

	[[nodiscard]]
	inline auto ToLower(wchar_t a_value) noexcept -> wchar_t
	{
		return std::tolower(a_value, GetOrCreateDefaultLocale());
	}

	[[nodiscard]]
	constexpr auto ToUpper(char a_value) noexcept -> char
	{
		if (a_value >= MIN_LOWER_LETTER_CHAR<char> && a_value <= MAX_LOWER_LETTER_CHAR<char>) {
			return static_cast<char>(a_value - MIN_LOWER_LETTER_CHAR<char> + MIN_UPPER_LETTER_CHAR<char>);
		}

		return a_value;
	}

	[[nodiscard]]
	inline auto ToUpper(wchar_t a_value) noexcept -> wchar_t
	{
		return std::toupper(a_value, GetOrCreateDefaultLocale());
	}

	template <REX::win32_character CharT>
	[[nodiscard]]
	constexpr auto ToLower(std::basic_string_view<CharT> a_value) -> std::basic_string<CharT>
	{
		auto result = std::basic_string<CharT>();
		result.reserve(a_value.size());

		std::ranges::transform(a_value, std::back_inserter(result), [](CharT a_char) noexcept -> CharT {
			return ToLower(a_char);
		});

		return result;
	}

	static_assert(ToLower("Hello, World!"sv) == "hello, world!"sv);

	template <REX::win32_character CharT>
	[[nodiscard]]
	constexpr auto ToUpper(std::basic_string_view<CharT> a_value) -> std::basic_string<CharT>
	{
		auto result = std::basic_string<CharT>();
		result.reserve(a_value.size());

		std::ranges::transform(a_value, std::back_inserter(result), [](CharT a_char) noexcept -> CharT {
			return ToUpper(a_char);
		});

		return result;
	}

	static_assert(ToUpper("Hello, World!"sv) == "HELLO, WORLD!"sv);

	template <REX::win32_character CharT>
	[[nodiscard]]
	constexpr auto Capitalize(std::basic_string_view<CharT> a_value, std::basic_string_view<CharT> a_delimiter)
		-> std::basic_string<CharT>
	{
		auto result = std::basic_string<CharT>();
		result.reserve(a_value.size());

		auto capitalizeNext = true;
		for (const auto character : a_value) {
			if (capitalizeNext) {
				result += ToUpper(character);
				capitalizeNext = false;
			}
			else {
				result += ToLower(character);
			}

			if (a_delimiter.find(character) != std::basic_string_view<CharT>::npos) {
				capitalizeNext = true;
			}
		}

		return result;
	}

	static_assert(Capitalize("hello, world!"sv, ", "sv) == "Hello, World!"sv);

	template <REX::character CharT>
	[[nodiscard]]
	constexpr auto ReplaceFirst(
		std::basic_string_view<CharT> a_value,
		std::basic_string_view<CharT> a_search,
		std::basic_string_view<CharT> a_replace) -> std::basic_string<CharT>
	{
		auto result = std::basic_string<CharT>();
		result.reserve(a_value.size());

		const auto position = a_value.find(a_search);
		if (position == std::basic_string_view<CharT>::npos) {
			return std::basic_string<CharT>(a_value);
		}

		result += a_value.substr(0, position);
		result += a_replace;
		result += a_value.substr(position + a_search.size());

		return result;
	}

	static_assert(ReplaceFirst("Hello, World!"sv, "World"sv, "Universe"sv) == "Hello, Universe!"sv);

	template <REX::character CharT>
	[[nodiscard]]
	constexpr auto ReplaceLast(
		std::basic_string_view<CharT> a_value,
		std::basic_string_view<CharT> a_search,
		std::basic_string_view<CharT> a_replace) -> std::basic_string<CharT>
	{
		auto result = std::basic_string<CharT>();
		result.reserve(a_value.size());

		const auto position = a_value.rfind(a_search);
		if (position == std::basic_string_view<CharT>::npos) {
			return std::basic_string<CharT>(a_value);
		}

		result += a_value.substr(0, position);
		result += a_replace;
		result += a_value.substr(position + a_search.size());

		return result;
	}

	static_assert(ReplaceLast("Hello, World!"sv, "o"sv, "a"sv) == "Hello, Warld!"sv);

	template <REX::character CharT>
	[[nodiscard]]
	constexpr auto ReplaceAll(
		std::basic_string_view<CharT> a_value,
		std::basic_string_view<CharT> a_search,
		std::basic_string_view<CharT> a_replace) -> std::basic_string<CharT>
	{
		auto result = std::basic_string<CharT>();
		result.reserve(a_value.size());

		auto position = a_value.find(a_search);
		if (position == std::basic_string_view<CharT>::npos) {
			return std::basic_string<CharT>(a_value);
		}

		auto lastPos = static_cast<std::size_t>(0);
		while ((position = a_value.find(a_search, lastPos)) != std::basic_string_view<CharT>::npos) {
			result += a_value.substr(lastPos, position - lastPos);
			result += a_replace;
			lastPos = position + a_search.size();
		}

		result += a_value.substr(lastPos);
		return result;
	}

	static_assert(ReplaceAll("Hello, World!"sv, "o"sv, "a"sv) == "Hella, Warld!"sv);

	template <REX::character CharT>
	[[nodiscard]]
	constexpr auto PadLeft(
		std::basic_string_view<CharT> a_value,
		std::size_t a_totalSize,
		std::basic_string_view<CharT> a_padString) -> std::basic_string<CharT>
	{
		if (a_padString.empty()) {
			return std::basic_string<CharT>(a_value);
		}

		const auto padSize = a_totalSize - a_value.size();
		if (padSize <= 0) {
			return std::basic_string<CharT>(a_value);
		}

		const auto padCount = padSize / a_padString.size();
		const auto padRemainder = padSize % a_padString.size();

		auto padding = std::basic_string<CharT>();
		padding.reserve(padSize);

		for (auto i = static_cast<std::size_t>(0); i < padCount; i++) {
			padding += a_padString;
		}

		padding += a_padString.substr(0, padRemainder);
		return padding + std::basic_string<CharT>(a_value);
	}

	static_assert(PadLeft("Hello"sv, 10, " "sv) == "     Hello"sv);

	template <REX::character CharT>
	[[nodiscard]]
	constexpr auto PadRight(
		std::basic_string_view<CharT> a_value,
		std::size_t a_totalSize,
		std::basic_string_view<CharT> a_padString) -> std::basic_string<CharT>
	{
		if (a_padString.empty()) {
			return std::basic_string<CharT>(a_value);
		}

		const auto padSize = a_totalSize - a_value.size();
		if (padSize <= 0) {
			return std::basic_string<CharT>(a_value);
		}

		const auto padCount = padSize / a_padString.size();
		const auto padRemainder = padSize % a_padString.size();

		auto padding = std::basic_string<CharT>();
		padding.reserve(padSize);

		for (auto i = static_cast<std::size_t>(0); i < padCount; i++) {
			padding += a_padString;
		}

		padding += a_padString.substr(0, padRemainder);
		return std::basic_string<CharT>(a_value) + padding;
	}

	static_assert(PadRight("Hello"sv, 10, " "sv) == "Hello     "sv);
}
