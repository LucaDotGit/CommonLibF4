#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSScriptUtil_Concepts.hpp"
#include "RE/B/BSScript_Struct.hpp"
#include "RE/B/BSScript_StructTypeInfo.hpp"
#include "RE/B/BSScript_TypeInfo.hpp"
#include "RE/B/BSScript_Variable.hpp"
#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/G/GameVM.hpp"

namespace RE::BSScript
{
	class Variable;

	template <REX::StaticString ScriptName, REX::StaticString StructName>
	class StructWrapper
	{
	public:
		inline static constexpr auto SCRIPT_NAME = ScriptName;
		inline static constexpr auto STRUCT_NAME = StructName;
		inline static constexpr auto TYPE_NAME = BSScript::CreateStructTag(ScriptName, StructName);

		constexpr StructWrapper() noexcept = default;
		constexpr ~StructWrapper() noexcept = default;

		constexpr StructWrapper(std::nullptr_t) noexcept
			: _proxy(nullptr)
		{
		}

		constexpr explicit StructWrapper(const BSTSmartPointer<Struct>& a_proxy)
			: _proxy(a_proxy)
		{
			REX::Assert(!_proxy || (_proxy->GetTypeInfo() == GetStructTypeInfo()));
		}

		constexpr StructWrapper(const StructWrapper&) noexcept = default;
		constexpr StructWrapper(StructWrapper&&) noexcept = default;

		constexpr StructWrapper& operator=(const StructWrapper&) noexcept = default;
		constexpr StructWrapper& operator=(StructWrapper&&) noexcept = default;

		constexpr StructWrapper& operator=(std::nullptr_t) noexcept
		{
			_proxy = nullptr;
			return *this;
		}

		constexpr StructWrapper& operator=(BSTSmartPointer<Struct> a_proxy)
		{
			REX::Assert(!a_proxy || (a_proxy->GetTypeInfo() == GetStructTypeInfo()));
			_proxy = std::move(a_proxy);
			return *this;
		}

		[[nodiscard]] constexpr friend bool operator==(const StructWrapper& a_lhs, const StructWrapper& a_rhs) noexcept { return a_lhs._proxy == a_rhs._proxy; }
		[[nodiscard]] constexpr friend bool operator==(const StructWrapper& a_lhs, std::nullptr_t) noexcept { return a_lhs._proxy == nullptr; }
		[[nodiscard]] constexpr friend bool operator==(std::nullptr_t, const StructWrapper& a_rhs) noexcept { return a_rhs._proxy == nullptr; }
		[[nodiscard]] constexpr friend bool operator==(const StructWrapper& a_lhs, const BSTSmartPointer<Struct>& a_rhs) noexcept { return a_lhs._proxy == a_rhs; }
		[[nodiscard]] constexpr friend bool operator==(const BSTSmartPointer<Struct>& a_lhs, const StructWrapper& a_rhs) noexcept { return a_lhs == a_rhs._proxy; }
		[[nodiscard]] constexpr friend auto operator<=>(const StructWrapper& a_lhs, const StructWrapper& a_rhs) noexcept { return a_lhs._proxy <=> a_rhs._proxy; }
		[[nodiscard]] constexpr friend auto operator<=>(const StructWrapper& a_lhs, std::nullptr_t) noexcept { return a_lhs._proxy <=> nullptr; }
		[[nodiscard]] constexpr friend auto operator<=>(std::nullptr_t, const StructWrapper& a_rhs) noexcept { return nullptr <=> a_rhs._proxy; }
		[[nodiscard]] constexpr friend auto operator<=>(const StructWrapper& a_lhs, const BSTSmartPointer<Struct>& a_rhs) noexcept { return a_lhs._proxy <=> a_rhs; }
		[[nodiscard]] constexpr friend auto operator<=>(const BSTSmartPointer<Struct>& a_lhs, const StructWrapper& a_rhs) noexcept { return a_lhs <=> a_rhs._proxy; }

		[[nodiscard]] constexpr BSTSmartPointer<Struct>& operator*() & noexcept { return _proxy; }
		[[nodiscard]] constexpr const BSTSmartPointer<Struct>& operator*() const& noexcept { return _proxy; }

		[[nodiscard]] constexpr BSTSmartPointer<Struct>&& operator*() && noexcept { return std::move(_proxy); }
		[[nodiscard]] constexpr const BSTSmartPointer<Struct>&& operator*() const&& noexcept { return std::move(_proxy); }

		[[nodiscard]] constexpr BSTSmartPointer<Struct>& operator->() noexcept { return _proxy; }
		[[nodiscard]] constexpr const BSTSmartPointer<Struct>& operator->() const noexcept { return _proxy; }

		[[nodiscard]] constexpr explicit operator BSTSmartPointer<Struct>&() noexcept { return _proxy; }
		[[nodiscard]] constexpr explicit operator const BSTSmartPointer<Struct>&() const noexcept { return _proxy; }

		[[nodiscard]] constexpr explicit operator bool() const noexcept { return _proxy != nullptr; }
		[[nodiscard]] constexpr bool IsNone() const noexcept { return _proxy == nullptr; }

		[[nodiscard]] constexpr RE::BSTSmartPointer<Struct>& get() & noexcept { return _proxy; }
		[[nodiscard]] constexpr const RE::BSTSmartPointer<Struct>& get() const& noexcept { return _proxy; }

		[[nodiscard]] constexpr RE::BSTSmartPointer<Struct>&& get() && noexcept { return std::move(_proxy); }
		[[nodiscard]] constexpr const RE::BSTSmartPointer<Struct>&& get() const&& noexcept { return std::move(_proxy); }

		[[nodiscard]] static constexpr REX::zstring_view GetTypeName() noexcept { return TYPE_NAME; }
		[[nodiscard]] static constexpr REX::zstring_view GetScriptName() noexcept { return SCRIPT_NAME; }
		[[nodiscard]] static constexpr REX::zstring_view GetStructName() noexcept { return STRUCT_NAME; }

		[[nodiscard]] static StructWrapper Create()
		{
			const auto scriptVM = GameVM::GetVMInterface();
			if (!scriptVM) [[unlikely]] {
				REX::Fail("Failed to get script VM."sv);
			}

			auto proxy = BSTSmartPointer<Struct>();
			if (!scriptVM->CreateStruct(BSFixedString(GetTypeName()), proxy) || !proxy) [[unlikely]] {
				REX::Fail(R"(Failed to create struct proxy of struct type "{}".)"sv,
					GetTypeName());
			}

			return StructWrapper{ std::move(proxy) };
		}

		[[nodiscard]] static TypeInfo GetTypeInfo()
		{
			const auto typeInfo = Impl::GetTypeInfo<StructWrapper>();
			return typeInfo.value_or(nullptr);
		}

		[[nodiscard]] static StructTypeInfo* GetStructTypeInfo()
		{
			const auto typeInfo = GetTypeInfo();
			return typeInfo.GetStructTypeInfo();
		}

		[[nodiscard]] BSAutoLock<BSSpinLock> Lock() const noexcept
		{
			return BSAutoLock(_proxy->structLock);
		}

		[[nodiscard]] bool Equals(const StructWrapper& a_rhs) const noexcept
		{
			if (_proxy == a_rhs._proxy) {
				return true;
			}

			if (!_proxy || !a_rhs._proxy) {
				return false;
			}

			return _proxy->Equals(*a_rhs._proxy);
		}

		[[nodiscard]] std::strong_ordering Compare(const StructWrapper& a_rhs) const noexcept
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

		[[nodiscard]] bool DeepEquals(const StructWrapper& a_rhs) const noexcept
		{
			if (_proxy == a_rhs._proxy) {
				return true;
			}

			if (!_proxy || !a_rhs._proxy) {
				return false;
			}

			return _proxy->DeepEquals(*a_rhs._proxy);
		}

		[[nodiscard]] std::partial_ordering DeepCompare(const StructWrapper& a_rhs) const noexcept
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

		[[nodiscard]] StructWrapper Clone() const
		{
			if (!_proxy) {
				return StructWrapper(nullptr);
			}

			auto scriptVM = GameVM::GetVMInterface();
			if (!scriptVM) [[unlikely]] {
				REX::Assert(false);
				return StructWrapper(nullptr);
			}

			return StructWrapper(_proxy->Clone(*scriptVM));
		}

		[[nodiscard]] StructWrapper DeepClone() const
		{
			if (!_proxy) {
				return StructWrapper(nullptr);
			}

			auto scriptVM = GameVM::GetVMInterface();
			if (!scriptVM) [[unlikely]] {
				REX::Assert(false);
				return StructWrapper(nullptr);
			}

			return StructWrapper(_proxy->DeepClone(*scriptVM));
		}

		template <class T>
		[[nodiscard]] auto Find(REX::zstring_view a_name) const -> std::optional<T>
			requires(BSScript::ValidateParameter<T>())
		{
			const auto* variable = GetVariableImpl(a_name);
			if (!variable) {
				return std::nullopt;
			}

			const auto structLock = BSAutoLock(_proxy->structLock);
			return Impl::UnpackVariable<T>(*variable);
		}

		template <class T>
		[[nodiscard]] auto Find_NoLock(REX::zstring_view a_name) const -> std::optional<T>
			requires(BSScript::ValidateParameter<T>())
		{
			const auto* variable = GetVariableImpl(a_name);
			if (!variable) {
				return std::nullopt;
			}

			return Impl::UnpackVariable<T>(*variable);
		}

		template <class T>
		[[nodiscard]] T FindOrDefault(REX::zstring_view a_name) const
			requires(BSScript::ValidateParameter<T>())
		{
			const auto* variable = GetVariableImpl(a_name);
			if (!variable) {
				return T();
			}

			const auto structLock = BSAutoLock(_proxy->structLock);
			return Impl::UnpackVariable<T>(*variable);
		}

		template <class T>
		[[nodiscard]] T FindOrDefault_NoLock(REX::zstring_view a_name) const
			requires(BSScript::ValidateParameter<T>())
		{
			const auto* variable = GetVariableImpl(a_name);
			if (!variable) {
				return T();
			}

			return Impl::UnpackVariable<T>(*variable);
		}

		template <class T>
		[[nodiscard]] T FindOrDefault(REX::zstring_view a_name, const T& a_default) const
			requires(BSScript::ValidateParameter<T>())
		{
			const auto* variable = GetVariableImpl(a_name);
			if (!variable) {
				return a_default;
			}

			const auto structLock = BSAutoLock(_proxy->structLock);
			return Impl::UnpackVariable<T>(*variable);
		}

		template <class T>
		[[nodiscard]] T FindOrDefault_NoLock(REX::zstring_view a_name, const T& a_default) const
			requires(BSScript::ValidateParameter<T>())
		{
			const auto* variable = GetVariableImpl(a_name);
			if (!variable) {
				return a_default;
			}

			return Impl::UnpackVariable<T>(*variable);
		}

		template <class T>
		bool Insert(REX::zstring_view a_name, T&& a_value)
			requires(BSScript::ValidateParameter<std::remove_reference_t<T>>())
		{
			auto* variable = GetVariableImpl(a_name);
			if (!variable) {
				return false;
			}

			const auto structLock = BSAutoLock(_proxy->structLock);
			Impl::PackVariable(*variable, std::forward<T>(a_value));
			return true;
		}

		template <class T>
		bool Insert_NoLock(REX::zstring_view a_name, T&& a_value)
			requires(BSScript::ValidateParameter<std::remove_reference_t<T>>())
		{
			auto* variable = GetVariableImpl(a_name);
			if (!variable) {
				return false;
			}

			Impl::PackVariable(*variable, std::forward<T>(a_value));
			return true;
		}

		void reset() noexcept
		{
			_proxy.reset();
		}

	protected:
		template <REX::StaticString, REX::StaticString>
		friend class StructWrapper;

	private:
		[[nodiscard]] Variable* GetVariableImpl(REX::zstring_view a_name) const
		{
			if (!_proxy) {
#if NDEBUG == 0
				const auto* typeInfo = GetStructTypeInfo();
				if (!typeInfo || !typeInfo->GetVariableIndex(BSFixedString(a_name)).has_value()) [[unlikely]] {
					REX::LogError(R"(Failed to find variable "{}" on struct "{}")"sv,
						a_name, GetTypeName());
					REX::Assert(false);
				}
#endif

				return nullptr;
			}

			auto* variable = _proxy->GetVariable(BSFixedString(a_name));
			if (!variable) [[unlikely]] {
				REX::LogError(R"(Failed to find variable "{}" on struct "{}")"sv,
					a_name, GetTypeName());
				REX::Assert(false);
				return nullptr;
			}

			return variable;
		}

		BSTSmartPointer<Struct> _proxy;
	};
}
