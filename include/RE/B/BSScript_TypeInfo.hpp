#pragma once

#include "RE/B/BSFixedString.hpp"

namespace RE::BSScript
{
	class IComplexType;
	class ObjectTypeInfo;
	class StructTypeInfo;

	class TypeInfo
	{
	public:
		enum class RawType : std::int32_t
		{
			kNone = 0,
			kObject = 1,
			kString = 2,
			kInt = 3,
			kFloat = 4,
			kBool = 5,
			kVar = 6,
			kStruct = 7,

			kType_Start = 0,
			kType_End = 8,

			kArrayObject = 11,
			kArrayString = 12,
			kArrayInt = 13,
			kArrayFloat = 14,
			kArrayBool = 15,
			kArrayVar = 16,
			kArrayStruct = 17,

			kArrayType_Start = 10,
			kArrayType_End = 18,

			// It is currently unknown where, or for what, this is used.
			kForceUInt32Size = -1
		};

		TypeInfo() noexcept;
		~TypeInfo() noexcept;

		TypeInfo(RawType a_rhs) noexcept;
		TypeInfo(IComplexType* a_rhs) noexcept;

		TypeInfo(const TypeInfo&) noexcept = default;
		TypeInfo(TypeInfo&&) noexcept = default;

		TypeInfo& operator=(RawType a_rhs) noexcept;
		TypeInfo& operator=(IComplexType* a_rhs) noexcept;

		TypeInfo& operator=(const TypeInfo&) noexcept = default;
		TypeInfo& operator=(TypeInfo&&) noexcept = default;

		[[nodiscard]] bool operator==(const TypeInfo& a_rhs) const noexcept;
		[[nodiscard]] bool operator!=(const TypeInfo& a_rhs) const noexcept;
		[[nodiscard]] std::strong_ordering operator<=>(const TypeInfo& a_rhs) const noexcept;

		[[nodiscard]] bool IsNone() const noexcept;
		[[nodiscard]] bool IsObject() const noexcept;
		[[nodiscard]] bool IsString() const noexcept;
		[[nodiscard]] bool IsInt() const noexcept;
		[[nodiscard]] bool IsUInt() const noexcept;
		[[nodiscard]] bool IsFloat() const noexcept;
		[[nodiscard]] bool IsBool() const noexcept;
		[[nodiscard]] bool IsVar() const noexcept;
		[[nodiscard]] bool IsStruct() const noexcept;

		[[nodiscard]] bool IsObjectArray() const noexcept;
		[[nodiscard]] bool IsStringArray() const noexcept;
		[[nodiscard]] bool IsIntArray() const noexcept;
		[[nodiscard]] bool IsUIntArray() const noexcept;
		[[nodiscard]] bool IsFloatArray() const noexcept;
		[[nodiscard]] bool IsBoolArray() const noexcept;
		[[nodiscard]] bool IsVarArray() const noexcept;
		[[nodiscard]] bool IsStructArray() const noexcept;

		[[nodiscard]] bool IsArray() const noexcept;
		[[nodiscard]] bool IsComplex() const noexcept;
		[[nodiscard]] bool IsComplexArray() const noexcept;
		[[nodiscard]] bool IsNoneAssignable() const noexcept;

		[[nodiscard]] bool IsAssignable(const TypeInfo& a_rhs) const noexcept;

		[[nodiscard]] bool Equals(const TypeInfo& a_rhs) const noexcept;
		[[nodiscard]] std::strong_ordering Compare(const TypeInfo& a_rhs) const noexcept;

		[[nodiscard]] RawType GetRawType() const noexcept;
		[[nodiscard]] IComplexType* GetComplexType() const noexcept;
		[[nodiscard]] ObjectTypeInfo* GetObjectTypeInfo() const noexcept;
		[[nodiscard]] StructTypeInfo* GetStructTypeInfo() const noexcept;
		[[nodiscard]] BSFixedString GetTypeName() const;

		void SetIsArray(bool a_set) noexcept;

		[[nodiscard]] std::string ToString() const;

		[[nodiscard]] static const BSFixedString& GetNoneTypeName();

		[[nodiscard]] static const BSFixedString& GetStringTypeName();
		[[nodiscard]] static const BSFixedString& GetIntTypeName();
		[[nodiscard]] static const BSFixedString& GetFloatTypeName();
		[[nodiscard]] static const BSFixedString& GetBoolTypeName();
		[[nodiscard]] static const BSFixedString& GetVarTypeName();

		[[nodiscard]] static const BSFixedString& GetStringArrayTypeName();
		[[nodiscard]] static const BSFixedString& GetIntArrayTypeName();
		[[nodiscard]] static const BSFixedString& GetFloatArrayTypeName();
		[[nodiscard]] static const BSFixedString& GetBoolArrayTypeName();
		[[nodiscard]] static const BSFixedString& GetVarArrayTypeName();

	private:
		// members
		union DataUnion
		{
		public:
			DataUnion() noexcept;
			~DataUnion() noexcept;

			DataUnion(RawType a_rhs) noexcept;
			DataUnion(IComplexType* a_rhs) noexcept;

			DataUnion(const DataUnion&) noexcept;
			DataUnion(DataUnion&& a_rhs) noexcept;

			DataUnion& operator=(RawType a_rhs) noexcept;
			DataUnion& operator=(IComplexType* a_rhs) noexcept;

			DataUnion& operator=(const DataUnion&) noexcept;
			DataUnion& operator=(DataUnion&& a_rhs) noexcept;

			// members
			REX::EnumSet<RawType, std::uintptr_t> rawType;
			IComplexType* complexTypeInfo{ nullptr };
		} _data; // 00
	};
	static_assert(sizeof(TypeInfo) == 0x08);

	[[nodiscard]] bool operator==(const TypeInfo& a_lhs, TypeInfo::RawType a_rhs) noexcept;
	[[nodiscard]] bool operator==(TypeInfo::RawType a_lhs, const TypeInfo& a_rhs) noexcept;

	[[nodiscard]] bool operator==(const TypeInfo& a_lhs, const IComplexType* a_rhs) noexcept;
	[[nodiscard]] bool operator==(const IComplexType* a_lhs, const TypeInfo& a_rhs) noexcept;
}

namespace std
{
	template <>
	struct hash<RE::BSScript::TypeInfo>
	{
	public:
		[[nodiscard]] std::size_t operator()(const RE::BSScript::TypeInfo& a_key) const noexcept;
	};
}
