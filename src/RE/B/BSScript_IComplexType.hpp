#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSScript_TypeInfo.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSScript
{
	class ObjectTypeInfo;
	class StructTypeInfo;
	class TypeInfo;

	class __declspec(novtable) IComplexType : public BSIntrusiveRefCounted // 0x08
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSScript__IComplexType;
		inline static constexpr const auto& VTABLE = VTABLE::BSScript__IComplexType;

		virtual ~IComplexType(); // 0x00

		// add
		virtual auto GetRawType() const -> TypeInfo::RawType = 0; // 0x01

		[[nodiscard]]
		auto IsObject() const -> bool
		{
			return GetRawType() == TypeInfo::RawType::Object;
		}

		[[nodiscard]]
		auto IsStruct() const -> bool
		{
			return GetRawType() == TypeInfo::RawType::Struct;
		}

		[[nodiscard]]
		auto Equals(const IComplexType& a_rhs) const noexcept -> bool;
		[[nodiscard]]
		auto IsAssignable(const IComplexType& a_rhs) const noexcept -> bool;

		[[nodiscard]]
		auto GetTypeName() const noexcept -> BSFixedString;

		[[nodiscard]]
		auto AsObjectType() noexcept -> BSTSmartPointer<ObjectTypeInfo>;
		[[nodiscard]]
		auto AsObjectType() const noexcept -> BSTSmartPointer<const ObjectTypeInfo>;

		[[nodiscard]]
		auto AsStructType() noexcept -> BSTSmartPointer<StructTypeInfo>;
		[[nodiscard]]
		auto AsStructType() const noexcept -> BSTSmartPointer<const StructTypeInfo>;
	};

	static_assert(sizeof(IComplexType) == 0x10);
}
