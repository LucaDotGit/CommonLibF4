#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE
{
	class AnimVariableCacheInfo;
	class BShkbAnimationGraph;
	class BSSpinLock;
	class hkbVariableValue;

	class BSAnimationGraphVariableCache
	{
	public:
		// members
		BSTArray<AnimVariableCacheInfo> variableCache;		  // 0x00
		BSTArray<hkbVariableValue*> variableQuickLookup;	  // 0x18
		mutable BSSpinLock* lock;							  // 0x30
		BSTSmartPointer<BShkbAnimationGraph> graphToCacheFor; // 0x38
	};

	static_assert(sizeof(BSAnimationGraphVariableCache) == 0x40);
}
