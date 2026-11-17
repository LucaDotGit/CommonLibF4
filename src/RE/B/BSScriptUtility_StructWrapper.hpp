#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSScriptUtility_Concepts.hpp"
#include "RE/B/BSScript_IVirtualMachine.hpp"
#include "RE/B/BSScript_Struct.hpp"
#include "RE/B/BSScript_StructTypeInfo.hpp"
#include "RE/B/BSScript_TypeInfo.hpp"
#include "RE/B/BSScript_Variable.hpp"
#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSScript
{
	class Variable;

	template <REX::StaticString ScriptName, REX::StaticString StructName>
	class StructWrapper final
	{
	public:
		inline static constexpr auto SCRIPT_NAME = ScriptName;
		inline static constexpr auto STRUCT_NAME = StructName;
		inline static constexpr auto TYPE_NAME = BSScript::CreateStructTag(ScriptName, StructName);

		constexpr StructWrapper() noexcept = default;
		constexpr ~StructWrapper() noexcept = default;

		// NOLINTNEXTLINE(misc-explicit-constructor)
		constexpr StructWrapper(std::nullptr_t) noexcept :
			_proxy(nullptr)
		{
		}

		constexpr explicit StructWrapper(const BSTSmartPointer<Struct>& a_proxy) :
			_proxy(a_proxy)
		{
		}

		constexpr StructWrapper(const StructWrapper&) noexcept = default;
		constexpr StructWrapper(StructWrapper&&) noexcept = default;

		constexpr auto operator=(const StructWrapper&) noexcept -> StructWrapper& = default;
		constexpr auto operator=(StructWrapper&&) noexcept -> StructWrapper& = default;

		constexpr auto operator=(std::nullptr_t) noexcept -> StructWrapper&
		{
			_proxy = nullptr;
			return *this;
		}

		constexpr auto operator=(BSTSmartPointer<Struct> a_proxy) -> StructWrapper&
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
		constexpr explicit operator BSTSmartPointer<Struct>() const noexcept
		{
			return _proxy;
		}

		[[nodiscard]]
		constexpr auto operator*() & noexcept -> BSTSmartPointer<Struct>&
		{
			return _proxy;
		}

		[[nodiscard]]
		constexpr auto operator*() const& noexcept -> const BSTSmartPointer<Struct>&
		{
			return _proxy;
		}

		[[nodiscard]]
		constexpr auto operator*() && noexcept -> BSTSmartPointer<Struct>&&
		{
			return std::move(_proxy);
		}

		[[nodiscard]]
		constexpr auto operator*() const&& noexcept -> const BSTSmartPointer<Struct>&&
		{
			return std::move(_proxy);
		}

		[[nodiscard]]
		constexpr auto operator->() noexcept -> BSTSmartPointer<Struct>&
		{
			return _proxy;
		}

		[[nodiscard]]
		constexpr auto operator->() const noexcept -> const BSTSmartPointer<Struct>&
		{
			return _proxy;
		}

		[[nodiscard]]
		constexpr auto IsNone() const noexcept -> bool
		{
			return _proxy == nullptr;
		}

		[[nodiscard]]
		constexpr auto get() & noexcept -> RE::BSTSmartPointer<Struct>&
		{
			return _proxy;
		}

		[[nodiscard]]
		constexpr auto get() const& noexcept -> const RE::BSTSmartPointer<Struct>&
		{
			return _proxy;
		}

		[[nodiscard]]
		constexpr auto get() && noexcept -> RE::BSTSmartPointer<Struct>&&
		{
			return std::move(_proxy);
		}

		[[nodiscard]]
		constexpr auto get() const&& noexcept -> const RE::BSTSmartPointer<Struct>&&
		{
			return std::move(_proxy);
		}

		[[nodiscard]]
		static constexpr auto GetTypeName() noexcept -> std::string_view
		{
			return TYPE_NAME;
		}

		[[nodiscard]]
		static constexpr auto GetScriptName() noexcept -> std::string_view
		{
			return SCRIPT_NAME;
		}

		[[nodiscard]]
		static constexpr auto GetStructName() noexcept -> std::string_view
		{
			return STRUCT_NAME;
		}

		[[nodiscard]]
		static auto Create(IVirtualMachine& a_vm) -> StructWrapper
		{
			auto proxy = BSTSmartPointer<Struct>();
			if (!a_vm.CreateStruct(BSFixedString(GetTypeName()), proxy) || !proxy) {
				return {};
			}

			return StructWrapper(std::move(proxy));
		}

		[[nodiscard]]
		static auto CreateOrFail(IVirtualMachine& a_vm) -> REX::NotNull<StructWrapper>
		{
			auto proxy = BSTSmartPointer<Struct>();
			if (!a_vm.CreateStruct(BSFixedString(GetTypeName()), proxy) || !proxy) [[unlikely]] {
				REX::Fail(R"(Failed to create struct of type "{}".)"sv, GetTypeName());
			}

			return StructWrapper(std::move(proxy));
		}

		[[nodiscard]]
		static auto GetTypeInfo(IVirtualMachine& a_vm) -> std::optional<TypeInfo>
		{
			return Impl::GetTypeInfo<StructWrapper>(a_vm);
		}

		[[nodiscard]]
		static auto GetStructTypeInfo(IVirtualMachine& a_vm) -> BSTSmartPointer<StructTypeInfo>
		{
			const auto typeInfo = GetTypeInfo(a_vm);
			if (!typeInfo.has_value()) {
				return nullptr;
			}

			return typeInfo->GetStructTypeInfo();
		}

		[[nodiscard]]
		auto Lock() const noexcept -> auto
		{
			return BSAutoSpinLock(_proxy->structLock);
		}

		[[nodiscard]]
		auto Equals(const StructWrapper& a_rhs) const noexcept -> bool
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
		auto Compare(const StructWrapper& a_rhs) const noexcept -> auto
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
		auto DeepEquals(const StructWrapper& a_rhs) const noexcept -> bool
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
		auto DeepCompare(const StructWrapper& a_rhs) const noexcept -> auto
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
		auto Clone(IVirtualMachine& a_vm) const -> StructWrapper
		{
			if (!_proxy) {
				return {};
			}

			return StructWrapper(_proxy->Clone(a_vm));
		}

		[[nodiscard]]
		auto DeepClone(IVirtualMachine& a_vm) const -> StructWrapper
		{
			if (!_proxy) {
				return {};
			}

			return StructWrapper(_proxy->DeepClone(a_vm));
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

			const auto structLock = BSAutoSpinLock(_proxy->structLock);
			return Impl::UnpackVariable<T>(a_vm, *variable);
		}

		template <class T>
		[[nodiscard]]
		auto FindVariableOrFail(IVirtualMachine& a_vm, REX::ZStringView a_name) const -> std::remove_cv_t<T>
			requires(BSScript::ValidateParameter<T>())
		{
			auto variable = FindVariable<T>(a_vm, a_name);
			if (!variable.has_value()) [[unlikely]] {
				REX::Fail(R"(Failed to find variable "{}" on struct "{}".)"sv, a_name, GetTypeName());
			}

			return std::move(variable).value();
		}

		template <class T>
		auto InsertVariable(IVirtualMachine& a_vm, REX::ZStringView a_name, T&& a_value) -> bool
			requires(BSScript::ValidateParameter<std::remove_reference_t<T>>())
		{
			auto* variable = GetVariableImpl(a_name);
			if (!variable) {
				return false;
			}

			const auto structLock = BSAutoSpinLock(_proxy->structLock);
			return Impl::PackVariable(a_vm, *variable, std::forward<T>(a_value));
		}

		template <class T>
		void InsertVariableOrFail(IVirtualMachine& a_vm, REX::ZStringView a_name, T&& a_value)
			requires(BSScript::ValidateParameter<std::remove_reference_t<T>>())
		{
			if (!InsertVariable(a_vm, a_name, std::forward<T>(a_value))) [[unlikely]] {
				REX::Fail(R"(Failed to insert variable "{}" on struct "{}".)"sv, a_name, GetTypeName());
			}
		}

		void reset() noexcept
		{
			_proxy.reset();
		}

		[[nodiscard]]
		constexpr friend auto operator==(const StructWrapper& a_lhs, const StructWrapper& a_rhs) noexcept -> bool
		{
			return a_lhs._proxy == a_rhs._proxy;
		}

		[[nodiscard]]
		constexpr friend auto operator==(const StructWrapper& a_lhs, std::nullptr_t) noexcept -> bool
		{
			return a_lhs._proxy == nullptr;
		}

		[[nodiscard]]
		constexpr friend auto operator==(std::nullptr_t, const StructWrapper& a_rhs) noexcept -> bool
		{
			return a_rhs._proxy == nullptr;
		}

		[[nodiscard]]
		constexpr friend auto operator==(const StructWrapper& a_lhs, const BSTSmartPointer<Struct>& a_rhs) noexcept
			-> bool
		{
			return a_lhs._proxy == a_rhs;
		}

		[[nodiscard]]
		constexpr friend auto operator==(const BSTSmartPointer<Struct>& a_lhs, const StructWrapper& a_rhs) noexcept
			-> bool
		{
			return a_lhs == a_rhs._proxy;
		}

		[[nodiscard]]
		constexpr friend auto operator<=>(const StructWrapper& a_lhs, const StructWrapper& a_rhs) noexcept -> auto
		{
			return a_lhs._proxy <=> a_rhs._proxy;
		}

		[[nodiscard]]
		constexpr friend auto operator<=>(const StructWrapper& a_lhs, std::nullptr_t) noexcept -> auto
		{
			return a_lhs._proxy <=> nullptr;
		}

		[[nodiscard]]
		constexpr friend auto operator<=>(std::nullptr_t, const StructWrapper& a_rhs) noexcept -> auto
		{
			return nullptr <=> a_rhs._proxy;
		}

		[[nodiscard]]
		constexpr friend auto operator<=>(const StructWrapper& a_lhs, const BSTSmartPointer<Struct>& a_rhs) noexcept
			-> auto
		{
			return a_lhs._proxy <=> a_rhs;
		}

		[[nodiscard]]
		constexpr friend auto operator<=>(const BSTSmartPointer<Struct>& a_lhs, const StructWrapper& a_rhs) noexcept
			-> auto
		{
			return a_lhs <=> a_rhs._proxy;
		}

	private:
		template <REX::StaticString, REX::StaticString>
		friend class StructWrapper;

		[[nodiscard]]
		auto GetVariableImpl(REX::ZStringView a_name) const -> Variable*
		{
			if (!_proxy) {
				return nullptr;
			}

			return _proxy->GetVariable(BSFixedString(a_name));
		}

		BSTSmartPointer<Struct> _proxy;
	};
}
