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

		[[nodiscard]] static consteval FormType GetObjectTypeID() = delete;

		[[nodiscard]] static auto GetTypeInfo()
			-> std::optional<TypeInfo> = delete;

		static void PackVariable(Variable& a_var, T&& a_val) = delete;

		[[nodiscard]] static T UnpackVariable(const Variable& a_var) = delete;
	};

	template <REX::win32_character CharT>
	inline constexpr auto SCRIPT_SEPARATOR = static_cast<CharT>(':');

	template <REX::win32_character CharT>
	inline constexpr auto STRUCT_SEPARATOR = static_cast<CharT>('#');

	template <class CharT, std::size_t N1, std::size_t N2>
	[[nodiscard]] consteval auto CreateScriptTag(
		const REX::StaticString<CharT, N1>& a_namespace,
		const REX::StaticString<CharT, N2>& a_scriptName) noexcept
	{
		auto result = REX::StaticString<CharT, N1 + 1 + N2 - 1>();
		std::copy_n(a_namespace.data(), a_namespace.size(), result.data());
		result[a_namespace.size()] = SCRIPT_SEPARATOR<CharT>;
		std::copy_n(a_scriptName.data(), a_scriptName.size(), result.data() + a_namespace.size() + 1);
		return result;
	}

	template <class CharT, std::size_t N1, std::size_t N2>
	[[nodiscard]] consteval auto CreateStructTag(
		const REX::StaticString<CharT, N1>& a_scriptName,
		const REX::StaticString<CharT, N2>& a_structName) noexcept
	{
		auto result = REX::StaticString<CharT, N1 + 1 + N2 - 1>();
		std::copy_n(a_scriptName.data(), a_scriptName.size(), result.data());
		result[a_scriptName.size()] = STRUCT_SEPARATOR<CharT>;
		std::copy_n(a_structName.data(), a_structName.size(), result.data() + a_scriptName.size() + 1);
		return result;
	}

	static_assert(
		CreateStructTag(
			REX::StaticString("MyNamespace:MyScript"),
			REX::StaticString("MyStruct")) == REX::StaticString("MyNamespace:MyScript#MyStruct"));

	static_assert(
		CreateScriptTag(
			REX::StaticString("MyNamespace"),
			REX::StaticString("MyScript")) == REX::StaticString("MyNamespace:MyScript"));
}

namespace RE::BSScript::Impl
{
	template <class T>
	using remove_cvptr_t =
		std::conditional_t<
			std::is_pointer_v<T>,
			std::remove_cv_t<std::remove_pointer_t<T>>,
			std::remove_cv_t<T>>;

	template <class T>
	using decay_t =
		std::conditional_t<
			std::is_pointer_v<T>,
			remove_cvptr_t<T>,
			std::remove_cvref_t<T>>;

	template <class From, class To>
	concept decays_to =
		std::same_as<
			decay_t<From>, To>;

	template <class>
	inline constexpr bool is_bs_ptr = false;

	template <class T, template <class> class R>
	inline constexpr bool is_bs_ptr<BSTSmartPointer<T, R>> = true;

	template <class T>
	concept bs_ptr =
		is_bs_ptr<std::remove_cv_t<T>>;

	template <class T>
	concept ni_ptr =
		std::same_as<
			std::remove_cv_t<T>,
			NiPointer<typename std::remove_cv_t<T>::element_type>>;

	template <class T>
	concept bs_handle_ptr =
		std::same_as<
			std::remove_cv_t<T>,
			BSPointerHandle<typename std::remove_cv_t<T>::element_type, typename std::remove_cv_t<T>::handle_type>>;

	template <class T>
	concept form_ptr =
		std::is_pointer_v<T> &&
		(std::derived_from<remove_cvptr_t<T>, TESForm> ||
			std::derived_from<remove_cvptr_t<T>, BGSBaseAlias> ||
			std::same_as<remove_cvptr_t<T>, ActiveEffect> ||
			std::same_as<remove_cvptr_t<T>, BSInputEnableLayer>) &&
		std::same_as<std::remove_cv_t<decltype(std::remove_pointer_t<T>::FORM_TYPE)>, FormType>;

	template <class T>
	concept inventory_object =
		(std::same_as<std::remove_cv_t<T>, GameScript::FormOrInventoryObj> ||
			std::same_as<std::remove_cv_t<T>, GameScript::RefrOrInventoryObj>) &&
		std::same_as<std::remove_cv_t<decltype(T::FORM_TYPE)>, FormType>;

	template <class T>
	concept vm_object_ptr =
		bs_ptr<T> &&
		std::same_as<std::remove_cv_t<typename T::element_type>, Object> &&
		std::same_as<std::remove_cv_t<decltype(T::element_type::FORM_TYPE)>, FormType>;

	template <class T>
	concept string =
		std::same_as<typename script_traits<std::remove_cv_t<T>>::is_string, std::true_type> &&
		std::is_constructible_v<T, std::string_view> &&
		std::is_convertible_v<T, std::string_view>;

	template <class T>
	concept wstring =
		std::same_as<typename script_traits<std::remove_cv_t<T>>::is_wstring, std::true_type> &&
		std::is_constructible_v<T, std::wstring_view> &&
		std::is_convertible_v<T, std::wstring_view>;

	template <class T>
	concept fs_path =
		std::same_as<typename script_traits<std::remove_cv_t<T>>::is_fs_path, std::true_type> &&
		std::is_constructible_v<T, std::string_view, std::filesystem::path::format> &&
		requires(T a_path) {
			{ a_path.generic_string() } -> std::same_as<std::string>;
		};

	template <class T>
	concept integer =
		(std::is_integral_v<T> && !std::same_as<std::remove_cv_t<T>, bool>) ||
		(std::is_enum_v<T> && std::is_integral_v<std::underlying_type_t<T>>);

	template <class T>
	concept floating_point =
		std::is_floating_point_v<T>;

	template <class T>
	concept boolean =
		std::same_as<std::remove_cv_t<T>, bool>;

	template <class T>
	concept vm_shared_var =
		std::same_as<std::remove_cv_t<T>, SharedVariant>;

	template <class T>
	concept vm_unique_var =
		std::same_as<T, UniqueVariant>;

	template <class T>
	concept array =
		std::same_as<typename script_traits<std::remove_cv_t<T>>::is_array, std::true_type> &&
		std::is_default_constructible_v<T> &&
		requires(T a_array, T::value_type&& a_value) {
			{ a_array.begin() } -> std::same_as<typename T::iterator>;
			{ a_array.end() } -> std::same_as<typename T::iterator>;
			{ a_array.size() } -> std::same_as<typename T::size_type>;
			a_array.push_back(a_value);
		};

	template <class T>
	concept reservable =
		requires(T a_array, std::remove_cv_t<T>::size_type a_size) {
			{ a_array.reserve(a_size) } -> std::same_as<void>;
		};

	template <class T>
	concept vm_object_wrapper =
		std::same_as<std::remove_cv_t<T>, ObjectWrapper<T::TYPE_NAME>>;

	template <class T>
	concept vm_struct_wrapper =
		std::same_as<std::remove_cv_t<T>, StructWrapper<T::SCRIPT_NAME, T::STRUCT_NAME>>;

	template <class T>
	concept vm_array_wrapper =
		std::same_as<std::remove_cv_t<T>, ArrayWrapper<typename T::element_type>>;

	template <class T>
	concept optional =
		std::same_as<typename script_traits<std::remove_cv_t<T>>::is_optional, std::true_type> &&
		std::is_default_constructible_v<T> &&
		requires(T a_optional) {
			{ static_cast<bool>(a_optional) } -> std::same_as<bool>;
			{ *static_cast<const T&>(a_optional) } -> decays_to<typename T::value_type>;
			{ *static_cast<T&&>(a_optional) } -> decays_to<typename T::value_type>;
		};

	template <class T>
	concept void_result =
		std::same_as<T, void>;

	template <class T>
	concept static_tag =
		std::same_as<T, StaticTag>;

	template <class T>
	[[nodiscard]] consteval FormType GetObjectTypeID() noexcept;

	template <class T>
	[[nodiscard]] __forceinline auto GetTypeInfo()
		-> std::optional<TypeInfo>;

	template <class T>
	__forceinline void PackVariable(Variable& a_var, T&& a_val);

	template <class T>
	[[nodiscard]] __forceinline T UnpackVariable(const Variable& a_var);

	template <class T>
	concept valid_self =
		static_tag<T> ||
		form_ptr<T> ||
		inventory_object<T> ||
		vm_object_ptr<T> ||
		vm_object_wrapper<T>;

	template <class T>
	concept valid_parameter =
		requires {
			{ variable_packer<T>::GetTypeInfo() } -> std::same_as<std::optional<TypeInfo>>;
			{ variable_packer<T>::PackVariable(std::declval<Variable&>(), std::declval<T&&>()) } -> std::same_as<void>;
			{ variable_packer<T>::UnpackVariable(std::declval<const Variable&>()) } -> std::same_as<std::remove_cv_t<T>>;
		};

	template <class T>
	concept valid_return =
		void_result<T> ||
		valid_parameter<T>;
}

namespace RE::BSScript
{
	template <class T>
	[[nodiscard]] consteval bool ValidateSelf() noexcept
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
		// A function without a self parameter (a static/global function) must replace this slot with `RE::BSScript::StaticTag`
		static_assert(Impl::valid_self<T>, "The self type is invalid.");

		return true;
	}

	template <class T>
	[[nodiscard]] consteval bool ValidateParameter() noexcept
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
		//			* A specialization of `RE::BSScript::script_traits` that provides a typedef `is_string` as `std::true_type`
		//			* A conversion to `std::string_view`
		//	* A wide string type that is one of:
		//		* `std::wstring`
		//		* `RE::BSFixedStringW`
		//		* `RE::BSFixedStringWCS`
		//		* `RE::BSStringW`
		//		* A custom type that implements:
		//			* A specialization of `RE::BSScript::script_traits` that provides a typedef `is_wstring` as `std::true_type`
		//			* A conversion to `std::wstring_view`
		//	* A filesystem path type that is one of:
		//		* `std::filesystem::path`
		//		* A custom type that implements:
		//			* A specialization of `RE::BSScript::script_traits` that provides a typedef `is_fs_path` as `std::true_type`
		//			* A constructor that takes:
		//				* A `std::string_view`
		//				* A `std::filesystem::path::format`
		//			* A method `generic_string` that returns a `std::string`
		//	* An integer type that is one of (optionally signed/unsigned):
		//		* `char`
		//		* `wchar_t`
		//		* `char8_t`
		//		* `char16_t`
		//		* `char32_t`
		//		* `short`
		//		* `int`
		//		* `long`
		//		* `long long`
		//	* An enumeration type with an integral underlying type
		//	* A floating point type that is one of:
		//		* `float`
		//		* `double`
		//		* `long double`
		//	* A boolean type that is one of:
		//		* `bool`
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
		//			* A specialization of `RE::BSScript::script_traits` that provides a typedef `is_array` as `std::true_type`
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
		//					* Invokable with a rvalue reference of type `value_type`
		// 				* `reserve` (optional)
		//					* Invokable with `size_type`
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
		//			* A specialization of `RE::BSScript::script_traits` that provides a typedef `is_optional` as `std::true_type`
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
		//				* Invokable with no arguments
		//				* Returns `std::optional<RE::BSScript::TypeInfo>`
		//			* `PackVariable`
		//				* Invokable with:
		//					* A reference to `RE::BSScript::Variable`
		//					* An instance of the custom type
		//				* Returns `void`
		//			* `UnpackVariable`
		//				* Invokable with:
		//					* A const reference to `RE::BSScript::Variable`
		//				* Returns the custom type
		static_assert(Impl::valid_parameter<T>, "The parameter type is invalid.");

		return true;
	}

	template <class T>
	[[nodiscard]] consteval bool ValidateReturn() noexcept
	{
		//	Must be one of:
		//	* `void`
		//	* A valid parameter type
		static_assert(Impl::valid_return<T>, "The return type is invalid.");

		return true;
	}
}
