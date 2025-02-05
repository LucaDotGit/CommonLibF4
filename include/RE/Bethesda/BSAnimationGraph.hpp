#pragma once

#include "RE/Bethesda/BSFixedString.hpp"
#include "RE/Bethesda/BSLock.hpp"
#include "RE/Bethesda/BSTArray.hpp"
#include "RE/Bethesda/BSTSmartPointer.hpp"

namespace RE
{
	class AnimVariableCacheInfo;
	class BSAnimationGraphChannel;
	class BShkbAnimationGraph;
	class hkbVariableValue;

	struct BSAnimationGraphEvent
	{
	public:
		// members
		const std::uint64_t holderID; // 00
		const BSFixedString tag;	  // 08
		const BSFixedString payload;  // 10
	};
	static_assert(sizeof(BSAnimationGraphEvent) == 0x18);

	struct BSAnimationGraphVariableCache
	{
	public:
		// members
		BSTArray<AnimVariableCacheInfo> variableCache;		  // 00
		BSTArray<hkbVariableValue*> variableQuickLookup;	  // 18
		mutable BSSpinLock* lock;							  // 30
		BSTSmartPointer<BShkbAnimationGraph> graphToCacheFor; // 38
	};
	static_assert(sizeof(BSAnimationGraphVariableCache) == 0x40);

	class BSAnimationGraphManager
		: public BSTEventSink<BSAnimationGraphEvent>, // 00
		  public BSIntrusiveRefCounted				  // 08
	{
	public:
		struct DependentManagerSmartPtr
		{
		public:
			// members
			std::uint64_t ptrAndFlagsStorage; // 00
		};
		static_assert(sizeof(DependentManagerSmartPtr) == 0x08);

		// members
		BSTArray<BSTSmartPointer<BSAnimationGraphChannel>> boundChannel;  // 10
		BSTArray<BSTSmartPointer<BSAnimationGraphChannel>> bumpedChannel; // 28
		BSTSmallArray<BSTSmartPointer<BShkbAnimationGraph>, 1> graph;	  // 40
		BSTArray<DependentManagerSmartPtr> subManagers;					  // 58
		BSTArray<BSTTuple<BSFixedString, BSFixedString>> eventQueues;	  // 70
		BSAnimationGraphVariableCache variableCache;					  // 88
		mutable BSSpinLock updateLock;									  // C8
		mutable BSSpinLock dependentManagerLock;						  // D0
		std::uint32_t activeGraph;										  // D8
		std::uint32_t generateDepth;									  // DC
	};
	static_assert(sizeof(BSAnimationGraphManager) == 0xE0);
}
