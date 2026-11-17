#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTSmartPointer.hpp"

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
			None = 0,
			Object = 1,
			String = 2,
			Int = 3,
			Float = 4,
			Bool = 5,
			Var = 6,
			Struct = 7,

			_Type_Start = 0,
			_Type_End = 8,

			ArrayObject = 11,
			ArrayString = 12,
			ArrayInt = 13,
			ArrayFloat = 14,
			ArrayBool = 15,
			ArrayVar = 16,
			ArrayStruct = 17,

			_ArrayType_Start = 10,
			_ArrayType_End = 18,

			// It is currently unknown where, or for what, this is used.
			ForceUInt32Size = -1
		};

		constexpr TypeInfo() noexcept = default;
		constexpr ~TypeInfo() noexcept = default;

		explicit TypeInfo(RawType a_rhs) noexcept;
		explicit TypeInfo(IComplexType* a_rhs) noexcept;
		explicit TypeInfo(const BSTSmartPointer<IComplexType>& a_rhs) noexcept;

		constexpr TypeInfo(const TypeInfo&) noexcept = default;
		constexpr TypeInfo(TypeInfo&&) noexcept = default;

		auto operator=(RawType a_rhs) noexcept -> TypeInfo&;
		auto operator=(IComplexType* a_rhs) noexcept -> TypeInfo&;
		auto operator=(const BSTSmartPointer<IComplexType>& a_rhs) noexcept -> TypeInfo&;

		constexpr auto operator=(const TypeInfo&) noexcept -> TypeInfo& = default;
		constexpr auto operator=(TypeInfo&&) noexcept -> TypeInfo& = default;

		[[nodiscard]]
		auto operator==(const TypeInfo& a_rhs) const noexcept -> bool;
		[[nodiscard]]
		auto operator<=>(const TypeInfo& a_rhs) const noexcept -> std::strong_ordering;

		[[nodiscard]]
		auto IsNone() const noexcept -> bool;
		[[nodiscard]]
		auto IsObject() const noexcept -> bool;
		[[nodiscard]]
		auto IsString() const noexcept -> bool;
		[[nodiscard]]
		auto IsInt() const noexcept -> bool;
		[[nodiscard]]
		auto IsUInt() const noexcept -> bool;
		[[nodiscard]]
		auto IsFloat() const noexcept -> bool;
		[[nodiscard]]
		auto IsBool() const noexcept -> bool;
		[[nodiscard]]
		auto IsVariant() const noexcept -> bool;
		[[nodiscard]]
		auto IsStruct() const noexcept -> bool;

		[[nodiscard]]
		auto IsObjectArray() const noexcept -> bool;
		[[nodiscard]]
		auto IsStringArray() const noexcept -> bool;
		[[nodiscard]]
		auto IsIntArray() const noexcept -> bool;
		[[nodiscard]]
		auto IsUIntArray() const noexcept -> bool;
		[[nodiscard]]
		auto IsFloatArray() const noexcept -> bool;
		[[nodiscard]]
		auto IsBoolArray() const noexcept -> bool;
		[[nodiscard]]
		auto IsVariantArray() const noexcept -> bool;
		[[nodiscard]]
		auto IsStructArray() const noexcept -> bool;

		[[nodiscard]]
		auto IsArray() const noexcept -> bool;
		[[nodiscard]]
		auto IsComplex() const noexcept -> bool;
		[[nodiscard]]
		auto IsComplexArray() const noexcept -> bool;
		[[nodiscard]]
		auto IsNoneAssignable() const noexcept -> bool;

		[[nodiscard]]
		auto IsAssignable(const TypeInfo& a_rhs) const noexcept -> bool;

		[[nodiscard]]
		auto Equals(const TypeInfo& a_rhs) const noexcept -> bool;
		[[nodiscard]]
		auto Compare(const TypeInfo& a_rhs) const noexcept -> std::strong_ordering;

		[[nodiscard]]
		auto GetRawType() const noexcept -> RawType;
		[[nodiscard]]
		auto GetComplexType() const noexcept -> BSTSmartPointer<IComplexType>;
		[[nodiscard]]
		auto GetObjectTypeInfo() const noexcept -> BSTSmartPointer<ObjectTypeInfo>;
		[[nodiscard]]
		auto GetStructTypeInfo() const noexcept -> BSTSmartPointer<StructTypeInfo>;
		[[nodiscard]]
		auto GetTypeName() const -> BSFixedString;

		void SetIsArray(bool a_set) noexcept;

		[[nodiscard]]
		auto ToString() const -> std::string;

		void swap(TypeInfo& a_other) noexcept;

		[[nodiscard]]
		static auto GetNoneTypeName() -> const BSFixedString&;

		[[nodiscard]]
		static auto GetStringTypeName() -> const BSFixedString&;
		[[nodiscard]]
		static auto GetIntTypeName() -> const BSFixedString&;
		[[nodiscard]]
		static auto GetFloatTypeName() -> const BSFixedString&;
		[[nodiscard]]
		static auto GetBoolTypeName() -> const BSFixedString&;
		[[nodiscard]]
		static auto GetVarTypeName() -> const BSFixedString&;

		[[nodiscard]]
		static auto GetStringArrayTypeName() -> const BSFixedString&;
		[[nodiscard]]
		static auto GetIntArrayTypeName() -> const BSFixedString&;
		[[nodiscard]]
		static auto GetFloatArrayTypeName() -> const BSFixedString&;
		[[nodiscard]]
		static auto GetBoolArrayTypeName() -> const BSFixedString&;
		[[nodiscard]]
		static auto GetVarArrayTypeName() -> const BSFixedString&;

	private:
		// members
		union DataUnion
		{
		public:
			constexpr DataUnion() noexcept = default;
			constexpr ~DataUnion() noexcept = default;

			explicit DataUnion(RawType a_rhs) noexcept;
			explicit DataUnion(IComplexType* a_rhs) noexcept;
			explicit DataUnion(const BSTSmartPointer<IComplexType>& a_rhs) noexcept;

			constexpr DataUnion(const DataUnion&) noexcept = default;
			constexpr DataUnion(DataUnion&&) noexcept = default;

			auto operator=(RawType a_rhs) noexcept -> DataUnion&;
			auto operator=(IComplexType* a_rhs) noexcept -> DataUnion&;
			auto operator=(const BSTSmartPointer<IComplexType>& a_rhs) noexcept -> DataUnion&;

			constexpr auto operator=(const DataUnion&) noexcept -> DataUnion& = default;
			constexpr auto operator=(DataUnion&&) noexcept -> DataUnion& = default;

			// members
			REX::EnumSet<RawType, std::uintptr_t> rawType;
			IComplexType* complexTypeInfo{nullptr};
		} _data; // 0x00
	};

	static_assert(sizeof(TypeInfo) == 0x08);

	[[nodiscard]]
	auto operator==(const TypeInfo& a_lhs, TypeInfo::RawType a_rhs) noexcept -> bool;
	[[nodiscard]]
	auto operator==(TypeInfo::RawType a_lhs, const TypeInfo& a_rhs) noexcept -> bool;

	[[nodiscard]]
	auto operator==(const TypeInfo& a_lhs, const IComplexType* a_rhs) noexcept -> bool;
	[[nodiscard]]
	auto operator==(const IComplexType* a_lhs, const TypeInfo& a_rhs) noexcept -> bool;

	inline constexpr auto NONE_TYPE_INFO = TypeInfo();
}

namespace std
{
	template <>
	struct hash<RE::BSScript::TypeInfo>
	{
	public:
		[[nodiscard]]
		auto operator()(const RE::BSScript::TypeInfo& a_key) const noexcept -> std::size_t;
	};
}
