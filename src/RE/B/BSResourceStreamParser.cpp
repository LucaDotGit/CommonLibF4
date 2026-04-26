#include "RE/B/BSResourceStreamParser.hpp"

namespace RE
{
	BSResourceStreamParser::BSResourceStreamParser(const char* a_file)
		: BSResourceNiBinaryStream(a_file)
	{
		REL::EmplaceVtable(this);
	}
}
