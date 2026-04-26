#pragma once

#include "REX/StaticSortedMap.hpp"

namespace REX
{
	template <class Key, class T, std::size_t N, class KeyCompare = std::less<Key>>
	using StaticMap = StaticSortedMap<Key, T, N, KeyCompare>;
}
