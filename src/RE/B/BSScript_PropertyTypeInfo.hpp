#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSScript_TypeInfo.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSScript
{
	enum class UserFlags : std::uint32_t;

	class IFunction;

	class PropertyTypeInfo
	{
	public:
		enum class Permissions : std::int32_t
		{
			Default = 0
		};

		// members
		BSFixedString parentObjName;					  // 0x00
		BSFixedString propertyName;						  // 0x08
		TypeInfo type;									  // 0x10
		REX::Enum<Permissions, std::int32_t> permissions; // 0x18
		BSTSmartPointer<IFunction> getFunction;			  // 0x20
		BSTSmartPointer<IFunction> setFunction;			  // 0x28
		std::uint32_t autoVarIndex; // 0x30 - equals to `std::numeric_limits<std::uint32_t>::max()` if there is no
									// backing variable
		REX::EnumSet<UserFlags, std::uint32_t> userFlags; // 0x34
		BSFixedString docString;						  // 0x38
	};

	static_assert(sizeof(PropertyTypeInfo) == 0x40);
}
