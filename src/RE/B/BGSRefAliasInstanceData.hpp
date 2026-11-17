#pragma once

#include "RE/B/BSTArray.hpp"

namespace RE
{
	class BGSRefAliasInstanceData
	{
	public:
		// members
		TESQuest* quest;						  // 0x00
		BGSRefAlias* alias;						  // 0x08
		BSTArray<TESPackage*>* instancedPackages; // 0x10
	};

	static_assert(sizeof(BGSRefAliasInstanceData) == 0x18);
}
