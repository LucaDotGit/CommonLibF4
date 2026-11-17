#pragma once

#include "REL/ASM/Branch5.hpp"

namespace REL::ASM
{
	using Jump5 = Branch5<0xE9>;
	static_assert(sizeof(Jump5) == 0x05);
}
