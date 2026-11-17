#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSScript_TypeInfo.hpp"
#include "RE/B/BSScript_Variant.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/F/FormType.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	enum class FormType : std::int32_t;
}

namespace RE::BSScript
{
	template <class T>
	class ArrayWrapper;

	template <class T>
	class LatentResult;

	template <REX::StaticString ScriptName>
	class ObjectWrapper;

	template <REX::StaticString ScriptName, REX::StaticString StructName>
	class StructWrapper;

	class Array;
	class IVirtualMachine;
	class Object;
	class Struct;
	class TypeInfo;
	class Variable;
}

namespace RE::GameScript
{
	class FormOrInventoryObj;
	class RefrOrInventoryObj;
}

namespace RE::BSScript
{
	template <class>
	struct script_traits
	{
		using is_array = std::false_type;
		using is_string = std::false_type;
		using is_wstring = std::false_type;
		using is_fs_path = std::false_type;
		using is_optional = std::false_type;
	};

	template <class T, class Allocator>
	struct script_traits<std::vector<T, Allocator>>
	{
		using is_array = std::true_type;
	};

	template <class T, class Allocator>
	struct script_traits<std::deque<T, Allocator>>
	{
		using is_array = std::true_type;
	};

	template <class Traits, class Allocator>
	struct script_traits<std::basic_string<char, Traits, Allocator>>
	{
		using is_string = std::true_type;
	};

	template <class Traits>
	struct script_traits<std::basic_string_view<char, Traits>>
	{
		using is_string = std::true_type;
	};

	template <class Traits, class Allocator>
	struct script_traits<std::basic_string<wchar_t, Traits, Allocator>>
	{
		using is_wstring = std::true_type;
	};

	template <class Traits>
	struct script_traits<std::basic_string_view<wchar_t, Traits>>
	{
		// Due to `BSScript::Variable` not being able to own wide strings,
		// wide views are not supported.
		using is_wstring = std::false_type;
	};

	template <>
	struct script_traits<std::filesystem::path>
	{
		using is_fs_path = std::true_type;
	};

	template <class T>
	struct script_traits<std::optional<T>>
	{
		using is_optional = std::true_type;
	};

	template <class T>
	struct variable_packer
	{
	public:
		variable_packer() = delete;

		[[nodiscard]]
		static consteval auto GetObjectTypeID() noexcept -> FormType = delete;

		[[nodiscard]]
		static auto GetTypeInfo(IVirtualMachine& a_vm) -> std::optional<TypeInfo> = delete;

		static auto PackVariable(IVirtualMachine& a_vm, Variable& a_var, T&& a_val) -> bool = delete;

		[[nodiscard]]
		static auto UnpackVariable(IVirtualMachine& a_vm, const Variable& a_var)
			-> std::optional<std::remove_cv_t<T>> = delete;
	};

	template <REX::win32_character CharT>
	inline constexpr auto SCRIPT_SEPARATOR = static_cast<CharT>(':');

	template <REX::win32_character CharT>
	inline constexpr auto STRUCT_SEPARATOR = static_cast<CharT>('#');

	template <class CharT, std::size_t N1, std::size_t N2>
	[[nodiscard]]
	consteval auto CreateScriptTag(
		const REX::BasicStaticString<CharT, N1>& a_namespace,
		const REX::BasicStaticString<CharT, N2>& a_scriptName) noexcept
	{
		auto result = REX::BasicStaticString<CharT, N1 + 1 + N2 - 1>();
		std::copy_n(a_namespace.data(), a_namespace.size(), result.data());
		result[a_namespace.size()] = SCRIPT_SEPARATOR<CharT>;
		std::copy_n(a_scriptName.data(), a_scriptName.size(), result.data() + a_namespace.size() + 1);
		return result;
	}

	template <class CharT, std::size_t N1, std::size_t N2>
	[[nodiscard]]
	consteval auto CreateStructTag(
		const REX::BasicStaticString<CharT, N1>& a_scriptName,
		const REX::BasicStaticString<CharT, N2>& a_structName) noexcept
	{
		auto result = REX::BasicStaticString<CharT, N1 + 1 + N2 - 1>();
		std::copy_n(a_scriptName.data(), a_scriptName.size(), result.data());
		result[a_scriptName.size()] = STRUCT_SEPARATOR<CharT>;
		std::copy_n(a_structName.data(), a_structName.size(), result.data() + a_scriptName.size() + 1);
		return result;
	}

	static_assert(
		CreateScriptTag(REX::StaticString("MyNamespace"), REX::StaticString("MyScript")) ==
		REX::StaticString("MyNamespace:MyScript"));

	static_assert(
		CreateStructTag(
			CreateScriptTag(REX::StaticString("MyNamespace"), REX::StaticString("MyScript")),
			REX::StaticString("MyStruct")) == REX::StaticString("MyNamespace:MyScript#MyStruct"));
}

namespace RE::BSScript::Impl
{
	template <class T>
	using decay_t = std::conditional_t<REX::pointer<T>, REX::remove_cvptr_t<T>, std::remove_cvref_t<T>>;

	template <class From, class To>
	concept decays_to = std::same_as<decay_t<From>, To>;

	template <class T>
	struct is_bs_pointer : public std::false_type
	{
	};

	template <class T, template <class> class RefManager>
	struct is_bs_pointer<BSTSmartPointer<T, RefManager>> : public std::true_type
	{
	};

	template <class T>
	concept bs_pointer = is_bs_pointer<std::remove_cv_t<T>>::value;

	template <class T>
	concept ni_pointer = std::same_as<std::remove_cv_t<T>, NiPointer<typename std::remove_cv_t<T>::element_type>>;

	template <class T>
	concept bs_handle_pointer = std::same_as<
		std::remove_cv_t<T>,
		BSPointerHandle<typename std::remove_cv_t<T>::element_type, typename std::remove_cv_t<T>::handle_type>>;

	template <class T>
	concept form_pointer = REX::pointer<T> &&
						   (std::derived_from<REX::remove_cvptr_t<T>, TESForm> ||
							std::derived_from<REX::remove_cvptr_t<T>, BGSBaseAlias> ||
							std::same_as<REX::remove_cvptr_t<T>, ActiveEffect> ||
							std::same_as<REX::remove_cvptr_t<T>, BSInputEnableLayer>) &&
						   std::same_as<std::remove_cv_t<decltype(std::remove_pointer_t<T>::FORM_TYPE)>, FormType>;

	template <class T>
	concept inventory_object = (std::same_as<std::remove_cv_t<T>, GameScript::FormOrInventoryObj> ||
								std::same_as<std::remove_cv_t<T>, GameScript::RefrOrInventoryObj>) &&
							   std::same_as<std::remove_cv_t<decltype(T::FORM_TYPE)>, FormType>;

	template <class T>
	concept vm_object_pointer = bs_pointer<T> &&
								std::same_as<std::remove_cv_t<typename T::element_type>, Object> &&
								std::same_as<std::remove_cv_t<decltype(T::element_type::FORM_TYPE)>, FormType>;

	template <class T>
	concept string = std::same_as<typename script_traits<std::remove_cv_t<T>>::is_string, std::true_type> &&
					 std::is_constructible_v<T, std::string_view> &&
					 std::is_convertible_v<T, std::string_view>;

	template <class T>
	concept wstring = std::same_as<typename script_traits<std::remove_cv_t<T>>::is_wstring, std::true_type> &&
					  std::is_constructible_v<T, std::wstring_view> &&
					  std::is_convertible_v<T, std::wstring_view>;

	template <class T>
	concept filesystem_path = std::same_as<typename script_traits<std::remove_cv_t<T>>::is_fs_path, std::true_type> &&
							  std::is_constructible_v<T, std::string_view, std::filesystem::path::format> &&
							  requires(T a_path) {
								  {
									  a_path.generic_string()
								  } -> std::same_as<std::string>;
							  };

	template <class T>
	concept integer = REX::integer<std::remove_cv_t<T>> || REX::enumeration<std::remove_cv_t<T>>;

	template <class T>
	concept floating_point = REX::floating_point<std::remove_cv_t<T>>;

	template <class T>
	concept boolean = REX::boolean<std::remove_cv_t<T>>;

	template <class T>
	concept chrono_duration =
		std::same_as<std::remove_cv_t<T>, std::chrono::duration<typename T::rep, typename T::period>>;

	template <class T>
	concept chrono_time_point =
		std::same_as<std::remove_cv_t<T>, std::chrono::time_point<typename T::clock, typename T::duration>>;

	template <class T>
	concept chrono_year = std::same_as<std::remove_cv_t<T>, std::chrono::year>;

	template <class T>
	concept chrono_month = std::same_as<std::remove_cv_t<T>, std::chrono::month>;

	template <class T>
	concept chrono_day = std::same_as<std::remove_cv_t<T>, std::chrono::day>;

	template <class T>
	concept chrono_weekday = std::same_as<std::remove_cv_t<T>, std::chrono::weekday>;

	template <class T>
	concept vm_shared_variant = std::same_as<std::remove_cv_t<T>, SharedVariant>;

	template <class T>
	concept vm_unique_variant = std::same_as<T, UniqueVariant>;

	template <class T>
	concept array = std::same_as<typename script_traits<std::remove_cv_t<T>>::is_array, std::true_type> &&
					std::is_default_constructible_v<T> &&
					requires(T a_array, T::value_type&& a_value) {
						{
							a_array.begin()
						} -> std::same_as<typename T::iterator>;
						{
							a_array.end()
						} -> std::same_as<typename T::iterator>;
						{
							a_array.size()
						} -> std::same_as<typename T::size_type>;
						{
							a_array.push_back(a_value)
						} -> std::same_as<void>;
					};

	template <class T>
	concept vm_object_wrapper = std::same_as<std::remove_cv_t<T>, ObjectWrapper<T::TYPE_NAME>>;

	template <class T>
	concept vm_struct_wrapper = std::same_as<std::remove_cv_t<T>, StructWrapper<T::SCRIPT_NAME, T::STRUCT_NAME>>;

	template <class T>
	concept vm_array_wrapper = std::same_as<std::remove_cv_t<T>, ArrayWrapper<typename T::element_type>>;

	template <class T>
	concept optional = std::same_as<typename script_traits<std::remove_cv_t<T>>::is_optional, std::true_type> &&
					   std::is_default_constructible_v<T> &&
					   requires(T a_optional) {
						   {
							   static_cast<bool>(a_optional)
						   } -> std::same_as<bool>;
						   {
							   *static_cast<const T&>(a_optional)
						   } -> decays_to<typename T::value_type>;
						   {
							   *static_cast<T&&>(a_optional)
						   } -> decays_to<typename T::value_type>;
					   };

	template <class T>
	concept void_result = std::same_as<T, void>;

	template <class T>
	concept static_tag = std::same_as<T, StaticTag>;

	template <class T>
	[[nodiscard]]
	consteval auto GetObjectTypeID() noexcept -> FormType;

	template <class T>
	[[nodiscard]] [[REX_ALWAYS_INLINE]]
	auto GetTypeInfo(IVirtualMachine& a_vm) -> std::optional<TypeInfo>;

	template <class T>
	[[REX_ALWAYS_INLINE]]
	auto PackVariable(IVirtualMachine& a_vm, Variable& a_var, T&& a_val) -> bool;

	template <class T>
	[[nodiscard]] [[REX_ALWAYS_INLINE]]
	auto UnpackVariable(IVirtualMachine& a_vm, const Variable& a_var) -> std::optional<std::remove_cv_t<T>>;

	template <class T>
	concept valid_self =
		static_tag<T> || form_pointer<T> || inventory_object<T> || vm_object_pointer<T> || vm_object_wrapper<T>;

	template <class T>
	concept valid_parameter = requires {
		{
			variable_packer<T>::GetTypeInfo(std::declval<IVirtualMachine&>())
		} -> std::same_as<std::optional<TypeInfo>>;
		{
			variable_packer<T>::PackVariable(
				std::declval<IVirtualMachine&>(),
				std::declval<Variable&>(),
				std::declval<T&&>())
		} -> std::same_as<bool>;
		{
			variable_packer<T>::UnpackVariable(std::declval<IVirtualMachine&>(), std::declval<const Variable&>())
		} -> std::same_as<std::optional<std::remove_cv_t<T>>>;
	};

	template <class T>
	concept valid_return = void_result<T> || valid_parameter<T>;
}

namespace RE::BSScript
{
	template <class T>
	[[nodiscard]]
	consteval auto ValidateSelf() noexcept -> bool
	{
		//	A function which takes a self parameter must be one of (optionally cv-qualified):
		//	* A raw pointer to one of:
		//		* `RE::TESForm` or any subclass thereof
		//		* `RE::BGSBaseAlias` or any subclass thereof
		//		* `RE::ActiveEffect`
		//		* `RE::BSInputEnableLayer`
		//	* An inventory object that is one of:
		//		* `RE::GameScript::FormOrInventoryObj`
		//		* `RE::GameScript::RefrOrInventoryObj`
		//	* A shared script object pointer that is one of:
		//		* `RE::BSTSmartPointer<RE::BSScript::Object>`
		//	* A script object wrapper that is one of:
		//		* `RE::BSScript::ObjectWrapper`
		// A function without a self parameter (a static/global function) must replace this slot with
		// `RE::BSScript::StaticTag`
		static_assert(Impl::valid_self<T>, "The self type is invalid.");

		return true;
	}

	template <class T>
	[[nodiscard]]
	consteval auto ValidateParameter() noexcept -> bool
	{
		//	Must be one of (optionally cv-qualified):
		//	* A raw pointer to one of:
		//		* `RE::TESForm` or any subclass thereof
		//		* `RE::BGSBaseAlias` or any subclass thereof
		//		* `RE::ActiveEffect`
		//		* `RE::BSInputEnableLayer`
		//	* An inventory object that is one of:
		//		* `RE::GameScript::FormOrInventoryObj`
		//		* `RE::GameScript::RefrOrInventoryObj`
		//	* A shared script object pointer that is one of:
		//		* `RE::BSTSmartPointer<RE::BSScript::Object>`
		//	* A Bethesda shared pointer that is one of:
		//		* `RE::BSTSmartPointer<RE::ActiveEffect>`
		//		* `RE::BSTSmartPointer<RE::BSInputEnableLayer>`
		//	* A NetImmerse shared pointer that is one of:
		//		* `RE::NiPointer<RE::TESObjectREFR>`
		//		* `RE::NiPointer<RE::Actor>`
		//		* `RE::NiPointer<RE::Projectile>`
		//	* A Bethesda weak pointer that is one of:
		//		* `RE::ObjectRefHandle`
		//		* `RE::ActorHandle`
		//		* `RE::ProjectileHandle`
		//	* A narrow string type that is one of:
		//		* `std::string`
		//		* `std::string_view`
		//		* `RE::BSFixedString`
		//		* `RE::BSFixedStringCS`
		//		* `RE::BGSLocalizedString`
		//		* `RE::BSString`
		//		* A custom type that implements:
		//			* A specialization of `RE::BSScript::script_traits` that defines `is_string` as `std::true_type`
		//			* A conversion to `std::string_view`
		//	* A wide string type that is one of:
		//		* `std::wstring`
		//		* `RE::BSFixedStringW`
		//		* `RE::BSFixedStringWCS`
		//		* `RE::BSStringW`
		//		* A custom type that implements:
		//			* A specialization of `RE::BSScript::script_traits` that defines `is_wstring` as `std::true_type`
		//			* A conversion to `std::wstring_view`
		//	* A filesystem path type that is one of:
		//		* `std::filesystem::path`
		//		* A custom type that implements:
		//			* A specialization of `RE::BSScript::script_traits` that defines `is_fs_path` as `std::true_type`
		//			* A constructor that takes:
		//				* A `std::string_view`
		//				* A `std::filesystem::path::format`
		//			* A method `generic_string` that returns a `std::string`
		//	* An enumeration type with an integer underlying type
		//	* An integer type that is one of (optionally signed/unsigned):
		//		* `char`
		//		* `wchar_t`
		//		* `char8_t`
		//		* `char16_t`
		//		* `char32_t`
		//		* `std::int8_t`
		//		* `std::uint8_t`
		//		* `std::int16_t`
		//		* `std::uint16_t`
		//		* `std::int32_t`
		//		* `std::uint32_t`
		//		* `std::int64_t`
		//		* `std::uint64_t`
		//	* A floating point type that is one of:
		//		* `REX::Float32`
		//		* `REX::Float64`
		//		* `REX::Float128`
		//	* A boolean type that is one of:
		//		* `bool`
		//	* A chrono type that is one of:
		//		* `std::chrono::duration`
		//		* `std::chrono::time_point`
		//		* `std::chrono::year`
		//		* `std::chrono::month`
		//		* `std::chrono::day`
		//		* `std::chrono::weekday`
		//	* An observing variant type that is one of:
		//		* `RE::BSScript::SharedVariant`
		//	* An owning variant type that is one of:
		//		* `RE::BSScript::UniqueVariant`
		//	* An array type that is one of:
		//		* `std::vector`
		//		* `std::deque`
		//		* `RE::BSTArray`
		//		* `RE::BSTAlignedArray`
		//		* `RE::BSScrapArray`
		//		* `RE::BSTSmallArray`
		//		* `RE::BSTHeapObjectArena`
		//		* `RE::BSTAlignedObjectArena`
		//		* `RE::BSTScrapObjectArena`
		//		* A custom type that implements:
		//			* A specialization of `RE::BSScript::script_traits` that defines `is_array` as `std::true_type`
		//			* A default constructor
		//			* The following typedefs:
		//				* `iterator`
		//				* `size_type`
		//				* `value_type`
		//			* The following methods:
		//				* `begin`
		//					* Invokable with no arguments
		//					* Returns a type of `iterator`
		//				* `end`
		//					* Invokable with no arguments
		//					* Returns a type of `iterator`
		//				* `size`
		//					* Invokable with no arguments
		//					* Returns a type of `size_type`
		//				* `push_back`
		//					* Invokable with:
		//						* A rvalue reference of type `value_type`
		//				* `reserve` (optional)
		//					* Invokable with:
		//						* A value of type `size_type`
		//					* Returns `void`
		//		* Additionally, the array's `value_type` must be a valid parameter type
		//	* A wrapper type that is one of:
		//		* `RE::BSScript::ObjectWrapper`
		//		* `RE::BSScript::StructWrapper`
		//		* `RE::BSScript::ArrayWrapper`
		//	* An optional type that is one of:
		//		* `std::optional`
		//		* `RE::BSTOptional`
		//		* A custom type that implements:
		//			* A specialization of `RE::BSScript::script_traits` that defines `is_optional` as `std::true_type`
		//			* A default constructor
		//			* The following typedefs:
		//				* `value_type`
		//			* The following methods:
		//				* `operator bool`
		//				* `operator *`
		//					* Returns type of `value_type`
		//		* Additionally, the optional's `value_type` must be a valid parameter type
		//	* A custom type that implements:
		//		* A specialization of `RE::BSScript::variable_packer` that provides the following static functions:
		//			* `GetTypeInfo`
		//				* Invokable with:
		//					* A reference to `RE::BSScript::IVirtualMachine`
		//				* Returns `std::optional<RE::BSScript::TypeInfo>`
		//			* `PackVariable`
		//				* Invokable with:
		//					* A reference to `RE::BSScript::IVirtualMachine`
		//					* A reference to `RE::BSScript::Variable`
		//					* A rvalue reference of type `T`
		//				* Returns `bool`
		//			* `UnpackVariable`
		//				* Invokable with:
		//					* A reference to `RE::BSScript::IVirtualMachine`
		//					* A const reference to `RE::BSScript::Variable`
		//				* Returns `std::optional<std::remove_cv_t<T>>`
		static_assert(Impl::valid_parameter<T>, "The parameter type is invalid.");

		return true;
	}

	template <class T>
	[[nodiscard]]
	consteval auto ValidateReturn() noexcept -> bool
	{
		//	Must be one of:
		//	* `void`
		//	* A valid parameter type
		static_assert(Impl::valid_return<T>, "The return type is invalid.");

		return true;
	}
}
