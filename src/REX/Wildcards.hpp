#pragma once

#include "REX/Comparison.hpp"
#include "REX/Concepts.hpp"
#include "REX/Macros.hpp"

namespace REX::Impl
{
	template <REX::character CharT>
	inline constexpr auto EXACTLY_ONE = static_cast<CharT>('?');

	template <REX::character CharT>
	inline constexpr auto ZERO_OR_MORE = static_cast<CharT>('*');

	template <REX::character CharT, bool IgnoreCase>
	[[nodiscard]] [[REX_ALWAYS_INLINE]]
	constexpr auto Equals(CharT a_leftChar, CharT a_rightChar) noexcept -> bool
	{
		if constexpr (IgnoreCase) {
			static_assert(REX::win32_character<CharT>);
			return REX::EqualsIgnoreCase(a_leftChar, a_rightChar);
		}
		else {
			return REX::Equals(a_leftChar, a_rightChar);
		}
	}

	template <REX::character CharT, bool IgnoreCase>
	[[nodiscard]] [[REX_ALWAYS_INLINE]]
	constexpr auto MatchWildcards(std::basic_string_view<CharT> a_text, std::basic_string_view<CharT> a_pattern)
		noexcept -> bool
	{
		if (a_pattern.empty()) {
			return a_text.empty();
		}

		auto textIt = a_text.begin();
		auto patternIt = a_pattern.begin();
		auto starIt = a_pattern.end();
		auto matchIt = a_text.begin();

		while (textIt != a_text.end()) {
			if (patternIt != a_pattern.end() &&
				(*patternIt == EXACTLY_ONE<CharT> || Equals<CharT, IgnoreCase>(*patternIt, *textIt))) {
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
}

namespace REX
{
	template <REX::character CharT>
	[[nodiscard]]
	constexpr auto MatchWildcards(std::basic_string_view<CharT> a_text, std::basic_string_view<CharT> a_pattern)
		noexcept -> bool
	{
		return Impl::MatchWildcards<CharT, false>(a_text, a_pattern);
	}

	static_assert(MatchWildcards("MyFile.txt"sv, "*.txt"sv));
	static_assert(MatchWildcards("MyFile.txt"sv, "MyFile.*"sv));
	static_assert(MatchWildcards("MyFile.txt"sv, "MyFile.txt"sv));
	static_assert(MatchWildcards("MyFile.txt"sv, "MyFile.tx?"sv));

	template <REX::win32_character CharT>
	[[nodiscard]]
	constexpr auto MatchWildcardsIgnoreCase(
		std::basic_string_view<CharT> a_text,
		std::basic_string_view<CharT> a_pattern) noexcept -> bool
	{
		return Impl::MatchWildcards<CharT, true>(a_text, a_pattern);
	}

	[[nodiscard]]
	auto MatchWildcards(const std::filesystem::path& a_path, const std::filesystem::path& a_pattern) noexcept -> bool;
}
