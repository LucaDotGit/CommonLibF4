#pragma once

#include "RE/Bethesda/BSFixedString.hpp"
#include "RE/Bethesda/BSTArray.hpp"
#include "RE/Bethesda/BSTSmartPointer.hpp"

namespace RE::BSScript
{
	class PropertyGroupInfo
		: public BSIntrusiveRefCounted // 00
	{
	public:
		// members
		BSFixedString groupName;			   // 08
		BSFixedString docString;			   // 10
		std::uint32_t userFlags;			   // 18
		BSTArray<BSFixedString> propertyNames; // 20
	};
	static_assert(sizeof(PropertyGroupInfo) == 0x38);
}
