#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSScriptUtility_Concepts.hpp"
#include "RE/B/BSScript_Array.hpp"
#include "RE/B/BSScript_IVirtualMachine.hpp"
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

namespace RE::BSScript
{
	template <class T>
		requires(
			Impl::bs_pointer<T> &&
			!Impl::vm_object_pointer<T> &&
			Impl::valid_parameter<std::add_pointer_t<typename T::element_type>>)
	struct variable_packer<T>
	{
	public:
		variable_packer() = delete;

		[[nodiscard]]
		static consteval auto GetObjectTypeID() noexcept -> FormType
		{
			using element_type = std::add_pointer_t<typename T::element_type>;
			return Impl::GetObjectTypeID<element_type>();
		}

		[[nodiscard]]
		static auto GetTypeInfo(IVirtualMachine& a_vm) -> std::optional<TypeInfo>
		{
			using element_type = std::add_pointer_t<typename T::element_type>;
			return Impl::GetTypeInfo<element_type>(a_vm);
		}

		static auto PackVariable(IVirtualMachine& a_vm, Variable& a_var, T a_val) -> bool
		{
			return Impl::PackVariable(a_vm, a_var, a_val.get());
		}

		[[nodiscard]]
		static auto UnpackVariable(IVirtualMachine& a_vm, const Variable& a_var) -> std::optional<std::remove_cv_t<T>>
		{
			using element_type = std::add_pointer_t<typename T::element_type>;

			if (!a_var.IsObject()) {
				return std::nullopt;
			}

			auto element = Impl::UnpackVariable<element_type>(a_vm, a_var);
			if (!element.has_value()) {
				return std::nullopt;
			}

			return std::remove_cv_t<T>(std::move(element).value());
		}
	};

	template <class T>
		requires(Impl::ni_pointer<T> && Impl::valid_parameter<std::add_pointer_t<typename T::element_type>>)
	struct variable_packer<T>
	{
	public:
		variable_packer() = delete;

		[[nodiscard]]
		static consteval auto GetObjectTypeID() noexcept -> FormType
		{
			using element_type = std::add_pointer_t<typename T::element_type>;
			return Impl::GetObjectTypeID<element_type>();
		}

		[[nodiscard]]
		static auto GetTypeInfo(IVirtualMachine& a_vm) -> std::optional<TypeInfo>
		{
			using element_type = std::add_pointer_t<typename T::element_type>;
			return Impl::GetTypeInfo<element_type>(a_vm);
		}

		static auto PackVariable(IVirtualMachine& a_vm, Variable& a_var, T a_val) -> bool
		{
			return Impl::PackVariable(a_vm, a_var, a_val.get());
		}

		[[nodiscard]]
		static auto UnpackVariable(IVirtualMachine& a_vm, const Variable& a_var) -> std::optional<std::remove_cv_t<T>>
		{
			using element_type = std::add_pointer_t<typename T::element_type>;

			if (!a_var.IsObject()) {
				return std::nullopt;
			}

			auto element = Impl::UnpackVariable<element_type>(a_vm, a_var);
			if (!element.has_value()) {
				return std::nullopt;
			}

			return std::remove_cv_t<T>(std::move(element).value());
		}
	};

	template <class T>
		requires(Impl::bs_handle_pointer<T> && Impl::valid_parameter<std::add_pointer_t<typename T::element_type>>)
	struct variable_packer<T>
	{
	public:
		variable_packer() = delete;

		[[nodiscard]]
		static consteval auto GetObjectTypeID() noexcept -> FormType
		{
			using element_type = std::add_pointer_t<typename T::element_type>;
			return Impl::GetObjectTypeID<element_type>();
		}

		[[nodiscard]]
		static auto GetTypeInfo(IVirtualMachine& a_vm) -> std::optional<TypeInfo>
		{
			using element_type = std::add_pointer_t<typename T::element_type>;
			return Impl::GetTypeInfo<element_type>(a_vm);
		}

		static auto PackVariable(IVirtualMachine& a_vm, Variable& a_var, T a_val) -> bool
		{
			return Impl::PackVariable(a_vm, a_var, a_val.get());
		}

		[[nodiscard]]
		static auto UnpackVariable(IVirtualMachine& a_vm, const Variable& a_var) -> std::optional<std::remove_cv_t<T>>
		{
			using element_type = std::add_pointer_t<typename T::element_type>;

			if (!a_var.IsObject()) {
				return std::nullopt;
			}

			auto element = Impl::UnpackVariable<element_type>(a_vm, a_var);
			if (!element.has_value()) {
				return std::nullopt;
			}

			return BSPointerHandleManagerInterface<std::remove_pointer_t<element_type>>::GetHandle(
				std::move(element).value());
		}
	};

	template <class T>
		requires(Impl::form_pointer<T>)
	struct variable_packer<T>
	{
	public:
		variable_packer() = delete;

		[[nodiscard]]
		static consteval auto GetObjectTypeID() noexcept -> FormType
		{
			using value_type = std::remove_pointer_t<T>;
			return value_type::FORM_TYPE;
		}

		[[nodiscard]]
		static auto GetTypeInfo(IVirtualMachine& a_vm) -> std::optional<TypeInfo>
		{
			auto objectTypeInfo = BSTSmartPointer<ObjectTypeInfo>();
			if (!a_vm.GetScriptObjectType(Impl::GetObjectTypeID<T>(), objectTypeInfo) || !objectTypeInfo) {
				return std::nullopt;
			}

			return TypeInfo(objectTypeInfo);
		}

		static auto PackVariable(IVirtualMachine& a_vm, Variable& a_var, T a_val) -> bool
		{
			if (!a_val) {
				a_var.SetNone();
				return true;
			}

			const auto typeInfo = Impl::GetTypeInfo<T>(a_vm);
			if (!typeInfo.has_value()) {
				a_var.SetNone();
				return false;
			}

			auto objectTypeInfo = typeInfo->GetObjectTypeInfo();
			if (!objectTypeInfo) {
				a_var.SetNone();
				return false;
			}

			const auto objectHandle = GameScript::HandlePolicy::GetHandleForTemplateObject(*a_val);
			if (objectHandle == GameScript::HandlePolicy::EMPTY_HANDLE) {
				a_var.SetNone();
				return true;
			}

			auto object = BSTSmartPointer<Object>();
			if (!a_vm.GetOrCreateScriptObject(objectTypeInfo->GetName(), objectHandle, object) || !object) {
				a_var.SetNone();
				return false;
			}

			a_var.SetObject(std::move(object));
			a_var.SetComplexType(objectTypeInfo);
			return true;
		}

		[[nodiscard]]
		static auto UnpackVariable(IVirtualMachine& a_vm, const Variable& a_var) -> std::optional<std::remove_cv_t<T>>
		{
			if (!a_var.IsObject()) {
				return std::nullopt;
			}

			const auto object = a_var.GetObject();
			if (!object) {
				return std::remove_cv_t<T>();
			}

			const auto& objectHandlePolicy = a_vm.GetObjectHandlePolicy();

			const auto objectHandle = object->GetHandle();
			if (objectHandle == GameScript::HandlePolicy::EMPTY_HANDLE) {
				return std::remove_cv_t<T>();
			}

			auto* result = objectHandlePolicy.GetObjectForHandle(Impl::GetObjectTypeID<T>(), objectHandle);
			return std::remove_cv_t<T>(result);
		}
	};

	template <class T>
		requires(Impl::inventory_object<T>)
	struct variable_packer<T>
	{
	public:
		variable_packer() = delete;

		[[nodiscard]]
		static consteval auto GetObjectTypeID() noexcept -> FormType
		{
			return T::FORM_TYPE;
		}

		[[nodiscard]]
		static auto GetTypeInfo(IVirtualMachine& a_vm) -> std::optional<TypeInfo>
		{
			auto objectTypeInfo = BSTSmartPointer<ObjectTypeInfo>();
			if (!a_vm.GetScriptObjectType(Impl::GetObjectTypeID<T>(), objectTypeInfo) || !objectTypeInfo) {
				return std::nullopt;
			}

			return TypeInfo(objectTypeInfo);
		}

		static auto PackVariable(IVirtualMachine& a_vm, Variable& a_var, const T& a_val) -> bool
		{
			if (!a_val) {
				a_var.SetNone();
				return true;
			}

			const auto typeInfo = Impl::GetTypeInfo<T>(a_vm);
			if (!typeInfo) {
				a_var.SetNone();
				return false;
			}

			auto objectTypeInfo = typeInfo->GetObjectTypeInfo();
			if (!objectTypeInfo) {
				a_var.SetNone();
				return false;
			}

			const auto objectHandle = a_val.GetHandle();
			if (objectHandle == GameScript::HandlePolicy::EMPTY_HANDLE) {
				a_var.SetNone();
				return true;
			}

			auto object = BSTSmartPointer<Object>();
			if (!a_vm.GetOrCreateScriptObject(objectTypeInfo->GetName(), objectHandle, object) || !object) {
				a_var.SetNone();
				return false;
			}

			a_var.SetObject(std::move(object));
			a_var.SetComplexType(objectTypeInfo);
			return true;
		}

		[[nodiscard]]
		static auto UnpackVariable(IVirtualMachine& a_vm, const Variable& a_var) -> std::optional<std::remove_cv_t<T>>
		{
			if (!a_var.IsObject()) {
				return std::nullopt;
			}

			const auto object = a_var.GetObject();
			if (!object) {
				return std::remove_cv_t<T>();
			}

			const auto objectHandle = object->GetHandle();
			if (objectHandle == GameScript::HandlePolicy::EMPTY_HANDLE) {
				return std::remove_cv_t<T>();
			}

			const auto* handlePolicy =
				DynamicCast<const GameScript::HandlePolicy*>(std::addressof(a_vm.GetObjectHandlePolicy()));
			if (!handlePolicy) {
				return std::nullopt;
			}

			return std::remove_cv_t<T>(*handlePolicy, objectHandle);
		}
	};

	template <class T>
		requires(Impl::vm_object_pointer<T>)
	struct variable_packer<T>
	{
	public:
		variable_packer() = delete;

		[[nodiscard]]
		static consteval auto GetObjectTypeID() noexcept -> FormType
		{
			using element_type = T::element_type;
			return element_type::FORM_TYPE;
		}

		[[nodiscard]]
		static auto GetTypeInfo(IVirtualMachine& a_vm) -> std::optional<TypeInfo>
		{
			auto objectTypeInfo = BSTSmartPointer<ObjectTypeInfo>();
			if (!a_vm.GetScriptObjectType(Impl::GetObjectTypeID<T>(), objectTypeInfo) || !objectTypeInfo) {
				return std::nullopt;
			}

			return TypeInfo(objectTypeInfo);
		}

		static auto PackVariable(IVirtualMachine& a_vm, Variable& a_var, T a_val) -> bool
		{
			const auto typeInfo = Impl::GetTypeInfo<T>(a_vm);
			if (!typeInfo.has_value()) {
				return false;
			}

			auto objectTypeInfo = typeInfo->GetObjectTypeInfo();
			if (!objectTypeInfo) {
				return false;
			}

			a_var.SetObject(std::move(a_val));
			a_var.SetComplexType(objectTypeInfo);
			return true;
		}

		[[nodiscard]]
		static auto UnpackVariable([[maybe_unused]] IVirtualMachine& a_vm, const Variable& a_var)
			-> std::optional<std::remove_cv_t<T>>
		{
			if (!a_var.IsObject()) {
				return std::nullopt;
			}

			return std::remove_cv_t<T>(a_var.GetObject());
		}
	};

	template <class T>
		requires(Impl::string<T>)
	struct variable_packer<T>
	{
	public:
		variable_packer() = delete;

		[[nodiscard]]
		static consteval auto GetObjectTypeID() noexcept -> FormType = delete;

		[[nodiscard]]
		static auto GetTypeInfo([[maybe_unused]] IVirtualMachine& a_vm) noexcept -> std::optional<TypeInfo>
		{
			return TypeInfo(TypeInfo::RawType::String);
		}

		static auto PackVariable([[maybe_unused]] IVirtualMachine& a_vm, Variable& a_var, T a_val) -> bool
		{
			a_var.SetString(BSFixedString(std::move(a_val)));
			return true;
		}

		[[nodiscard]]
		static auto UnpackVariable([[maybe_unused]] IVirtualMachine& a_vm, const Variable& a_var)
			-> std::optional<std::remove_cv_t<T>>
		{
			if (!a_var.IsString()) {
				return std::nullopt;
			}

			return std::remove_cv_t<T>(a_var.GetString());
		}
	};

	template <class T>
		requires(Impl::wstring<T>)
	struct variable_packer<T>
	{
	public:
		variable_packer() = delete;

		[[nodiscard]]
		static consteval auto GetObjectTypeID() noexcept -> FormType = delete;

		[[nodiscard]]
		static auto GetTypeInfo([[maybe_unused]] IVirtualMachine& a_vm) noexcept -> std::optional<TypeInfo>
		{
			return TypeInfo(TypeInfo::RawType::String);
		}

		static auto PackVariable([[maybe_unused]] IVirtualMachine& a_vm, Variable& a_var, const T& a_val) -> bool
		{
			auto u8String = REX::Utf16ToUtf8(a_val);
			if (!u8String.has_value()) {
				a_var.SetString(BSFixedString());
				return false;
			}

			a_var.SetString(BSFixedString(std::move(u8String).value()));
			return true;
		}

		[[nodiscard]]
		static auto UnpackVariable([[maybe_unused]] IVirtualMachine& a_vm, const Variable& a_var)
			-> std::optional<std::remove_cv_t<T>>
		{
			if (!a_var.IsString()) {
				return std::nullopt;
			}

			auto u16String = REX::Utf8ToUtf16(a_var.GetString());
			if (!u16String.has_value()) {
				return std::nullopt;
			}

			return std::remove_cv_t<T>(std::move(u16String).value());
		}
	};

	template <class T>
		requires(Impl::filesystem_path<T>)
	struct variable_packer<T>
	{
	public:
		variable_packer() = delete;

		[[nodiscard]]
		static consteval auto GetObjectTypeID() noexcept -> FormType = delete;

		[[nodiscard]]
		static auto GetTypeInfo([[maybe_unused]] IVirtualMachine& a_vm) noexcept -> std::optional<TypeInfo>
		{
			return TypeInfo(TypeInfo::RawType::String);
		}

		static auto PackVariable([[maybe_unused]] IVirtualMachine& a_vm, Variable& a_var, const T& a_val) -> bool
		{
			auto u8String = a_val.generic_string();
			a_var.SetString(BSFixedString(std::move(u8String)));
			return true;
		}

		[[nodiscard]]
		static auto UnpackVariable([[maybe_unused]] IVirtualMachine& a_vm, const Variable& a_var)
			-> std::optional<std::remove_cv_t<T>>
		{
			if (!a_var.IsString()) {
				return std::nullopt;
			}

			const auto string = a_var.GetString();
			return std::remove_cv_t<T>(std::string_view(string), std::filesystem::path::generic_format);
		}
	};

	template <class T>
		requires(Impl::integer<T>)
	struct variable_packer<T>
	{
	public:
		variable_packer() = delete;

		[[nodiscard]]
		static consteval auto GetObjectTypeID() noexcept -> FormType = delete;

		[[nodiscard]]
		static auto GetTypeInfo([[maybe_unused]] IVirtualMachine& a_vm) noexcept -> std::optional<TypeInfo>
		{
			return TypeInfo(TypeInfo::RawType::Int);
		}

		static auto PackVariable([[maybe_unused]] IVirtualMachine& a_vm, Variable& a_var, T a_val) -> bool
		{
			a_var.SetInt(static_cast<std::int32_t>(a_val));
			return true;
		}

		[[nodiscard]]
		static auto UnpackVariable([[maybe_unused]] IVirtualMachine& a_vm, const Variable& a_var)
			-> std::optional<std::remove_cv_t<T>>
		{
			if (!a_var.IsInt()) {
				return std::nullopt;
			}

			return static_cast<std::remove_cv_t<T>>(a_var.GetInt());
		}
	};

	template <class T>
		requires(Impl::floating_point<T>)
	struct variable_packer<T>
	{
	public:
		variable_packer() = delete;

		[[nodiscard]]
		static consteval auto GetObjectTypeID() noexcept -> FormType = delete;

		[[nodiscard]]
		static auto GetTypeInfo([[maybe_unused]] IVirtualMachine& a_vm) noexcept -> std::optional<TypeInfo>
		{
			return TypeInfo(TypeInfo::RawType::Float);
		}

		static auto PackVariable([[maybe_unused]] IVirtualMachine& a_vm, Variable& a_var, T a_val) -> bool
		{
			a_var.SetFloat(static_cast<REX::Float32>(a_val));
			return true;
		}

		[[nodiscard]]
		static auto UnpackVariable([[maybe_unused]] IVirtualMachine& a_vm, const Variable& a_var)
			-> std::optional<std::remove_cv_t<T>>
		{
			if (!a_var.IsFloat()) {
				return std::nullopt;
			}

			return static_cast<std::remove_cv_t<T>>(a_var.GetFloat());
		}
	};

	template <class T>
		requires(Impl::boolean<T>)
	struct variable_packer<T>
	{
	public:
		variable_packer() = delete;

		[[nodiscard]]
		static consteval auto GetObjectTypeID() noexcept -> FormType = delete;

		[[nodiscard]]
		static auto GetTypeInfo([[maybe_unused]] IVirtualMachine& a_vm) noexcept -> std::optional<TypeInfo>
		{
			return TypeInfo(TypeInfo::RawType::Bool);
		}

		static auto PackVariable([[maybe_unused]] IVirtualMachine& a_vm, Variable& a_var, T a_val) -> bool
		{
			a_var.SetBool(static_cast<bool>(a_val));
			return true;
		}

		[[nodiscard]]
		static auto UnpackVariable([[maybe_unused]] IVirtualMachine& a_vm, const Variable& a_var)
			-> std::optional<std::remove_cv_t<T>>
		{
			if (!a_var.IsBool()) {
				return std::nullopt;
			}

			return static_cast<std::remove_cv_t<T>>(a_var.GetBool());
		}
	};

	template <class T>
		requires(Impl::chrono_duration<T> && Impl::valid_parameter<typename T::rep>)
	struct variable_packer<T>
	{
	public:
		variable_packer() = delete;

		[[nodiscard]]
		static consteval auto GetObjectTypeID() noexcept -> FormType = delete;

		[[nodiscard]]
		static auto GetTypeInfo(IVirtualMachine& a_vm) -> std::optional<TypeInfo>
		{
			return Impl::GetTypeInfo<typename T::rep>(a_vm);
		}

		static auto PackVariable(IVirtualMachine& a_vm, Variable& a_var, T a_val) -> bool
		{
			return Impl::PackVariable(a_vm, a_var, a_val.count());
		}

		[[nodiscard]]
		static auto UnpackVariable(IVirtualMachine& a_vm, const Variable& a_var) -> std::optional<std::remove_cv_t<T>>
		{
			auto rep = Impl::UnpackVariable<typename T::rep>(a_vm, a_var);
			if (!rep.has_value()) {
				return std::nullopt;
			}

			return std::remove_cv_t<T>(std::move(rep).value());
		}
	};

	template <class T>
		requires(Impl::chrono_time_point<T> && Impl::valid_parameter<typename T::duration>)
	struct variable_packer<T>
	{
	public:
		variable_packer() = delete;

		[[nodiscard]]
		static consteval auto GetObjectTypeID() noexcept -> FormType = delete;

		[[nodiscard]]
		static auto GetTypeInfo(IVirtualMachine& a_vm) -> std::optional<TypeInfo>
		{
			return Impl::GetTypeInfo<typename T::duration>(a_vm);
		}

		static auto PackVariable(IVirtualMachine& a_vm, Variable& a_var, T a_val) -> bool
		{
			return Impl::PackVariable(a_vm, a_var, a_val.time_since_epoch());
		}

		[[nodiscard]]
		static auto UnpackVariable(IVirtualMachine& a_vm, const Variable& a_var) -> std::optional<std::remove_cv_t<T>>
		{
			auto duration = Impl::UnpackVariable<typename T::duration>(a_vm, a_var);
			if (!duration.has_value()) {
				return std::nullopt;
			}

			return std::remove_cv_t<T>(std::move(duration).value());
		}
	};

	template <class T>
		requires(Impl::chrono_year<T>)
	struct variable_packer<T>
	{
	public:
		variable_packer() = delete;

		[[nodiscard]]
		static consteval auto GetObjectTypeID() noexcept -> FormType = delete;

		[[nodiscard]]
		static auto GetTypeInfo([[maybe_unused]] IVirtualMachine& a_vm) noexcept -> std::optional<TypeInfo>
		{
			return TypeInfo(TypeInfo::RawType::Int);
		}

		static auto PackVariable([[maybe_unused]] IVirtualMachine& a_vm, Variable& a_var, T a_val) -> bool
		{
			a_var.SetInt(static_cast<std::int32_t>(a_val));
			return true;
		}

		[[nodiscard]]
		static auto UnpackVariable([[maybe_unused]] IVirtualMachine& a_vm, const Variable& a_var)
			-> std::optional<std::remove_cv_t<T>>
		{
			if (!a_var.IsInt()) {
				return std::nullopt;
			}

			return static_cast<std::remove_cv_t<T>>(a_var.GetInt());
		}
	};

	template <class T>
		requires(Impl::chrono_month<T>)
	struct variable_packer<T>
	{
	public:
		variable_packer() = delete;

		[[nodiscard]]
		static consteval auto GetObjectTypeID() noexcept -> FormType = delete;

		[[nodiscard]]
		static auto GetTypeInfo([[maybe_unused]] IVirtualMachine& a_vm) noexcept -> std::optional<TypeInfo>
		{
			return TypeInfo(TypeInfo::RawType::Int);
		}

		static auto PackVariable([[maybe_unused]] IVirtualMachine& a_vm, Variable& a_var, T a_val) -> bool
		{
			a_var.SetUInt(static_cast<std::uint32_t>(a_val));
			return true;
		}

		[[nodiscard]]
		static auto UnpackVariable([[maybe_unused]] IVirtualMachine& a_vm, const Variable& a_var)
			-> std::optional<std::remove_cv_t<T>>
		{
			if (!a_var.IsUInt()) {
				return std::nullopt;
			}

			return static_cast<std::remove_cv_t<T>>(a_var.GetUInt());
		}
	};

	template <class T>
		requires(Impl::chrono_day<T>)
	struct variable_packer<T>
	{
	public:
		variable_packer() = delete;

		[[nodiscard]]
		static consteval auto GetObjectTypeID() noexcept -> FormType = delete;

		[[nodiscard]]
		static auto GetTypeInfo([[maybe_unused]] IVirtualMachine& a_vm) noexcept -> std::optional<TypeInfo>
		{
			return TypeInfo(TypeInfo::RawType::Int);
		}

		static auto PackVariable([[maybe_unused]] IVirtualMachine& a_vm, Variable& a_var, T a_val) -> bool
		{
			a_var.SetUInt(static_cast<std::uint32_t>(a_val));
			return true;
		}

		[[nodiscard]]
		static auto UnpackVariable([[maybe_unused]] IVirtualMachine& a_vm, const Variable& a_var)
			-> std::optional<std::remove_cv_t<T>>
		{
			if (!a_var.IsUInt()) {
				return std::nullopt;
			}

			return static_cast<std::remove_cv_t<T>>(a_var.GetUInt());
		}
	};

	template <class T>
		requires(Impl::chrono_weekday<T>)
	struct variable_packer<T>
	{
	public:
		variable_packer() = delete;

		[[nodiscard]]
		static consteval auto GetObjectTypeID() noexcept -> FormType = delete;

		[[nodiscard]]
		static auto GetTypeInfo([[maybe_unused]] IVirtualMachine& a_vm) noexcept -> std::optional<TypeInfo>
		{
			return TypeInfo(TypeInfo::RawType::Int);
		}

		static auto PackVariable([[maybe_unused]] IVirtualMachine& a_vm, Variable& a_var, T a_val) -> bool
		{
			a_var.SetUInt(a_val.iso_encoding());
			return true;
		}

		[[nodiscard]]
		static auto UnpackVariable([[maybe_unused]] IVirtualMachine& a_vm, const Variable& a_var)
			-> std::optional<std::remove_cv_t<T>>
		{
			if (!a_var.IsUInt()) {
				return std::nullopt;
			}

			return static_cast<std::remove_cv_t<T>>(a_var.GetUInt());
		}
	};

	template <class T>
		requires(Impl::vm_shared_variant<T>)
	struct variable_packer<T>
	{
	public:
		variable_packer() = delete;

		[[nodiscard]]
		static consteval auto GetObjectTypeID() noexcept -> FormType = delete;

		[[nodiscard]]
		static auto GetTypeInfo([[maybe_unused]] IVirtualMachine& a_vm) noexcept -> std::optional<TypeInfo>
		{
			return TypeInfo(TypeInfo::RawType::Var);
		}

		static auto PackVariable([[maybe_unused]] IVirtualMachine& a_vm, Variable& a_var, T a_val) -> bool
		{
			a_var.SetVariant(a_val);
			return true;
		}

		[[nodiscard]]
		static auto UnpackVariable([[maybe_unused]] IVirtualMachine& a_vm, const Variable& a_var)
			-> std::optional<std::remove_cv_t<T>>
		{
			if (!a_var.IsVariant()) {
				return std::nullopt;
			}

			return a_var.GetVariant();
		}
	};

	template <class T>
		requires(Impl::vm_unique_variant<T>)
	struct variable_packer<T>
	{
	public:
		variable_packer() = delete;

		[[nodiscard]]
		static consteval auto GetObjectTypeID() noexcept -> FormType = delete;

		[[nodiscard]]
		static auto GetTypeInfo([[maybe_unused]] IVirtualMachine& a_vm) noexcept -> std::optional<TypeInfo>
		{
			return TypeInfo(TypeInfo::RawType::Var);
		}

		static auto PackVariable([[maybe_unused]] IVirtualMachine& a_vm, Variable& a_var, T a_val) -> bool
		{
			a_var.SetVariant(std::move(a_val));
			return true;
		}

		[[nodiscard]]
		static auto UnpackVariable([[maybe_unused]] IVirtualMachine& a_vm, const Variable& a_var)
			-> std::optional<std::remove_cv_t<T>>
		{
			if (!a_var.IsVariant()) {
				return std::nullopt;
			}

			const auto* value = a_var.GetVariant();
			if (!value) {
				return std::remove_cv_t<T>();
			}

			return BSScript::CreateVariant(*value);
		}
	};

	template <class T>
		requires(Impl::array<T> && Impl::valid_parameter<typename T::value_type>)
	struct variable_packer<T>
	{
	public:
		variable_packer() = delete;

		[[nodiscard]]
		static consteval auto GetObjectTypeID() noexcept -> FormType = delete;

		[[nodiscard]]
		static auto GetTypeInfo(IVirtualMachine& a_vm) -> std::optional<TypeInfo>
		{
			using value_type = T::value_type;

			auto typeInfo = Impl::GetTypeInfo<value_type>(a_vm);
			if (!typeInfo.has_value()) {
				return std::nullopt;
			}

			typeInfo->SetIsArray(true);
			return typeInfo;
		}

		static auto PackVariable(IVirtualMachine& a_vm, Variable& a_var, T a_val) -> bool
		{
			using reference_type = std::conditional_t<
				std::is_const_v<T>,
				std::add_lvalue_reference_t<typename T::value_type>,
				std::add_rvalue_reference_t<typename T::value_type>>;
			using size_type = Array::size_type;

			const auto typeInfo = Impl::GetTypeInfo<T>(a_vm);
			if (!typeInfo.has_value()) {
				a_var.SetNone();
				return false;
			}

			const auto arraySize = static_cast<size_type>(a_val.size());

			auto result = BSTSmartPointer<Array>();
			if (!a_vm.CreateArray(*typeInfo, arraySize, result) || !result) {
				a_var.SetNone();
				return false;
			}

			const auto arrayLock = BSAutoSpinLock(result->elementsLock);

			for (auto i = static_cast<size_type>(0); i < arraySize; i++) {
				std::ignore = Impl::PackVariable(a_vm, result->elements[i], static_cast<reference_type>(a_val[i]));
			}

			a_var.SetArray(std::move(result));
			return true;
		}

		[[nodiscard]]
		static auto UnpackVariable(IVirtualMachine& a_vm, const Variable& a_var) -> std::optional<std::remove_cv_t<T>>
		{
			using value_type = T::value_type;
			using size_type = T::size_type;

			if (!a_var.IsArray()) {
				return std::nullopt;
			}

			const auto array = a_var.GetArray();
			if (!array) {
				return std::remove_cv_t<T>();
			}

			const auto arrayLock = BSAutoSpinLock(array->elementsLock);

			const auto& arrayElements = array->elements;
			const auto arraySize = static_cast<size_type>(arrayElements.size());

			auto result = std::remove_cv_t<T>();

			if constexpr (REX::reservable<T>) {
				result.reserve(arraySize);
			}

			for (auto i = static_cast<size_type>(0); i < arraySize; i++) {
				auto element = Impl::UnpackVariable<value_type>(a_vm, arrayElements[i]);
				if (!element.has_value()) {
					return std::nullopt;
				}

				result.push_back(std::move(element).value());
			}

			return result;
		}
	};

	template <class T>
		requires(Impl::vm_object_wrapper<T>)
	struct variable_packer<T>
	{
	public:
		variable_packer() = delete;

		[[nodiscard]]
		static consteval auto GetObjectTypeID() noexcept -> FormType = delete;

		[[nodiscard]]
		static auto GetTypeInfo(IVirtualMachine& a_vm) -> std::optional<TypeInfo>
		{
			auto objectTypeInfo = BSTSmartPointer<ObjectTypeInfo>();
			if (!a_vm.GetScriptObjectType(BSFixedString(T::TYPE_NAME), objectTypeInfo) || !objectTypeInfo) {
				return std::nullopt;
			}

			return TypeInfo(objectTypeInfo.get());
		}

		static auto PackVariable([[maybe_unused]] IVirtualMachine& a_vm, Variable& a_var, T a_val) -> bool
		{
			a_var.SetObject(std::move(a_val).get());
			return true;
		}

		[[nodiscard]]
		static auto UnpackVariable([[maybe_unused]] IVirtualMachine& a_vm, const Variable& a_var)
			-> std::optional<std::remove_cv_t<T>>
		{
			if (!a_var.IsObject()) {
				return std::nullopt;
			}

			auto object = a_var.GetObject();
			if (!object) {
				return std::remove_cv_t<T>();
			}

			return std::remove_cv_t<T>(std::move(object));
		}
	};

	template <class T>
		requires(Impl::vm_struct_wrapper<T>)
	struct variable_packer<T>
	{
	public:
		variable_packer() = delete;

		[[nodiscard]]
		static consteval auto GetObjectTypeID() noexcept -> FormType = delete;

		[[nodiscard]]
		static auto GetTypeInfo([[maybe_unused]] IVirtualMachine& a_vm) noexcept -> std::optional<TypeInfo>
		{
			auto structTypeInfo = BSTSmartPointer<StructTypeInfo>();
			if (!a_vm.GetScriptStructType(BSFixedString(T::TYPE_NAME), structTypeInfo) || !structTypeInfo) {
				return std::nullopt;
			}

			return TypeInfo(structTypeInfo.get());
		}

		static auto PackVariable([[maybe_unused]] IVirtualMachine& a_vm, Variable& a_var, T a_val) -> bool
		{
			a_var.SetStruct(std::move(a_val).get());
			return true;
		}

		[[nodiscard]]
		static auto UnpackVariable([[maybe_unused]] IVirtualMachine& a_vm, const Variable& a_var)
			-> std::optional<std::remove_cv_t<T>>
		{
			if (!a_var.IsStruct()) {
				return std::nullopt;
			}

			auto structure = a_var.GetStruct();
			if (!structure) {
				return std::remove_cv_t<T>();
			}

			return std::remove_cv_t<T>(std::move(structure));
		}
	};

	template <class T>
		requires(Impl::vm_array_wrapper<T> && Impl::valid_parameter<typename T::element_type>)
	struct variable_packer<T>
	{
	public:
		variable_packer() = delete;

		[[nodiscard]]
		static consteval auto GetObjectTypeID() noexcept -> FormType = delete;

		[[nodiscard]]
		static auto GetTypeInfo(IVirtualMachine& a_vm) -> std::optional<TypeInfo>
		{
			using element_type = T::element_type;

			auto typeInfo = Impl::GetTypeInfo<element_type>(a_vm);
			if (!typeInfo.has_value()) {
				return std::nullopt;
			}

			typeInfo->SetIsArray(true);
			return typeInfo;
		}

		static auto PackVariable([[maybe_unused]] IVirtualMachine& a_vm, Variable& a_var, T a_val) -> bool
		{
			a_var.SetArray(std::move(a_val).get());
			return true;
		}

		[[nodiscard]]
		static auto UnpackVariable([[maybe_unused]] IVirtualMachine& a_vm, const Variable& a_var)
			-> std::optional<std::remove_cv_t<T>>
		{
			if (!a_var.IsArray()) {
				return std::nullopt;
			}

			auto array = a_var.GetArray();
			if (!array) {
				return std::remove_cv_t<T>();
			}

			return std::remove_cv_t<T>(std::move(array));
		}
	};

	template <class T>
		requires(Impl::optional<T> && Impl::valid_parameter<typename T::value_type>)
	struct variable_packer<T>
	{
	public:
		variable_packer() = delete;

		[[nodiscard]]
		static consteval auto GetObjectTypeID() noexcept -> FormType = delete;

		[[nodiscard]]
		static auto GetTypeInfo(IVirtualMachine& a_vm) -> std::optional<TypeInfo>
		{
			using value_type = T::value_type;
			return Impl::GetTypeInfo<value_type>(a_vm);
		}

		static auto PackVariable([[maybe_unused]] IVirtualMachine& a_vm, Variable& a_var, T a_val) -> bool
		{
			if (!a_val.has_value()) {
				a_var.SetNone();
				return true;
			}

			return Impl::PackVariable(a_vm, a_var, std::move(a_val).value());
		}

		[[nodiscard]]
		static auto UnpackVariable([[maybe_unused]] IVirtualMachine& a_vm, const Variable& a_var)
			-> std::optional<std::remove_cv_t<T>>
		{
			using value_type = T::value_type;

			if (a_var.IsNone()) {
				return std::nullopt;
			}

			return Impl::UnpackVariable<value_type>(a_vm, a_var);
		}
	};

	template <class T>
		requires(Impl::void_result<T>)
	struct variable_packer<T>
	{
	public:
		variable_packer() = delete;

		[[nodiscard]]
		static consteval auto GetObjectTypeID() noexcept -> FormType = delete;

		[[nodiscard]]
		static auto GetTypeInfo([[maybe_unused]] IVirtualMachine& a_vm) noexcept -> std::optional<TypeInfo>
		{
			return TypeInfo(TypeInfo::RawType::None);
		}

		// static bool PackVariable([[maybe_unused]] IVirtualMachine& a_vm, Variable& a_var, T a_val) = delete;

		// [[nodiscard]] static auto UnpackVariable([[maybe_unused]] IVirtualMachine& a_vm, const Variable& a_var)
		// 	-> std::optional<std::remove_cv_t<T>> = delete;
	};
}

namespace RE::BSScript
{
	template <class T>
	[[nodiscard]]
	consteval auto GetObjectTypeID() noexcept -> FormType
		requires(requires { BSScript::variable_packer<T>::GetObjectTypeID(); })
	{
		return Impl::GetObjectTypeID<T>();
	}

	template <class T>
	[[nodiscard]] [[REX_ALWAYS_INLINE]]
	auto GetTypeInfo(IVirtualMachine& a_vm) -> std::optional<TypeInfo>
		requires(requires { BSScript::variable_packer<T>::GetTypeInfo(a_vm); })
	{
		return Impl::GetTypeInfo<T>(a_vm);
	}

	template <class T>
	[[REX_ALWAYS_INLINE]]
	auto PackVariable(IVirtualMachine& a_vm, Variable& a_var, T&& a_val) -> bool
		requires(requires {
			BSScript::variable_packer<std::remove_reference_t<T>>::PackVariable(a_vm, a_var, std::forward<T>(a_val));
		})
	{
		return Impl::PackVariable(a_vm, a_var, std::forward<T>(a_val));
	}

	template <class T>
	[[nodiscard]] [[REX_ALWAYS_INLINE]]
	auto UnpackVariable(IVirtualMachine& a_vm, const Variable& a_var) -> std::optional<std::remove_cv_t<T>>
		requires(requires { BSScript::variable_packer<T>::UnpackVariable(a_vm, a_var); })
	{
		return Impl::UnpackVariable<T>(a_vm, a_var);
	}

	template <class... Args>
	[[nodiscard]]
	auto PackVariables(IVirtualMachine& a_vm, BSScrapArray<Variable>& a_outArgs, Args&&... a_args) -> bool
		requires((BSScript::ValidateParameter<std::remove_reference_t<Args>>() && ...))
	{
		constexpr auto ARGS_SIZE = sizeof...(a_args);

		const auto argsTuple = std::make_tuple(std::forward<Args>(a_args)...);
		a_outArgs.resize(ARGS_SIZE);

		return [&a_vm, &a_outArgs, &argsTuple]<std::size_t... Indexes>(std::index_sequence<Indexes...>) -> auto {
			return ((Impl::PackVariable(a_vm, a_outArgs.at(Indexes), std::get<Indexes>(argsTuple))), ...);
		}(std::make_index_sequence<ARGS_SIZE>());
	}

	template <class... Args>
	[[nodiscard]]
	auto CreateThreadScrapFunction(IVirtualMachine& a_vm, Args&&... a_args)
		-> BSTThreadScrapFunction<bool(BSScrapArray<Variable>&)>
		requires((BSScript::ValidateParameter<std::remove_reference_t<Args>>() && ...))
	{
		return [&a_vm, ... a_args = std::forward<Args>(a_args)](BSScrapArray<Variable>& a_outArgs) mutable -> bool {
			return BSScript::PackVariables(a_vm, a_outArgs, std::forward<Args>(a_args)...);
		};
	}

	[[nodiscard]]
	inline auto CreateAppliedThreadScrapFunction(std::span<const Variable> a_args)
		-> BSTThreadScrapFunction<bool(BSScrapArray<Variable>&)>
	{
		return [a_args](BSScrapArray<Variable>& a_outArgs) -> bool {
			a_outArgs = {a_args.begin(), a_args.end()};
			return true;
		};
	}
}

namespace RE::BSScript::Impl
{
	template <class T>
	[[nodiscard]]
	consteval auto GetObjectTypeID() noexcept -> FormType
	{
		return BSScript::variable_packer<T>::GetObjectTypeID();
	}

	template <class T>
	[[nodiscard]] [[REX_ALWAYS_INLINE]]
	auto GetTypeInfo(IVirtualMachine& a_vm) -> std::optional<TypeInfo>
	{
		return BSScript::variable_packer<T>::GetTypeInfo(a_vm);
	}

	template <class T>
	[[REX_ALWAYS_INLINE]]
	auto PackVariable(IVirtualMachine& a_vm, Variable& a_var, T&& a_val) -> bool
	{
		return BSScript::variable_packer<std::remove_reference_t<T>>::PackVariable(a_vm, a_var, std::forward<T>(a_val));
	}

	template <class T>
	[[nodiscard]] [[REX_ALWAYS_INLINE]]
	auto UnpackVariable(IVirtualMachine& a_vm, const Variable& a_var) -> std::optional<std::remove_cv_t<T>>
	{
		return BSScript::variable_packer<T>::UnpackVariable(a_vm, a_var);
	}
}
