#pragma once

#include "REL/ASM/Branch6.hpp"

namespace REL::ASM
{
	using Jump6 = Branch6<0x25>;
	static_assert(sizeof(Jump6) == 0x06);
}
