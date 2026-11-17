#pragma once

#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE::BSScript
{
	class Variable;

	class __declspec(novtable) IStackCallbackFunctor : public BSIntrusiveRefCounted // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSScript__IStackCallbackFunctor;
		inline static constexpr const auto& VTABLE = VTABLE::BSScript__IStackCallbackFunctor;

		virtual ~IStackCallbackFunctor() = default; // 0x00

		// add
		virtual void CallQueued() = 0;								   // 0x01
		virtual void CallCanceled() = 0;							   // 0x02
		virtual void StartMultiDispatch() = 0;						   // 0x03
		virtual void EndMultiDispatch() = 0;						   // 0x04
		virtual void operator()(BSScript::Variable a_returnValue) = 0; // 0x05

		virtual auto CanSave() -> bool // 0x06
		{
			return false;
		}

		GAME_HEAP_REDEFINE_NEW(IStackCallbackFunctor);
	};

	static_assert(sizeof(IStackCallbackFunctor) == 0x10);
}
