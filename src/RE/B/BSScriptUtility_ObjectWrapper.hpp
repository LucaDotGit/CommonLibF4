#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSScriptUtility_Concepts.hpp"
#include "RE/B/BSScript_IVirtualMachine.hpp"
#include "RE/B/BSScript_Object.hpp"
#include "RE/B/BSScript_ObjectTypeInfo.hpp"
#include "RE/B/BSScript_TypeInfo.hpp"
#include "RE/B/BSScript_Variable.hpp"
#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSScript
{
	template <REX::StaticString ScriptName>
	class ObjectWrapper final
	{
	public:
		inline static constexpr auto TYPE_NAME = ScriptName;

		constexpr ObjectWrapper() noexcept = default;
		constexpr ~ObjectWrapper() noexcept = default;

		// NOLINTNEXTLINE(misc-explicit-constructor)
		constexpr ObjectWrapper(std::nullptr_t) noexcept :
			_proxy(nullptr)
		{
		}

		constexpr explicit ObjectWrapper(BSTSmartPointer<Object> a_proxy) :
			_proxy(std::move(a_proxy))
		{
		}

		constexpr ObjectWrapper(const ObjectWrapper&) noexcept = default;
		constexpr ObjectWrapper(ObjectWrapper&&) noexcept = default;

		constexpr auto operator=(const ObjectWrapper&) noexcept -> ObjectWrapper& = default;
		constexpr auto operator=(ObjectWrapper&&) noexcept -> ObjectWrapper& = default;

		constexpr auto operator=(std::nullptr_t) noexcept -> ObjectWrapper&
		{
			_proxy = nullptr;
			return *this;
		}

		constexpr auto operator=(BSTSmartPointer<Object> a_proxy) -> ObjectWrapper&
		{
			_proxy = std::move(a_proxy);
			return *this;
		}

		[[nodiscard]]
		constexpr explicit operator bool() const noexcept
		{
			return static_cast<bool>(_proxy);
		}

		[[nodiscard]]
		constexpr explicit operator BSTSmartPointer<Object>() const noexcept
		{
			return _proxy;
		}

		[[nodiscard]]
		constexpr auto operator*() & noexcept -> BSTSmartPointer<Object>&
		{
			return _proxy;
		}

		[[nodiscard]]
		constexpr auto operator*() const& noexcept -> const BSTSmartPointer<Object>&
		{
			return _proxy;
		}

		[[nodiscard]]
		constexpr auto operator*() && noexcept -> BSTSmartPointer<Object>&&
		{
			return std::move(_proxy);
		}

		[[nodiscard]]
		constexpr auto operator*() const&& noexcept -> const BSTSmartPointer<Object>&&
		{
			return std::move(_proxy);
		}

		[[nodiscard]]
		constexpr auto operator->() noexcept -> BSTSmartPointer<Object>&
		{
			return _proxy;
		}

		[[nodiscard]]
		constexpr auto operator->() const noexcept -> const BSTSmartPointer<Object>&
		{
			return _proxy;
		}

		[[nodiscard]]
		constexpr auto IsNone() const noexcept -> bool
		{
			return _proxy == nullptr;
		}

		[[nodiscard]]
		constexpr auto get() & noexcept -> BSTSmartPointer<Object>&
		{
			return _proxy;
		}

		[[nodiscard]]
		constexpr auto get() const& noexcept -> const BSTSmartPointer<Object>&
		{
			return _proxy;
		}

		[[nodiscard]]
		constexpr auto get() && noexcept -> BSTSmartPointer<Object>&&
		{
			return std::move(_proxy);
		}

		[[nodiscard]]
		constexpr auto get() const&& noexcept -> const BSTSmartPointer<Object>&&
		{
			return std::move(_proxy);
		}

		[[nodiscard]]
		static constexpr auto GetTypeName() noexcept -> std::string_view
		{
			return TYPE_NAME;
		}

		[[nodiscard]]
		static auto Create(IVirtualMachine& a_vm, ObjectHandle a_objectHandle) -> REX::NotNull<ObjectWrapper>
		{
			auto proxy = BSTSmartPointer<Object>();
			if (!a_vm.GetOrCreateScriptObject(BSFixedString(GetTypeName()), a_objectHandle, proxy) || !proxy) {
				return {};
			}

			return ObjectWrapper(std::move(proxy));
		}

		[[nodiscard]]
		static auto CreateOrFail(IVirtualMachine& a_vm, ObjectHandle a_objectHandle) -> REX::NotNull<ObjectWrapper>
		{
			auto proxy = BSTSmartPointer<Object>();
			if (!a_vm.GetOrCreateScriptObject(BSFixedString(GetTypeName()), a_objectHandle, proxy) || !proxy)
				[[unlikely]] {
				REX::Fail(R"(Failed to create object of type "{}" with handle {:X}.)"sv, GetTypeName(), a_objectHandle);
			}

			return ObjectWrapper(std::move(proxy));
		}

		[[nodiscard]]
		static auto GetTypeInfo(IVirtualMachine& a_vm) -> std::optional<TypeInfo>
		{
			return Impl::GetTypeInfo<ObjectWrapper>(a_vm);
		}

		[[nodiscard]]
		static auto GetObjectTypeInfo(IVirtualMachine& a_vm) -> BSTSmartPointer<ObjectTypeInfo>
		{
			const auto typeInfo = GetTypeInfo(a_vm);
			if (!typeInfo.has_value()) {
				return nullptr;
			}

			return typeInfo->GetObjectTypeInfo();
		}

		[[nodiscard]]
		auto Equals(const ObjectWrapper& a_rhs) const noexcept -> bool
		{
			if (_proxy == a_rhs._proxy) {
				return true;
			}

			if (!_proxy || !a_rhs._proxy) {
				return false;
			}

			return _proxy->Equals(*a_rhs._proxy);
		}

		[[nodiscard]]
		auto Compare(const ObjectWrapper& a_rhs) const noexcept -> auto
		{
			if (_proxy == a_rhs._proxy) {
				return std::strong_ordering::equal;
			}

			if (!_proxy) {
				return std::strong_ordering::less;
			}

			if (!a_rhs._proxy) {
				return std::strong_ordering::greater;
			}

			return _proxy->Compare(*a_rhs._proxy);
		}

		[[nodiscard]]
		auto DeepEquals(const ObjectWrapper& a_rhs) const noexcept -> bool
		{
			if (_proxy == a_rhs._proxy) {
				return true;
			}

			if (!_proxy || !a_rhs._proxy) {
				return false;
			}

			return _proxy->DeepEquals(*a_rhs._proxy);
		}

		[[nodiscard]]
		auto DeepCompare(const ObjectWrapper& a_rhs) const noexcept -> auto
		{
			if (_proxy == a_rhs._proxy) {
				return std::partial_ordering::equivalent;
			}

			if (!_proxy) {
				return std::partial_ordering::less;
			}

			if (!a_rhs._proxy) {
				return std::partial_ordering::greater;
			}

			return _proxy->DeepCompare(*a_rhs._proxy);
		}

		[[nodiscard]]
		auto Clone(IVirtualMachine& a_vm) const -> ObjectWrapper
		{
			if (!_proxy) {
				return {};
			}

			return ObjectWrapper(_proxy->Clone(a_vm));
		}

		[[nodiscard]]
		auto DeepClone(IVirtualMachine& a_vm) const -> ObjectWrapper
		{
			if (!_proxy) {
				return {};
			}

			return ObjectWrapper(_proxy->DeepClone(a_vm));
		}

		template <class T>
		[[nodiscard]]
		auto FindVariable(IVirtualMachine& a_vm, REX::ZStringView a_name) const -> std::optional<std::remove_cv_t<T>>
			requires(BSScript::ValidateParameter<T>())
		{
			const auto* variable = GetVariableImpl(a_name);
			if (!variable) {
				return std::nullopt;
			}

			const auto arrayLock = BSAutoSpinLock(*_proxy);
			return Impl::UnpackVariable<T>(a_vm, *variable);
		}

		template <class T>
		[[nodiscard]]
		auto FindVariableOrFail(IVirtualMachine& a_vm, REX::ZStringView a_name) const -> std::remove_cv_t<T>
			requires(BSScript::ValidateParameter<T>())
		{
			auto variable = FindVariable<T>(a_vm, a_name);
			if (!variable.has_value()) [[unlikely]] {
				REX::Fail(R"(Failed to find variable "{}" on object of type "{}".)"sv, a_name, GetTypeName());
			}

			return std::move(variable).value();
		}

		template <class T>
		[[nodiscard]]
		auto FindProperty(IVirtualMachine& a_vm, REX::ZStringView a_name) const -> std::optional<std::remove_cv_t<T>>
			requires(BSScript::ValidateParameter<T>())
		{
			const auto* property = GetAutoPropertyImpl(a_name);
			if (!property) {
				return std::nullopt;
			}

			const auto arrayLock = BSAutoSpinLock(*_proxy);
			return Impl::UnpackVariable<T>(a_vm, *property);
		}

		template <class T>
		[[nodiscard]]
		auto FindPropertyOrFail(IVirtualMachine& a_vm, REX::ZStringView a_name) const -> std::remove_cv_t<T>
			requires(BSScript::ValidateParameter<T>())
		{
			auto property = FindProperty<T>(a_vm, a_name);
			if (!property.has_value()) [[unlikely]] {
				REX::Fail(R"(Failed to find property "{}" on object of type "{}".)"sv, a_name, GetTypeName());
			}

			return std::move(property).value();
		}

		template <class T>
		auto InsertVariable(IVirtualMachine& a_vm, REX::ZStringView a_name, T&& a_value) -> bool
			requires(BSScript::ValidateParameter<std::remove_reference_t<T>>())
		{
			auto* variable = GetVariableImpl(a_name);
			if (!variable) {
				return false;
			}

			const auto arrayLock = BSAutoSpinLock(*_proxy);
			return Impl::PackVariable(a_vm, *variable, std::forward<T>(a_value));
		}

		template <class T>
		void InsertVariableOrFail(IVirtualMachine& a_vm, REX::ZStringView a_name, T&& a_value)
			requires(BSScript::ValidateParameter<std::remove_reference_t<T>>())
		{
			if (!InsertVariable(a_vm, a_name, std::forward<T>(a_value))) [[unlikely]] {
				REX::Fail(R"(Failed to insert variable "{}" on object of type "{}".)"sv, a_name, GetTypeName());
			}
		}

		template <class T>
		auto InsertProperty(IVirtualMachine& a_vm, REX::ZStringView a_name, T&& a_value) -> bool
			requires(BSScript::ValidateParameter<std::remove_reference_t<T>>())
		{
			auto* property = GetAutoPropertyImpl(a_name);
			if (!property) {
				return false;
			}

			const auto arrayLock = BSAutoSpinLock(*_proxy);
			return Impl::PackVariable(a_vm, *property, std::forward<T>(a_value));
		}

		template <class T>
		void InsertPropertyOrFail(IVirtualMachine& a_vm, REX::ZStringView a_name, T&& a_value)
			requires(BSScript::ValidateParameter<std::remove_reference_t<T>>())
		{
			if (!InsertProperty(a_vm, a_name, std::forward<T>(a_value))) [[unlikely]] {
				REX::Fail(R"(Failed to insert property "{}" on object of type "{}".)"sv, a_name, GetTypeName());
			}
		}

		void reset() noexcept
		{
			_proxy.reset();
		}

		[[nodiscard]]
		constexpr friend auto operator==(const ObjectWrapper& a_lhs, const ObjectWrapper& a_rhs) noexcept -> bool
		{
			return a_lhs._proxy == a_rhs._proxy;
		}

		[[nodiscard]]
		constexpr friend auto operator==(const ObjectWrapper& a_lhs, std::nullptr_t) noexcept -> bool
		{
			return a_lhs._proxy == nullptr;
		}

		[[nodiscard]]
		constexpr friend auto operator==(std::nullptr_t, const ObjectWrapper& a_rhs) noexcept -> bool
		{
			return nullptr == a_rhs._proxy;
		}

		[[nodiscard]]
		constexpr friend auto operator==(const ObjectWrapper& a_lhs, const BSTSmartPointer<Object>& a_rhs) noexcept
			-> bool
		{
			return a_lhs._proxy == a_rhs;
		}

		[[nodiscard]]
		constexpr friend auto operator==(const BSTSmartPointer<Object>& a_lhs, const ObjectWrapper& a_rhs) noexcept
			-> bool
		{
			return a_lhs == a_rhs._proxy;
		}

		[[nodiscard]]
		constexpr friend auto operator<=>(const ObjectWrapper& a_lhs, const ObjectWrapper& a_rhs) noexcept -> auto
		{
			return a_lhs._proxy <=> a_rhs._proxy;
		}

		[[nodiscard]]
		constexpr friend auto operator<=>(const ObjectWrapper& a_lhs, std::nullptr_t) noexcept -> auto
		{
			return a_lhs._proxy <=> nullptr;
		}

		[[nodiscard]]
		constexpr friend auto operator<=>(std::nullptr_t, const ObjectWrapper& a_rhs) noexcept -> auto
		{
			return nullptr <=> a_rhs._proxy;
		}

		[[nodiscard]]
		constexpr friend auto operator<=>(const ObjectWrapper& a_lhs, const BSTSmartPointer<Object>& a_rhs) noexcept
			-> auto
		{
			return a_lhs._proxy <=> a_rhs;
		}

		[[nodiscard]]
		constexpr friend auto operator<=>(const BSTSmartPointer<Object>& a_lhs, const ObjectWrapper& a_rhs) noexcept
			-> auto
		{
			return a_lhs <=> a_rhs._proxy;
		}

	private:
		template <REX::StaticString>
		friend class ObjectWrapper;

		[[nodiscard]]
		auto GetVariableImpl(REX::ZStringView a_name) const -> Variable*
		{
			if (!_proxy) {
				return nullptr;
			}

			return _proxy->GetVariable(BSFixedString(a_name));
		}

		[[nodiscard]]
		auto GetAutoPropertyImpl(REX::ZStringView a_name) const -> Variable*
		{
			if (!_proxy) {
				return nullptr;
			}

			return _proxy->GetProperty(BSFixedString(a_name));
		}

		BSTSmartPointer<Object> _proxy;
	};
}
