#pragma once

#include "RE/Bethesda/BSContainer.hpp"
#include "RE/Bethesda/BSFixedString.hpp"
#include "RE/Bethesda/BSLock.hpp"
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
		class Variable;

		class __declspec(novtable) alignas(0x08) IStackCallbackFunctor
			: public BSIntrusiveRefCounted
		{
		public:
			inline static constexpr auto RTTI{ RTTI::BSScript__IStackCallbackFunctor };
			inline static constexpr auto VTABLE{ VTABLE::BSScript__IStackCallbackFunctor };

			virtual ~IStackCallbackFunctor() = default; // 00

			// add
			virtual void CallQueued() = 0;					 // 01
			virtual void CallCanceled() = 0;				 // 02
			virtual void StartMultiDispatch() = 0;			 // 03
			virtual void EndMultiDispatch() = 0;			 // 04
			virtual void operator()(BSScript::Variable) = 0; // 05
			virtual bool CanSave() { return false; };		 // 06
		};
		static_assert(sizeof(IStackCallbackFunctor) == 0x10);
	}
}
