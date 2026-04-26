#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSTArray.hpp"

namespace RE::BSScript
{
	enum class UserFlags : std::uint32_t;

	class PropertyGroupInfo
		: public BSIntrusiveRefCounted // 00
	{
	public:
		// members
		BSFixedString groupName;						  // 08
		BSFixedString docString;						  // 10
		REX::EnumSet<UserFlags, std::uint32_t> userFlags; // 18
		BSTArray<BSFixedString> propertyNames;			  // 20
	};
	static_assert(sizeof(PropertyGroupInfo) == 0x38);
}
