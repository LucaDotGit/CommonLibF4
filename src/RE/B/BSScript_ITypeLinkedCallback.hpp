#pragma once

#include "RE/B/BSTSmartPointer.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE::BSScript
{
	class ObjectTypeInfo;

	class __declspec(novtable) ITypeLinkedCallback
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSScript__ITypeLinkedCallback;
		inline static constexpr const auto& VTABLE = VTABLE::BSScript__ITypeLinkedCallback;

		virtual ~ITypeLinkedCallback() = default; // 0x00

		// add
		virtual void TypeLinked(const BSTSmartPointer<ObjectTypeInfo>& a_typeInfo) = 0; // 0x01

		GAME_HEAP_REDEFINE_NEW(ITypeLinkedCallback);
	};

	static_assert(sizeof(ITypeLinkedCallback) == 0x08);
}
