#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSScriptUtil_Concepts.hpp"
#include "RE/B/BSScript_Object.hpp"
#include "RE/B/BSScript_ObjectTypeInfo.hpp"
#include "RE/B/BSScript_TypeInfo.hpp"
#include "RE/B/BSScript_Variable.hpp"
#include "RE/B/BSSpinLockPolicy.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/G/GameVM.hpp"

namespace RE::BSScript
{
	template <REX::StaticString ScriptName>
	class ObjectWrapper
	{
	public:
		inline static constexpr auto TYPE_NAME = ScriptName;

		constexpr ObjectWrapper() noexcept = default;
		constexpr ~ObjectWrapper() noexcept = default;

		constexpr ObjectWrapper(std::nullptr_t) noexcept
			: _proxy(nullptr)
		{
		}

		constexpr explicit ObjectWrapper(BSTSmartPointer<Object> a_proxy)
			: _proxy(std::move(a_proxy))
		{
			REX::Assert(!_proxy || (_proxy->GetTypeInfo() == GetObjectTypeInfo()));
		}

		constexpr ObjectWrapper(const ObjectWrapper&) noexcept = default;
		constexpr ObjectWrapper(ObjectWrapper&&) noexcept = default;

		constexpr ObjectWrapper& operator=(const ObjectWrapper&) noexcept = default;
		constexpr ObjectWrapper& operator=(ObjectWrapper&&) noexcept = default;

		constexpr ObjectWrapper& operator=(std::nullptr_t) noexcept
		{
			_proxy = nullptr;
			return *this;
		}

		constexpr ObjectWrapper& operator=(BSTSmartPointer<Object> a_proxy)
		{
			REX::Assert(!a_proxy || (a_proxy->GetTypeInfo() == GetObjectTypeInfo()));
			_proxy = std::move(a_proxy);
			return *this;
		}

		[[nodiscard]] constexpr friend bool operator==(const ObjectWrapper& a_lhs, const ObjectWrapper& a_rhs) noexcept { return a_lhs._proxy == a_rhs._proxy; }
		[[nodiscard]] constexpr friend bool operator==(const ObjectWrapper& a_lhs, std::nullptr_t) noexcept { return a_lhs._proxy == nullptr; }
		[[nodiscard]] constexpr friend bool operator==(std::nullptr_t, const ObjectWrapper& a_rhs) noexcept { return nullptr == a_rhs._proxy; }
		[[nodiscard]] constexpr friend bool operator==(const ObjectWrapper& a_lhs, const BSTSmartPointer<Object>& a_rhs) noexcept { return a_lhs._proxy == a_rhs; }
		[[nodiscard]] constexpr friend bool operator==(const BSTSmartPointer<Object>& a_lhs, const ObjectWrapper& a_rhs) noexcept { return a_lhs == a_rhs._proxy; }
		[[nodiscard]] constexpr friend auto operator<=>(const ObjectWrapper& a_lhs, const ObjectWrapper& a_rhs) noexcept { return a_lhs._proxy <=> a_rhs._proxy; }
		[[nodiscard]] constexpr friend auto operator<=>(const ObjectWrapper& a_lhs, std::nullptr_t) noexcept { return a_lhs._proxy <=> nullptr; }
		[[nodiscard]] constexpr friend auto operator<=>(std::nullptr_t, const ObjectWrapper& a_rhs) noexcept { return nullptr <=> a_rhs._proxy; }
		[[nodiscard]] constexpr friend auto operator<=>(const ObjectWrapper& a_lhs, const BSTSmartPointer<Object>& a_rhs) noexcept { return a_lhs._proxy <=> a_rhs; }
		[[nodiscard]] constexpr friend auto operator<=>(const BSTSmartPointer<Object>& a_lhs, const ObjectWrapper& a_rhs) noexcept { return a_lhs <=> a_rhs._proxy; }

		[[nodiscard]] constexpr BSTSmartPointer<Object>& operator*() & noexcept { return _proxy; }
		[[nodiscard]] constexpr const BSTSmartPointer<Object>& operator*() const& noexcept { return _proxy; }

		[[nodiscard]] constexpr BSTSmartPointer<Object>&& operator*() && noexcept { return std::move(_proxy); }
		[[nodiscard]] constexpr const BSTSmartPointer<Object>&& operator*() const&& noexcept { return std::move(_proxy); }

		[[nodiscard]] constexpr BSTSmartPointer<Object>& operator->() noexcept { return _proxy; }
		[[nodiscard]] constexpr const BSTSmartPointer<Object>& operator->() const noexcept { return _proxy; }

		[[nodiscard]] constexpr explicit operator bool() const noexcept { return _proxy != nullptr; }
		[[nodiscard]] constexpr bool IsNone() const noexcept { return _proxy == nullptr; }

		[[nodiscard]] constexpr explicit operator BSTSmartPointer<Object>&() noexcept { return _proxy; }
		[[nodiscard]] constexpr explicit operator const BSTSmartPointer<Object>&() const noexcept { return _proxy; }

		[[nodiscard]] constexpr BSTSmartPointer<Object>& get() & noexcept { return _proxy; }
		[[nodiscard]] constexpr const BSTSmartPointer<Object>& get() const& noexcept { return _proxy; }

		[[nodiscard]] constexpr BSTSmartPointer<Object>&& get() && noexcept { return std::move(_proxy); }
		[[nodiscard]] constexpr const BSTSmartPointer<Object>&& get() const&& noexcept { return std::move(_proxy); }

		[[nodiscard]] static constexpr REX::zstring_view GetTypeName() noexcept { return TYPE_NAME; }

		[[nodiscard]] static ObjectWrapper Create(ObjectHandle a_objectHandle)
		{
			const auto scriptVM = GameVM::GetVMInterface();
			if (!scriptVM) [[unlikely]] {
				REX::Fail("Failed to get script VM."sv);
			}

			auto proxy = BSTSmartPointer<Object>();
			if (!scriptVM->GetOrCreateScriptObject(BSFixedString(GetTypeName()), a_objectHandle, proxy) || !proxy) [[unlikely]] {
				REX::Fail(R"(Failed to create object proxy of object type "{}".)"sv,
					GetTypeName());
			}

			return ObjectWrapper{ std::move(proxy) };
		}

		[[nodiscard]] static TypeInfo GetTypeInfo()
		{
			const auto typeInfo = Impl::GetTypeInfo<ObjectWrapper>();
			return typeInfo.value_or(nullptr);
		}

		[[nodiscard]] static ObjectTypeInfo* GetObjectTypeInfo()
		{
			const auto typeInfo = GetTypeInfo();
			return typeInfo.GetObjectTypeInfo();
		}

		[[nodiscard]] BSAutoLock<Object> Lock() const
		{
			return BSAutoLock(*_proxy);
		}

		[[nodiscard]] bool Equals(const ObjectWrapper& a_rhs) const noexcept
		{
			if (_proxy == a_rhs._proxy) {
				return true;
			}

			if (!_proxy || !a_rhs._proxy) {
				return false;
			}

			return _proxy->Equals(*a_rhs._proxy);
		}

		[[nodiscard]] std::strong_ordering Compare(const ObjectWrapper& a_rhs) const noexcept
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

		[[nodiscard]] bool DeepEquals(const ObjectWrapper& a_rhs) const noexcept
		{
			if (_proxy == a_rhs._proxy) {
				return true;
			}

			if (!_proxy || !a_rhs._proxy) {
				return false;
			}

			return _proxy->DeepEquals(*a_rhs._proxy);
		}

		[[nodiscard]] std::partial_ordering DeepCompare(const ObjectWrapper& a_rhs) const noexcept
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

		[[nodiscard]] ObjectWrapper Clone() const
		{
			if (!_proxy) {
				return ObjectWrapper(nullptr);
			}

			auto scriptVM = GameVM::GetVMInterface();
			if (!scriptVM) [[unlikely]] {
				REX::Assert(false);
				return ObjectWrapper(nullptr);
			}

			return ObjectWrapper(_proxy->Clone(*scriptVM));
		}

		[[nodiscard]] ObjectWrapper DeepClone() const
		{
			if (!_proxy) {
				return ObjectWrapper(nullptr);
			}

			auto scriptVM = GameVM::GetVMInterface();
			if (!scriptVM) [[unlikely]] {
				REX::Assert(false);
				return ObjectWrapper(nullptr);
			}

			return ObjectWrapper(_proxy->DeepClone(*scriptVM));
		}

		template <class T>
		[[nodiscard]] auto FindVariable(REX::zstring_view a_name) const -> std::optional<T>
			requires(BSScript::ValidateParameter<T>())
		{
			const auto* variable = GetVariableImpl(a_name);
			if (!variable) {
				return std::nullopt;
			}

			const auto arrayLock = BSAutoLock(*_proxy);
			return Impl::UnpackVariable<T>(*variable);
		}

		template <class T>
		[[nodiscard]] auto FindVariable_NoLock(REX::zstring_view a_name) const -> std::optional<T>
			requires(BSScript::ValidateParameter<T>())
		{
			const auto* variable = GetVariableImpl(a_name);
			if (!variable) {
				return std::nullopt;
			}

			return Impl::UnpackVariable<T>(*variable);
		}

		template <class T>
		[[nodiscard]] T FindVariableOrDefault(REX::zstring_view a_name) const
			requires(BSScript::ValidateParameter<T>())
		{
			const auto* variable = GetVariableImpl(a_name);
			if (!variable) {
				return {};
			}

			const auto arrayLock = BSAutoLock(*_proxy);
			return Impl::UnpackVariable<T>(*variable);
		}

		template <class T>
		[[nodiscard]] T FindVariableOrDefault_NoLock(REX::zstring_view a_name) const
			requires(BSScript::ValidateParameter<T>())
		{
			const auto* variable = GetVariableImpl(a_name);
			if (!variable) {
				return {};
			}

			return Impl::UnpackVariable<T>(*variable);
		}

		template <class T>
		[[nodiscard]] auto FindProperty(REX::zstring_view a_name) const -> std::optional<T>
			requires(BSScript::ValidateParameter<T>())
		{
			const auto* property = GetPropertyImpl(a_name);
			if (!property) {
				return std::nullopt;
			}

			const auto arrayLock = BSAutoLock(*_proxy);
			return Impl::UnpackVariable<T>(*property);
		}

		template <class T>
		[[nodiscard]] auto FindProperty_NoLock(REX::zstring_view a_name) const -> std::optional<T>
			requires(BSScript::ValidateParameter<T>())
		{
			const auto* property = GetPropertyImpl(a_name);
			if (!property) {
				return std::nullopt;
			}

			return Impl::UnpackVariable<T>(*property);
		}

		template <class T>
		[[nodiscard]] T FindPropertyOrDefault(REX::zstring_view a_name) const
			requires(BSScript::ValidateParameter<T>())
		{
			const auto* property = GetPropertyImpl(a_name);
			if (!property) {
				return {};
			}

			const auto arrayLock = BSAutoLock(*_proxy);
			return Impl::UnpackVariable<T>(*property);
		}

		template <class T>
		[[nodiscard]] T FindPropertyOrDefault_NoLock(REX::zstring_view a_name) const
			requires(BSScript::ValidateParameter<T>())
		{
			const auto* property = GetPropertyImpl(a_name);
			if (!property) {
				return {};
			}

			return Impl::UnpackVariable<T>(*property);
		}

		template <class T>
		bool InsertVariable(REX::zstring_view a_name, T&& a_value)
			requires(BSScript::ValidateParameter<std::remove_reference_t<T>>())
		{
			auto* variable = GetVariableImpl(a_name);
			if (!variable) {
				return false;
			}

			const auto arrayLock = BSAutoLock(*_proxy);
			Impl::PackVariable(*variable, std::forward<T>(a_value));
			return true;
		}

		template <class T>
		bool InsertVariable_NoLock(REX::zstring_view a_name, T&& a_value)
			requires(BSScript::ValidateParameter<std::remove_reference_t<T>>())
		{
			auto* variable = GetVariableImpl(a_name);
			if (!variable) {
				return false;
			}

			Impl::PackVariable(*variable, std::forward<T>(a_value));
			return true;
		}

		template <class T>
		bool InsertProperty(REX::zstring_view a_name, T&& a_value)
			requires(BSScript::ValidateParameter<std::remove_reference_t<T>>())
		{
			auto* property = GetPropertyImpl(a_name);
			if (!property) {
				return false;
			}

			const auto arrayLock = BSAutoLock(*_proxy);
			Impl::PackVariable(*property, std::forward<T>(a_value));
			return true;
		}

		template <class T>
		bool InsertProperty_NoLock(REX::zstring_view a_name, T&& a_value)
			requires(BSScript::ValidateParameter<std::remove_reference_t<T>>())
		{
			auto* property = GetPropertyImpl(a_name);
			if (!property) {
				return false;
			}

			Impl::PackVariable(*property, std::forward<T>(a_value));
			return true;
		}

		void reset() noexcept
		{
			_proxy.reset();
		}

	protected:
		template <REX::StaticString>
		friend class ObjectWrapper;

	private:
		[[nodiscard]] Variable* GetVariableImpl(REX::zstring_view a_name) const
		{
			if (!_proxy) {
#if NDEBUG == 0
				const auto* typeInfo = GetObjectTypeInfo();
				if (!typeInfo || !typeInfo->GetVariableIndex(BSFixedString(a_name)).has_value()) [[unlikely]] {
					REX::LogError(R"(Failed to find variable "{}" on object "{}")"sv,
						a_name, GetTypeName());
					REX::Assert(false);
				}
#endif

				return nullptr;
			}

			auto* variable = _proxy->GetVariable(BSFixedString(a_name));
			if (!variable) [[unlikely]] {
				REX::LogError(R"(Failed to find variable "{}" on object "{}")"sv,
					a_name, GetTypeName());
				REX::Assert(false);
				return nullptr;
			}

			return variable;
		}

		[[nodiscard]] Variable* GetPropertyImpl(REX::zstring_view a_name) const
		{
			if (!_proxy) {
#if NDEBUG == 0
				const auto* typeInfo = GetObjectTypeInfo();
				if (!typeInfo || !typeInfo->GetPropertyIndex(BSFixedString(a_name)).has_value()) [[unlikely]] {
					REX::LogError(R"(Failed to find property "{}" on object "{}")"sv,
						a_name, GetTypeName());
					REX::Assert(false);
				}
#endif

				return nullptr;
			}

			auto* property = _proxy->GetProperty(BSFixedString(a_name));
			if (!property) [[unlikely]] {
				REX::LogError(R"(Failed to find property "{}" on object "{}")"sv,
					a_name, GetTypeName());
				REX::Assert(false);
				return nullptr;
			}

			return property;
		}

		BSTSmartPointer<Object> _proxy;
	};
}
