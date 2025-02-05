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
		class __declspec(novtable) IClientVM
		{
		public:
			inline static constexpr auto RTTI{ RTTI::BSScript__IClientVM };
			inline static constexpr auto VTABLE{ VTABLE::BSScript__IClientVM };

			virtual ~IClientVM(); // 00

			// add
			virtual bool IsVMFrozen() const; // 01
			virtual void PreSave();			 // 02
		};
		static_assert(sizeof(IClientVM) == 0x8);
	}
}
