#pragma once

#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSScript
{
	class ObjectTypeInfo;

	class __declspec(novtable) ITypeLinkedCallback
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSScript__ITypeLinkedCallback };
		inline static constexpr auto VTABLE{ VTABLE::BSScript__ITypeLinkedCallback };

		virtual ~ITypeLinkedCallback() = default; // 00

		// add
		virtual void TypeLinked(const BSTSmartPointer<ObjectTypeInfo>& a_typeInfo) = 0; // 01
	};
	static_assert(sizeof(ITypeLinkedCallback) == 0x08);
}
