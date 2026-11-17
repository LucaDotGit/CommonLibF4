#pragma once

#include "REL/ASM/Branch5.hpp"

namespace REL::ASM
{
	using Call5 = Branch5<0xE8>;
	static_assert(sizeof(Call5) == 0x05);
}
