#pragma once

#include "REX/Compare.hpp"
#include "REX/Concepts.hpp"

namespace REX::Impl
{
	template <REX::win32_character CharT>
	inline constexpr auto EXACTLY_ONE = static_cast<CharT>('?');

	template <REX::win32_character CharT>
	inline constexpr auto ZERO_OR_MORE = static_cast<CharT>('*');

	template <REX::win32_character CharT, bool IgnoreCase>
	[[nodiscard]] __forceinline constexpr bool Equals(CharT a_leftChar, CharT a_rightChar) noexcept
	{
		if constexpr (IgnoreCase) {
			return REX::EqualsIgnoreCase(a_leftChar, a_rightChar);
		}
		else {
			return REX::Equals(a_leftChar, a_rightChar);
		}
	}

	extern template bool Equals<char, false>(char a_leftChar, char a_rightChar) noexcept;
	extern template bool Equals<wchar_t, false>(wchar_t a_leftChar, wchar_t a_rightChar) noexcept;
	extern template bool Equals<char, true>(char a_leftChar, char a_rightChar) noexcept;
	extern template bool Equals<wchar_t, true>(wchar_t a_leftChar, wchar_t a_rightChar) noexcept;

	template <REX::win32_character CharT, bool IgnoreCase>
	[[nodiscard]] __forceinline constexpr bool MatchWildcards(std::basic_string_view<CharT> a_text, std::basic_string_view<CharT> a_pattern) noexcept
	{
		if (a_pattern.empty()) {
			return a_text.empty();
		}

		auto textIt = a_text.begin();
		auto patternIt = a_pattern.begin();
		auto starIt = a_pattern.end();
		auto matchIt = a_text.begin();

		while (textIt != a_text.end()) {
			if (patternIt != a_pattern.end() && (*patternIt == EXACTLY_ONE<CharT> || Equals<CharT, IgnoreCase>(*patternIt, *textIt))) {
				textIt++;
				patternIt++;
				continue;
			}

			if (patternIt != a_pattern.end() && *patternIt == ZERO_OR_MORE<CharT>) {
				starIt = patternIt++;
				matchIt = textIt;
				continue;
			}

			if (starIt != a_pattern.end()) {
				patternIt = starIt + 1;
				textIt = ++matchIt;
				continue;
			}

			return false;
		}

		while (patternIt != a_pattern.end() && *patternIt == ZERO_OR_MORE<CharT>) {
			patternIt++;
		}

		return patternIt == a_pattern.end();
	}

	extern template bool MatchWildcards<char, false>(std::string_view a_text, std::string_view a_pattern) noexcept;
	extern template bool MatchWildcards<wchar_t, false>(std::wstring_view a_text, std::wstring_view a_pattern) noexcept;
	extern template bool MatchWildcards<char, true>(std::string_view a_text, std::string_view a_pattern) noexcept;
	extern template bool MatchWildcards<wchar_t, true>(std::wstring_view a_text, std::wstring_view a_pattern) noexcept;
}

namespace REX
{
	template <REX::win32_character CharT>
	[[nodiscard]] constexpr bool MatchWildcards(std::basic_string_view<CharT> a_text, std::basic_string_view<CharT> a_pattern) noexcept
	{
		return Impl::MatchWildcards<CharT, false>(a_text, a_pattern);
	}

	extern template bool MatchWildcards(std::string_view a_text, std::string_view a_pattern) noexcept;
	extern template bool MatchWildcards(std::wstring_view a_text, std::wstring_view a_pattern) noexcept;

	template <REX::win32_character CharT>
	[[nodiscard]] constexpr bool MatchWildcardsIgnoreCase(std::basic_string_view<CharT> a_text, std::basic_string_view<CharT> a_pattern) noexcept
	{
		return Impl::MatchWildcards<CharT, true>(a_text, a_pattern);
	}

	extern template bool MatchWildcardsIgnoreCase(std::string_view a_text, std::string_view a_pattern) noexcept;
	extern template bool MatchWildcardsIgnoreCase(std::wstring_view a_text, std::wstring_view a_pattern) noexcept;
}
