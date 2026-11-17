#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSScriptUtility_Concepts.hpp"
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

	class Struct : public BSIntrusiveRefCounted // 0x00
	{
	public:
		Struct() noexcept;
		~Struct() noexcept;

		Struct(const Struct&) = delete;
		Struct(Struct&&) = delete;

		auto operator=(const Struct&) -> Struct& = delete;
		auto operator=(Struct&&) -> Struct& = delete;

		GAME_HEAP_REDEFINE_NEW(Struct);

		[[nodiscard]]
		constexpr auto IsConstructed() const noexcept -> bool
		{
			return constructed;
		}

		[[nodiscard]]
		constexpr auto IsValid() const noexcept -> bool
		{
			return valid;
		}

		[[nodiscard]]
		auto Equals(const Struct& a_rhs) const noexcept -> bool;
		[[nodiscard]]
		auto RefEquals(const Struct& a_rhs) const noexcept -> bool;
		[[nodiscard]]
		auto DeepEquals(const Struct& a_rhs) const noexcept -> bool;

		[[nodiscard]]
		auto Compare(const Struct& a_rhs) const noexcept -> std::strong_ordering;
		[[nodiscard]]
		auto RefCompare(const Struct& a_rhs) const noexcept -> std::strong_ordering;
		[[nodiscard]]
		auto DeepCompare(const Struct& a_rhs) const noexcept -> std::partial_ordering;

		[[nodiscard]]
		auto GetTypeInfo() const noexcept -> BSTSmartPointer<StructTypeInfo>;
		[[nodiscard]]
		auto GetTypeInfoName() const noexcept -> std::optional<BSFixedString>;

		[[nodiscard]]
		auto GetVariables() noexcept -> std::span<Variable>;
		[[nodiscard]]
		auto GetVariables() const noexcept -> std::span<const Variable>;

		[[nodiscard]]
		auto GetVariable(const BSFixedString& a_name) noexcept -> Variable*;
		[[nodiscard]]
		auto GetVariable(const BSFixedString& a_name) const noexcept -> const Variable*;

		auto SetVariable(const BSFixedString& a_name, const Variable& a_value) noexcept -> bool;

		[[nodiscard]]
		auto Clone(IVirtualMachine& a_vm) const -> BSTSmartPointer<Struct>;
		[[nodiscard]]
		auto DeepClone(IVirtualMachine& a_vm) const -> BSTSmartPointer<Struct>;

		[[nodiscard]]
		auto ToString() const -> std::string;

		template <class T>
		[[nodiscard]]
		auto FindVariable(IVirtualMachine& a_vm, REX::ZStringView a_name) const -> std::optional<std::remove_cv_t<T>>
			requires(BSScript::ValidateParameter<T>());

		template <class T>
		auto InsertVariable(IVirtualMachine& a_vm, REX::ZStringView a_name, T&& a_value) -> bool
			requires(BSScript::ValidateParameter<std::remove_reference_t<T>>());

		// members
		mutable BSSpinLock structLock;		  // 0x04
		BSTSmartPointer<StructTypeInfo> type; // 0x10
		bool constructed{true};				  // 0x18
		bool valid{false};					  // 0x19
		Variable variables[0];				  // 0x20 - NOLINT(modernize-avoid-c-arrays)
	};

	static_assert(sizeof(Struct) == 0x20);
}

#if (__cpp_lib_format > 0l)
namespace std
{
	template <>
	struct formatter<RE::BSScript::Struct> : public formatter<std::string>
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
		constexpr auto format(const RE::BSScript::Struct& a_value, FormatContext& a_context) const
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
	struct formatter<RE::BSScript::Struct> : public formatter<std::string>
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
		constexpr auto format(const RE::BSScript::Struct& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, a_value.ToString());
		}
	};
}
#endif
