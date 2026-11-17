#include "RE/B/BSScript_IComplexType.hpp"

#include "RE/B/BSScript_ObjectTypeInfo.hpp"
#include "RE/B/BSScript_StructTypeInfo.hpp"

namespace RE::BSScript
{
	auto IComplexType::GetTypeName() const noexcept -> BSFixedString
	{
		const auto objectType = AsObjectType();
		if (objectType) {
			return objectType->GetName();
		}

		const auto structType = AsStructType();
		if (structType) {
			return structType->GetName();
		}

		return {};
	}

	auto IComplexType::Equals(const IComplexType& a_rhs) const noexcept -> bool
	{
		return this == std::addressof(a_rhs);
	}

	auto IComplexType::IsAssignable(const IComplexType& a_rhs) const noexcept -> bool
	{
		if (this == std::addressof(a_rhs)) {
			return true;
		}

		const auto leftObjectType = AsObjectType();
		const auto rightObjectType = a_rhs.AsObjectType();

		if (!leftObjectType || !rightObjectType) {
			return false;
		}

		return leftObjectType->IsChildOf(rightObjectType.get());
	}

	auto IComplexType::AsObjectType() noexcept -> BSTSmartPointer<ObjectTypeInfo>
	{
		return BSTSmartPointer(IsObject() ? DynamicCast<ObjectTypeInfo*>(this) : nullptr);
	}

	auto IComplexType::AsObjectType() const noexcept -> BSTSmartPointer<const ObjectTypeInfo>
	{
		return BSTSmartPointer(IsObject() ? DynamicCast<const ObjectTypeInfo*>(this) : nullptr);
	}

	auto IComplexType::AsStructType() noexcept -> BSTSmartPointer<StructTypeInfo>
	{
		return BSTSmartPointer(IsStruct() ? DynamicCast<StructTypeInfo*>(this) : nullptr);
	}

	auto IComplexType::AsStructType() const noexcept -> BSTSmartPointer<const StructTypeInfo>
	{
		return BSTSmartPointer(IsStruct() ? DynamicCast<const StructTypeInfo*>(this) : nullptr);
	}
}
