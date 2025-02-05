#pragma once

#include "RE/Bethesda/BSContainer.hpp"
#include "RE/Bethesda/BSFixedString.hpp"
#include "RE/Bethesda/BSLock.hpp"
#include "RE/Bethesda/BSScript/IVirtualMachine.hpp"
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
		class IVirtualMachine;
		class Variable;

		template <typename T>
		class ArrayWrapper
		{
		public:
			ArrayWrapper() = delete;

			F4_HEAP_REDEFINE_NEW(ArrayWrapper<T>);

		private:
			// members
			Variable wrappedVar; // 00
		};
		static_assert(sizeof(ArrayWrapper<void*>) == 0x10);

		template <>
		class ArrayWrapper<BSScript::Variable>
		{
		public:
			ArrayWrapper() = delete;
			ArrayWrapper(BSScrapArray<Variable>& a_copy, IVirtualMachine& a_vm)
			{
				ReplaceArray(a_copy, a_vm);
			}

			F4_HEAP_REDEFINE_NEW(ArrayWrapper<BSScript::Variable>);

			void ReplaceArray(BSScrapArray<Variable>& a_copy, IVirtualMachine& a_vm)
			{
				using func_t = decltype(&ArrayWrapper::ReplaceArray);
				static REL::Relocation<func_t> func{ REL::ID(445184) };
				return func(this, a_copy, a_vm);
			}

		private:
			// members
			Variable wrappedVar; // 00
		};
		static_assert(sizeof(ArrayWrapper<Variable>) == 0x10);
	}
}
