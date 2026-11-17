#include "REX/Wildcards.hpp"

namespace REX
{
	auto MatchWildcards(const std::filesystem::path& a_path, const std::filesystem::path& a_pattern) noexcept -> bool
	{
#if (_WIN32 != 0)
		return MatchWildcardsIgnoreCase(
			std::basic_string_view(a_path.native()),
			std::basic_string_view(a_pattern.native()));
#else
		return MatchWildcards(std::basic_string_view(a_path.native()), std::basic_string_view(a_pattern.native()));
#endif
	}
}
