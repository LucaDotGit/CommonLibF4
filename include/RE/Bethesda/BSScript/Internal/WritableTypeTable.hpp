#pragma once

#include "RE/Bethesda/BSFixedString.hpp"
#include "RE/Bethesda/BSTHashMap.hpp"
#include "RE/Bethesda/BSTSmartPointer.hpp"

namespace RE
{
	namespace BSScript
	{
		class ObjectTypeInfo;
		class StructTypeInfo;

		namespace Internal
		{
			class WritableTypeTable
			{
			public:
				// members
				BSTScrapHashMap<BSFixedString, BSTSmartPointer<ObjectTypeInfo>>* objectTypeMap; // 00
				BSTScrapHashMap<BSFixedString, BSTSmartPointer<StructTypeInfo>>* structTypeMap; // 08
			};
			static_assert(sizeof(WritableTypeTable) == 0x10);
		}
	}
}
