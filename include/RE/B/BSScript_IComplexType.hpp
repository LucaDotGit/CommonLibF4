#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSScript_TypeInfo.hpp"

namespace RE::BSScript
{
	class ObjectTypeInfo;
	class StructTypeInfo;
	class TypeInfo;

	class __declspec(novtable) IComplexType
		: public BSIntrusiveRefCounted // 08
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSScript__IComplexType };
		inline static constexpr auto VTABLE{ VTABLE::BSScript__IComplexType };

		virtual ~IComplexType(); // 00

		// add
		virtual TypeInfo::RawType GetRawType() const = 0; // 01

		[[nodiscard]] bool IsObject() const { return GetRawType() == TypeInfo::RawType::kObject; }
		[[nodiscard]] bool IsStruct() const { return GetRawType() == TypeInfo::RawType::kStruct; }

		[[nodiscard]] bool Equals(const IComplexType& a_rhs) const noexcept;
		[[nodiscard]] bool IsAssignable(const IComplexType& a_rhs) const noexcept;

		[[nodiscard]] BSFixedString GetTypeName() const;

		[[nodiscard]] ObjectTypeInfo* AsObjectType();
		[[nodiscard]] const ObjectTypeInfo* AsObjectType() const;

		[[nodiscard]] StructTypeInfo* AsStructType();
		[[nodiscard]] const StructTypeInfo* AsStructType() const;
	};
	static_assert(sizeof(IComplexType) == 0x10);
}
