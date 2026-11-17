#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSScriptUtility_Concepts.hpp"
#include "RE/B/BSScript_Variable.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/F/FormType.hpp"

namespace RE
{
	enum class FormType : std::int32_t;
}

namespace RE::BSScript
{
	class IVirtualMachine;
	class ObjectTypeInfo;
	class Variable;

	class Object
	{
	public:
		inline static constexpr auto FORM_TYPE = FormType::ScriptObject;

		Object() noexcept;
		~Object() noexcept;

		Object(const Object&) = delete;
		Object(Object&&) = delete;

		auto operator=(const Object&) -> Object& = delete;
		auto operator=(Object&&) -> Object& = delete;

		GAME_HEAP_REDEFINE_NEW(Object);

		[[nodiscard]]
		constexpr auto IsConstructed() const noexcept -> bool
		{
			return static_cast<bool>(constructed);
		}

		[[nodiscard]]
		constexpr auto IsInitialized() const noexcept -> bool
		{
			return static_cast<bool>(initialized);
		}

		[[nodiscard]]
		constexpr auto IsValid() const noexcept -> bool
		{
			return static_cast<bool>(valid);
		}

		[[nodiscard]]
		auto Equals(const Object& a_rhs) const noexcept -> bool;
		[[nodiscard]]
		auto RefEquals(const Object& a_rhs) const noexcept -> bool;
		[[nodiscard]]
		auto DeepEquals(const Object& a_rhs) const noexcept -> bool;

		[[nodiscard]]
		auto Compare(const Object& a_rhs) const noexcept -> std::strong_ordering;
		[[nodiscard]]
		auto RefCompare(const Object& a_rhs) const noexcept -> std::strong_ordering;
		[[nodiscard]]
		auto DeepCompare(const Object& a_rhs) const noexcept -> std::strong_ordering;

		[[nodiscard]]
		auto GetTypeInfo() const noexcept -> BSTSmartPointer<ObjectTypeInfo>;
		[[nodiscard]]
		auto GetTypeInfoName() const noexcept -> std::optional<BSFixedString>;
		[[nodiscard]]
		auto GetCurrentState() const noexcept -> BSFixedString;
		[[nodiscard]]
		auto GetHandle() const noexcept -> ObjectHandle;

		[[nodiscard]]
		auto Is(const BSScript::IVirtualMachine& a_vm, FormType a_typeID) const -> bool;
		[[nodiscard]]
		auto As(const BSScript::IVirtualMachine& a_vm, FormType a_typeID) const -> void*;

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
		auto GetProperty(const BSFixedString& a_name) noexcept -> Variable*;
		[[nodiscard]]
		auto GetProperty(const BSFixedString& a_name) const noexcept -> const Variable*;

		auto SetProperty(const BSFixedString& a_name, const Variable& a_value) noexcept -> bool;

		[[nodiscard]]
		auto Clone(IVirtualMachine& a_vm) noexcept -> BSTSmartPointer<Object>;
		[[nodiscard]]
		auto DeepClone(IVirtualMachine& a_vm) noexcept -> BSTSmartPointer<Object>;

		[[nodiscard]]
		auto ToString() const -> std::string;

		[[nodiscard]]
		auto try_lock() const noexcept -> bool;

		void lock() const noexcept;
		void unlock() const noexcept;

		void IncRef() const noexcept;
		auto DecRef() const noexcept -> std::uint32_t;

		template <Impl::form_pointer T>
		[[nodiscard]]
		auto Is(const BSScript::IVirtualMachine& a_vm) const -> bool
		{
			return Is(a_vm, std::to_underlying(T::FORM_TYPE));
		}

		template <Impl::form_pointer T>
		[[nodiscard]]
		auto As(const BSScript::IVirtualMachine& a_vm) const -> T
		{
			return static_cast<T>(As(a_vm, T::FORM_TYPE));
		}

		template <class T>
		[[nodiscard]]
		auto FindVariable(IVirtualMachine& a_vm, REX::ZStringView a_name) const -> std::optional<std::remove_cv_t<T>>
			requires(BSScript::ValidateParameter<T>());

		template <class T>
		[[nodiscard]]
		auto InsertVariable(IVirtualMachine& a_vm, REX::ZStringView a_name, T&& a_value) -> bool
			requires(BSScript::ValidateParameter<std::remove_reference_t<T>>());

		template <class T>
		[[nodiscard]]
		auto FindProperty(IVirtualMachine& a_vm, REX::ZStringView a_name) const -> std::optional<std::remove_cv_t<T>>
			requires(BSScript::ValidateParameter<T>());

		template <class T>
		[[nodiscard]]
		auto InsertProperty(IVirtualMachine& a_vm, REX::ZStringView a_name, T&& a_value) -> bool
			requires(BSScript::ValidateParameter<std::remove_reference_t<T>>());

		// NOLINTBEGIN(modernize-avoid-c-arrays)

		// members
		std::uint32_t constructed		   : 1 {0};				 // 0x00:00
		std::uint32_t initialized		   : 1 {0};				 // 0x00:01 - whether `OnInit` has been called
		std::uint32_t valid				   : 1 {0};				 // 0x00:02
		std::uint32_t remainingPropsToInit : 29 {0};			 // 0x00:03
		BSTSmartPointer<ObjectTypeInfo> type;					 // 0x08
		BSFixedString currentState;								 // 0x10
		mutable volatile std::uintptr_t lockStructure{0};		 // 0x18 - the first bit is used as flag
		volatile ObjectHandle handle;							 // 0x20
		mutable volatile std::uint32_t refCountAndHandleLock{1}; // 0x28 - the flag `0x80000000` is used as handle lock
		Variable variables[0]; // 0x30 - the size is equal to `type->GetNumVariables()`

		// NOLINTEND(modernize-avoid-c-arrays)
	};

	static_assert(sizeof(Object) == 0x30);
}

#if (__cpp_lib_format > 0l)
namespace std
{
	template <>
	struct formatter<RE::BSScript::Object> : public formatter<std::string>
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
		constexpr auto format(const RE::BSScript::Object& a_value, FormatContext& a_context) const
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
	struct formatter<RE::BSScript::Object> : public formatter<std::string>
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
		constexpr auto format(const RE::BSScript::Object& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, a_value.ToString());
		}
	};
}
#endif
