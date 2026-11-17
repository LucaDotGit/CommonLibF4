#include "RE/B/BSScript_Variable.hpp"

#include "RE/B/BSScript_Array.hpp"
#include "RE/B/BSScript_Object.hpp"
#include "RE/B/BSScript_ObjectTypeInfo.hpp" // IWYU pragma: keep
#include "RE/B/BSScript_Struct.hpp"
#include "RE/B/BSScript_StructTypeInfo.hpp" // IWYU pragma: keep

namespace RE::BSScript
{
	Variable::~Variable() noexcept
	{
		reset();
	}

	Variable::Variable(const Variable& a_rhs)
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
		SetVariant(std::move(a_value));
	}

	Variable::Variable(SharedVariant a_value)
	{
		SetVariant(a_value);
	}

	Variable::Variable(BSTSmartPointer<Struct> a_value) noexcept
	{
		SetStruct(std::move(a_value));
	}

	Variable::Variable(BSTSmartPointer<Array> a_value) noexcept
	{
		SetArray(std::move(a_value));
	}

	auto Variable::operator=(const Variable& a_rhs) -> Variable&
	{
		if (this == std::addressof(a_rhs)) {
			return *this;
		}

		Assign(a_rhs);
		return *this;
	}

	auto Variable::operator=(Variable&& a_rhs) noexcept -> Variable&
	{
		if (this == std::addressof(a_rhs)) {
			return *this;
		}

		Assign(std::move(a_rhs));
		return *this;
	}

	auto Variable::operator=(std::nullptr_t) noexcept -> Variable&
	{
		SetNone();
		return *this;
	}

	auto Variable::operator=(BSTSmartPointer<Object> a_value) noexcept -> Variable&
	{
		SetObject(std::move(a_value));
		return *this;
	}

	auto Variable::operator=(BSFixedString a_value) noexcept -> Variable&
	{
		SetString(std::move(a_value));
		return *this;
	}

	auto Variable::operator=(std::int32_t a_value) noexcept -> Variable&
	{
		SetInt(a_value);
		return *this;
	}

	auto Variable::operator=(std::uint32_t a_value) noexcept -> Variable&
	{
		SetUInt(a_value);
		return *this;
	}

	auto Variable::operator=(REX::Float32 a_value) noexcept -> Variable&
	{
		SetFloat(a_value);
		return *this;
	}

	auto Variable::operator=(bool a_value) noexcept -> Variable&
	{
		SetBool(a_value);
		return *this;
	}

	auto Variable::operator=(UniqueVariant a_value) noexcept -> Variable&
	{
		SetVariant(std::move(a_value));
		return *this;
	}

	auto Variable::operator=(SharedVariant a_value) -> Variable&
	{
		SetVariant(a_value);
		return *this;
	}

	auto Variable::operator=(BSTSmartPointer<Struct> a_value) noexcept -> Variable&
	{
		SetStruct(std::move(a_value));
		return *this;
	}

	auto Variable::operator=(BSTSmartPointer<Array> a_value) noexcept -> Variable&
	{
		SetArray(std::move(a_value));
		return *this;
	}

	auto Variable::operator==(const Variable& a_rhs) const noexcept -> bool
	{
		return Equals(a_rhs);
	}

	auto Variable::operator<=>(const Variable& a_rhs) const noexcept -> std::partial_ordering
	{
		return Compare(a_rhs);
	}

	auto Variable::IsNone() const noexcept -> bool
	{
		return _varType.IsNone();
	}

	auto Variable::IsObject() const noexcept -> bool
	{
		return _varType.IsObject();
	}

	auto Variable::IsString() const noexcept -> bool
	{
		return _varType.IsString();
	}

	auto Variable::IsInt() const noexcept -> bool
	{
		return _varType.IsInt();
	}

	auto Variable::IsUInt() const noexcept -> bool
	{
		return _varType.IsUInt();
	}

	auto Variable::IsFloat() const noexcept -> bool
	{
		return _varType.IsFloat();
	}

	auto Variable::IsBool() const noexcept -> bool
	{
		return _varType.IsBool();
	}

	auto Variable::IsVariant() const noexcept -> bool
	{
		return _varType.IsVariant();
	}

	auto Variable::IsStruct() const noexcept -> bool
	{
		return _varType.IsStruct();
	}

	auto Variable::IsObjectArray() const noexcept -> bool
	{
		return _varType.IsObjectArray();
	}

	auto Variable::IsStringArray() const noexcept -> bool
	{
		return _varType.IsStringArray();
	}

	auto Variable::IsIntArray() const noexcept -> bool
	{
		return _varType.IsIntArray();
	}

	auto Variable::IsUIntArray() const noexcept -> bool
	{
		return _varType.IsUIntArray();
	}

	auto Variable::IsFloatArray() const noexcept -> bool
	{
		return _varType.IsFloatArray();
	}

	auto Variable::IsBoolArray() const noexcept -> bool
	{
		return _varType.IsBoolArray();
	}

	auto Variable::IsVariantArray() const noexcept -> bool
	{
		return _varType.IsVariantArray();
	}

	auto Variable::IsStructArray() const noexcept -> bool
	{
		return _varType.IsStructArray();
	}

	auto Variable::IsArray() const noexcept -> bool
	{
		return _varType.IsArray();
	}

	auto Variable::IsComplex() const noexcept -> bool
	{
		return _varType.IsComplex();
	}

	auto Variable::IsComplexArray() const noexcept -> bool
	{
		return _varType.IsComplexArray();
	}

	auto Variable::IsNoneAssignable() const noexcept -> bool
	{
		return _varType.IsNoneAssignable();
	}

	auto Variable::Equals(const Variable& a_rhs) const noexcept -> bool
	{
		if (this == std::addressof(a_rhs)) {
			return true;
		}

		const auto leftRawType = GetRawType();
		const auto rightRawType = a_rhs.GetRawType();

		const auto isLeftVar = leftRawType == RawType::Var;
		const auto isRightVar = rightRawType == RawType::Var;

		if (isLeftVar && isRightVar) {
			const auto* leftValue = GetVariant();
			const auto* rightValue = a_rhs.GetVariant();

			if (leftValue && rightValue) {
				return *leftValue == *rightValue;
			}

			return leftValue == rightValue;
		}

		if (isLeftVar) {
			const auto* leftValue = GetVariant();
			if (!leftValue) {
				return false;
			}

			return *leftValue == a_rhs;
		}

		if (isRightVar) {
			const auto* rightValue = a_rhs.GetVariant();
			if (!rightValue) {
				return false;
			}

			return *this == *rightValue;
		}

		if (leftRawType != rightRawType) {
			return false;
		}

		switch (leftRawType) {
			case RawType::None: {
				return true;
			}
			case RawType::Object: {
				return GetObject() == a_rhs.GetObject();
			}
			case RawType::String: {
				return GetString() == a_rhs.GetString();
			}
			case RawType::Int: {
				return GetInt() == a_rhs.GetInt();
			}
			case RawType::Float: {
				return GetFloat() == a_rhs.GetFloat();
			}
			case RawType::Bool: {
				return GetBool() == a_rhs.GetBool();
			}
			case RawType::Var: {
				const auto* leftValue = GetVariant();
				const auto* rightValue = a_rhs.GetVariant();

				if (leftValue && rightValue) {
					return leftValue->Equals(*rightValue);
				}

				return leftValue == rightValue;
			}
			case RawType::Struct: {
				return GetStruct() == a_rhs.GetStruct();
			}
			case RawType::ArrayObject:
			case RawType::ArrayString:
			case RawType::ArrayInt:
			case RawType::ArrayFloat:
			case RawType::ArrayBool:
			case RawType::ArrayVar:
			case RawType::ArrayStruct: {
				return GetArray() == a_rhs.GetArray();
			}
			default: {
				std::unreachable();
			}
		}
	}

	auto Variable::RefEquals(const Variable& a_rhs) const noexcept -> bool
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
			case RawType::None: {
				return true;
			}
			case RawType::Object: {
				return GetObject() == a_rhs.GetObject();
			}
			case RawType::String: {
				return GetString() == a_rhs.GetString();
			}
			case RawType::Int:
			case RawType::Float:
			case RawType::Bool: {
				return false;
			}
			case RawType::Struct: {
				return GetStruct() == a_rhs.GetStruct();
			}
			case RawType::Var: {
				const auto* leftValue = GetVariant();
				const auto* rightValue = a_rhs.GetVariant();

				if (leftValue && rightValue) {
					return leftValue->RefEquals(*rightValue);
				}

				return leftValue == rightValue;
			}
			case RawType::ArrayObject:
			case RawType::ArrayString:
			case RawType::ArrayInt:
			case RawType::ArrayFloat:
			case RawType::ArrayBool:
			case RawType::ArrayVar:
			case RawType::ArrayStruct: {
				return GetArray() == a_rhs.GetArray();
			}
			default: {
				std::unreachable();
			}
		}
	}

	auto Variable::DeepEquals(const Variable& a_rhs) const noexcept -> bool
	{
		if (this == std::addressof(a_rhs)) {
			return true;
		}

		const auto leftRawType = GetRawType();
		const auto rightRawType = a_rhs.GetRawType();

		const auto isLeftVar = leftRawType == RawType::Var;
		const auto isRightVar = rightRawType == RawType::Var;

		if (isLeftVar && isRightVar) {
			const auto* leftValue = GetVariant();
			const auto* rightValue = a_rhs.GetVariant();

			if (leftValue && rightValue) {
				return leftValue->DeepEquals(*rightValue);
			}

			return leftValue == rightValue;
		}

		if (isLeftVar) {
			const auto* leftValue = GetVariant();
			if (!leftValue) {
				return false;
			}

			return leftValue->DeepEquals(a_rhs);
		}

		if (isRightVar) {
			const auto* rightValue = a_rhs.GetVariant();
			if (!rightValue) {
				return false;
			}

			return rightValue->DeepEquals(*this);
		}

		if (leftRawType != rightRawType && leftRawType != RawType::ArrayVar && rightRawType != RawType::ArrayVar) {
			return false;
		}

		switch (leftRawType) {
			case RawType::None: {
				return true;
			}
			case RawType::Object: {
				const auto leftValue = GetObject();
				const auto rightValue = a_rhs.GetObject();

				if (leftValue && rightValue) {
					return leftValue->DeepEquals(*rightValue);
				}

				return leftValue == rightValue;
			}
			case RawType::String: {
				return GetString() == a_rhs.GetString();
			}
			case RawType::Int: {
				return GetInt() == a_rhs.GetInt();
			}
			case RawType::Float: {
				return GetFloat() == a_rhs.GetFloat();
			}
			case RawType::Bool: {
				return GetBool() == a_rhs.GetBool();
			}
			case RawType::Struct: {
				const auto leftValue = GetStruct();
				const auto rightValue = a_rhs.GetStruct();

				if (leftValue && rightValue) {
					return leftValue->DeepEquals(*rightValue);
				}

				return leftValue == rightValue;
			}
			case RawType::Var: {
				const auto* leftValue = GetVariant();
				const auto* rightValue = a_rhs.GetVariant();

				if (leftValue && rightValue) {
					return leftValue->DeepEquals(*rightValue);
				}

				return leftValue == rightValue;
			}
			case RawType::ArrayObject:
			case RawType::ArrayString:
			case RawType::ArrayInt:
			case RawType::ArrayFloat:
			case RawType::ArrayBool:
			case RawType::ArrayVar:
			case RawType::ArrayStruct: {
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

	auto Variable::Compare(const Variable& a_rhs) const noexcept -> std::partial_ordering
	{
		if (this == std::addressof(a_rhs)) {
			return std::partial_ordering::equivalent;
		}

		const auto leftRawType = GetRawType();
		const auto rightRawType = a_rhs.GetRawType();

		const auto isLeftVar = leftRawType == RawType::Var;
		const auto isRightVar = rightRawType == RawType::Var;

		if (isLeftVar && isRightVar) {
			const auto* leftValue = GetVariant();
			const auto* rightValue = a_rhs.GetVariant();

			if (leftValue && rightValue) {
				return leftValue->Compare(*rightValue);
			}

			return leftValue <=> rightValue;
		}

		if (isLeftVar) {
			const auto* leftValue = GetVariant();
			if (!leftValue) {
				return std::partial_ordering::less;
			}

			return leftValue->Compare(a_rhs);
		}

		if (isRightVar) {
			const auto* rightValue = a_rhs.GetVariant();
			if (!rightValue) {
				return std::partial_ordering::greater;
			}

			return rightValue->Compare(*this);
		}

		if (leftRawType != rightRawType) {
			return leftRawType <=> rightRawType;
		}

		switch (leftRawType) {
			case RawType::None: {
				return std::partial_ordering::equivalent;
			}
			case RawType::Object: {
				return GetObject() <=> a_rhs.GetObject();
			}
			case RawType::String: {
				return GetString() <=> a_rhs.GetString();
			}
			case RawType::Int: {
				return GetInt() <=> a_rhs.GetInt();
			}
			case RawType::Float: {
				return GetFloat() <=> a_rhs.GetFloat();
			}
			case RawType::Bool: {
				return GetBool() <=> a_rhs.GetBool();
			}
			case RawType::Var: {
				const auto* leftValue = GetVariant();
				const auto* rightValue = a_rhs.GetVariant();

				if (leftValue && rightValue) {
					return leftValue->Compare(*rightValue);
				}

				return leftValue <=> rightValue;
			}
			case RawType::Struct: {
				return GetStruct() <=> a_rhs.GetStruct();
			}
			case RawType::ArrayObject:
			case RawType::ArrayString:
			case RawType::ArrayInt:
			case RawType::ArrayFloat:
			case RawType::ArrayBool:
			case RawType::ArrayVar:
			case RawType::ArrayStruct: {
				return GetArray() <=> a_rhs.GetArray();
			}
			default: {
				std::unreachable();
			}
		}
	}

	auto Variable::RefCompare(const Variable& a_rhs) const noexcept -> std::partial_ordering
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
			case RawType::None: {
				return std::partial_ordering::equivalent;
			}
			case RawType::Object: {
				return GetObject() <=> a_rhs.GetObject();
			}
			case RawType::String: {
				return GetString() <=> a_rhs.GetString();
			}
			case RawType::Int:
			case RawType::Float:
			case RawType::Bool: {
				return std::partial_ordering::unordered;
			}
			case RawType::Struct: {
				return GetStruct() <=> a_rhs.GetStruct();
			}
			case RawType::Var: {
				const auto* leftValue = GetVariant();
				const auto* rightValue = a_rhs.GetVariant();

				if (leftValue && rightValue) {
					return leftValue->RefCompare(*rightValue);
				}

				return leftValue <=> rightValue;
			}
			case RawType::ArrayObject:
			case RawType::ArrayString:
			case RawType::ArrayInt:
			case RawType::ArrayFloat:
			case RawType::ArrayBool:
			case RawType::ArrayVar:
			case RawType::ArrayStruct: {
				return GetArray() <=> a_rhs.GetArray();
			}
			default: {
				std::unreachable();
			}
		}
	}

	auto Variable::DeepCompare(const Variable& a_rhs) const noexcept -> std::partial_ordering
	{
		if (this == std::addressof(a_rhs)) {
			return std::partial_ordering::equivalent;
		}

		const auto leftRawType = GetRawType();
		const auto rightRawType = a_rhs.GetRawType();

		const auto isLeftVar = leftRawType == RawType::Var;
		const auto isRightVar = rightRawType == RawType::Var;

		if (isLeftVar && isRightVar) {
			const auto* leftValue = GetVariant();
			const auto* rightValue = a_rhs.GetVariant();

			if (leftValue && rightValue) {
				return leftValue->DeepCompare(*rightValue);
			}

			return leftValue <=> rightValue;
		}

		if (isLeftVar) {
			const auto* leftValue = GetVariant();
			if (!leftValue) {
				return std::partial_ordering::less;
			}

			return leftValue->DeepCompare(a_rhs);
		}

		if (isRightVar) {
			const auto* rightValue = a_rhs.GetVariant();
			if (!rightValue) {
				return std::partial_ordering::greater;
			}

			return rightValue->DeepCompare(*this);
		}

		if (leftRawType != rightRawType && leftRawType != RawType::ArrayVar && rightRawType != RawType::ArrayVar) {
			return leftRawType <=> rightRawType;
		}

		switch (leftRawType) {
			case RawType::None: {
				return std::partial_ordering::equivalent;
			}
			case RawType::Object: {
				const auto leftValue = GetObject();
				const auto rightValue = a_rhs.GetObject();

				if (leftValue && rightValue) {
					return leftValue->DeepCompare(*rightValue);
				}

				return leftValue <=> rightValue;
			}
			case RawType::String: {
				return GetString() <=> a_rhs.GetString();
			}
			case RawType::Int: {
				return GetInt() <=> a_rhs.GetInt();
			}
			case RawType::Float: {
				return GetFloat() <=> a_rhs.GetFloat();
			}
			case RawType::Bool: {
				return GetBool() <=> a_rhs.GetBool();
			}
			case RawType::Struct: {
				const auto leftValue = GetStruct();
				const auto rightValue = a_rhs.GetStruct();

				if (leftValue && rightValue) {
					return leftValue->DeepCompare(*rightValue);
				}

				return leftValue <=> rightValue;
			}
			case RawType::Var: {
				const auto* leftValue = GetVariant();
				const auto* rightValue = a_rhs.GetVariant();

				if (leftValue && rightValue) {
					return leftValue->DeepCompare(*rightValue);
				}

				return leftValue <=> rightValue;
			}
			case RawType::ArrayObject:
			case RawType::ArrayString:
			case RawType::ArrayInt:
			case RawType::ArrayFloat:
			case RawType::ArrayBool:
			case RawType::ArrayVar:
			case RawType::ArrayStruct: {
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

	auto Variable::GetNone() const noexcept -> std::nullptr_t
	{
		REX::Assert(IsNone());
		REX::Assert(_value.none == nullptr);
		return nullptr;
	}

	auto Variable::GetObject() const noexcept -> BSTSmartPointer<Object>
	{
		REX::Assert(IsObject());
		return _value.object;
	}

	auto Variable::GetString() const noexcept -> BSFixedString
	{
		REX::Assert(IsString());
		return _value.string;
	}

	auto Variable::GetInt() const noexcept -> std::int32_t
	{
		REX::Assert(IsInt());
		return _value.int32;
	}

	auto Variable::GetUInt() const noexcept -> std::uint32_t
	{
		REX::Assert(IsUInt());
		return _value.uint32;
	}

	auto Variable::GetFloat() const noexcept -> REX::Float32
	{
		REX::Assert(IsFloat());
		return _value.float32;
	}

	auto Variable::GetBool() const noexcept -> bool
	{
		REX::Assert(IsBool());
		return _value.boolean;
	}

	auto Variable::GetVariant() const noexcept -> SharedVariant
	{
		REX::Assert(IsVariant());
		return _value.variant.get();
	}

	auto Variable::GetStruct() const noexcept -> BSTSmartPointer<Struct>
	{
		REX::Assert(IsStruct());
		return _value.structure;
	}

	auto Variable::GetArray() const noexcept -> BSTSmartPointer<Array>
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
		_varType = RawType::String;

		REX::Assert(IsString());
	}

	void Variable::SetInt(std::int32_t a_value) noexcept
	{
		reset();

		_value.int32 = a_value;
		_varType = RawType::Int;

		REX::Assert(IsInt());
	}

	void Variable::SetUInt(std::uint32_t a_value) noexcept
	{
		reset();

		_value.uint32 = a_value;
		_varType = RawType::Int;

		REX::Assert(IsUInt());
	}

	void Variable::SetFloat(REX::Float32 a_value) noexcept
	{
		reset();

		_value.float32 = a_value;
		_varType = RawType::Float;

		REX::Assert(IsFloat());
	}

	void Variable::SetBool(bool a_value) noexcept
	{
		reset();

		_value.boolean = a_value;
		_varType = RawType::Bool;

		REX::Assert(IsBool());
	}

	void Variable::SetVariant(UniqueVariant a_value) noexcept
	{
		reset();

		_value.variant = std::move(a_value);
		_varType = RawType::Var;

		REX::Assert(IsVariant());
	}

	void Variable::SetVariant(SharedVariant a_value)
	{
		reset();

		_value.variant = a_value ? std::make_unique<Variable>(*a_value) : nullptr;
		_varType = RawType::Var;

		REX::Assert(IsVariant());
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

	auto Variable::GetTypeInfo() noexcept -> TypeInfo&
	{
		return _varType;
	}

	auto Variable::GetTypeInfo() const noexcept -> const TypeInfo&
	{
		return _varType;
	}

	auto Variable::GetRawType() const noexcept -> TypeInfo::RawType
	{
		return _varType.GetRawType();
	}

	auto Variable::GetDeepRawType() const noexcept -> TypeInfo::RawType
	{
		const auto rawType = GetRawType();
		if (rawType != TypeInfo::RawType::Var) {
			return rawType;
		}

		const auto* value = GetVariant();
		if (!value) {
			return TypeInfo::RawType::Var;
		}

		return value->GetRawType();
	}

	auto Variable::GetComplexType() const noexcept -> BSTSmartPointer<IComplexType>
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

	void Variable::SetComplexType(const BSTSmartPointer<IComplexType>& a_type) noexcept
	{
		_varType = a_type;
	}

	auto Variable::TryAssign(const Variable& a_rhs) noexcept -> bool
	{
		if (this == std::addressof(a_rhs)) {
			return true;
		}

		if (_varType.IsAssignable(a_rhs._varType)) {
			Assign(a_rhs);
			return true;
		}

		if (!IsVariant()) {
			return false;
		}

		if (a_rhs.IsNone()) {
			SetVariant(UniqueVariant());
			return true;
		}

		SetVariant(CreateVariant(a_rhs));
		return true;
	}

	auto Variable::TryAssign(Variable&& a_rhs) noexcept -> bool
	{
		if (this == std::addressof(a_rhs)) {
			return true;
		}

		if (_varType.IsAssignable(a_rhs._varType)) {
			Assign(std::move(a_rhs));
			return true;
		}

		if (!IsVariant()) {
			return false;
		}

		if (a_rhs.IsNone()) {
			SetVariant(UniqueVariant());
			return true;
		}

		SetVariant(CreateVariant(std::move(a_rhs)));
		return true;
	}

	auto Variable::Clone([[maybe_unused]] IVirtualMachine& a_vm) const noexcept -> Variable
	{
		auto result = Variable();
		result.Assign(*this);
		return result;
	}

	auto Variable::DeepClone(IVirtualMachine& a_vm) const -> Variable
	{
		switch (GetRawType()) {
			case RawType::None: {
				return {};
			}
			case RawType::Object: {
				const auto value = GetObject();
				if (!value) {
					return {};
				}

				return Variable(value->DeepClone(a_vm));
			}
			case RawType::String: {
				return Variable(GetString());
			}
			case RawType::Int: {
				return Variable(GetInt());
			}
			case RawType::Float: {
				return Variable(GetFloat());
			}
			case RawType::Bool: {
				return Variable(GetBool());
			}
			case RawType::Var: {
				const auto* value = GetVariant();
				if (!value) {
					return Variable(UniqueVariant());
				}

				return Variable(CreateVariant(value->DeepClone(a_vm)));
			}
			case RawType::Struct: {
				const auto value = GetStruct();
				if (!value) {
					return {};
				}

				return Variable(value->DeepClone(a_vm));
			}
			case RawType::ArrayObject:
			case RawType::ArrayString:
			case RawType::ArrayInt:
			case RawType::ArrayFloat:
			case RawType::ArrayBool:
			case RawType::ArrayVar:
			case RawType::ArrayStruct: {
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

	auto Variable::ToString() const -> std::string
	{
		switch (GetRawType()) {
			case RawType::None: {
				return std::string(NONE_STRING);
			}
			case RawType::Object: {
				const auto value = GetObject();
				if (!value) {
					return std::string(NONE_STRING);
				}

				return value->ToString();
			}
			case RawType::String: {
				const auto result = GetString();
				return std::string(result);
			}
			case RawType::Int: {
				auto result = REX::ToString(GetInt());
				if (!result.has_value()) [[unlikely]] {
					REX::Assert(false);
					return std::string(NONE_STRING);
				}

				return std::move(result).value();
			}
			case RawType::Float: {
				auto result = REX::ToString(GetFloat());
				if (!result.has_value()) [[unlikely]] {
					REX::Assert(false);
					return std::string(NONE_STRING);
				}

				return std::move(result).value();
			}
			case RawType::Bool: {
				constexpr auto BOOL_FORMAT = REX::EnumSet(REX::BoolFormat::TrueFalse, REX::BoolFormat::Capitalize);

				auto result = REX::ToString(GetBool(), BOOL_FORMAT.get());
				if (!result.has_value()) [[unlikely]] {
					REX::Assert(false);
					return std::string(NONE_STRING);
				}

				return std::move(result).value();
			}
			case RawType::Var: {
				const auto* value = GetVariant();
				if (!value) {
					return std::string(NONE_STRING);
				}

				return value->ToString();
			}
			case RawType::Struct: {
				const auto value = GetStruct();
				if (!value) {
					return std::string(NONE_STRING);
				}

				return value->ToString();
			}
			case RawType::ArrayObject:
			case RawType::ArrayString:
			case RawType::ArrayInt:
			case RawType::ArrayFloat:
			case RawType::ArrayBool:
			case RawType::ArrayVar:
			case RawType::ArrayStruct: {
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
			case RawType::None: {
				break;
			}
			case RawType::Object: {
				_value.object.reset();
				break;
			}
			case RawType::String: {
				_value.string.clear();
				break;
			}
			case RawType::Int:
			case RawType::Float:
			case RawType::Bool: {
				break;
			}
			case RawType::Var: {
				_value.variant.reset();
				break;
			}
			case RawType::Struct: {
				_value.structure.reset();
				break;
			}
			case RawType::ArrayObject:
			case RawType::ArrayString:
			case RawType::ArrayInt:
			case RawType::ArrayFloat:
			case RawType::ArrayBool:
			case RawType::ArrayVar:
			case RawType::ArrayStruct: {
				_value.array.reset();
				break;
			}
			default: {
				std::unreachable();
			}
		}

		_varType = RawType::None;
		_value.none = nullptr;

		REX::Assert(IsNone());
	}

	void Variable::Assign(const Variable& a_other)
	{
		switch (a_other.GetRawType()) {
			case RawType::None: {
				SetNone();
				break;
			}
			case RawType::Object: {
				SetObject(a_other.GetObject());
				break;
			}
			case RawType::String: {
				SetString(a_other.GetString());
				break;
			}
			case RawType::Int: {
				SetInt(a_other.GetInt());
				break;
			}
			case RawType::Float: {
				SetFloat(a_other.GetFloat());
				break;
			}
			case RawType::Bool: {
				SetBool(a_other.GetBool());
				break;
			}
			case RawType::Var: {
				const auto* value = a_other.GetVariant();
				if (!value) {
					SetVariant(UniqueVariant());
					break;
				}

				SetVariant(CreateVariant(*value));
				break;
			}
			case RawType::Struct: {
				SetStruct(a_other.GetStruct());
				break;
			}
			case RawType::ArrayObject:
			case RawType::ArrayString:
			case RawType::ArrayInt:
			case RawType::ArrayFloat:
			case RawType::ArrayBool:
			case RawType::ArrayVar:
			case RawType::ArrayStruct: {
				SetArray(a_other.GetArray());
				break;
			}
			default: {
				std::unreachable();
			}
		}

		_varType = a_other._varType;
	}

	void Variable::Assign(Variable&& a_other) noexcept
	{
		switch (a_other.GetRawType()) {
			case RawType::None: {
				SetNone();
				break;
			}
			case RawType::Object: {
				SetObject(std::move(a_other)._value.object);
				break;
			}
			case RawType::String: {
				SetString(std::move(a_other)._value.string);
				break;
			}
			case RawType::Int: {
				SetInt(std::move(a_other)._value.int32);
				break;
			}
			case RawType::Float: {
				SetFloat(std::move(a_other)._value.float32);
				break;
			}
			case RawType::Bool: {
				SetBool(std::move(a_other)._value.boolean);
				break;
			}
			case RawType::Var: {
				SetVariant(std::move(a_other)._value.variant);
				break;
			}
			case RawType::Struct: {
				SetStruct(std::move(a_other)._value.structure);
				break;
			}
			case RawType::ArrayObject:
			case RawType::ArrayString:
			case RawType::ArrayInt:
			case RawType::ArrayFloat:
			case RawType::ArrayBool:
			case RawType::ArrayVar:
			case RawType::ArrayStruct: {
				SetArray(std::move(a_other)._value.array);
				break;
			}
			default: {
				std::unreachable();
			}
		}

		_varType = a_other._varType;
	}

	Variable::ValueUnion::~ValueUnion() noexcept
	{
	}

	Variable::ValueUnion::ValueUnion(ValueUnion&& a_rhs) noexcept :
		none(std::exchange(a_rhs.none, nullptr))
	{
	}

	auto Variable::ValueUnion::operator=(ValueUnion&& a_rhs) noexcept -> Variable::ValueUnion&
	{
		if (this == std::addressof(a_rhs)) {
			return *this;
		}

		none = std::exchange(a_rhs.none, nullptr);
		return *this;
	}

	void Variable::ValueUnion::swap(ValueUnion& a_other) noexcept
	{
		if (this == std::addressof(a_other)) {
			return;
		}

		std::swap(none, a_other.none);
	}

	auto CreateVariant() -> UniqueVariant
	{
		return std::make_unique<Variable>();
	}

	auto GetDefaultVariable(const TypeInfo& a_typeInfo) noexcept -> Variable
	{
		auto value = Variable();

		switch (a_typeInfo.GetRawType()) {
			case TypeInfo::RawType::None: {
				value.SetNone();
				break;
			}
			case TypeInfo::RawType::Bool: {
				value.SetBool(false);
				break;
			}
			case TypeInfo::RawType::Int: {
				value.SetInt(0);
				break;
			}
			case TypeInfo::RawType::Float: {
				value.SetFloat(static_cast<REX::Float32>(0.0));
				break;
			}
			case TypeInfo::RawType::String: {
				value.SetString(BSFixedString());
				break;
			}
			case TypeInfo::RawType::Object: {
				value.SetObject(BSTSmartPointer<Object>());
				break;
			}
			case TypeInfo::RawType::Struct: {
				value.SetStruct(BSTSmartPointer<Struct>());
				break;
			}
			case TypeInfo::RawType::Var: {
				value.SetVariant(UniqueVariant());
				break;
			}
			case TypeInfo::RawType::ArrayBool:
			case TypeInfo::RawType::ArrayInt:
			case TypeInfo::RawType::ArrayFloat:
			case TypeInfo::RawType::ArrayString:
			case TypeInfo::RawType::ArrayObject:
			case TypeInfo::RawType::ArrayStruct:
			case TypeInfo::RawType::ArrayVar: {
				value.SetArray(BSTSmartPointer<Array>());
				break;
			}
			default: {
				std::unreachable();
			}
		}

		return value;
	}

	auto UnwrapVariant(UniqueVariant a_value) noexcept -> Variable
	{
		if (!a_value) {
			return NONE_VARIABLE;
		}

		return Variable(std::move(a_value));
	}

	auto UnwrapVariant(const Variable* a_value) noexcept -> const Variable&
	{
		if (!a_value) {
			return NONE_VARIABLE;
		}

		return *a_value;
	}
}

namespace std
{
	auto hash<RE::BSScript::Variable>::operator()(const RE::BSScript::Variable& a_key) const noexcept -> std::size_t
	{
		using RawType = RE::BSScript::TypeInfo::RawType;

		const auto rawType = a_key.GetRawType();
		switch (rawType) {
			case RawType::None: {
				return REX::HashCombine(rawType, a_key.GetNone());
			}
			case RawType::Object: {
				return REX::HashCombine(rawType, a_key.GetObject());
			}
			case RawType::String: {
				return REX::HashCombine(rawType, a_key.GetString());
			}
			case RawType::Int: {
				return REX::HashCombine(rawType, a_key.GetInt());
			}
			case RawType::Float: {
				return REX::HashCombine(rawType, a_key.GetFloat());
			}
			case RawType::Bool: {
				return REX::HashCombine(rawType, a_key.GetBool());
			}
			case RawType::Var: {
				const auto* value = a_key.GetVariant();
				if (!value) {
					return REX::HashCombine(rawType, nullptr);
				}

				return REX::HashCombine(rawType, *value);
			}
			case RawType::Struct:
				return REX::HashCombine(rawType, a_key.GetStruct());
			case RawType::ArrayObject:
			case RawType::ArrayString:
			case RawType::ArrayInt:
			case RawType::ArrayFloat:
			case RawType::ArrayBool:
			case RawType::ArrayVar:
			case RawType::ArrayStruct: {
				return REX::HashCombine(rawType, a_key.GetArray());
			}
			default: {
				std::unreachable();
			}
		}
	}
}
