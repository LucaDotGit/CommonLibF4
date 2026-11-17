#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/B/BSTSingleton.hpp"

namespace RE
{
	class BSNavmeshInfo;

	class BSPrecomputedNavmeshInfoPathMap : public BSTSingletonExplicit<BSPrecomputedNavmeshInfoPathMap> // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSPrecomputedNavmeshInfoPathMap;

		// members
		BSTArray<BSTArray<const BSNavmeshInfo*>*> allPaths;				// 0x00
		BSTHashMap<const BSNavmeshInfo*, std::uint32_t> infoToIndexMap; // 0x18
	};

	static_assert(sizeof(BSPrecomputedNavmeshInfoPathMap) == 0x48);
}
