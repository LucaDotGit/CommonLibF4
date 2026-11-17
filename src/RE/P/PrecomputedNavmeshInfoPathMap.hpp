#pragma once

#include "RE/B/BSPrecomputedNavmeshInfoPathMap.hpp"

namespace RE
{
	class PrecomputedNavmeshInfoPathMap : public BSPrecomputedNavmeshInfoPathMap // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::PrecomputedNavmeshInfoPathMap;
	};

	static_assert(sizeof(PrecomputedNavmeshInfoPathMap) == 0x48);
}
