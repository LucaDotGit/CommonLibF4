#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSScriptUtil_Concepts.hpp"
#include "RE/B/BSScript_Variable.hpp"
#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE::BSContainer
{
	enum class ForEachResult : std::int32_t;
}

namespace RE::BSScript
{
	class IVirtualMachine;
	class StructTypeInfo;
	class Variable;

	class Struct
		: public BSIntrusiveRefCounted // 00
	{
	public:
		Struct() noexcept;
		~Struct() noexcept;

		Struct(const Struct&) = delete;
		Struct(Struct&&) = delete;

		Struct& operator=(const Struct&) = delete;
		Struct& operator=(Struct&&) = delete;

		GAME_HEAP_REDEFINE_NEW(Struct);

		[[nodiscard]] constexpr bool IsConstructed() const noexcept { return constructed; }
		[[nodiscard]] constexpr bool IsValid() const noexcept { return valid; }

		[[nodiscard]] bool Equals(const Struct& a_rhs) const noexcept;
		[[nodiscard]] bool RefEquals(const Struct& a_rhs) const noexcept;
		[[nodiscard]] bool DeepEquals(const Struct& a_rhs) const noexcept;

		[[nodiscard]] std::strong_ordering Compare(const Struct& a_rhs) const noexcept;
		[[nodiscard]] std::strong_ordering RefCompare(const Struct& a_rhs) const noexcept;
		[[nodiscard]] std::partial_ordering DeepCompare(const Struct& a_rhs) const noexcept;

		[[nodiscard]] BSTSmartPointer<StructTypeInfo> GetTypeInfo() const noexcept;
		[[nodiscard]] auto GetTypeInfoName() const noexcept
			-> std::optional<BSFixedString>;

		[[nodiscard]] auto GetVariables() noexcept
			-> std::span<Variable>;
		[[nodiscard]] auto GetVariables() const noexcept
			-> std::span<const Variable>;

		[[nodiscard]] Variable* GetVariable(const BSFixedString& a_name);
		[[nodiscard]] const Variable* GetVariable(const BSFixedString& a_name) const;

		bool SetVariable(const BSFixedString& a_name, const Variable& a_value);

		[[nodiscard]] BSTSmartPointer<Struct> Clone(IVirtualMachine& a_vm) const;
		[[nodiscard]] BSTSmartPointer<Struct> DeepClone(IVirtualMachine& a_vm) const;

		[[nodiscard]] std::string ToString() const;

		template <class T>
		[[nodiscard]] auto Find(REX::zstring_view a_name) const
			-> std::optional<T>
			requires(BSScript::ValidateParameter<T>());

		template <class T>
		[[nodiscard]] T FindOrDefault(REX::zstring_view a_name) const
			requires(BSScript::ValidateParameter<T>());

		template <class T>
		[[nodiscard]] T FindOrDefault(REX::zstring_view a_name, const T& a_default) const
			requires(BSScript::ValidateParameter<T>());

		template <class T>
		bool Insert(REX::zstring_view a_name, T&& a_value)
			requires(BSScript::ValidateParameter<std::remove_reference_t<T>>());

		// members
		mutable BSSpinLock structLock;		  // 04
		BSTSmartPointer<StructTypeInfo> type; // 10
		bool constructed{ true };			  // 18
		bool valid{ false };				  // 19
		Variable variables[0];				  // 20 - NOLINT(modernize-avoid-c-arrays)
	};
	static_assert(sizeof(Struct) == 0x20);
}

#if __cpp_lib_format > 0l
namespace std
{
	template <>
	struct formatter<RE::BSScript::Struct>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const RE::BSScript::Struct& a_value, FormatContext& a_context) const
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
	struct formatter<RE::BSScript::Struct>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const RE::BSScript::Struct& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, a_value.ToString());
		}
	};
}
#endif
