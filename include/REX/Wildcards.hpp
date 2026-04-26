#pragma once

#include "REX/Compare.hpp"
#include "REX/Concepts.hpp"

namespace REX::Impl
{
	template <REX::win32_character T>
	inline constexpr auto EXACTLY_ONE = static_cast<T>('?');

	template <REX::win32_character T>
	inline constexpr auto ZERO_OR_MORE = static_cast<T>('*');

	template <REX::win32_character T, bool IgnoreCase>
	[[nodiscard]] __forceinline constexpr auto Equals(T a_leftChar, T a_rightChar) noexcept
	{
		if constexpr (IgnoreCase) {
			return REX::EqualsIgnoreCase(a_leftChar, a_rightChar);
		}
		else {
			return REX::Equals(a_leftChar, a_rightChar);
		}
	}

	template <REX::win32_character T, bool IgnoreCase>
	[[nodiscard]] __forceinline constexpr bool MatchWildcards(std::basic_string_view<T> a_text, std::basic_string_view<T> a_pattern) noexcept
	{
		if (a_pattern.empty()) {
			return a_text.empty();
		}

		auto textIt = a_text.begin();
		auto patternIt = a_pattern.begin();
		auto starIt = a_pattern.end();
		auto matchIt = a_text.begin();

		while (textIt != a_text.end()) {
			if (patternIt != a_pattern.end() && (*patternIt == EXACTLY_ONE<T> || Equals<T, IgnoreCase>(*patternIt, *textIt))) {
				textIt++;
				patternIt++;
				continue;
			}

			if (patternIt != a_pattern.end() && *patternIt == ZERO_OR_MORE<T>) {
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

		while (patternIt != a_pattern.end() && *patternIt == ZERO_OR_MORE<T>) {
			patternIt++;
		}

		return patternIt == a_pattern.end();
	}
}

namespace REX
{
	template <REX::win32_character T>
	[[nodiscard]] constexpr bool MatchWildcards(std::basic_string_view<T> a_text, std::basic_string_view<T> a_pattern) noexcept
	{
		return Impl::MatchWildcards<T, false>(a_text, a_pattern);
	}

	extern template bool MatchWildcards(std::string_view a_text, std::string_view a_pattern) noexcept;
	extern template bool MatchWildcards(std::wstring_view a_text, std::wstring_view a_pattern) noexcept;

	template <REX::win32_character T>
	[[nodiscard]] constexpr bool MatchWildcardsIgnoreCase(std::basic_string_view<T> a_text, std::basic_string_view<T> a_pattern) noexcept
	{
		return Impl::MatchWildcards<T, true>(a_text, a_pattern);
	}

	extern template bool MatchWildcardsIgnoreCase(std::string_view a_text, std::string_view a_pattern) noexcept;
	extern template bool MatchWildcardsIgnoreCase(std::wstring_view a_text, std::wstring_view a_pattern) noexcept;
}
