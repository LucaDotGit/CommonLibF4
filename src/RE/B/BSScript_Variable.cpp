#include "RE/B/BSScript_Variable.hpp"

#include "RE/B/BSScript_Array.hpp"
#include "RE/B/BSScript_Object.hpp"
#include "RE/B/BSScript_ObjectTypeInfo.hpp" // IWYU pragma: keep
#include "RE/B/BSScript_Struct.hpp"
#include "RE/B/BSScript_StructTypeInfo.hpp" // IWYU pragma: keep

namespace RE::BSScript
{
	Variable::Variable() noexcept = default;

	Variable::~Variable() noexcept
	{
		reset();
	}

	Variable::Variable(const Variable& a_rhs) noexcept
	{
		Assign(a_rhs);
	}

	Variable::Variable(Variable&& a_rhs) noexcept
	{
		Assign(std::move(a_rhs));
	}

	Variable::Variable(std::nullptr_t) noexcept
	{
		SetNone();
	}

	Variable::Variable(BSTSmartPointer<Object> a_value) noexcept
	{
		SetObject(std::move(a_value));
	}

	Variable::Variable(BSFixedString a_value) noexcept
	{
		SetString(std::move(a_value));
	}

	Variable::Variable(std::int32_t a_value) noexcept
	{
		SetInt(a_value);
	}

	Variable::Variable(std::uint32_t a_value) noexcept
	{
		SetUInt(a_value);
	}

	Variable::Variable(REX::Float32 a_value) noexcept
	{
		SetFloat(a_value);
	}

	Variable::Variable(bool a_value) noexcept
	{
		SetBool(a_value);
	}

	Variable::Variable(UniqueVariant a_value) noexcept
	{
		SetVar(std::move(a_value));
	}

	Variable::Variable(SharedVariant a_value) noexcept
	{
		SetVar(a_value);
	}

	Variable::Variable(BSTSmartPointer<Struct> a_value) noexcept
	{
		SetStruct(std::move(a_value));
	}

	Variable::Variable(BSTSmartPointer<Array> a_value) noexcept
	{
		SetArray(std::move(a_value));
	}

	Variable& Variable::operator=(const Variable& a_rhs) noexcept
	{
		if (this == std::addressof(a_rhs)) {
			return *this;
		}

		Assign(a_rhs);
		return *this;
	}

	Variable& Variable::operator=(Variable&& a_rhs) noexcept
	{
		if (this == std::addressof(a_rhs)) {
			return *this;
		}

		Assign(std::move(a_rhs));
		return *this;
	}

	Variable& Variable::operator=(std::nullptr_t) noexcept
	{
		SetNone();
		return *this;
	}

	Variable& Variable::operator=(BSTSmartPointer<Object> a_value) noexcept
	{
		SetObject(std::move(a_value));
		return *this;
	}

	Variable& Variable::operator=(BSFixedString a_value) noexcept
	{
		SetString(std::move(a_value));
		return *this;
	}

	Variable& Variable::operator=(std::int32_t a_value) noexcept
	{
		SetInt(a_value);
		return *this;
	}

	Variable& Variable::operator=(std::uint32_t a_value) noexcept
	{
		SetUInt(a_value);
		return *this;
	}

	Variable& Variable::operator=(REX::Float32 a_value) noexcept
	{
		SetFloat(a_value);
		return *this;
	}

	Variable& Variable::operator=(bool a_value) noexcept
	{
		SetBool(a_value);
		return *this;
	}

	Variable& Variable::operator=(UniqueVariant a_value) noexcept
	{
		SetVar(std::move(a_value));
		return *this;
	}

	Variable& Variable::operator=(SharedVariant a_value) noexcept
	{
		SetVar(a_value);
		return *this;
	}

	Variable& Variable::operator=(BSTSmartPointer<Struct> a_value) noexcept
	{
		SetStruct(std::move(a_value));
		return *this;
	}

	Variable& Variable::operator=(BSTSmartPointer<Array> a_value) noexcept
	{
		SetArray(std::move(a_value));
		return *this;
	}

	bool Variable::operator==(const Variable& a_rhs) const noexcept
	{
		return Equals(a_rhs);
	}

	bool Variable::operator!=(const Variable& a_rhs) const noexcept
	{
		return !(*this == a_rhs);
	}

	std::partial_ordering Variable::operator<=>(const Variable& a_rhs) const noexcept
	{
		return Compare(a_rhs);
	}

	bool Variable::IsNone() const noexcept
	{
		return _varType.IsNone();
	}

	bool Variable::IsObject() const noexcept
	{
		return _varType.IsObject();
	}

	bool Variable::IsString() const noexcept
	{
		return _varType.IsString();
	}

	bool Variable::IsInt() const noexcept
	{
		return _varType.IsInt();
	}
	bool Variable::IsUInt() const noexcept
	{
		return _varType.IsUInt();
	}

	bool Variable::IsFloat() const noexcept
	{
		return _varType.IsFloat();
	}

	bool Variable::IsBool() const noexcept
	{
		return _varType.IsBool();
	}

	bool Variable::IsVar() const noexcept
	{
		return _varType.IsVar();
	}

	bool Variable::IsStruct() const noexcept
	{
		return _varType.IsStruct();
	}

	bool Variable::IsObjectArray() const noexcept
	{
		return _varType.IsObjectArray();
	}

	bool Variable::IsStringArray() const noexcept
	{
		return _varType.IsStringArray();
	}

	bool Variable::IsIntArray() const noexcept
	{
		return _varType.IsIntArray();
	}

	bool Variable::IsUIntArray() const noexcept
	{
		return _varType.IsUIntArray();
	}

	bool Variable::IsFloatArray() const noexcept
	{
		return _varType.IsFloatArray();
	}

	bool Variable::IsBoolArray() const noexcept
	{
		return _varType.IsBoolArray();
	}

	bool Variable::IsVarArray() const noexcept
	{
		return _varType.IsVarArray();
	}

	bool Variable::IsStructArray() const noexcept
	{
		return _varType.IsStructArray();
	}

	bool Variable::IsArray() const noexcept
	{
		return _varType.IsArray();
	}

	bool Variable::IsComplex() const noexcept
	{
		return _varType.IsComplex();
	}

	bool Variable::IsComplexArray() const noexcept
	{
		return _varType.IsComplexArray();
	}

	bool Variable::IsNoneAssignable() const noexcept
	{
		return _varType.IsNoneAssignable();
	}

	bool Variable::Equals(const Variable& a_rhs) const noexcept
	{
		if (this == std::addressof(a_rhs)) {
			return true;
		}

		const auto leftRawType = GetRawType();
		const auto rightRawType = a_rhs.GetRawType();

		const auto isLeftVar = leftRawType == RawType::kVar;
		const auto isRightVar = rightRawType == RawType::kVar;

		if (isLeftVar && isRightVar) {
			const auto* leftValue = GetVar();
			const auto* rightValue = a_rhs.GetVar();

			if (leftValue && rightValue) {
				return *leftValue == *rightValue;
			}

			return leftValue == rightValue;
		}

		if (isLeftVar) {
			const auto* leftValue = GetVar();
			if (!leftValue) {
				return false;
			}

			return *leftValue == a_rhs;
		}

		if (isRightVar) {
			const auto* rightValue = a_rhs.GetVar();
			if (!rightValue) {
				return false;
			}

			return *this == *rightValue;
		}

		if (leftRawType != rightRawType) {
			return false;
		}

		switch (leftRawType) {
			case RawType::kNone: {
				return true;
			}
			case RawType::kObject: {
				return GetObject() == a_rhs.GetObject();
			}
			case RawType::kString: {
				return GetString() == a_rhs.GetString();
			}
			case RawType::kInt: {
				return GetInt() == a_rhs.GetInt();
			}
			case RawType::kFloat: {
				return GetFloat() == a_rhs.GetFloat();
			}
			case RawType::kBool: {
				return GetBool() == a_rhs.GetBool();
			}
			case RawType::kVar: {
				const auto* leftValue = GetVar();
				const auto* rightValue = a_rhs.GetVar();

				if (leftValue && rightValue) {
					return leftValue->Equals(*rightValue);
				}

				return leftValue == rightValue;
			}
			case RawType::kStruct: {
				return GetStruct() == a_rhs.GetStruct();
			}
			case RawType::kArrayObject:
			case RawType::kArrayString:
			case RawType::kArrayInt:
			case RawType::kArrayFloat:
			case RawType::kArrayBool:
			case RawType::kArrayVar:
			case RawType::kArrayStruct: {
				return GetArray() == a_rhs.GetArray();
			}
			default: {
				std::unreachable();
			}
		}
	}

	bool Variable::RefEquals(const Variable& a_rhs) const noexcept
	{
		if (this == std::addressof(a_rhs)) {
			return true;
		}

		const auto leftRawType = GetRawType();
		const auto rightRawType = a_rhs.GetRawType();

		if (leftRawType != rightRawType) {
			return false;
		}

		switch (leftRawType) {
			case RawType::kNone: {
				return true;
			}
			case RawType::kObject: {
				return GetObject() == a_rhs.GetObject();
			}
			case RawType::kString: {
				return GetString() == a_rhs.GetString();
			}
			case RawType::kInt:
			case RawType::kFloat:
			case RawType::kBool: {
				return false;
			}
			case RawType::kStruct: {
				return GetStruct() == a_rhs.GetStruct();
			}
			case RawType::kVar: {
				const auto* leftValue = GetVar();
				const auto* rightValue = a_rhs.GetVar();

				if (leftValue && rightValue) {
					return leftValue->RefEquals(*rightValue);
				}

				return leftValue == rightValue;
			}
			case RawType::kArrayObject:
			case RawType::kArrayString:
			case RawType::kArrayInt:
			case RawType::kArrayFloat:
			case RawType::kArrayBool:
			case RawType::kArrayVar:
			case RawType::kArrayStruct: {
				return GetArray() == a_rhs.GetArray();
			}
			default: {
				std::unreachable();
			}
		}
	}

	bool Variable::DeepEquals(const Variable& a_rhs) const noexcept
	{
		if (this == std::addressof(a_rhs)) {
			return true;
		}

		const auto leftRawType = GetRawType();
		const auto rightRawType = a_rhs.GetRawType();

		const auto isLeftVar = leftRawType == RawType::kVar;
		const auto isRightVar = rightRawType == RawType::kVar;

		if (isLeftVar && isRightVar) {
			const auto* leftValue = GetVar();
			const auto* rightValue = a_rhs.GetVar();

			if (leftValue && rightValue) {
				return leftValue->DeepEquals(*rightValue);
			}

			return leftValue == rightValue;
		}

		if (isLeftVar) {
			const auto* leftValue = GetVar();
			if (!leftValue) {
				return false;
			}

			return leftValue->DeepEquals(a_rhs);
		}

		if (isRightVar) {
			const auto* rightValue = a_rhs.GetVar();
			if (!rightValue) {
				return false;
			}

			return rightValue->DeepEquals(*this);
		}

		if (leftRawType != rightRawType &&
			leftRawType != RawType::kArrayVar &&
			rightRawType != RawType::kArrayVar) {
			return false;
		}

		switch (leftRawType) {
			case RawType::kNone: {
				return true;
			}
			case RawType::kObject: {
				const auto leftValue = GetObject();
				const auto rightValue = a_rhs.GetObject();

				if (leftValue && rightValue) {
					return leftValue->DeepEquals(*rightValue);
				}

				return leftValue == rightValue;
			}
			case RawType::kString: {
				return GetString() == a_rhs.GetString();
			}
			case RawType::kInt: {
				return GetInt() == a_rhs.GetInt();
			}
			case RawType::kFloat: {
				return GetFloat() == a_rhs.GetFloat();
			}
			case RawType::kBool: {
				return GetBool() == a_rhs.GetBool();
			}
			case RawType::kStruct: {
				const auto leftValue = GetStruct();
				const auto rightValue = a_rhs.GetStruct();

				if (leftValue && rightValue) {
					return leftValue->DeepEquals(*rightValue);
				}

				return leftValue == rightValue;
			}
			case RawType::kVar: {
				const auto* leftValue = GetVar();
				const auto* rightValue = a_rhs.GetVar();

				if (leftValue && rightValue) {
					return leftValue->DeepEquals(*rightValue);
				}

				return leftValue == rightValue;
			}
			case RawType::kArrayObject:
			case RawType::kArrayString:
			case RawType::kArrayInt:
			case RawType::kArrayFloat:
			case RawType::kArrayBool:
			case RawType::kArrayVar:
			case RawType::kArrayStruct: {
				const auto leftValue = GetArray();
				const auto rightValue = a_rhs.GetArray();

				if (leftValue && rightValue) {
					return leftValue->DeepEquals(*rightValue);
				}

				return leftValue == rightValue;
			}
			default: {
				std::unreachable();
			}
		}
	}

	std::partial_ordering Variable::Compare(const Variable& a_rhs) const noexcept
	{
		if (this == std::addressof(a_rhs)) {
			return std::partial_ordering::equivalent;
		}

		const auto leftRawType = GetRawType();
		const auto rightRawType = a_rhs.GetRawType();

		const auto isLeftVar = leftRawType == RawType::kVar;
		const auto isRightVar = rightRawType == RawType::kVar;

		if (isLeftVar && isRightVar) {
			const auto* leftValue = GetVar();
			const auto* rightValue = a_rhs.GetVar();

			if (leftValue && rightValue) {
				return leftValue->Compare(*rightValue);
			}

			return leftValue <=> rightValue;
		}

		if (isLeftVar) {
			const auto* leftValue = GetVar();
			if (!leftValue) {
				return std::partial_ordering::less;
			}

			return leftValue->Compare(a_rhs);
		}

		if (isRightVar) {
			const auto* rightValue = a_rhs.GetVar();
			if (!rightValue) {
				return std::partial_ordering::greater;
			}

			return rightValue->Compare(*this);
		}

		if (leftRawType != rightRawType) {
			return leftRawType <=> rightRawType;
		}

		switch (leftRawType) {
			case RawType::kNone: {
				return std::partial_ordering::equivalent;
			}
			case RawType::kObject: {
				return GetObject() <=> a_rhs.GetObject();
			}
			case RawType::kString: {
				return GetString() <=> a_rhs.GetString();
			}
			case RawType::kInt: {
				return GetInt() <=> a_rhs.GetInt();
			}
			case RawType::kFloat: {
				return GetFloat() <=> a_rhs.GetFloat();
			}
			case RawType::kBool: {
				return GetBool() <=> a_rhs.GetBool();
			}
			case RawType::kVar: {
				const auto* leftValue = GetVar();
				const auto* rightValue = a_rhs.GetVar();

				if (leftValue && rightValue) {
					return leftValue->Compare(*rightValue);
				}

				return leftValue <=> rightValue;
			}
			case RawType::kStruct: {
				return GetStruct() <=> a_rhs.GetStruct();
			}
			case RawType::kArrayObject:
			case RawType::kArrayString:
			case RawType::kArrayInt:
			case RawType::kArrayFloat:
			case RawType::kArrayBool:
			case RawType::kArrayVar:
			case RawType::kArrayStruct: {
				return GetArray() <=> a_rhs.GetArray();
			}
			default: {
				std::unreachable();
			}
		}
	}

	std::partial_ordering Variable::RefCompare(const Variable& a_rhs) const noexcept
	{
		if (this == std::addressof(a_rhs)) {
			return std::partial_ordering::equivalent;
		}

		const auto leftRawType = GetRawType();
		const auto rightRawType = a_rhs.GetRawType();

		if (leftRawType != rightRawType) {
			return leftRawType <=> rightRawType;
		}

		switch (leftRawType) {
			case RawType::kNone: {
				return std::partial_ordering::equivalent;
			}
			case RawType::kObject: {
				return GetObject() <=> a_rhs.GetObject();
			}
			case RawType::kString: {
				return GetString() <=> a_rhs.GetString();
			}
			case RawType::kInt:
			case RawType::kFloat:
			case RawType::kBool: {
				return std::partial_ordering::unordered;
			}
			case RawType::kStruct: {
				return GetStruct() <=> a_rhs.GetStruct();
			}
			case RawType::kVar: {
				const auto* leftValue = GetVar();
				const auto* rightValue = a_rhs.GetVar();

				if (leftValue && rightValue) {
					return leftValue->RefCompare(*rightValue);
				}

				return leftValue <=> rightValue;
			}
			case RawType::kArrayObject:
			case RawType::kArrayString:
			case RawType::kArrayInt:
			case RawType::kArrayFloat:
			case RawType::kArrayBool:
			case RawType::kArrayVar:
			case RawType::kArrayStruct: {
				return GetArray() <=> a_rhs.GetArray();
			}
			default: {
				std::unreachable();
			}
		}
	}

	std::partial_ordering Variable::DeepCompare(const Variable& a_rhs) const noexcept
	{
		if (this == std::addressof(a_rhs)) {
			return std::partial_ordering::equivalent;
		}

		const auto leftRawType = GetRawType();
		const auto rightRawType = a_rhs.GetRawType();

		const auto isLeftVar = leftRawType == RawType::kVar;
		const auto isRightVar = rightRawType == RawType::kVar;

		if (isLeftVar && isRightVar) {
			const auto* leftValue = GetVar();
			const auto* rightValue = a_rhs.GetVar();

			if (leftValue && rightValue) {
				return leftValue->DeepCompare(*rightValue);
			}

			return leftValue <=> rightValue;
		}

		if (isLeftVar) {
			const auto* leftValue = GetVar();
			if (!leftValue) {
				return std::partial_ordering::less;
			}

			return leftValue->DeepCompare(a_rhs);
		}

		if (isRightVar) {
			const auto* rightValue = a_rhs.GetVar();
			if (!rightValue) {
				return std::partial_ordering::greater;
			}

			return rightValue->DeepCompare(*this);
		}

		if (leftRawType != rightRawType &&
			leftRawType != RawType::kArrayVar &&
			rightRawType != RawType::kArrayVar) {
			return leftRawType <=> rightRawType;
		}

		switch (leftRawType) {
			case RawType::kNone: {
				return std::partial_ordering::equivalent;
			}
			case RawType::kObject: {
				const auto leftValue = GetObject();
				const auto rightValue = a_rhs.GetObject();

				if (leftValue && rightValue) {
					return leftValue->DeepCompare(*rightValue);
				}

				return leftValue <=> rightValue;
			}
			case RawType::kString: {
				return GetString() <=> a_rhs.GetString();
			}
			case RawType::kInt: {
				return GetInt() <=> a_rhs.GetInt();
			}
			case RawType::kFloat: {
				return GetFloat() <=> a_rhs.GetFloat();
			}
			case RawType::kBool: {
				return GetBool() <=> a_rhs.GetBool();
			}
			case RawType::kStruct: {
				const auto leftValue = GetStruct();
				const auto rightValue = a_rhs.GetStruct();

				if (leftValue && rightValue) {
					return leftValue->DeepCompare(*rightValue);
				}

				return leftValue <=> rightValue;
			}
			case RawType::kVar: {
				const auto* leftValue = GetVar();
				const auto* rightValue = a_rhs.GetVar();

				if (leftValue && rightValue) {
					return leftValue->DeepCompare(*rightValue);
				}

				return leftValue <=> rightValue;
			}
			case RawType::kArrayObject:
			case RawType::kArrayString:
			case RawType::kArrayInt:
			case RawType::kArrayFloat:
			case RawType::kArrayBool:
			case RawType::kArrayVar:
			case RawType::kArrayStruct: {
				const auto leftValue = GetArray();
				const auto rightValue = a_rhs.GetArray();

				if (leftValue && rightValue) {
					return leftValue->DeepCompare(*rightValue);
				}

				return leftValue <=> rightValue;
			}
			default: {
				std::unreachable();
			}
		}
	}

	std::nullptr_t Variable::GetNone() const noexcept
	{
		REX::Assert(IsNone());
		REX::Assert(_value.none == nullptr);
		return nullptr;
	}

	BSTSmartPointer<Object> Variable::GetObject() const noexcept
	{
		REX::Assert(IsObject());
		return _value.object;
	}

	BSFixedString Variable::GetString() const noexcept
	{
		REX::Assert(IsString());
		return _value.string;
	}

	std::int32_t Variable::GetInt() const noexcept
	{
		REX::Assert(IsInt());
		return _value.int32;
	}

	std::uint32_t Variable::GetUInt() const noexcept
	{
		REX::Assert(IsUInt());
		return _value.uint32;
	}

	REX::Float32 Variable::GetFloat() const noexcept
	{
		REX::Assert(IsFloat());
		return _value.float32;
	}

	bool Variable::GetBool() const noexcept
	{
		REX::Assert(IsBool());
		return _value.boolean;
	}

	SharedVariant Variable::GetVar() const noexcept
	{
		REX::Assert(IsVar());
		return _value.var.get();
	}

	BSTSmartPointer<Struct> Variable::GetStruct() const noexcept
	{
		REX::Assert(IsStruct());
		return _value.structure;
	}

	BSTSmartPointer<Array> Variable::GetArray() const noexcept
	{
		REX::Assert(IsArray());
		return _value.array;
	}

	void Variable::SetNone() noexcept
	{
		reset();
	}

	void Variable::SetObject(BSTSmartPointer<Object> a_value) noexcept
	{
		reset();

		if (!a_value) {
			return;
		}

		_varType = a_value->type.get();
		_value.object = std::move(a_value);

		REX::Assert(IsObject());
	}

	void Variable::SetString(BSFixedString a_value) noexcept
	{
		reset();

		_value.string = std::move(a_value);
		_varType = RawType::kString;

		REX::Assert(IsString());
	}

	void Variable::SetInt(std::int32_t a_value) noexcept
	{
		reset();

		_value.int32 = a_value;
		_varType = RawType::kInt;

		REX::Assert(IsInt());
	}

	void Variable::SetUInt(std::uint32_t a_value) noexcept
	{
		reset();

		_value.uint32 = a_value;
		_varType = RawType::kInt;

		REX::Assert(IsUInt());
	}

	void Variable::SetFloat(REX::Float32 a_value) noexcept
	{
		reset();

		_value.float32 = a_value;
		_varType = RawType::kFloat;

		REX::Assert(IsFloat());
	}

	void Variable::SetBool(bool a_value) noexcept
	{
		reset();

		_value.boolean = a_value;
		_varType = RawType::kBool;

		REX::Assert(IsBool());
	}

	void Variable::SetVar(UniqueVariant a_value) noexcept
	{
		reset();

		_value.var = std::move(a_value);
		_varType = RawType::kVar;

		REX::Assert(IsVar());
	}

	void Variable::SetVar(SharedVariant a_value) noexcept
	{
		reset();

		_value.var = a_value ? std::make_unique<Variable>(*a_value) : nullptr;
		_varType = RawType::kVar;

		REX::Assert(IsVar());
	}

	void Variable::SetStruct(BSTSmartPointer<Struct> a_value) noexcept
	{
		reset();

		if (!a_value) {
			return;
		}

		_varType = a_value->type.get();
		_value.structure = std::move(a_value);

		REX::Assert(IsStruct());
	}

	void Variable::SetArray(BSTSmartPointer<Array> a_value) noexcept
	{
		reset();

		if (!a_value) {
			return;
		}

		_varType = a_value->elementType;
		_value.array = std::move(a_value);
		_varType.SetIsArray(true);

		REX::Assert(IsArray());
	}

	TypeInfo& Variable::GetTypeInfo() noexcept
	{
		return _varType;
	}

	const TypeInfo& Variable::GetTypeInfo() const noexcept
	{
		return _varType;
	}

	TypeInfo::RawType Variable::GetRawType() const noexcept
	{
		return _varType.GetRawType();
	}

	TypeInfo::RawType Variable::GetDeepRawType() const noexcept
	{
		const auto rawType = GetRawType();
		if (rawType != TypeInfo::RawType::kVar) {
			return rawType;
		}

		const auto* value = GetVar();
		if (!value) {
			return TypeInfo::RawType::kVar;
		}

		return value->GetRawType();
	}

	IComplexType* Variable::GetComplexType() const noexcept
	{
		return _varType.GetComplexType();
	}

	void Variable::SetTypeInfo(const TypeInfo& a_type) noexcept
	{
		_varType = a_type;
	}

	void Variable::SetRawType(TypeInfo::RawType a_type) noexcept
	{
		_varType = a_type;
	}

	void Variable::SetComplexType(IComplexType* a_type) noexcept
	{
		_varType = a_type;
	}

	bool Variable::TryAssign(const Variable& a_rhs) noexcept
	{
		if (this == std::addressof(a_rhs)) {
			return true;
		}

		if (_varType.IsAssignable(a_rhs._varType)) {
			Assign(a_rhs);
			return true;
		}

		if (!IsVar()) {
			return false;
		}

		if (a_rhs.IsNone()) {
			SetVar(UniqueVariant());
			return true;
		}

		SetVar(CreateVariant(a_rhs));
		return true;
	}

	bool Variable::TryAssign(Variable&& a_rhs) noexcept
	{
		if (this == std::addressof(a_rhs)) {
			return true;
		}

		if (_varType.IsAssignable(a_rhs._varType)) {
			Assign(std::move(a_rhs));
			return true;
		}

		if (!IsVar()) {
			return false;
		}

		if (a_rhs.IsNone()) {
			SetVar(UniqueVariant());
			return true;
		}

		SetVar(CreateVariant(std::move(a_rhs)));
		return true;
	}

	Variable Variable::Clone([[maybe_unused]] IVirtualMachine& a_vm) const noexcept
	{
		auto result = Variable();
		result.Assign(*this);
		return result;
	}

	Variable Variable::DeepClone(IVirtualMachine& a_vm) const
	{
		switch (GetRawType()) {
			case RawType::kNone: {
				return {};
			}
			case RawType::kObject: {
				const auto value = GetObject();
				if (!value) {
					return {};
				}

				return Variable(value->DeepClone(a_vm));
			}
			case RawType::kString: {
				return Variable(GetString());
			}
			case RawType::kInt: {
				return Variable(GetInt());
			}
			case RawType::kFloat: {
				return Variable(GetFloat());
			}
			case RawType::kBool: {
				return Variable(GetBool());
			}
			case RawType::kVar: {
				const auto* value = GetVar();
				if (!value) {
					return Variable(UniqueVariant());
				}

				return Variable(CreateVariant(value->DeepClone(a_vm)));
			}
			case RawType::kStruct: {
				const auto value = GetStruct();
				if (!value) {
					return {};
				}

				return Variable(value->DeepClone(a_vm));
			}
			case RawType::kArrayObject:
			case RawType::kArrayString:
			case RawType::kArrayInt:
			case RawType::kArrayFloat:
			case RawType::kArrayBool:
			case RawType::kArrayVar:
			case RawType::kArrayStruct: {
				const auto value = GetArray();
				if (!value) {
					return {};
				}

				return Variable(value->DeepClone(a_vm));
			}
			default: {
				std::unreachable();
			}
		}
	}

	std::string Variable::ToString() const
	{
		switch (GetRawType()) {
			case RawType::kNone: {
				return std::string(NONE_STRING);
			}
			case RawType::kObject: {
				const auto value = GetObject();
				if (!value) {
					return std::string(NONE_STRING);
				}

				return value->ToString();
			}
			case RawType::kString: {
				const auto string = GetString();
				return std::string(string);
			}
			case RawType::kInt: {
				auto string = REX::ToString(GetInt());
				if (!string) {
					return std::string(NONE_STRING);
				}

				return *std::move(string);
			}
			case RawType::kFloat: {
				auto string = REX::ToString(GetFloat());
				if (!string) {
					return std::string(NONE_STRING);
				}

				return *std::move(string);
			}
			case RawType::kBool: {
				constexpr auto BOOL_FORMAT = REX::EnumSet(REX::BoolFormat::kTrueFalse, REX::BoolFormat::kCapitalize);

				auto string = REX::ToString(GetBool(), BOOL_FORMAT.get());
				if (!string) {
					return std::string(NONE_STRING);
				}

				return *std::move(string);
			}
			case RawType::kVar: {
				const auto* value = GetVar();
				if (!value) {
					return std::string(NONE_STRING);
				}

				return value->ToString();
			}
			case RawType::kStruct: {
				const auto structure = GetStruct();
				if (!structure) {
					return std::string(NONE_STRING);
				}

				return structure->ToString();
			}
			case RawType::kArrayObject:
			case RawType::kArrayString:
			case RawType::kArrayInt:
			case RawType::kArrayFloat:
			case RawType::kArrayBool:
			case RawType::kArrayVar:
			case RawType::kArrayStruct: {
				const auto value = GetArray();
				if (!value) {
					return std::string(NONE_STRING);
				}

				return value->ToString();
			}
			default: {
				std::unreachable();
			}
		}
	}

	void Variable::swap(Variable& a_other) noexcept
	{
		if (this == std::addressof(a_other)) {
			return;
		}

		std::swap(_varType, a_other._varType);
		std::swap(_value, a_other._value);
	}

	void Variable::reset() noexcept
	{
		switch (GetRawType()) {
			case RawType::kNone: {
				break;
			}
			case RawType::kObject: {
				_value.object.reset();
				break;
			}
			case RawType::kString: {
				_value.string.clear();
				break;
			}
			case RawType::kInt:
			case RawType::kFloat:
			case RawType::kBool: {
				break;
			}
			case RawType::kVar: {
				_value.var.reset();
				break;
			}
			case RawType::kStruct: {
				_value.structure.reset();
				break;
			}
			case RawType::kArrayObject:
			case RawType::kArrayString:
			case RawType::kArrayInt:
			case RawType::kArrayFloat:
			case RawType::kArrayBool:
			case RawType::kArrayVar:
			case RawType::kArrayStruct: {
				_value.array.reset();
				break;
			}
			default: {
				std::unreachable();
			}
		}

		_varType = RawType::kNone;
		_value.none = nullptr;

		REX::Assert(IsNone());
	}

	void Variable::Assign(const Variable& a_other) noexcept
	{
		switch (a_other.GetRawType()) {
			case RawType::kNone: {
				SetNone();
				break;
			}
			case RawType::kObject: {
				SetObject(a_other.GetObject());
				break;
			}
			case RawType::kString: {
				SetString(a_other.GetString());
				break;
			}
			case RawType::kInt: {
				SetInt(a_other.GetInt());
				break;
			}
			case RawType::kFloat: {
				SetFloat(a_other.GetFloat());
				break;
			}
			case RawType::kBool: {
				SetBool(a_other.GetBool());
				break;
			}
			case RawType::kVar: {
				const auto* value = a_other.GetVar();
				if (!value) {
					SetVar(UniqueVariant());
					break;
				}

				SetVar(CreateVariant(*value));
				break;
			}
			case RawType::kStruct: {
				SetStruct(a_other.GetStruct());
				break;
			}
			case RawType::kArrayObject:
			case RawType::kArrayString:
			case RawType::kArrayInt:
			case RawType::kArrayFloat:
			case RawType::kArrayBool:
			case RawType::kArrayVar:
			case RawType::kArrayStruct: {
				SetArray(a_other.GetArray());
				break;
			}
			default: {
				std::unreachable();
			}
		}

		_varType = a_other._varType;
	}

	void Variable::Assign(Variable&& a_other) noexcept // NOLINT(cppcoreguidelines-rvalue-reference-param-not-moved)
	{
		switch (a_other.GetRawType()) {
			case RawType::kNone: {
				SetNone();
				break;
			}
			case RawType::kObject: {
				SetObject(std::move(a_other._value.object));
				break;
			}
			case RawType::kString: {
				SetString(std::move(a_other._value.string));
				break;
			}
			case RawType::kInt: {
				SetInt(a_other._value.int32);
				break;
			}
			case RawType::kFloat: {
				SetFloat(a_other._value.float32);
				break;
			}
			case RawType::kBool: {
				SetBool(a_other._value.boolean);
				break;
			}
			case RawType::kVar: {
				SetVar(std::move(a_other._value.var));
				break;
			}
			case RawType::kStruct: {
				SetStruct(std::move(a_other._value.structure));
				break;
			}
			case RawType::kArrayObject:
			case RawType::kArrayString:
			case RawType::kArrayInt:
			case RawType::kArrayFloat:
			case RawType::kArrayBool:
			case RawType::kArrayVar:
			case RawType::kArrayStruct: {
				SetArray(std::move(a_other._value.array));
				break;
			}
			default: {
				std::unreachable();
			}
		}

		_varType = std::move(a_other._varType);
	}

	Variable::ValueUnion::ValueUnion() noexcept
	{
	}

	Variable::ValueUnion::~ValueUnion() noexcept
	{
	}

	Variable::ValueUnion::ValueUnion(ValueUnion&& a_rhs) noexcept
		: none(std::exchange(a_rhs.none, nullptr))
	{
	}

	Variable::ValueUnion& Variable::ValueUnion::operator=(ValueUnion&& a_rhs) noexcept
	{
		if (this == std::addressof(a_rhs)) {
			return *this;
		}

		none = std::exchange(a_rhs.none, nullptr);
		return *this;
	}

	void swap(Variable& a_lhs, Variable& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}

	Variable GetDefaultVariable(const TypeInfo& a_typeInfo)
	{
		auto value = Variable();

		switch (a_typeInfo.GetRawType()) {
			case TypeInfo::RawType::kNone: {
				value.SetNone();
				break;
			}
			case TypeInfo::RawType::kBool: {
				value.SetBool(false);
				break;
			}
			case TypeInfo::RawType::kInt: {
				value.SetInt(0);
				break;
			}
			case TypeInfo::RawType::kFloat: {
				value.SetFloat(0.0_f32);
				break;
			}
			case TypeInfo::RawType::kString: {
				value.SetString(BSFixedString());
				break;
			}
			case TypeInfo::RawType::kObject: {
				value.SetObject(BSTSmartPointer<Object>());
				break;
			}
			case TypeInfo::RawType::kStruct: {
				value.SetStruct(BSTSmartPointer<Struct>());
				break;
			}
			case TypeInfo::RawType::kVar: {
				value.SetVar(UniqueVariant());
				break;
			}
			case TypeInfo::RawType::kArrayBool:
			case TypeInfo::RawType::kArrayInt:
			case TypeInfo::RawType::kArrayFloat:
			case TypeInfo::RawType::kArrayString:
			case TypeInfo::RawType::kArrayObject:
			case TypeInfo::RawType::kArrayStruct:
			case TypeInfo::RawType::kArrayVar: {
				value.SetArray(BSTSmartPointer<Array>());
				break;
			}
			default: {
				std::unreachable();
			}
		}

		return value;
	}

	Variable UnwrapVariant(UniqueVariant a_value)
	{
		if (!a_value) {
			return NONE_VARIABLE;
		}

		return Variable(std::move(a_value));
	}

	const Variable& UnwrapVariant(const Variable* a_value) noexcept
	{
		if (!a_value) {
			return NONE_VARIABLE;
		}

		return *a_value;
	}
}

namespace std
{
	std::size_t hash<RE::BSScript::Variable>::operator()(const RE::BSScript::Variable& a_key) const noexcept
	{
		using RawType = RE::BSScript::TypeInfo::RawType;

		const auto rawType = a_key.GetRawType();
		switch (rawType) {
			case RawType::kNone: {
				return REX::HashCombine(rawType, a_key.GetNone());
			}
			case RawType::kObject: {
				return REX::HashCombine(rawType, a_key.GetObject());
			}
			case RawType::kString: {
				return REX::HashCombine(rawType, a_key.GetString());
			}
			case RawType::kInt: {
				return REX::HashCombine(rawType, a_key.GetInt());
			}
			case RawType::kFloat: {
				return REX::HashCombine(rawType, a_key.GetFloat());
			}
			case RawType::kBool: {
				return REX::HashCombine(rawType, a_key.GetBool());
			}
			case RawType::kVar: {
				const auto* value = a_key.GetVar();
				if (!value) {
					return REX::HashCombine(rawType, nullptr);
				}

				return REX::HashCombine(rawType, *value);
			}
			case RawType::kStruct:
				return REX::HashCombine(rawType, a_key.GetStruct());
			case RawType::kArrayObject:
			case RawType::kArrayString:
			case RawType::kArrayInt:
			case RawType::kArrayFloat:
			case RawType::kArrayBool:
			case RawType::kArrayVar:
			case RawType::kArrayStruct: {
				return REX::HashCombine(rawType, a_key.GetArray());
			}
			default: {
				std::unreachable();
			}
		}
	}
}
