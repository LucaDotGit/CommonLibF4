#pragma once

#include "RE/C/CombatMathUtilities_Shape.hpp"

namespace RE::CombatMathUtilities
{
	template <class T>
	class ShapeT
		: public CombatMathUtilities::Shape
	{
	};
	static_assert(sizeof(ShapeT<std::any>) == 0x04);
}
