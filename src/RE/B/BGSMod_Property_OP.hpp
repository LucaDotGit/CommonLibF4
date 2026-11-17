#pragma once

namespace RE::BGSMod::Property
{
	enum class OP : std::int32_t
	{
		Set = 0,
		Mul = 1,
		And = 1,
		Rem = 1,
		Add = 2,
		Or = 2
	};
}
