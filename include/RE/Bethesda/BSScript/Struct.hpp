#pragma once

#include "RE/Bethesda/BSContainer.hpp"
#include "RE/Bethesda/BSFixedString.hpp"
#include "RE/Bethesda/BSLock.hpp"
#include "RE/Bethesda/BSScript/StructTypeInfo.hpp"
#include "RE/Bethesda/BSScript/Variable.hpp"
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
		class StructTypeInfo;
		class Variable;

		class Struct
			: public BSIntrusiveRefCounted // 00
		{
		public:
			~Struct();

			F4_HEAP_REDEFINE_NEW(Struct);

			// members
			mutable BSSpinLock structLock;		  // 04
			BSTSmartPointer<StructTypeInfo> type; // 10
			bool constructed{ true };			  // 18
			bool valid{ false };				  // 19
			Variable variables[0];				  // 20
		};
		static_assert(sizeof(Struct) == 0x20);
	}
}
