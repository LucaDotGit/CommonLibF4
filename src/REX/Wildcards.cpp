#include "REX/Wildcards.hpp"

namespace REX::Impl
{
	template bool Equals<char, false>(char, char) noexcept;
	template bool Equals<wchar_t, false>(wchar_t, wchar_t) noexcept;
	template bool Equals<char, true>(char, char) noexcept;
	template bool Equals<wchar_t, true>(wchar_t, wchar_t) noexcept;

	template bool MatchWildcards<char, false>(std::string_view, std::string_view) noexcept;
	template bool MatchWildcards<wchar_t, false>(std::wstring_view, std::wstring_view) noexcept;
	template bool MatchWildcards<char, true>(std::string_view, std::string_view) noexcept;
	template bool MatchWildcards<wchar_t, true>(std::wstring_view, std::wstring_view) noexcept;
}

namespace REX
{
	template bool MatchWildcards(std::string_view, std::string_view) noexcept;
	template bool MatchWildcards(std::wstring_view, std::wstring_view) noexcept;

	static_assert(MatchWildcards("Hello"sv, "H*o"sv));
	static_assert(MatchWildcards("Hello"sv, "H?llo"sv));

	static_assert(!MatchWildcards("Hello"sv, "H*o "sv));
	static_assert(!MatchWildcards("Hello"sv, "H?llo "sv));

	template bool MatchWildcardsIgnoreCase(std::string_view, std::string_view) noexcept;
	template bool MatchWildcardsIgnoreCase(std::wstring_view, std::wstring_view) noexcept;

	static_assert(MatchWildcardsIgnoreCase("Hello"sv, "h*O"sv));
	static_assert(MatchWildcardsIgnoreCase("Hello"sv, "H?LLo"sv));

	static_assert(!MatchWildcardsIgnoreCase("Hello"sv, "H*O "sv));
	static_assert(!MatchWildcardsIgnoreCase("Hello"sv, "H?LLO "sv));
}
