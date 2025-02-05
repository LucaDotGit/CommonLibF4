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
		class PropertyGroupInfo
			: public BSIntrusiveRefCounted // 00
		{
		public:
			// members
			BSFixedString groupName;			   // 08
			BSFixedString docString;			   // 10
			std::uint32_t userFlags;			   // 18
			BSTArray<BSFixedString> propertyNames; // 20
		};
		static_assert(sizeof(PropertyGroupInfo) == 0x38);
	}
}
