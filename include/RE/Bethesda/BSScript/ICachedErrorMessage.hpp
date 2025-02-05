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
		class __declspec(novtable) ICachedErrorMessage
		{
		public:
			inline static constexpr auto RTTI{ RTTI::BSScript__ICachedErrorMessage };
			inline static constexpr auto VTABLE{ VTABLE::BSScript__ICachedErrorMessage };

			virtual ~ICachedErrorMessage() = default; // 00

			// add
			virtual void GetErrorMsg(BSFixedString& a_message) const = 0; // 01
		};
		static_assert(sizeof(ICachedErrorMessage) == 0x8);
	}
}
