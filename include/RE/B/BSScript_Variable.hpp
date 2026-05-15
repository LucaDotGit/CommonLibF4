#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSScriptUtil_Concepts.hpp"
#include "RE/B/BSScript_TypeInfo.hpp"
#include "RE/B/BSScript_Variant.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE::BSScript
{
	class Array;
	class IComplexType;
	class IVirtualMachine;
	class Object;
	class Struct;

	class Variable
	{
	public:
		Variable() noexcept;
		~Variable() noexcept;

		explicit Variable(std::nullptr_t) noexcept;
		explicit Variable(BSTSmartPointer<Object> a_value) noexcept;
		explicit Variable(const char* a_value) = delete;
		explicit Variable(BSFixedString a_value) noexcept;
		explicit Variable(std::int32_t a_value) noexcept;
		explicit Variable(std::uint32_t a_value) noexcept;
		explicit Variable(REX::Float32 a_value) noexcept;
		explicit Variable(bool a_value) noexcept;
		explicit Variable(UniqueVariant a_value) noexcept;
		explicit Variable(SharedVariant a_value) noexcept;
		explicit Variable(BSTSmartPointer<Struct> a_value) noexcept;
		explicit Variable(BSTSmartPointer<Array> a_value) noexcept;

		Variable(const Variable& a_rhs) noexcept;
		Variable(Variable&& a_rhs) noexcept;

		Variable& operator=(std::nullptr_t) noexcept;
		Variable& operator=(BSTSmartPointer<Object> a_value) noexcept;
		Variable& operator=(const char* a_value) = delete;
		Variable& operator=(BSFixedString a_value) noexcept;
		Variable& operator=(std::int32_t a_value) noexcept;
		Variable& operator=(std::uint32_t a_value) noexcept;
		Variable& operator=(REX::Float32 a_value) noexcept;
		Variable& operator=(bool a_value) noexcept;
		Variable& operator=(UniqueVariant a_value) noexcept;
		Variable& operator=(SharedVariant a_value) noexcept;
		Variable& operator=(BSTSmartPointer<Struct> a_value) noexcept;
		Variable& operator=(BSTSmartPointer<Array> a_value) noexcept;

		Variable& operator=(const Variable& a_rhs) noexcept;
		Variable& operator=(Variable&& a_rhs) noexcept;

		GAME_HEAP_REDEFINE_NEW(Variable);

		[[nodiscard]] bool operator==(const Variable& a_rhs) const noexcept;
		[[nodiscard]] bool operator!=(const Variable& a_rhs) const noexcept;
		[[nodiscard]] std::partial_ordering operator<=>(const Variable& a_rhs) const noexcept;

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

		[[nodiscard]] bool Equals(const Variable& a_rhs) const noexcept;
		[[nodiscard]] bool RefEquals(const Variable& a_rhs) const noexcept;
		[[nodiscard]] bool DeepEquals(const Variable& a_rhs) const noexcept;

		[[nodiscard]] std::partial_ordering Compare(const Variable& a_rhs) const noexcept;
		[[nodiscard]] std::partial_ordering RefCompare(const Variable& a_rhs) const noexcept;
		[[nodiscard]] std::partial_ordering DeepCompare(const Variable& a_rhs) const noexcept;

		[[nodiscard]] std::nullptr_t GetNone() const noexcept;
		[[nodiscard]] BSTSmartPointer<Object> GetObject() const noexcept;
		[[nodiscard]] BSFixedString GetString() const noexcept;
		[[nodiscard]] std::int32_t GetInt() const noexcept;
		[[nodiscard]] std::uint32_t GetUInt() const noexcept;
		[[nodiscard]] REX::Float32 GetFloat() const noexcept;
		[[nodiscard]] bool GetBool() const noexcept;
		[[nodiscard]] SharedVariant GetVar() const noexcept;
		[[nodiscard]] BSTSmartPointer<Struct> GetStruct() const noexcept;
		[[nodiscard]] BSTSmartPointer<Array> GetArray() const noexcept;

		void SetNone() noexcept;
		void SetObject(BSTSmartPointer<Object> a_value) noexcept;
		void SetString(BSFixedString a_value) noexcept;
		void SetInt(std::int32_t a_value) noexcept;
		void SetUInt(std::uint32_t a_value) noexcept;
		void SetFloat(REX::Float32 a_value) noexcept;
		void SetBool(bool a_value) noexcept;
		void SetVar(UniqueVariant a_value) noexcept;
		void SetVar(SharedVariant a_value) noexcept;
		void SetStruct(BSTSmartPointer<Struct> a_value) noexcept;
		void SetArray(BSTSmartPointer<Array> a_value) noexcept;

		[[nodiscard]] TypeInfo& GetTypeInfo() noexcept;
		[[nodiscard]] const TypeInfo& GetTypeInfo() const noexcept;
		[[nodiscard]] TypeInfo::RawType GetRawType() const noexcept;
		[[nodiscard]] TypeInfo::RawType GetDeepRawType() const noexcept;
		[[nodiscard]] IComplexType* GetComplexType() const noexcept;

		void SetTypeInfo(const TypeInfo& a_type) noexcept;
		void SetRawType(TypeInfo::RawType a_type) noexcept;
		void SetComplexType(IComplexType* a_type) noexcept;

		bool TryAssign(const Variable& a_rhs) noexcept;
		bool TryAssign(Variable&& a_rhs) noexcept;

		[[nodiscard]] Variable Clone(IVirtualMachine& a_vm) const noexcept;
		[[nodiscard]] Variable DeepClone(IVirtualMachine& a_vm) const;

		[[nodiscard]] std::string ToString() const;

		void swap(Variable& a_other) noexcept;

		void reset() noexcept;

		template <class T>
		void Pack(T&& a_value)
			requires(BSScript::ValidateParameter<std::remove_reference_t<T>>());

		template <class T>
		[[nodiscard]] T Unpack() const
			requires(BSScript::ValidateParameter<T>());

	private:
		using RawType = TypeInfo::RawType;

		void Assign(const Variable& a_other) noexcept;
		void Assign(Variable&& a_other) noexcept;

		// members
		TypeInfo _varType; // 00
		union ValueUnion
		{
		public:
			ValueUnion() noexcept;
			~ValueUnion() noexcept;

			ValueUnion(const ValueUnion&) = delete;
			ValueUnion(ValueUnion&& a_rhs) noexcept;

			ValueUnion& operator=(const ValueUnion&) = delete;
			ValueUnion& operator=(ValueUnion&& a_rhs) noexcept;

			// members
			std::nullptr_t none{ nullptr };
			BSTSmartPointer<Object> object;
			BSFixedString string;
			std::int32_t int32;
			std::uint32_t uint32;
			REX::Float32 float32;
			bool boolean;
			UniqueVariant var;
			BSTSmartPointer<Struct> structure;
			BSTSmartPointer<Array> array;
		} _value; // 08
	};
	static_assert(sizeof(Variable) == 0x10);

	[[nodiscard]] inline UniqueVariant make_variant()
	{
		return std::make_unique<Variable>();
	}

	template <class T>
	[[nodiscard]] UniqueVariant make_variant(T&& a_value)
		requires(std::is_constructible_v<Variable, T>)
	{
		return std::make_unique<Variable>(std::forward<T>(a_value));
	}

	[[nodiscard]] inline UniqueVariant CreateVariant()
	{
		return std::make_unique<Variable>();
	}

	template <class T>
	[[nodiscard]] UniqueVariant CreateVariant(T&& a_value)
		requires(std::is_constructible_v<Variable, T>)
	{
		return std::make_unique<Variable>(std::forward<T>(a_value));
	}

	void swap(Variable& a_lhs, Variable& a_rhs) noexcept;

	inline constexpr auto NONE_STRING = "None"sv;
	inline const auto NONE_VARIABLE = Variable(nullptr);

	[[nodiscard]] Variable GetDefaultVariable(const TypeInfo& a_typeInfo);

	[[nodiscard]] Variable UnwrapVariant(UniqueVariant a_value);
	[[nodiscard]] const Variable& UnwrapVariant(SharedVariant a_value) noexcept;
}

namespace std
{
	template <>
	struct hash<RE::BSScript::Variable>
	{
	public:
		[[nodiscard]] std::size_t operator()(const RE::BSScript::Variable& a_key) const noexcept;
	};
}

#if __cpp_lib_format > 0l
namespace std
{
	template <>
	struct formatter<RE::BSScript::Variable>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const RE::BSScript::Variable& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, a_value.ToString());
		}
	};
}
#endif

#if FMT_VERSION > 0l
namespace fmt
{
	template <>
	struct formatter<RE::BSScript::Variable>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const RE::BSScript::Variable& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, a_value.ToString());
		}
	};
}
#endif
