#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSScriptUtil_Concepts.hpp"
#include "RE/B/BSScript_Array.hpp"
#include "RE/B/BSScript_Object.hpp"
#include "RE/B/BSScript_ObjectTypeInfo.hpp"
#include "RE/B/BSScript_Struct.hpp"
#include "RE/B/BSScript_StructTypeInfo.hpp"
#include "RE/B/BSScript_TypeInfo.hpp"
#include "RE/B/BSScript_Variable.hpp"
#include "RE/B/BSScript_Variant.hpp"
#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/B/BSTThreadScrapFunction.hpp"
#include "RE/F/FormType.hpp"
#include "RE/G/GameScript_FormOrInventoryObj.hpp"
#include "RE/G/GameScript_HandlePolicy.hpp"
#include "RE/G/GameScript_RefrOrInventoryObj.hpp"
#include "RE/G/GameVM.hpp"

namespace RE::BSScript
{
	template <class T>
		requires(Impl::bs_ptr<T> && !Impl::vm_object_ptr<T> && Impl::valid_parameter<std::add_pointer_t<typename T::element_type>>)
	struct variable_packer<T>
	{
	public:
		[[nodiscard]] static consteval FormType GetObjectTypeID() noexcept
		{
			using element_type = std::add_pointer_t<typename T::element_type>;
			return Impl::GetObjectTypeID<element_type>();
		}

		[[nodiscard]] static auto GetTypeInfo() -> std::optional<TypeInfo>
		{
			using element_type = std::add_pointer_t<typename T::element_type>;
			return Impl::GetTypeInfo<element_type>();
		}

		static void PackVariable(Variable& a_var, T a_val)
		{
			Impl::PackVariable(a_var, a_val.get());
		}

		[[nodiscard]] static auto UnpackVariable(const Variable& a_var) -> std::remove_cv_t<T>
		{
			using element_type = std::add_pointer_t<typename T::element_type>;

			if (!a_var.IsObject()) [[unlikely]] {
				REX::Assert(a_var.IsNone());
				return {};
			}

			auto* element = Impl::UnpackVariable<element_type>(a_var);
			if (!element) {
				return {};
			}

			return T(element);
		}
	};

	template <class T>
		requires(Impl::ni_ptr<T> && Impl::valid_parameter<std::add_pointer_t<typename T::element_type>>)
	struct variable_packer<T>
	{
	public:
		[[nodiscard]] static consteval FormType GetObjectTypeID() noexcept
		{
			using element_type = std::add_pointer_t<typename T::element_type>;
			return Impl::GetObjectTypeID<element_type>();
		}

		[[nodiscard]] static auto GetTypeInfo() -> std::optional<TypeInfo>
		{
			using element_type = std::add_pointer_t<typename T::element_type>;
			return Impl::GetTypeInfo<element_type>();
		}

		static void PackVariable(Variable& a_var, T a_val)
		{
			Impl::PackVariable(a_var, a_val.get());
		}

		[[nodiscard]] static auto UnpackVariable(const Variable& a_var) -> std::remove_cv_t<T>
		{
			using element_type = std::add_pointer_t<typename T::element_type>;

			if (!a_var.IsObject()) [[unlikely]] {
				REX::Assert(a_var.IsNone());
				return {};
			}

			auto* element = Impl::UnpackVariable<element_type>(a_var);
			if (!element) {
				return {};
			}

			return T(element);
		}
	};

	template <class T>
		requires(Impl::bs_handle_ptr<T> && Impl::valid_parameter<std::add_pointer_t<typename T::element_type>>)
	struct variable_packer<T>
	{
	public:
		[[nodiscard]] static consteval FormType GetObjectTypeID() noexcept
		{
			using element_type = std::add_pointer_t<typename T::element_type>;
			return Impl::GetObjectTypeID<element_type>();
		}

		[[nodiscard]] static auto GetTypeInfo() -> std::optional<TypeInfo>
		{
			using element_type = std::add_pointer_t<typename T::element_type>;
			return Impl::GetTypeInfo<element_type>();
		}

		static void PackVariable(Variable& a_var, T a_val)
		{
			Impl::PackVariable(a_var, a_val.get());
		}

		[[nodiscard]] static auto UnpackVariable(const Variable& a_var) -> std::remove_cv_t<T>
		{
			using element_type = std::add_pointer_t<typename T::element_type>;

			if (!a_var.IsObject()) [[unlikely]] {
				REX::Assert(a_var.IsNone());
				return {};
			}

			auto* element = Impl::UnpackVariable<element_type>(a_var);
			if (!element) {
				return {};
			}

			return BSPointerHandleManagerInterface<std::remove_pointer_t<element_type>>::GetHandle(element);
		}
	};

	template <class T>
		requires(Impl::form_ptr<T>)
	struct variable_packer<T>
	{
	public:
		[[nodiscard]] static consteval FormType GetObjectTypeID() noexcept
		{
			using value_type = std::remove_pointer_t<T>;
			return value_type::FORM_TYPE;
		}

		[[nodiscard]] static auto GetTypeInfo() -> std::optional<TypeInfo>
		{
			const auto scriptVM = GameVM::GetVMInterface();
			if (!scriptVM) [[unlikely]] {
				REX::Assert(false);
				return std::nullopt;
			}

			auto objectTypeInfo = BSTSmartPointer<ObjectTypeInfo>();
			if (!scriptVM->GetScriptObjectType(Impl::GetObjectTypeID<T>(), objectTypeInfo) || !objectTypeInfo) [[unlikely]] {
				REX::Assert(false);
				return std::nullopt;
			}

			return objectTypeInfo.get();
		}

		static void PackVariable(Variable& a_var, T a_val)
		{
			if (!a_val) {
				a_var.SetNone();
				return;
			}

			const auto scriptVM = GameVM::GetVMInterface();
			if (!scriptVM) [[unlikely]] {
				REX::Assert(false);
				a_var.SetNone();
				return;
			}

			const auto typeInfo = Impl::GetTypeInfo<T>();
			if (!typeInfo) [[unlikely]] {
				REX::Assert(false);
				a_var.SetNone();
				return;
			}

			auto* objectTypeInfo = typeInfo->GetObjectTypeInfo();
			if (!objectTypeInfo) [[unlikely]] {
				REX::Assert(false);
				a_var.SetNone();
				return;
			}

			const auto objectHandle = GameScript::HandlePolicy::GetHandleForTemplateObject(*a_val);
			if (objectHandle == GameScript::HandlePolicy::EMPTY_HANDLE) {
				a_var.SetNone();
				return;
			}

			auto object = BSTSmartPointer<Object>();
			if (!scriptVM->GetOrCreateScriptObject(objectTypeInfo->GetName(), objectHandle, object) || !object) [[unlikely]] {
				REX::Assert(false);
				a_var.SetNone();
				return;
			}

			a_var.SetObject(std::move(object));
			a_var.SetComplexType(objectTypeInfo);
		}

		[[nodiscard]] static auto UnpackVariable(const Variable& a_var) -> std::remove_cv_t<T>
		{
			if (!a_var.IsObject()) [[unlikely]] {
				REX::Assert(a_var.IsNone());
				return nullptr;
			}

			const auto object = a_var.GetObject();
			if (!object) {
				return nullptr;
			}

			const auto scriptVM = GameVM::GetVMInterface();
			if (!scriptVM) [[unlikely]] {
				REX::Assert(false);
				return nullptr;
			}

			const auto& objectHandlePolicy = scriptVM->GetObjectHandlePolicy();

			const auto objectHandle = object->GetHandle();
			if (objectHandle == GameScript::HandlePolicy::EMPTY_HANDLE) {
				return nullptr;
			}

			auto* result = objectHandlePolicy.GetObjectForHandle(Impl::GetObjectTypeID<T>(), objectHandle);
			return static_cast<T>(result);
		}
	};

	template <class T>
		requires(Impl::inventory_object<T>)
	struct variable_packer<T>
	{
	public:
		[[nodiscard]] static consteval FormType GetObjectTypeID() noexcept
		{
			return T::FORM_TYPE;
		}

		[[nodiscard]] static auto GetTypeInfo() -> std::optional<TypeInfo>
		{
			const auto scriptVM = GameVM::GetVMInterface();
			if (!scriptVM) [[unlikely]] {
				REX::Assert(false);
				return std::nullopt;
			}

			auto objectTypeInfo = BSTSmartPointer<ObjectTypeInfo>();
			if (!scriptVM->GetScriptObjectType(Impl::GetObjectTypeID<T>(), objectTypeInfo) || !objectTypeInfo) [[unlikely]] {
				REX::Assert(false);
				return std::nullopt;
			}

			return objectTypeInfo.get();
		}

		static void PackVariable(Variable& a_var, const T& a_val)
		{
			if (!a_val) {
				a_var.SetNone();
				return;
			}

			const auto scriptVM = GameVM::GetVMInterface();
			if (!scriptVM) [[unlikely]] {
				REX::Assert(false);
				a_var.SetNone();
				return;
			}

			const auto typeInfo = Impl::GetTypeInfo<T>();
			if (!typeInfo || !typeInfo->IsObject()) [[unlikely]] {
				REX::Assert(false);
				a_var.SetNone();
				return;
			}

			auto* objectTypeInfo = typeInfo->GetObjectTypeInfo();
			if (!objectTypeInfo) [[unlikely]] {
				REX::Assert(false);
				a_var.SetNone();
				return;
			}

			const auto objectHandle = a_val.GetHandle();
			if (objectHandle == GameScript::HandlePolicy::EMPTY_HANDLE) {
				a_var.SetNone();
				return;
			}

			auto object = BSTSmartPointer<Object>();
			if (!scriptVM->GetOrCreateScriptObject(objectTypeInfo->GetName(), objectHandle, object) || !object) [[unlikely]] {
				REX::Assert(false);
				a_var.SetNone();
				return;
			}

			a_var.SetObject(std::move(object));
			a_var.SetComplexType(objectTypeInfo);
		}

		[[nodiscard]] static auto UnpackVariable(const Variable& a_var) -> std::remove_cv_t<T>
		{
			if (!a_var.IsObject()) [[unlikely]] {
				REX::Assert(a_var.IsNone());
				return {};
			}

			const auto object = a_var.GetObject();
			if (!object) {
				return {};
			}

			const auto* gameVM = GameVM::GetSingleton();
			if (!gameVM) [[unlikely]] {
				REX::Assert(false);
				return {};
			}

			const auto scriptVM = gameVM->impl;
			if (!scriptVM) [[unlikely]] {
				REX::Assert(false);
				return {};
			}

			const auto objectHandle = object->GetHandle();
			if (objectHandle == GameScript::HandlePolicy::EMPTY_HANDLE) {
				return {};
			}

			return T(*gameVM, objectHandle);
		}
	};

	template <class T>
		requires(Impl::vm_object_ptr<T>)
	struct variable_packer<T>
	{
	public:
		[[nodiscard]] static consteval FormType GetObjectTypeID() noexcept
		{
			using element_type = T::element_type;
			return element_type::FORM_TYPE;
		}

		[[nodiscard]] static auto GetTypeInfo() -> std::optional<TypeInfo>
		{
			const auto scriptVM = GameVM::GetVMInterface();
			if (!scriptVM) [[unlikely]] {
				REX::Assert(false);
				return std::nullopt;
			}

			auto objectTypeInfo = BSTSmartPointer<ObjectTypeInfo>();
			if (!scriptVM->GetScriptObjectType(Impl::GetObjectTypeID<T>(), objectTypeInfo) || !objectTypeInfo) [[unlikely]] {
				REX::Assert(false);
				return std::nullopt;
			}

			return objectTypeInfo.get();
		}

		static void PackVariable(Variable& a_var, T a_val)
		{
			const auto typeInfo = Impl::GetTypeInfo<T>();
			if (!typeInfo) [[unlikely]] {
				REX::Assert(false);
				return;
			}

			auto* objectTypeInfo = typeInfo->GetObjectTypeInfo();
			if (!objectTypeInfo) [[unlikely]] {
				REX::Assert(false);
				return;
			}

			a_var.SetObject(std::move(a_val));
			a_var.SetComplexType(objectTypeInfo);
		}

		[[nodiscard]] static auto UnpackVariable(const Variable& a_var) -> std::remove_cv_t<T>
		{
			if (!a_var.IsObject()) [[unlikely]] {
				REX::Assert(a_var.IsNone());
				return {};
			}

			auto object = a_var.GetObject();
			if (!object) {
				return {};
			}

			return object;
		}
	};

	template <class T>
		requires(Impl::string<T>)
	struct variable_packer<T>
	{
	public:
		[[nodiscard]] static consteval FormType GetObjectTypeID() = delete;

		[[nodiscard]] static auto GetTypeInfo() -> std::optional<TypeInfo>
		{
			return TypeInfo::RawType::kString;
		}

		static void PackVariable(Variable& a_var, T a_val)
		{
			a_var.SetString(RE::BSFixedString(std::move(a_val)));
		}

		[[nodiscard]] static auto UnpackVariable(const Variable& a_var) -> std::remove_cv_t<T>
		{
			if (!a_var.IsString()) [[unlikely]] {
				REX::Assert(a_var.IsNone());
				return {};
			}

			return T(a_var.GetString());
		}
	};

	template <class T>
		requires(Impl::wstring<T>)
	struct variable_packer<T>
	{
	public:
		[[nodiscard]] static consteval FormType GetObjectTypeID() = delete;

		[[nodiscard]] static auto GetTypeInfo() -> std::optional<TypeInfo>
		{
			return TypeInfo::RawType::kString;
		}

		static void PackVariable(Variable& a_var, const T& a_val)
		{
			auto u8String = REX::Utf16ToUtf8(a_val);
			if (!u8String) {
				a_var.SetString(BSFixedString());
				return;
			}

			a_var.SetString(BSFixedString(*std::move(u8String)));
		}

		[[nodiscard]] static auto UnpackVariable(const Variable& a_var) -> std::remove_cv_t<T>
		{
			if (!a_var.IsString()) [[unlikely]] {
				REX::Assert(a_var.IsNone());
				return {};
			}

			auto u16String = REX::Utf8ToUtf16(a_var.GetString());
			if (!u16String) {
				return {};
			}

			return T(*std::move(u16String));
		}
	};

	template <class T>
		requires(Impl::fs_path<T>)
	struct variable_packer<T>
	{
	public:
		[[nodiscard]] static consteval FormType GetObjectTypeID() = delete;

		[[nodiscard]] static auto GetTypeInfo() -> std::optional<TypeInfo>
		{
			return TypeInfo::RawType::kString;
		}

		static void PackVariable(Variable& a_var, const T& a_val)
		{
			auto u8String = a_val.generic_string();
			a_var.SetString(BSFixedString(std::move(u8String)));
		}

		[[nodiscard]] static auto UnpackVariable(const Variable& a_var) -> std::remove_cv_t<T>
		{
			if (!a_var.IsString()) [[unlikely]] {
				REX::Assert(a_var.IsNone());
				return {};
			}

			const auto string = a_var.GetString();
			return T(static_cast<std::string_view>(string), std::filesystem::path::generic_format);
		}
	};

	template <class T>
		requires(Impl::integral<T>)
	struct variable_packer<T>
	{
	public:
		[[nodiscard]] static consteval FormType GetObjectTypeID() = delete;

		[[nodiscard]] static auto GetTypeInfo() -> std::optional<TypeInfo>
		{
			return TypeInfo::RawType::kInt;
		}

		static void PackVariable(Variable& a_var, T a_val)
		{
			a_var.SetInt(static_cast<std::int32_t>(a_val));
		}

		[[nodiscard]] static auto UnpackVariable(const Variable& a_var) -> std::remove_cv_t<T>
		{
			if (!a_var.IsInt()) [[unlikely]] {
				REX::Assert(a_var.IsNone());
				return {};
			}

			return static_cast<T>(a_var.GetInt());
		}
	};

	template <class T>
		requires(Impl::floating_point<T>)
	struct variable_packer<T>
	{
	public:
		[[nodiscard]] static consteval FormType GetObjectTypeID() = delete;

		[[nodiscard]] static auto GetTypeInfo() -> std::optional<TypeInfo>
		{
			return TypeInfo::RawType::kFloat;
		}

		static void PackVariable(Variable& a_var, T a_val)
		{
			a_var.SetFloat(static_cast<REX::Float32>(a_val));
		}

		[[nodiscard]] static auto UnpackVariable(const Variable& a_var) -> std::remove_cv_t<T>
		{
			if (!a_var.IsFloat()) [[unlikely]] {
				REX::Assert(a_var.IsNone());
				return {};
			}

			return static_cast<T>(a_var.GetFloat());
		}
	};

	template <class T>
		requires(Impl::boolean<T>)
	struct variable_packer<T>
	{
	public:
		[[nodiscard]] static consteval FormType GetObjectTypeID() = delete;

		[[nodiscard]] static auto GetTypeInfo() -> std::optional<TypeInfo>
		{
			return TypeInfo::RawType::kBool;
		}

		static void PackVariable(Variable& a_var, T a_val)
		{
			a_var.SetBool(static_cast<bool>(a_val));
		}

		[[nodiscard]] static auto UnpackVariable(const Variable& a_var) -> std::remove_cv_t<T>
		{
			if (!a_var.IsBool()) [[unlikely]] {
				REX::Assert(a_var.IsNone());
				return {};
			}

			return static_cast<T>(a_var.GetBool());
		}
	};

	template <class T>
		requires(Impl::vm_shared_var<T>)
	struct variable_packer<T>
	{
	public:
		[[nodiscard]] static consteval FormType GetObjectTypeID() = delete;

		[[nodiscard]] static auto GetTypeInfo() -> std::optional<TypeInfo>
		{
			return TypeInfo::RawType::kVar;
		}

		static void PackVariable(Variable& a_var, T a_val)
		{
			a_var.SetVar(a_val);
		}

		[[nodiscard]] static auto UnpackVariable(const Variable& a_var) -> std::remove_cv_t<T>
		{
			if (!a_var.IsVar()) [[unlikely]] {
				REX::Assert(a_var.IsNone());
				return nullptr;
			}

			return a_var.GetVar();
		}
	};

	template <class T>
		requires(Impl::vm_unique_var<T>)
	struct variable_packer<T>
	{
	public:
		[[nodiscard]] static consteval FormType GetObjectTypeID() = delete;

		[[nodiscard]] static auto GetTypeInfo() -> std::optional<TypeInfo>
		{
			return TypeInfo::RawType::kVar;
		}

		static void PackVariable(Variable& a_var, T a_val)
		{
			a_var.SetVar(std::move(a_val));
		}

		[[nodiscard]] static auto UnpackVariable(const Variable& a_var) -> std::remove_cv_t<T>
		{
			if (!a_var.IsVar()) [[unlikely]] {
				REX::Assert(a_var.IsNone());
				return {};
			}

			const auto* value = a_var.GetVar();
			if (!value) {
				return {};
			}

			return BSScript::CreateVariant(*value);
		}
	};

	template <class T>
		requires(Impl::array<T> && Impl::valid_parameter<typename T::value_type>)
	struct variable_packer<T>
	{
	public:
		[[nodiscard]] static consteval FormType GetObjectTypeID() = delete;

		[[nodiscard]] static auto GetTypeInfo() -> std::optional<TypeInfo>
		{
			using value_type = T::value_type;

			auto typeInfo = Impl::GetTypeInfo<value_type>();
			if (!typeInfo) [[unlikely]] {
				REX::Assert(false);
				return std::nullopt;
			}

			typeInfo->SetIsArray(true);
			return typeInfo;
		}

		static void PackVariable(Variable& a_var, T a_val)
		{
			using reference_type =
				std::conditional_t<
					std::is_const_v<T>,
					std::add_lvalue_reference_t<typename T::value_type>,
					std::add_rvalue_reference_t<typename T::value_type>>;
			using size_type = Array::size_type;

			const auto scriptVM = GameVM::GetVMInterface();
			if (!scriptVM) [[unlikely]] {
				REX::Assert(false);
				a_var.SetNone();
				return;
			}

			const auto typeInfo = Impl::GetTypeInfo<T>();
			if (!typeInfo) [[unlikely]] {
				REX::Assert(false);
				a_var.SetNone();
				return;
			}

			const auto arraySize = static_cast<size_type>(a_val.size());

			auto result = BSTSmartPointer<Array>();
			if (!scriptVM->CreateArray(*typeInfo, arraySize, result) || !result) [[unlikely]] {
				REX::Assert(false);
				a_var.SetNone();
				return;
			}

			const auto arrayLock = BSAutoLock(result->elementsLock);

			for (auto i = static_cast<size_type>(0); i < arraySize; i++) {
				Impl::PackVariable(result->elements[i], static_cast<reference_type>(a_val[i]));
			}

			a_var.SetArray(std::move(result));
		}

		[[nodiscard]] static auto UnpackVariable(const Variable& a_var) -> std::remove_cv_t<T>
		{
			using value_type = T::value_type;
			using size_type = T::size_type;

			if (!a_var.IsArray()) [[unlikely]] {
				REX::Assert(a_var.IsNone());
				return {};
			}

			const auto array = a_var.GetArray();
			if (!array) {
				return {};
			}

			const auto arrayLock = BSAutoLock(array->elementsLock);

			const auto& arrayElements = array->elements;
			const auto arraySize = static_cast<size_type>(arrayElements.size());

			auto result = T();
			if constexpr (Impl::reservable<T>) {
				result.reserve(arraySize);
			}

			for (auto i = static_cast<size_type>(0); i < arraySize; i++) {
				result.push_back(Impl::UnpackVariable<value_type>(arrayElements[i]));
			}

			return result;
		}
	};

	template <class T>
		requires(Impl::vm_object_wrapper<T>)
	struct variable_packer<T>
	{
	public:
		[[nodiscard]] static consteval FormType GetObjectTypeID() = delete;

		[[nodiscard]] static auto GetTypeInfo() -> std::optional<TypeInfo>
		{
			const auto scriptVM = GameVM::GetVMInterface();
			if (!scriptVM) [[unlikely]] {
				REX::Assert(false);
				return std::nullopt;
			}

			auto objectTypeInfo = BSTSmartPointer<ObjectTypeInfo>();
			if (!scriptVM->GetScriptObjectType(BSFixedString(T::TYPE_NAME), objectTypeInfo) || !objectTypeInfo) [[unlikely]] {
				REX::Assert(false);
				return std::nullopt;
			}

			return objectTypeInfo.get();
		}

		static void PackVariable(Variable& a_var, T a_val)
		{
			a_var.SetObject(std::move(a_val).get());
		}

		[[nodiscard]] static auto UnpackVariable(const Variable& a_var) -> std::remove_cv_t<T>
		{
			if (!a_var.IsObject()) [[unlikely]] {
				REX::Assert(a_var.IsNone());
				return nullptr;
			}

			const auto object = a_var.GetObject();
			if (!object) {
				return nullptr;
			}

			return T(object);
		}
	};

	template <class T>
		requires(Impl::vm_struct_wrapper<T>)
	struct variable_packer<T>
	{
	public:
		[[nodiscard]] static consteval FormType GetObjectTypeID() = delete;

		[[nodiscard]] static auto GetTypeInfo() -> std::optional<TypeInfo>
		{
			const auto scriptVM = GameVM::GetVMInterface();
			if (!scriptVM) [[unlikely]] {
				REX::Assert(false);
				return std::nullopt;
			}

			auto structTypeInfo = BSTSmartPointer<StructTypeInfo>();
			if (!scriptVM->GetScriptStructType(BSFixedString(T::TYPE_NAME), structTypeInfo) || !structTypeInfo) [[unlikely]] {
				REX::Assert(false);
				return std::nullopt;
			}

			return structTypeInfo.get();
		}

		static void PackVariable(Variable& a_var, T a_val)
		{
			a_var.SetStruct(std::move(a_val).get());
		}

		[[nodiscard]] static auto UnpackVariable(const Variable& a_var) -> std::remove_cv_t<T>
		{
			if (!a_var.IsStruct()) [[unlikely]] {
				REX::Assert(a_var.IsNone());
				return nullptr;
			}

			const auto structure = a_var.GetStruct();
			if (!structure) {
				return nullptr;
			}

			return T(structure);
		}
	};

	template <class T>
		requires(Impl::vm_array_wrapper<T> && Impl::valid_parameter<typename T::element_type>)
	struct variable_packer<T>
	{
	public:
		[[nodiscard]] static consteval FormType GetObjectTypeID() = delete;

		[[nodiscard]] static auto GetTypeInfo() -> std::optional<TypeInfo>
		{
			using element_type = T::element_type;

			auto typeInfo = Impl::GetTypeInfo<element_type>();
			if (!typeInfo) [[unlikely]] {
				REX::Assert(false);
				return std::nullopt;
			}

			typeInfo->SetIsArray(true);
			return typeInfo;
		}

		static void PackVariable(Variable& a_var, T a_val)
		{
			a_var.SetArray(std::move(a_val).get());
		}

		[[nodiscard]] static auto UnpackVariable(const Variable& a_var) -> std::remove_cv_t<T>
		{
			if (!a_var.IsArray()) [[unlikely]] {
				REX::Assert(a_var.IsNone());
				return nullptr;
			}

			const auto array = a_var.GetArray();
			if (!array) {
				return nullptr;
			}

			return T(array);
		}
	};

	template <class T>
		requires(Impl::optional<T> && Impl::valid_parameter<typename T::value_type>)
	struct variable_packer<T>
	{
	public:
		[[nodiscard]] static consteval FormType GetObjectTypeID() = delete;

		[[nodiscard]] static auto GetTypeInfo() -> std::optional<TypeInfo>
		{
			using value_type = T::value_type;
			return Impl::GetTypeInfo<value_type>();
		}

		static void PackVariable(Variable& a_var, T a_val)
		{
			if (!a_val) {
				a_var.SetNone();
				return;
			}

			Impl::PackVariable(a_var, *std::move(a_val));
		}

		[[nodiscard]] static auto UnpackVariable(const Variable& a_var) -> std::remove_cv_t<T>
		{
			using value_type = T::value_type;

			if (a_var.IsNone()) {
				return std::nullopt;
			}

			return Impl::UnpackVariable<value_type>(a_var);
		}
	};

	template <class T>
		requires(Impl::void_result<T>)
	struct variable_packer<T>
	{
	public:
		[[nodiscard]] static consteval FormType GetObjectTypeID() = delete;

		[[nodiscard]] static auto GetTypeInfo() -> std::optional<TypeInfo>
		{
			return TypeInfo::RawType::kNone;
		}

		// static void PackVariable(Variable& a_var, T a_val) = delete;

		// [[nodiscard]] static auto UnpackVariable(const Variable& a_var) -> std::remove_cv_t<T> = delete;
	};
}

namespace RE::BSScript
{
	template <class T>
	[[nodiscard]] consteval FormType GetObjectTypeID() noexcept
		requires(requires { BSScript::variable_packer<T>::GetObjectTypeID(); })
	{
		return Impl::GetObjectTypeID<T>();
	}

	template <class T>
	[[nodiscard]] __forceinline std::optional<TypeInfo> GetTypeInfo()
		requires(requires { BSScript::variable_packer<T>::GetTypeInfo(); })
	{
		return Impl::GetTypeInfo<T>();
	}

	template <class T>
	__forceinline void PackVariable(Variable& a_var, T&& a_val)
		requires(requires { BSScript::variable_packer<std::remove_reference_t<T>>::PackVariable(a_var, std::forward<T>(a_val)); })
	{
		Impl::PackVariable(a_var, std::forward<T>(a_val));
	}

	template <class T>
	[[nodiscard]] __forceinline T UnpackVariable(const Variable& a_var)
		requires(requires { BSScript::variable_packer<T>::UnpackVariable(a_var); })
	{
		return Impl::UnpackVariable<T>(a_var);
	}

	template <class... Args>
	[[nodiscard]] BSScrapArray<Variable> PackVariables(Args&&... a_args)
		requires((BSScript::ValidateParameter<std::remove_reference_t<Args>>() && ...))
	{
		constexpr auto SIZE = sizeof...(a_args);

		auto args = std::make_tuple(std::forward<Args>(a_args)...);
		auto result = BSScrapArray<Variable>(SIZE);

		[&result, &args]<std::size_t... Indexes>(std::index_sequence<Indexes...>) {
			((Impl::PackVariable(result[Indexes], std::get<Indexes>(args))), ...);
		}(std::make_index_sequence<SIZE>());

		return result;
	}

	template <class... Args>
	[[nodiscard]] auto CreateThreadScrapFunction(Args&&... a_args) -> BSTThreadScrapFunction<bool(BSScrapArray<Variable>&)>
		requires((BSScript::ValidateParameter<std::remove_reference_t<Args>>() && ...))
	{
		return [... a_args = std::forward<Args>(a_args)](BSScrapArray<Variable>& a_out) mutable {
			a_out = PackVariables(std::forward<Args>(a_args)...);
			return true;
		};
	}

	[[nodiscard]] inline auto CreateAppliedThreadScrapFunction(std::span<const Variable> a_args) -> BSTThreadScrapFunction<bool(BSScrapArray<Variable>&)>
	{
		return [a_args = a_args](BSScrapArray<Variable>& a_out) {
			a_out = { a_args.begin(), a_args.end() };
			return true;
		};
	}

	[[nodiscard]] inline auto CreateAppliedThreadScrapFunction(BSScrapArray<Variable>&& a_args) -> BSTThreadScrapFunction<bool(BSScrapArray<Variable>&)>
	{
		return [a_args = std::move(a_args)](BSScrapArray<Variable>& a_out) mutable {
			a_out = std::move(a_args);
			return true;
		};
	}
}

namespace RE::BSScript::Impl
{
	template <class T>
	[[nodiscard]] consteval FormType GetObjectTypeID() noexcept
	{
		return BSScript::variable_packer<T>::GetObjectTypeID();
	}

	template <class T>
	[[nodiscard]] __forceinline std::optional<TypeInfo> GetTypeInfo()
	{
		return BSScript::variable_packer<T>::GetTypeInfo();
	}

	template <class T>
	__forceinline void PackVariable(Variable& a_var, T&& a_val)
	{
		BSScript::variable_packer<std::remove_reference_t<T>>::PackVariable(a_var, std::forward<T>(a_val));
	}

	template <class T>
	[[nodiscard]] __forceinline T UnpackVariable(const Variable& a_var)
	{
		return BSScript::variable_packer<T>::UnpackVariable(a_var);
	}
}
