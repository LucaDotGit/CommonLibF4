#pragma once

#include "REX/Concepts.hpp"

namespace REX
{
	template <REX::pointer T>
	using Owner = T;

	template <REX::pointer T>
	using Observer = T;
}
