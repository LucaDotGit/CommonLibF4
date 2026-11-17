#include "RE/B/BSScript_TypeInfo.hpp"

#include "RE/B/BSScript_IComplexType.hpp"
#include "RE/B/BSScript_ObjectTypeInfo.hpp"
#include "RE/B/BSScript_StructTypeInfo.hpp"

namespace RE::BSScript
{
	TypeInfo::TypeInfo(RawType a_rhs) noexcept :
		_data(a_rhs)
	{
	}

	TypeInfo::TypeInfo(IComplexType* a_rhs) noexcept :
		_data(a_rhs)
	{
	}

	TypeInfo::TypeInfo(const BSTSmartPointer<IComplexType>& a_rhs) noexcept :
		_data(a_rhs)
	{
	}

	auto TypeInfo::operator=(RawType a_rhs) noexcept -> TypeInfo&
	{
		_data = a_rhs;
		return *this;
	}

	auto TypeInfo::operator=(IComplexType* a_rhs) noexcept -> TypeInfo&
	{
		_data = a_rhs;
		return *this;
	}

	auto TypeInfo::operator=(const BSTSmartPointer<IComplexType>& a_rhs) noexcept -> TypeInfo&
	{
		_data = a_rhs;
		return *this;
	}

	auto TypeInfo::operator==(const TypeInfo& a_rhs) const noexcept -> bool
	{
		return Equals(a_rhs);
	}

	auto TypeInfo::operator<=>(const TypeInfo& a_rhs) const noexcept -> std::strong_ordering
	{
		return Compare(a_rhs);
	}

	auto TypeInfo::IsNone() const noexcept -> bool
	{
		return GetRawType() == RawType::None;
	}

	auto TypeInfo::IsObject() const noexcept -> bool
	{
		return GetRawType() == RawType::Object;
	}

	auto TypeInfo::IsString() const noexcept -> bool
	{
		return GetRawType() == RawType::String;
	}

	auto TypeInfo::IsInt() const noexcept -> bool
	{
		return GetRawType() == RawType::Int;
	}

	auto TypeInfo::IsUInt() const noexcept -> bool
	{
		return GetRawType() == RawType::Int;
	}

	auto TypeInfo::IsFloat() const noexcept -> bool
	{
		return GetRawType() == RawType::Float;
	}

	auto TypeInfo::IsBool() const noexcept -> bool
	{
		return GetRawType() == RawType::Bool;
	}

	auto TypeInfo::IsVariant() const noexcept -> bool
	{
		return GetRawType() == RawType::Var;
	}

	auto TypeInfo::IsStruct() const noexcept -> bool
	{
		return GetRawType() == RawType::Struct;
	}

	auto TypeInfo::IsObjectArray() const noexcept -> bool
	{
		return GetRawType() == RawType::ArrayObject;
	}

	auto TypeInfo::IsStringArray() const noexcept -> bool
	{
		return GetRawType() == RawType::ArrayString;
	}

	auto TypeInfo::IsIntArray() const noexcept -> bool
	{
		return GetRawType() == RawType::ArrayInt;
	}

	auto TypeInfo::IsUIntArray() const noexcept -> bool
	{
		return GetRawType() == RawType::ArrayInt;
	}

	auto TypeInfo::IsFloatArray() const noexcept -> bool
	{
		return GetRawType() == RawType::ArrayFloat;
	}

	auto TypeInfo::IsBoolArray() const noexcept -> bool
	{
		return GetRawType() == RawType::ArrayBool;
	}

	auto TypeInfo::IsVariantArray() const noexcept -> bool
	{
		return GetRawType() == RawType::ArrayVar;
	}

	auto TypeInfo::IsStructArray() const noexcept -> bool
	{
		return GetRawType() == RawType::ArrayStruct;
	}

	auto TypeInfo::IsArray() const noexcept -> bool
	{
		if (IsComplex()) {
			return _data.rawType.all(RawType::Object);
		}

		return _data.rawType > RawType::_ArrayType_Start && _data.rawType < RawType::_ArrayType_End;
	}

	auto TypeInfo::IsComplex() const noexcept -> bool
	{
		return _data.rawType >= RawType::_ArrayType_End;
	}

	auto TypeInfo::IsComplexArray() const noexcept -> bool
	{
		return IsComplex() && IsArray();
	}

	auto TypeInfo::IsNoneAssignable() const noexcept -> bool
	{
		switch (GetRawType()) {
			case RawType::None:
			case RawType::Object:
			case RawType::Struct:
			case RawType::ArrayObject:
			case RawType::ArrayString:
			case RawType::ArrayInt:
			case RawType::ArrayFloat:
			case RawType::ArrayBool:
			case RawType::ArrayVar:
			case RawType::ArrayStruct: {
				return true;
			}
			case RawType::String:
			case RawType::Int:
			case RawType::Float:
			case RawType::Bool:
			case RawType::Var: {
				return false;
			}
			default: {
				std::unreachable();
			}
		}
	}

	auto TypeInfo::IsAssignable(const TypeInfo& a_rhs) const noexcept -> bool
	{
		if (this == std::addressof(a_rhs)) {
			return true;
		}

		const auto rightRawType = a_rhs.GetRawType();
		if (rightRawType == RawType::None) {
			return IsNoneAssignable();
		}

		const auto leftRawType = GetRawType();
		if (leftRawType == rightRawType) {
			return true;
		}

		const auto isLeftComplex = IsComplex();
		const auto isRightComplex = a_rhs.IsComplex();

		if (isLeftComplex != isRightComplex) {
			return false;
		}

		const auto* leftComplexType = _data.complexTypeInfo;
		const auto* rightComplexType = a_rhs._data.complexTypeInfo;

		if (!leftComplexType || !rightComplexType) {
			return false;
		}

		return leftComplexType->IsAssignable(*rightComplexType);
	}

	auto TypeInfo::Equals(const TypeInfo& a_rhs) const noexcept -> bool
	{
		if (this == std::addressof(a_rhs)) {
			return true;
		}

		const auto isLeftComplex = IsComplex();
		const auto isRightComplex = a_rhs.IsComplex();

		if (isLeftComplex != isRightComplex) {
			return false;
		}

		if (isLeftComplex && isRightComplex) {
			return _data.complexTypeInfo == a_rhs._data.complexTypeInfo;
		}

		return _data.rawType == a_rhs._data.rawType;
	}

	auto TypeInfo::Compare(const TypeInfo& a_rhs) const noexcept -> std::strong_ordering
	{
		if (this == std::addressof(a_rhs)) {
			return std::strong_ordering::equal;
		}

		const auto isLeftComplex = IsComplex();
		const auto isRightComplex = a_rhs.IsComplex();

		if (isLeftComplex != isRightComplex) {
			return isLeftComplex <=> isRightComplex;
		}

		if (isLeftComplex && isRightComplex) {
			return _data.complexTypeInfo <=> a_rhs._data.complexTypeInfo;
		}

		return _data.rawType <=> a_rhs._data.rawType;
	}

	auto TypeInfo::GetRawType() const noexcept -> TypeInfo::RawType
	{
		const auto complexType = GetComplexType();
		if (!complexType) {
			return _data.rawType.get();
		}

		const auto rawType = REX::EnumSet(complexType->GetRawType());
		if (IsArray()) {
			return (rawType + RawType::_ArrayType_Start).get();
		}

		return rawType.get();
	}

	auto TypeInfo::GetComplexType() const noexcept -> BSTSmartPointer<IComplexType>
	{
		if (!IsComplex()) {
			return nullptr;
		}

		auto* complexType = std::bit_cast<IComplexType*>(
			std::bit_cast<std::uintptr_t>(_data.complexTypeInfo) & ~static_cast<std::uintptr_t>(1));
		return BSTSmartPointer(complexType);
	}

	auto TypeInfo::GetObjectTypeInfo() const noexcept -> BSTSmartPointer<ObjectTypeInfo>
	{
		switch (GetRawType()) {
			case RawType::Object:
			case RawType::ArrayObject: {
				return dynamic_pointer_cast<ObjectTypeInfo>(GetComplexType());
			}
			default: {
				return nullptr;
			}
		}
	}

	auto TypeInfo::GetStructTypeInfo() const noexcept -> BSTSmartPointer<StructTypeInfo>
	{
		switch (GetRawType()) {
			case RawType::Struct:
			case RawType::ArrayStruct: {
				return dynamic_pointer_cast<StructTypeInfo>(GetComplexType());
			}
			default: {
				return nullptr;
			}
		}
	}

	auto TypeInfo::GetTypeName() const -> BSFixedString
	{
		switch (GetRawType()) {
			case RawType::None: {
				return GetNoneTypeName();
			}
			case RawType::String: {
				return GetStringTypeName();
			}
			case RawType::Int: {
				return GetIntTypeName();
			}
			case RawType::Float: {
				return GetFloatTypeName();
			}
			case RawType::Bool: {
				return GetBoolTypeName();
			}
			case RawType::Var: {
				return GetVarTypeName();
			}
			default: {
				const auto complexType = GetComplexType();
				if (!complexType) {
					return {};
				}

				auto rawTypeName = complexType->GetTypeName();
				if (rawTypeName.empty()) {
					return {};
				}

				if (!IsArray()) {
					return rawTypeName;
				}

				const auto arrayTypeName = REX::Format("{}[]"sv, rawTypeName);
				return BSFixedString(arrayTypeName);
			}
		}
	}

	void TypeInfo::SetIsArray(bool a_set) noexcept
	{
		if (IsComplex()) {
			if (a_set) {
				REX::Assert(!IsArray());
				_data.rawType.set(RawType::Object);
				REX::Assert(IsArray());
				return;
			}

			REX::Assert(IsArray());
			_data.rawType.reset(RawType::Object);
			REX::Assert(!IsArray());
			return;
		}

		if (a_set) {
			REX::Assert(!IsArray());
			_data.rawType += RawType::_ArrayType_Start;
			REX::Assert(IsArray());
			return;
		}

		REX::Assert(IsArray());
		_data.rawType -= RawType::_ArrayType_Start;
		REX::Assert(!IsArray());
	}

	auto TypeInfo::ToString() const -> std::string
	{
		const auto typeName = GetTypeName();
		return std::string{typeName.begin(), typeName.end()};
	}

	void TypeInfo::swap(TypeInfo& a_other) noexcept
	{
		if (this == std::addressof(a_other)) {
			return;
		}

		std::swap(_data, a_other._data);
	}

	auto TypeInfo::GetNoneTypeName() -> const BSFixedString&
	{
		static const auto NONE_TYPE_NAME = BSFixedString("None"sv);
		return NONE_TYPE_NAME;
	}

	auto TypeInfo::GetStringTypeName() -> const BSFixedString&
	{
		static const auto STRING_TYPE_NAME = BSFixedString("String"sv);
		return STRING_TYPE_NAME;
	}

	auto TypeInfo::GetIntTypeName() -> const BSFixedString&
	{
		static const auto INT_TYPE_NAME = BSFixedString("Int"sv);
		return INT_TYPE_NAME;
	}

	auto TypeInfo::GetFloatTypeName() -> const BSFixedString&
	{
		static const auto FLOAT_TYPE_NAME = BSFixedString("Float"sv);
		return FLOAT_TYPE_NAME;
	}

	auto TypeInfo::GetBoolTypeName() -> const BSFixedString&
	{
		static const auto BOOL_TYPE_NAME = BSFixedString("Bool"sv);
		return BOOL_TYPE_NAME;
	}

	auto TypeInfo::GetVarTypeName() -> const BSFixedString&
	{
		static const auto VAR_TYPE_NAME = BSFixedString("Var"sv);
		return VAR_TYPE_NAME;
	}

	auto TypeInfo::GetStringArrayTypeName() -> const BSFixedString&
	{
		static const auto STRING_ARRAY_TYPE_NAME = BSFixedString("String[]"sv);
		return STRING_ARRAY_TYPE_NAME;
	}

	auto TypeInfo::GetIntArrayTypeName() -> const BSFixedString&
	{
		static const auto INT_ARRAY_TYPE_NAME = BSFixedString("Int[]"sv);
		return INT_ARRAY_TYPE_NAME;
	}

	auto TypeInfo::GetFloatArrayTypeName() -> const BSFixedString&
	{
		static const auto FLOAT_ARRAY_TYPE_NAME = BSFixedString("Float[]"sv);
		return FLOAT_ARRAY_TYPE_NAME;
	}

	auto TypeInfo::GetBoolArrayTypeName() -> const BSFixedString&
	{
		static const auto BOOL_ARRAY_TYPE_NAME = BSFixedString("Bool[]"sv);
		return BOOL_ARRAY_TYPE_NAME;
	}

	auto TypeInfo::GetVarArrayTypeName() -> const BSFixedString&
	{
		static const auto VAR_ARRAY_TYPE_NAME = BSFixedString("Var[]"sv);
		return VAR_ARRAY_TYPE_NAME;
	}

	TypeInfo::DataUnion::DataUnion(RawType a_rhs) noexcept :
		rawType(a_rhs)
	{
	}

	TypeInfo::DataUnion::DataUnion(IComplexType* a_rhs) noexcept :
		complexTypeInfo(a_rhs)
	{
	}

	TypeInfo::DataUnion::DataUnion(const BSTSmartPointer<IComplexType>& a_rhs) noexcept :
		complexTypeInfo(a_rhs.get())
	{
	}

	auto TypeInfo::DataUnion::operator=(RawType a_rhs) noexcept -> TypeInfo::DataUnion&
	{
		rawType = a_rhs;
		return *this;
	}

	auto TypeInfo::DataUnion::operator=(IComplexType* a_rhs) noexcept -> TypeInfo::DataUnion&
	{
		complexTypeInfo = a_rhs;
		return *this;
	}

	auto TypeInfo::DataUnion::operator=(const BSTSmartPointer<IComplexType>& a_rhs) noexcept -> TypeInfo::DataUnion&
	{
		complexTypeInfo = a_rhs.get();
		return *this;
	}

	auto operator==(const TypeInfo& a_lhs, TypeInfo::RawType a_rhs) noexcept -> bool
	{
		return a_lhs.GetRawType() == a_rhs;
	}

	auto operator==(TypeInfo::RawType a_lhs, const TypeInfo& a_rhs) noexcept -> bool
	{
		return a_lhs == a_rhs.GetRawType();
	}

	auto operator==(const TypeInfo& a_lhs, const IComplexType* a_rhs) noexcept -> bool
	{
		return a_lhs.GetComplexType() == a_rhs;
	}

	auto operator==(const IComplexType* a_lhs, const TypeInfo& a_rhs) noexcept -> bool
	{
		return a_lhs == a_rhs.GetComplexType();
	}
}

namespace std
{
	auto hash<RE::BSScript::TypeInfo>::operator()(const RE::BSScript::TypeInfo& a_key) const noexcept -> std::size_t
	{
		const auto complexType = a_key.GetComplexType();
		if (complexType) {
			return REX::HashCombine(complexType->GetRawType(), complexType);
		}

		return REX::Hash(a_key.GetRawType());
	}
}
