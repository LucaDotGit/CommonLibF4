#pragma once

#include "RE/Bethesda/BSScript/IStackCallbackFunctor.hpp"
#include "RE/Bethesda/BSStorage.hpp"
#include "RE/Bethesda/BSTSmartPointer.hpp"

namespace RE::BSScript
{
	class IStackCallbackFunctor;

	class __declspec(novtable) IStackCallbackSaveInterface
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSScript__IStackCallbackSaveInterface };
		inline static constexpr auto VTABLE{ VTABLE::BSScript__IStackCallbackSaveInterface };

		virtual ~IStackCallbackSaveInterface(); // 00

		// add
		virtual bool SaveStackCallback(BSStorage& a_buffer, const BSTSmartPointer<IStackCallbackFunctor>& a_callback) const;		// 01
		virtual bool LoadStackCallback(const BSStorage& a_buffer, bool&, BSTSmartPointer<IStackCallbackFunctor>& a_callback) const; // 02
	};
	static_assert(sizeof(IStackCallbackSaveInterface) == 0x8);
}
