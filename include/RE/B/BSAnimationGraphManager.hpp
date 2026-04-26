#pragma once

#include "RE/B/BSAnimationGraphVariableCache.hpp"
#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/B/BSTTuple.hpp"

namespace RE
{
	class BSAnimationGraphChannel;
	class BShkbAnimationGraph;
	class BSAnimationGraphEvent;

	class BSAnimationGraphManager
		: public BSTEventSink<BSAnimationGraphEvent>, // 00
		  public BSIntrusiveRefCounted				  // 08
	{
	public:
		class DependentManagerSmartPtr
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
		BSTArray<BSTPair<BSFixedString, BSFixedString>> eventQueue;		  // 70
		BSAnimationGraphVariableCache variableCache;					  // 88
		mutable BSSpinLock updateLock;									  // C8
		mutable BSSpinLock dependentManagerLock;						  // D0
		std::uint32_t activeGraph;										  // D8
		std::uint32_t generateDepth;									  // DC
	};
	static_assert(sizeof(BSAnimationGraphManager) == 0xE0);
}
