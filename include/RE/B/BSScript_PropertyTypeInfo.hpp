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
			kDefault = 0
		};

		// members
		BSFixedString parentObjName;					  // 00
		BSFixedString propertyName;						  // 08
		TypeInfo type;									  // 10
		REX::Enum<Permissions, std::int32_t> permissions; // 18
		BSTSmartPointer<IFunction> getFunction;			  // 20
		BSTSmartPointer<IFunction> setFunction;			  // 28
		std::uint32_t autoVarIndex;						  // 30
		REX::EnumSet<UserFlags, std::uint32_t> userFlags; // 34
		BSFixedString docString;						  // 38
	};
	static_assert(sizeof(PropertyTypeInfo) == 0x40);
}
