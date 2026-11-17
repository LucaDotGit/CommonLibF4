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
		class SaveTypeInfo : public BSIntrusiveRefCounted // 0x00
		{
		public:
			// members
			BSFixedString parentType;					  // 0x08
			BSScrapArray<std::uint32_t> variableIndicies; // 0x10
		};

		static_assert(sizeof(SaveTypeInfo) == 0x30);

		// members
		BSTScrapHashMap<BSFixedString, BSTSmartPointer<SaveTypeInfo>>* saveTypeInfo; // 0x00
	};

	static_assert(sizeof(ReadableTypeTable) == 0x08);
}
