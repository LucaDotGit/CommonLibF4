#pragma once

#include "RE/B/BSTSmartPointer.hpp"

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
		inline static constexpr auto RTTI{ RTTI::BSScript__IStackCallbackSaveInterface };
		inline static constexpr auto VTABLE{ VTABLE::BSScript__IStackCallbackSaveInterface };

		virtual ~IStackCallbackSaveInterface() = default; // 00

		// add
		virtual bool SaveStackCallback(BSStorage& a_buffer, const BSTSmartPointer<IStackCallbackFunctor>& a_callbackFunctor) const;				   // 01
		virtual bool LoadStackCallback(const BSStorage& a_buffer, bool& a_unk01, BSTSmartPointer<IStackCallbackFunctor>& a_callbackFunctor) const; // 02
	};
	static_assert(sizeof(IStackCallbackSaveInterface) == 0x08);
}
