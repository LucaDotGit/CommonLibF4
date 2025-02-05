#pragma once

#include "RE/Bethesda/BSContainer.hpp"
#include "RE/Bethesda/BSFixedString.hpp"
#include "RE/Bethesda/BSLock.hpp"
#include "RE/Bethesda/BSScript/IVirtualMachine.hpp"
#include "RE/Bethesda/BSScript/StackFrame.hpp"
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
		class IVirtualMachine;
		class StackFrame;

		class ISavePatcherInterface
		{
		public:
			inline static constexpr auto RTTI{ RTTI::BSScript__ISavePatcherInterface };
			inline static constexpr auto VTABLE{ VTABLE::BSScript__ISavePatcherInterface };

			virtual ~ISavePatcherInterface() = default; // 00

			// add
			virtual void PatchStackFrame(StackFrame&, IVirtualMachine&) = 0; // 01
		};
		static_assert(sizeof(ISavePatcherInterface) == 0x8);
	}
}
