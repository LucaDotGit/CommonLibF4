#pragma once

#include "REX/StaticSortedSet.hpp"

namespace REX
{
	template <class Key, std::size_t N, class KeyCompare = std::less<Key>>
	using StaticSet = StaticSortedSet<Key, N, KeyCompare>;
}
