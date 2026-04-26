#include "REX/Wildcards.hpp"

namespace REX
{
	template bool MatchWildcards(std::string_view a_text, std::string_view a_pattern) noexcept;
	template bool MatchWildcards(std::wstring_view a_text, std::wstring_view a_pattern) noexcept;

	static_assert(MatchWildcards("Hello"sv, "H*o"sv));
	static_assert(MatchWildcards("Hello"sv, "H?llo"sv));

	static_assert(!MatchWildcards("Hello"sv, "H*o "sv));
	static_assert(!MatchWildcards("Hello"sv, "H?llo "sv));

	template bool MatchWildcardsIgnoreCase(std::string_view a_text, std::string_view a_pattern) noexcept;
	template bool MatchWildcardsIgnoreCase(std::wstring_view a_text, std::wstring_view a_pattern) noexcept;

	static_assert(MatchWildcardsIgnoreCase("Hello"sv, "h*O"sv));
	static_assert(MatchWildcardsIgnoreCase("Hello"sv, "H?LLo"sv));

	static_assert(!MatchWildcardsIgnoreCase("Hello"sv, "H*O "sv));
	static_assert(!MatchWildcardsIgnoreCase("Hello"sv, "H?LLO "sv));
}
