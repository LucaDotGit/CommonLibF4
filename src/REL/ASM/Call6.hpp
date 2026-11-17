#pragma once

#include "REL/ASM/Branch6.hpp"

namespace REL::ASM
{
	using Call6 = Branch6<0x15>;
	static_assert(sizeof(Call6) == 0x06);
}
