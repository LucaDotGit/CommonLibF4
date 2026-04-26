#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSScriptUtil_Concepts.hpp"
#include "RE/B/BSScript_Variable.hpp"
#include "RE/B/BSSpinLockPolicy.hpp"
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
		inline static constexpr auto FORM_TYPE{ FormType::kScriptObject };

		Object() noexcept;
		~Object() noexcept;

		Object(const Object&) = delete;
		Object(Object&&) = delete;

		Object& operator=(const Object&) = delete;
		Object& operator=(Object&&) = delete;

		GAME_HEAP_REDEFINE_NEW(Object);

		[[nodiscard]] constexpr bool IsConstructed() const noexcept { return static_cast<bool>(constructed); }
		[[nodiscard]] constexpr bool IsInitialized() const noexcept { return static_cast<bool>(initialized); }
		[[nodiscard]] constexpr bool IsValid() const noexcept { return static_cast<bool>(valid); }

		[[nodiscard]] bool Equals(const Object& a_rhs) const noexcept;
		[[nodiscard]] bool RefEquals(const Object& a_rhs) const noexcept;
		[[nodiscard]] bool DeepEquals(const Object& a_rhs) const noexcept;

		[[nodiscard]] std::strong_ordering Compare(const Object& a_rhs) const noexcept;
		[[nodiscard]] std::strong_ordering RefCompare(const Object& a_rhs) const noexcept;
		[[nodiscard]] std::strong_ordering DeepCompare(const Object& a_rhs) const noexcept;

		[[nodiscard]] BSTSmartPointer<ObjectTypeInfo> GetTypeInfo() const noexcept;
		[[nodiscard]] auto GetTypeInfoName() const noexcept -> std::optional<BSFixedString>;
		[[nodiscard]] BSFixedString GetCurrentState() const noexcept;
		[[nodiscard]] ObjectHandle GetHandle() const noexcept;

		[[nodiscard]] bool Is(const BSTSmartPointer<BSScript::IVirtualMachine>& a_vm, FormType a_typeID) const;
		[[nodiscard]] void* As(const BSTSmartPointer<BSScript::IVirtualMachine>& a_vm, FormType a_typeID) const;

		[[nodiscard]] auto GetVariables() noexcept -> std::span<Variable>;
		[[nodiscard]] auto GetVariables() const noexcept -> std::span<const Variable>;

		[[nodiscard]] Variable* GetVariable(const BSFixedString& a_name);
		[[nodiscard]] const Variable* GetVariable(const BSFixedString& a_name) const;

		bool SetVariable(const BSFixedString& a_name, const Variable& a_value);

		[[nodiscard]] Variable* GetProperty(const BSFixedString& a_name);
		[[nodiscard]] const Variable* GetProperty(const BSFixedString& a_name) const;

		bool SetProperty(const BSFixedString& a_name, const Variable& a_value);

		[[nodiscard]] BSTSmartPointer<Object> Clone(IVirtualMachine& a_vm) noexcept;
		[[nodiscard]] BSTSmartPointer<Object> DeepClone(IVirtualMachine& a_vm) noexcept;

		[[nodiscard]] std::string ToString() const;

		[[nodiscard]] bool try_lock() const noexcept;

		void lock() const noexcept;
		void unlock() const noexcept;

		void IncRef() noexcept;
		std::uint32_t DecRef() noexcept;

		template <Impl::form_ptr T>
		[[nodiscard]] bool Is(const BSTSmartPointer<BSScript::IVirtualMachine>& a_vm) const
		{
			return Is(a_vm, std::to_underlying(T::FORM_TYPE));
		}

		template <Impl::form_ptr T>
		[[nodiscard]] T As(const BSTSmartPointer<BSScript::IVirtualMachine>& a_vm) const
		{
			return reinterpret_cast<T>(As(a_vm, T::FORM_TYPE));
		}

		template <class T>
		[[nodiscard]] auto FindVariable(REX::zstring_view a_name) const -> std::optional<T>
			requires(BSScript::ValidateParameter<T>());

		template <class T>
		[[nodiscard]] T FindVariableOrDefault(REX::zstring_view a_name) const
			requires(BSScript::ValidateParameter<T>());

		template <class T>
		[[nodiscard]] auto FindProperty(REX::zstring_view a_name) const -> std::optional<T>
			requires(BSScript::ValidateParameter<T>());

		template <class T>
		[[nodiscard]] T FindPropertyOrDefault(REX::zstring_view a_name) const
			requires(BSScript::ValidateParameter<T>());

		template <class T>
		[[nodiscard]] bool InsertVariable(REX::zstring_view a_name, T&& a_value)
			requires(BSScript::ValidateParameter<std::remove_reference_t<T>>());

		template <class T>
		[[nodiscard]] bool InsertProperty(REX::zstring_view a_name, T&& a_value)
			requires(BSScript::ValidateParameter<std::remove_reference_t<T>>());

		// members
		std::uint32_t constructed		   : 1 { 0 };			   // 00:00
		std::uint32_t initialized		   : 1 { 0 };			   // 00:01 - whether `OnInit` has been called
		std::uint32_t valid				   : 1 { 0 };			   // 00:02
		std::uint32_t remainingPropsToInit : 29 { 0 };			   // 00:03
		BSTSmartPointer<ObjectTypeInfo> type;					   // 08
		BSFixedString currentState;								   // 10
		mutable void* volatile lockStructure{ nullptr };		   // 18 - the first bit is used as flag
		volatile ObjectHandle handle;							   // 20
		mutable volatile std::uint32_t refCountAndHandleLock{ 1 }; // 28 - the flag `0x80000000` is used as handle lock
		Variable variables[0];									   // 30 - the size is equal to `type->GetNumVariables()` - NOLINT(modernize-avoid-c-arrays)
	};
	static_assert(sizeof(Object) == 0x30);
}

namespace RE
{
	extern template class BSAutoLockDefaultPolicy<BSScript::Object>;
	extern template class BSAutoLock<BSScript::Object, BSAutoLockDefaultPolicy>;
}

#if __cpp_lib_format > 0l
namespace std
{
	template <>
	struct formatter<RE::BSScript::Object>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_ctx) const
		{
			return a_ctx.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const RE::BSScript::Object& a_value, FormatContext& a_ctx) const
		{
			using namespace std::string_view_literals;

			return format_to(a_ctx.out(), "{}"sv, a_value.ToString());
		}
	};
}
#endif

#if FMT_VERSION > 0l
namespace fmt
{
	template <>
	struct formatter<RE::BSScript::Object>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_ctx) const
		{
			return a_ctx.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const RE::BSScript::Object& a_value, FormatContext& a_ctx) const
		{
			using namespace std::string_view_literals;

			return format_to(a_ctx.out(), "{}"sv, a_value.ToString());
		}
	};
}
#endif
