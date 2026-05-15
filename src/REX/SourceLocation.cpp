#include "REX/SourceLocation.hpp"

namespace REX
{
	static_assert(GetCurrentFileName() == "SourceLocation.cpp"sv);
	static_assert(GetCurrentFileNameWithoutExtension() == "SourceLocation"sv);
	static_assert(GetCurrentFileExtension() == ".cpp"sv);
}
