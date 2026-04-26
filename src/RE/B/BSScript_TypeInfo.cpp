#include "RE/B/BSScript_TypeInfo.hpp"

#include "RE/B/BSScript_IComplexType.hpp"
#include "RE/B/BSScript_ObjectTypeInfo.hpp"
#include "RE/B/BSScript_StructTypeInfo.hpp"

namespace RE::BSScript
{
	TypeInfo::TypeInfo() noexcept = default;

	TypeInfo::~TypeInfo() noexcept = default;

	TypeInfo::TypeInfo(RawType a_rhs) noexcept
		: _data(a_rhs)
	{
	}

	TypeInfo::TypeInfo(IComplexType* a_rhs) noexcept
		: _data(a_rhs)
	{
	}

	TypeInfo& TypeInfo::operator=(RawType a_rhs) noexcept
	{
		_data.rawType = a_rhs;
		return *this;
	}

	TypeInfo& TypeInfo::operator=(IComplexType* a_rhs) noexcept
	{
		_data.complexTypeInfo = a_rhs;
		return *this;
	}

	bool TypeInfo::operator==(const TypeInfo& a_rhs) const noexcept
	{
		return Equals(a_rhs);
	}

	bool TypeInfo::operator!=(const TypeInfo& a_rhs) const noexcept
	{
		return !(*this == a_rhs);
	}

	std::strong_ordering TypeInfo::operator<=>(const TypeInfo& a_rhs) const noexcept
	{
		return Compare(a_rhs);
	}

	bool TypeInfo::IsNone() const noexcept
	{
		return GetRawType() == RawType::kNone;
	}

	bool TypeInfo::IsObject() const noexcept
	{
		return GetRawType() == RawType::kObject;
	}

	bool TypeInfo::IsString() const noexcept
	{
		return GetRawType() == RawType::kString;
	}

	bool TypeInfo::IsInt() const noexcept
	{
		return GetRawType() == RawType::kInt;
	}

	bool TypeInfo::IsUInt() const noexcept
	{
		return GetRawType() == RawType::kInt;
	}

	bool TypeInfo::IsFloat() const noexcept
	{
		return GetRawType() == RawType::kFloat;
	}

	bool TypeInfo::IsBool() const noexcept
	{
		return GetRawType() == RawType::kBool;
	}

	bool TypeInfo::IsVar() const noexcept
	{
		return GetRawType() == RawType::kVar;
	}

	bool TypeInfo::IsStruct() const noexcept
	{
		return GetRawType() == RawType::kStruct;
	}

	bool TypeInfo::IsObjectArray() const noexcept
	{
		return GetRawType() == RawType::kArrayObject;
	}

	bool TypeInfo::IsStringArray() const noexcept
	{
		return GetRawType() == RawType::kArrayString;
	}

	bool TypeInfo::IsIntArray() const noexcept
	{
		return GetRawType() == RawType::kArrayInt;
	}

	bool TypeInfo::IsUIntArray() const noexcept
	{
		return GetRawType() == RawType::kArrayInt;
	}

	bool TypeInfo::IsFloatArray() const noexcept
	{
		return GetRawType() == RawType::kArrayFloat;
	}

	bool TypeInfo::IsBoolArray() const noexcept
	{
		return GetRawType() == RawType::kArrayBool;
	}

	bool TypeInfo::IsVarArray() const noexcept
	{
		return GetRawType() == RawType::kArrayVar;
	}

	bool TypeInfo::IsStructArray() const noexcept
	{
		return GetRawType() == RawType::kArrayStruct;
	}

	bool TypeInfo::IsArray() const noexcept
	{
		if (IsComplex()) {
			return _data.rawType.all(RawType::kObject);
		}

		return _data.rawType > RawType::kArrayType_Start && _data.rawType < RawType::kArrayType_End;
	}

	bool TypeInfo::IsComplex() const noexcept
	{
		return _data.rawType >= RawType::kArrayType_End;
	}

	bool TypeInfo::IsComplexArray() const noexcept
	{
		return IsComplex() && IsArray();
	}

	bool TypeInfo::IsNoneAssignable() const noexcept
	{
		switch (GetRawType()) {
			case RawType::kNone:
			case RawType::kObject:
			case RawType::kStruct:
			case RawType::kArrayObject:
			case RawType::kArrayString:
			case RawType::kArrayInt:
			case RawType::kArrayFloat:
			case RawType::kArrayBool:
			case RawType::kArrayVar:
			case RawType::kArrayStruct: {
				return true;
			}
			case RawType::kString:
			case RawType::kInt:
			case RawType::kFloat:
			case RawType::kBool:
			case RawType::kVar: {
				return false;
			}
			default: {
				std::unreachable();
			}
		}
	}

	bool TypeInfo::IsAssignable(const TypeInfo& a_rhs) const noexcept
	{
		if (this == std::addressof(a_rhs)) {
			return true;
		}

		const auto rightRawType = a_rhs.GetRawType();
		if (rightRawType == RawType::kNone) {
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

	bool TypeInfo::Equals(const TypeInfo& a_rhs) const noexcept
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

	std::strong_ordering TypeInfo::Compare(const TypeInfo& a_rhs) const noexcept
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

	TypeInfo::RawType TypeInfo::GetRawType() const noexcept
	{
		const auto* complexType = GetComplexType();
		if (!complexType) {
			return *_data.rawType;
		}

		const auto rawType = REX::EnumSet(complexType->GetRawType());
		if (IsArray()) {
			return *(rawType + RawType::kArrayType_Start);
		}

		return *rawType;
	}

	IComplexType* TypeInfo::GetComplexType() const noexcept
	{
		if (!IsComplex()) {
			return nullptr;
		}

		return std::bit_cast<IComplexType*>(
			std::bit_cast<std::uintptr_t>(_data.complexTypeInfo) &
			~static_cast<std::uintptr_t>(1));
	}

	ObjectTypeInfo* TypeInfo::GetObjectTypeInfo() const noexcept
	{
		switch (GetRawType()) {
			case RawType::kObject:
			case RawType::kArrayObject: {
				return reinterpret_cast<ObjectTypeInfo*>(GetComplexType());
			}
			default: {
				return nullptr;
			}
		}
	}

	StructTypeInfo* TypeInfo::GetStructTypeInfo() const noexcept
	{
		switch (GetRawType()) {
			case RawType::kStruct:
			case RawType::kArrayStruct: {
				return reinterpret_cast<StructTypeInfo*>(GetComplexType());
			}
			default: {
				return nullptr;
			}
		}
	}

	BSFixedString TypeInfo::GetTypeName() const
	{
		switch (GetRawType()) {
			case RawType::kNone: {
				return GetNoneTypeName();
			}
			case RawType::kString: {
				return GetStringTypeName();
			}
			case RawType::kInt: {
				return GetIntTypeName();
			}
			case RawType::kFloat: {
				return GetFloatTypeName();
			}
			case RawType::kBool: {
				return GetBoolTypeName();
			}
			case RawType::kVar: {
				return GetVarTypeName();
			}
			default: {
				const auto* complexType = GetComplexType();
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

				return BSFixedString(REX::Format("{}[]"sv, rawTypeName));
			}
		}
	}

	void TypeInfo::SetIsArray(bool a_set) noexcept
	{
		if (IsComplex()) {
			if (a_set) {
				REX::Assert(!IsArray());
				_data.rawType.set(RawType::kObject);
				REX::Assert(IsArray());
			}
			else {
				REX::Assert(IsArray());
				_data.rawType.reset(RawType::kObject);
				REX::Assert(!IsArray());
			}
		}
		else {
			if (a_set) {
				REX::Assert(!IsArray());
				_data.rawType += RawType::kArrayType_Start;
				REX::Assert(IsArray());
			}
			else {
				REX::Assert(IsArray());
				_data.rawType -= RawType::kArrayType_Start;
				REX::Assert(!IsArray());
			}
		}
	}

	std::string TypeInfo::ToString() const
	{
		return std::string{ static_cast<std::string_view>(GetTypeName()) };
	}

	const BSFixedString& TypeInfo::GetNoneTypeName() noexcept
	{
		static const auto NONE_TYPE_NAME = BSFixedString("None"sv);
		return NONE_TYPE_NAME;
	}

	const BSFixedString& TypeInfo::GetStringTypeName() noexcept
	{
		static const auto STRING_TYPE_NAME = BSFixedString("String"sv);
		return STRING_TYPE_NAME;
	}

	const BSFixedString& TypeInfo::GetIntTypeName() noexcept
	{
		static const auto INT_TYPE_NAME = BSFixedString("Int"sv);
		return INT_TYPE_NAME;
	}

	const BSFixedString& TypeInfo::GetFloatTypeName() noexcept
	{
		static const auto FLOAT_TYPE_NAME = BSFixedString("Float"sv);
		return FLOAT_TYPE_NAME;
	}

	const BSFixedString& TypeInfo::GetBoolTypeName() noexcept
	{
		static const auto BOOL_TYPE_NAME = BSFixedString("Bool"sv);
		return BOOL_TYPE_NAME;
	}

	const BSFixedString& TypeInfo::GetVarTypeName() noexcept
	{
		static const auto VAR_TYPE_NAME = BSFixedString("Var"sv);
		return VAR_TYPE_NAME;
	}

	const BSFixedString& TypeInfo::GetStringArrayTypeName() noexcept
	{
		static const auto STRING_ARRAY_TYPE_NAME = BSFixedString("String[]"sv);
		return STRING_ARRAY_TYPE_NAME;
	}

	const BSFixedString& TypeInfo::GetIntArrayTypeName() noexcept
	{
		static const auto INT_ARRAY_TYPE_NAME = BSFixedString("Int[]"sv);
		return INT_ARRAY_TYPE_NAME;
	}

	const BSFixedString& TypeInfo::GetFloatArrayTypeName() noexcept
	{
		static const auto FLOAT_ARRAY_TYPE_NAME = BSFixedString("Float[]"sv);
		return FLOAT_ARRAY_TYPE_NAME;
	}

	const BSFixedString& TypeInfo::GetBoolArrayTypeName() noexcept
	{
		static const auto BOOL_ARRAY_TYPE_NAME = BSFixedString("Bool[]"sv);
		return BOOL_ARRAY_TYPE_NAME;
	}

	const BSFixedString& TypeInfo::GetVarArrayTypeName() noexcept
	{
		static const auto VAR_ARRAY_TYPE_NAME = BSFixedString("Var[]"sv);
		return VAR_ARRAY_TYPE_NAME;
	}

	TypeInfo::DataUnion::DataUnion() noexcept
	{
	}

	TypeInfo::DataUnion::~DataUnion() noexcept
	{
	}

	TypeInfo::DataUnion::DataUnion(RawType a_rhs) noexcept
		: rawType(a_rhs)
	{
	}

	TypeInfo::DataUnion::DataUnion(IComplexType* a_rhs) noexcept
		: complexTypeInfo(a_rhs)
	{
	}

	TypeInfo::DataUnion::DataUnion(const DataUnion& a_rhs) noexcept
		: complexTypeInfo(a_rhs.complexTypeInfo)
	{
	}

	TypeInfo::DataUnion::DataUnion(DataUnion&& a_rhs) noexcept
		: complexTypeInfo(std::exchange(a_rhs.complexTypeInfo, nullptr))
	{
	}

	TypeInfo::DataUnion& TypeInfo::DataUnion::operator=(RawType a_rhs) noexcept
	{
		rawType = a_rhs;
		return *this;
	}

	TypeInfo::DataUnion& TypeInfo::DataUnion::operator=(IComplexType* a_rhs) noexcept
	{
		complexTypeInfo = a_rhs;
		return *this;
	}

	TypeInfo::DataUnion& TypeInfo::DataUnion::operator=(const DataUnion& a_rhs) noexcept
	{
		if (this == std::addressof(a_rhs)) {
			return *this;
		}

		complexTypeInfo = a_rhs.complexTypeInfo;
		return *this;
	}

	TypeInfo::DataUnion& TypeInfo::DataUnion::operator=(DataUnion&& a_rhs) noexcept
	{
		if (this == std::addressof(a_rhs)) {
			return *this;
		}

		complexTypeInfo = std::exchange(a_rhs.complexTypeInfo, nullptr);
		return *this;
	}

	bool operator==(const TypeInfo& a_lhs, TypeInfo::RawType a_rhs) noexcept
	{
		return a_lhs.GetRawType() == a_rhs;
	}

	bool operator==(TypeInfo::RawType a_lhs, const TypeInfo& a_rhs) noexcept
	{
		return a_lhs == a_rhs.GetRawType();
	}

	bool operator==(const TypeInfo& a_lhs, const IComplexType* a_rhs) noexcept
	{
		return a_lhs.GetComplexType() == a_rhs;
	}

	bool operator==(const IComplexType* a_lhs, const TypeInfo& a_rhs) noexcept
	{
		return a_lhs == a_rhs.GetComplexType();
	}
}

namespace std
{
	std::size_t hash<RE::BSScript::TypeInfo>::operator()(const RE::BSScript::TypeInfo& a_key) const noexcept
	{
		const auto* complexType = a_key.GetComplexType();
		if (complexType) {
			return REX::HashCombine(complexType->GetRawType(), complexType);
		}

		return REX::Hash(a_key.GetRawType());
	}
}
