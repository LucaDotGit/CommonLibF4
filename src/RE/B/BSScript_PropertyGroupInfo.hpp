#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSTArray.hpp"

namespace RE::BSScript
{
	enum class UserFlags : std::uint32_t;

	class PropertyGroupInfo : public BSIntrusiveRefCounted // 0x00
	{
	public:
		// members
		BSFixedString groupName;						  // 0x08
		BSFixedString docString;						  // 0x10
		REX::EnumSet<UserFlags, std::uint32_t> userFlags; // 0x18
		BSTArray<BSFixedString> propertyNames;			  // 0x20
	};

	static_assert(sizeof(PropertyGroupInfo) == 0x38);
}
