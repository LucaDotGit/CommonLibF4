#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSScript::Internal
{
	class ReadableTypeTable
	{
	public:
		class SaveTypeInfo
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
