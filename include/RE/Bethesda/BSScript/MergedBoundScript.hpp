#pragma once

#include "RE/Bethesda/BSContainer.hpp"
#include "RE/Bethesda/BSFixedString.hpp"
#include "RE/Bethesda/BSLock.hpp"
#include "RE/Bethesda/BSTArray.hpp"
#include "RE/Bethesda/BSTEvent.hpp"
#include "RE/Bethesda/BSTHashMap.hpp"
#include "RE/Bethesda/BSTObjectArena.hpp"
#include "RE/Bethesda/BSTSmartPointer.hpp"
#include "RE/Bethesda/BSTTuple.hpp"
#include "RE/Bethesda/MemoryManager.hpp"

namespace RE
{
	namespace BSScript
	{
		class BoundScript; // stub

		class MergedBoundScript
		{
		public:
			// members
			BSTSmartPointer<BoundScript> childScript;  // 00
			BSTSmartPointer<BoundScript> parentScript; // 08
		};
		static_assert(sizeof(MergedBoundScript) == 0x10);
	}
}
