#pragma once

#include "RE/Bethesda/BSFixedString.hpp"
#include "RE/Bethesda/BSTArray.hpp"
#include "RE/Bethesda/BSTHashMap.hpp"
#include "RE/Bethesda/BSTSmartPointer.hpp"

namespace RE::BSScript::Internal
{
	class ReadableTypeTable
	{
	public:
		struct SaveTypeInfo
			: public BSIntrusiveRefCounted // 00
		{
		public:
			// members
			BSFixedString parentType;					  // 08
			BSScrapArray<std::uint32_t> variableIndicies; // 10
		};
		static_assert(sizeof(SaveTypeInfo) == 0x30);

		// members
		BSTScrapHashMap<BSFixedString, BSTSmartPointer<SaveTypeInfo>>* saveTypeInfo; // 00
	};
	static_assert(sizeof(ReadableTypeTable) == 0x08);
}
