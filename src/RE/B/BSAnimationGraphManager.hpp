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

	class BSAnimationGraphManager :
		public BSTEventSink<BSAnimationGraphEvent>, // 0x00
		public BSIntrusiveRefCounted				// 0x08
	{
	public:
		class DependentManagerSmartPtr
		{
		public:
			// members
			std::uint64_t ptrAndFlagsStorage; // 0x00
		};

		static_assert(sizeof(DependentManagerSmartPtr) == 0x08);

		// members
		BSTArray<BSTSmartPointer<BSAnimationGraphChannel>> boundChannel;  // 0x10
		BSTArray<BSTSmartPointer<BSAnimationGraphChannel>> bumpedChannel; // 0x28
		BSTSmallArray<BSTSmartPointer<BShkbAnimationGraph>, 1> graph;	  // 0x40
		BSTArray<DependentManagerSmartPtr> subManagers;					  // 0x58
		BSTArray<BSTPair<BSFixedString, BSFixedString>> eventQueue;		  // 0x70
		BSAnimationGraphVariableCache variableCache;					  // 0x88
		mutable BSSpinLock updateLock;									  // 0xC8
		mutable BSSpinLock dependentManagerLock;						  // 0xD0
		std::uint32_t activeGraph;										  // 0xD8
		std::uint32_t generateDepth;									  // 0xDC
	};

	static_assert(sizeof(BSAnimationGraphManager) == 0xE0);
}
