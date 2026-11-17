#pragma once

#include "RE/B/BSTSmartPointer.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class BSStorage;
}

namespace RE::BSScript
{
	class IStackCallbackFunctor;

	class __declspec(novtable) IStackCallbackSaveInterface
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSScript__IStackCallbackSaveInterface;
		inline static constexpr const auto& VTABLE = VTABLE::BSScript__IStackCallbackSaveInterface;

		virtual ~IStackCallbackSaveInterface() = default; // 0x00

		// add
		virtual auto SaveStackCallback(
			BSStorage& a_buffer,
			const BSTSmartPointer<IStackCallbackFunctor>& a_callbackFunctor) const -> bool; // 0x01
		virtual auto LoadStackCallback(
			const BSStorage& a_buffer,
			bool& a_unk01,
			BSTSmartPointer<IStackCallbackFunctor>& a_callbackFunctor) const -> bool; // 0x02

		GAME_HEAP_REDEFINE_NEW(IStackCallbackSaveInterface);
	};

	static_assert(sizeof(IStackCallbackSaveInterface) == 0x08);
}
