#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTHashMap.hpp"

namespace RE
{
	using BGSCellNumericIDArrayMap = RE::BSTHashMap<std::uint32_t, RE::BSTArray<std::uint32_t, RE::BSTArrayHeapAllocator>*>;
}
