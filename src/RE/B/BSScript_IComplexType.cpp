#include "RE/B/BSScript_IComplexType.hpp"

#include "RE/B/BSScript_ObjectTypeInfo.hpp"
#include "RE/B/BSScript_StructTypeInfo.hpp"

namespace RE::BSScript
{
	BSFixedString IComplexType::GetTypeName() const
	{
		const auto* objectType = AsObjectType();
		if (objectType) {
			return objectType->GetName();
		}

		const auto* structType = AsStructType();
		if (structType) {
			return structType->GetName();
		}

		return {};
	}

	bool IComplexType::Equals(const IComplexType& a_rhs) const noexcept
	{
		return this == std::addressof(a_rhs);
	}

	bool IComplexType::IsAssignable(const IComplexType& a_rhs) const noexcept
	{
		if (this == std::addressof(a_rhs)) {
			return true;
		}

		const auto* leftObjectType = AsObjectType();
		const auto* rightObjectType = a_rhs.AsObjectType();

		if (!leftObjectType || !rightObjectType) {
			return false;
		}

		return leftObjectType->IsChildOf(rightObjectType);
	}

	ObjectTypeInfo* IComplexType::AsObjectType()
	{
		return IsObject() ? DynamicCast<ObjectTypeInfo*>(this) : nullptr;
	}

	const ObjectTypeInfo* IComplexType::AsObjectType() const
	{
		return IsObject() ? DynamicCast<const ObjectTypeInfo*>(this) : nullptr;
	}

	StructTypeInfo* IComplexType::AsStructType()
	{
		return IsStruct() ? DynamicCast<StructTypeInfo*>(this) : nullptr;
	}

	const StructTypeInfo* IComplexType::AsStructType() const
	{
		return IsStruct() ? DynamicCast<const StructTypeInfo*>(this) : nullptr;
	}
}
