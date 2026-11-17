#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSScriptUtility_Concepts.hpp"
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
		constexpr Variable() noexcept = default;
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
		explicit Variable(SharedVariant a_value);
		explicit Variable(BSTSmartPointer<Struct> a_value) noexcept;
		explicit Variable(BSTSmartPointer<Array> a_value) noexcept;

		Variable(const Variable& a_rhs);
		Variable(Variable&& a_rhs) noexcept;

		auto operator=(std::nullptr_t) noexcept -> Variable&;
		auto operator=(BSTSmartPointer<Object> a_value) noexcept -> Variable&;
		auto operator=(const char* a_value) -> Variable& = delete;
		auto operator=(BSFixedString a_value) noexcept -> Variable&;
		auto operator=(std::int32_t a_value) noexcept -> Variable&;
		auto operator=(std::uint32_t a_value) noexcept -> Variable&;
		auto operator=(REX::Float32 a_value) noexcept -> Variable&;
		auto operator=(bool a_value) noexcept -> Variable&;
		auto operator=(UniqueVariant a_value) noexcept -> Variable&;
		auto operator=(SharedVariant a_value) -> Variable&;
		auto operator=(BSTSmartPointer<Struct> a_value) noexcept -> Variable&;
		auto operator=(BSTSmartPointer<Array> a_value) noexcept -> Variable&;

		auto operator=(const Variable& a_rhs) -> Variable&;
		auto operator=(Variable&& a_rhs) noexcept -> Variable&;

		GAME_HEAP_REDEFINE_NEW(Variable);

		[[nodiscard]]
		auto operator==(const Variable& a_rhs) const noexcept -> bool;
		[[nodiscard]]
		auto operator<=>(const Variable& a_rhs) const noexcept -> std::partial_ordering;

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
		auto Equals(const Variable& a_rhs) const noexcept -> bool;
		[[nodiscard]]
		auto RefEquals(const Variable& a_rhs) const noexcept -> bool;
		[[nodiscard]]
		auto DeepEquals(const Variable& a_rhs) const noexcept -> bool;

		[[nodiscard]]
		auto Compare(const Variable& a_rhs) const noexcept -> std::partial_ordering;
		[[nodiscard]]
		auto RefCompare(const Variable& a_rhs) const noexcept -> std::partial_ordering;
		[[nodiscard]]
		auto DeepCompare(const Variable& a_rhs) const noexcept -> std::partial_ordering;

		[[nodiscard]]
		auto GetNone() const noexcept -> std::nullptr_t;
		[[nodiscard]]
		auto GetObject() const noexcept -> BSTSmartPointer<Object>;
		[[nodiscard]]
		auto GetString() const noexcept -> BSFixedString;
		[[nodiscard]]
		auto GetInt() const noexcept -> std::int32_t;
		[[nodiscard]]
		auto GetUInt() const noexcept -> std::uint32_t;
		[[nodiscard]]
		auto GetFloat() const noexcept -> REX::Float32;
		[[nodiscard]]
		auto GetBool() const noexcept -> bool;
		[[nodiscard]]
		auto GetVariant() const noexcept -> SharedVariant;
		[[nodiscard]]
		auto GetStruct() const noexcept -> BSTSmartPointer<Struct>;
		[[nodiscard]]
		auto GetArray() const noexcept -> BSTSmartPointer<Array>;

		void SetNone() noexcept;
		void SetObject(BSTSmartPointer<Object> a_value) noexcept;
		void SetString(BSFixedString a_value) noexcept;
		void SetInt(std::int32_t a_value) noexcept;
		void SetUInt(std::uint32_t a_value) noexcept;
		void SetFloat(REX::Float32 a_value) noexcept;
		void SetBool(bool a_value) noexcept;
		void SetVariant(UniqueVariant a_value) noexcept;
		void SetVariant(SharedVariant a_value);
		void SetStruct(BSTSmartPointer<Struct> a_value) noexcept;
		void SetArray(BSTSmartPointer<Array> a_value) noexcept;

		[[nodiscard]]
		auto GetTypeInfo() noexcept -> TypeInfo&;
		[[nodiscard]]
		auto GetTypeInfo() const noexcept -> const TypeInfo&;
		[[nodiscard]]
		auto GetRawType() const noexcept -> TypeInfo::RawType;
		[[nodiscard]]
		auto GetDeepRawType() const noexcept -> TypeInfo::RawType;
		[[nodiscard]]
		auto GetComplexType() const noexcept -> BSTSmartPointer<IComplexType>;

		void SetTypeInfo(const TypeInfo& a_type) noexcept;
		void SetRawType(TypeInfo::RawType a_type) noexcept;
		void SetComplexType(IComplexType* a_type) noexcept;
		void SetComplexType(const BSTSmartPointer<IComplexType>& a_type) noexcept;

		auto TryAssign(const Variable& a_rhs) noexcept -> bool;
		auto TryAssign(Variable&& a_rhs) noexcept -> bool;

		[[nodiscard]]
		auto Clone(IVirtualMachine& a_vm) const noexcept -> Variable;
		[[nodiscard]]
		auto DeepClone(IVirtualMachine& a_vm) const -> Variable;

		[[nodiscard]]
		auto ToString() const -> std::string;

		void swap(Variable& a_other) noexcept;

		void reset() noexcept;

		template <class T>
		auto Pack(IVirtualMachine& a_vm, T&& a_value) -> bool
			requires(BSScript::ValidateParameter<std::remove_reference_t<T>>());

		template <class T>
		[[nodiscard]]
		auto Unpack(IVirtualMachine& a_vm) const -> std::optional<std::remove_cv_t<T>>
			requires(BSScript::ValidateParameter<T>());

	private:
		using RawType = TypeInfo::RawType;

		void Assign(const Variable& a_other);
		void Assign(Variable&& a_other) noexcept;

		// members
		TypeInfo _varType; // 0x00

		union ValueUnion
		{
		public:
			constexpr ValueUnion() noexcept = default;
			~ValueUnion() noexcept;

			ValueUnion(const ValueUnion&) = delete;
			ValueUnion(ValueUnion&& a_rhs) noexcept;

			auto operator=(const ValueUnion&) -> ValueUnion& = delete;
			auto operator=(ValueUnion&& a_rhs) noexcept -> ValueUnion&;

			void swap(ValueUnion& a_other) noexcept;

			// members
			std::nullptr_t none{nullptr};
			BSTSmartPointer<Object> object;
			BSFixedString string;
			std::int32_t int32;
			std::uint32_t uint32;
			REX::Float32 float32;
			bool boolean;
			UniqueVariant variant;
			BSTSmartPointer<Struct> structure;
			BSTSmartPointer<Array> array;
		} _value; // 0x08
	};

	static_assert(sizeof(Variable) == 0x10);

	[[nodiscard]]
	auto CreateVariant() -> UniqueVariant;

	template <class T>
	[[nodiscard]]
	auto CreateVariant(T&& a_value) -> UniqueVariant
		requires(std::is_constructible_v<Variable, T>)
	{
		return std::make_unique<Variable>(std::forward<T>(a_value));
	}

	inline constexpr auto NONE_STRING = "None"sv;
	inline const constinit auto NONE_VARIABLE = Variable();

	[[nodiscard]]
	auto GetDefaultVariable(const TypeInfo& a_typeInfo) noexcept -> Variable;

	[[nodiscard]]
	auto UnwrapVariant(UniqueVariant a_value) noexcept -> Variable;
	[[nodiscard]]
	auto UnwrapVariant(SharedVariant a_value) noexcept -> const Variable&;
}

namespace std
{
	template <>
	struct hash<RE::BSScript::Variable>
	{
	public:
		[[nodiscard]]
		auto operator()(const RE::BSScript::Variable& a_key) const noexcept -> std::size_t;
	};
}

#if (__cpp_lib_format > 0l)
namespace std
{
	template <>
	struct formatter<RE::BSScript::Variable> : public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]]
		constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]]
		constexpr auto format(const RE::BSScript::Variable& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, a_value.ToString());
		}
	};
}
#endif

#if (FMT_VERSION > 0l)
namespace fmt
{
	template <>
	struct formatter<RE::BSScript::Variable> : public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]]
		constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]]
		constexpr auto format(const RE::BSScript::Variable& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, a_value.ToString());
		}
	};
}
#endif
