#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSScript
{
	class ObjectTypeInfo;
	class StructTypeInfo;
}

namespace RE::BSScript::Internal
{
	class WritableTypeTable
	{
	public:
		// members
		BSTScrapHashMap<BSFixedString, BSTSmartPointer<ObjectTypeInfo>>* objectTypeMap; // 0x00
		BSTScrapHashMap<BSFixedString, BSTSmartPointer<StructTypeInfo>>* structTypeMap; // 0x08
	};

	static_assert(sizeof(WritableTypeTable) == 0x10);
}
