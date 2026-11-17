#pragma once

#include "RE/B/BSScriptUtility_Concepts.hpp"
#include "RE/B/BSScript_Array.hpp"
#include "RE/B/BSScript_IVirtualMachine.hpp"
#include "RE/B/BSScript_TypeInfo.hpp"
#include "RE/B/BSScript_Variable.hpp"
#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSScript
{
	template <class T>
	class ArrayWrapper final
	{
	public:
		using element_type = T;
		using value_type = Array::value_type;
		using size_type = Array::size_type;
		using difference_type = Array::difference_type;
		using pointer = Array::pointer;
		using const_pointer = Array::const_pointer;
		using reference = Array::reference;
		using const_reference = Array::const_reference;
		using iterator = Array::iterator;
		using const_iterator = Array::const_iterator;
		using reverse_iterator = Array::reverse_iterator;
		using const_reverse_iterator = Array::const_reverse_iterator;

		static_assert(BSScript::ValidateParameter<element_type>());

		constexpr ArrayWrapper() noexcept = default;
		constexpr ~ArrayWrapper() noexcept = default;

		// NOLINTNEXTLINE(misc-explicit-constructor)
		constexpr ArrayWrapper(std::nullptr_t) noexcept :
			_proxy(nullptr)
		{
		}

		constexpr explicit ArrayWrapper(BSTSmartPointer<Array> a_proxy) :
			_proxy(std::move(a_proxy))
		{
		}

		constexpr ArrayWrapper(const ArrayWrapper&) noexcept = default;
		constexpr ArrayWrapper(ArrayWrapper&&) noexcept = default;

		constexpr auto operator=(const ArrayWrapper&) noexcept -> ArrayWrapper& = default;
		constexpr auto operator=(ArrayWrapper&&) noexcept -> ArrayWrapper& = default;

		constexpr auto operator=(std::nullptr_t) noexcept -> ArrayWrapper&
		{
			_proxy = nullptr;
			return *this;
		}

		constexpr auto operator=(BSTSmartPointer<Array> a_proxy) -> ArrayWrapper&
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
		constexpr explicit operator BSTSmartPointer<Array>() const noexcept
		{
			return _proxy;
		}

		[[nodiscard]]
		constexpr auto operator*() & noexcept -> BSTSmartPointer<Array>&
		{
			return _proxy;
		}

		[[nodiscard]]
		constexpr auto operator*() const& noexcept -> const BSTSmartPointer<Array>&
		{
			return _proxy;
		}

		[[nodiscard]]
		constexpr auto operator*() && noexcept -> BSTSmartPointer<Array>&&
		{
			return std::move(_proxy);
		}

		[[nodiscard]]
		constexpr auto operator*() const&& noexcept -> const BSTSmartPointer<Array>&&
		{
			return std::move(_proxy);
		}

		[[nodiscard]]
		constexpr auto operator->() noexcept -> BSTSmartPointer<Array>&
		{
			return _proxy;
		}

		[[nodiscard]]
		constexpr auto operator->() const noexcept -> const BSTSmartPointer<Array>&
		{
			return _proxy;
		}

		[[nodiscard]]
		constexpr auto IsNone() const noexcept -> bool
		{
			return _proxy == nullptr;
		}

		[[nodiscard]]
		constexpr auto get() & noexcept -> RE::BSTSmartPointer<Array>&
		{
			return _proxy;
		}

		[[nodiscard]]
		constexpr auto get() const& noexcept -> const RE::BSTSmartPointer<Array>&
		{
			return _proxy;
		}

		[[nodiscard]]
		constexpr auto get() && noexcept -> RE::BSTSmartPointer<Array>&&
		{
			return std::move(_proxy);
		}

		[[nodiscard]]
		constexpr auto get() const&& noexcept -> const RE::BSTSmartPointer<Array>&&
		{
			return std::move(_proxy);
		}

		[[nodiscard]]
		auto operator[](size_type a_index) noexcept -> reference
		{
			return _proxy->operator[](a_index);
		}

		[[nodiscard]]
		auto operator[](size_type a_index) const noexcept -> const_reference
		{
			return _proxy->operator[](a_index);
		}

		[[nodiscard]]
		auto at(size_type a_index) noexcept -> reference
		{
			return _proxy->at(a_index);
		}

		[[nodiscard]]
		auto at(size_type a_index) const noexcept -> const_reference
		{
			return _proxy->at(a_index);
		}

		[[nodiscard]]
		auto front() noexcept -> reference
		{
			return _proxy->front();
		}

		[[nodiscard]]
		auto front() const noexcept -> const_reference
		{
			return _proxy->front();
		}

		[[nodiscard]]
		auto back() noexcept -> reference
		{
			return _proxy->back();
		}

		[[nodiscard]]
		auto back() const noexcept -> const_reference
		{
			return _proxy->back();
		}

		[[nodiscard]]
		auto data() noexcept -> pointer
		{
			return _proxy->data();
		}

		[[nodiscard]]
		auto data() const noexcept -> const_pointer
		{
			return _proxy->data();
		}

		[[nodiscard]]
		auto begin() noexcept -> iterator
		{
			return _proxy->begin();
		}

		[[nodiscard]]
		auto begin() const noexcept -> const_iterator
		{
			return _proxy->begin();
		}

		[[nodiscard]]
		auto cbegin() const noexcept -> const_iterator
		{
			return _proxy->cbegin();
		}

		[[nodiscard]]
		auto end() noexcept -> iterator
		{
			return _proxy->end();
		}

		[[nodiscard]]
		auto end() const noexcept -> const_iterator
		{
			return _proxy->end();
		}

		[[nodiscard]]
		auto cend() const noexcept -> const_iterator
		{
			return _proxy->cend();
		}

		[[nodiscard]]
		auto rbegin() noexcept -> reverse_iterator
		{
			return _proxy->rbegin();
		}

		[[nodiscard]]
		auto rbegin() const noexcept -> const_reverse_iterator
		{
			return _proxy->rbegin();
		}

		[[nodiscard]]
		auto crbegin() const noexcept -> const_reverse_iterator
		{
			return _proxy->crbegin();
		}

		[[nodiscard]]
		auto rend() noexcept -> reverse_iterator
		{
			return _proxy->rend();
		}

		[[nodiscard]]
		auto rend() const noexcept -> const_reverse_iterator
		{
			return _proxy->rend();
		}

		[[nodiscard]]
		auto crend() const noexcept -> const_reverse_iterator
		{
			return _proxy->crend();
		}

		[[nodiscard]]
		auto size() const noexcept -> size_type
		{
			return _proxy->size();
		}

		[[nodiscard]]
		auto capacity() const noexcept -> size_type
		{
			return _proxy->capacity();
		}

		[[nodiscard]]
		constexpr auto max_size() const noexcept -> size_type
		{
			return _proxy->max_size();
		}

		[[nodiscard]]
		auto empty() const noexcept -> bool
		{
			return _proxy->empty();
		}

		[[nodiscard]]
		auto elements() noexcept -> BSTArray<value_type>&
		{
			return _proxy->elements;
		}

		[[nodiscard]]
		auto elements() const noexcept -> const BSTArray<value_type>&
		{
			return _proxy->elements;
		}

		[[nodiscard]]
		static auto Create(IVirtualMachine& a_vm, std::uint32_t a_size = 0) -> ArrayWrapper
		{
			const auto elementTypeInfo = GetElementTypeInfo(a_vm);
			if (!elementTypeInfo.has_value()) {
				return {};
			}

			auto array = BSTSmartPointer<Array>();
			if (!a_vm.CreateArray(elementTypeInfo.value(), a_size, array) || !array) {
				return {};
			}

			return ArrayWrapper(std::move(array));
		}

		[[nodiscard]]
		static auto CreateOrFail(IVirtualMachine& a_vm, std::uint32_t a_size = 0) -> REX::NotNull<ArrayWrapper>
		{
			const auto elementTypeInfo = GetElementTypeInfo(a_vm);
			if (!elementTypeInfo.has_value()) [[unlikely]] {
				REX::Fail(R"(Failed to get type info for array element type "{}".)"sv, typeid(element_type).name());
			}

			auto array = BSTSmartPointer<Array>();
			if (!a_vm.CreateArray(elementTypeInfo.value(), a_size, array) || !array) [[unlikely]] {
				REX::Fail(R"(Failed to create array of element type "{}".)"sv, elementTypeInfo->GetTypeName());
			}

			return ArrayWrapper(std::move(array));
		}

		[[nodiscard]]
		static auto GetTypeInfo(IVirtualMachine& a_vm) -> std::optional<TypeInfo>
		{
			return Impl::GetTypeInfo<ArrayWrapper>(a_vm);
		}

		[[nodiscard]]
		static auto GetElementTypeInfo(IVirtualMachine& a_vm) -> std::optional<TypeInfo>
		{
			return Impl::GetTypeInfo<element_type>(a_vm);
		}

		[[nodiscard]]
		auto Lock() const noexcept -> auto
		{
			return BSAutoSpinLock(_proxy->elementsLock);
		}

		[[nodiscard]]
		auto Equals(const ArrayWrapper& a_rhs) const noexcept -> bool
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
		auto Compare(const ArrayWrapper& a_rhs) const noexcept -> auto
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
		auto DeepEquals(const ArrayWrapper& a_rhs) const noexcept -> bool
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
		auto DeepCompare(const ArrayWrapper& a_rhs) const noexcept -> auto
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
		auto Clone(IVirtualMachine& a_vm) const -> ArrayWrapper
		{
			if (!_proxy) {
				return {};
			}

			return ArrayWrapper(_proxy->Clone(a_vm));
		}

		[[nodiscard]]
		auto DeepClone(IVirtualMachine& a_vm) const -> ArrayWrapper
		{
			if (!_proxy) {
				return {};
			}

			return ArrayWrapper(_proxy->DeepClone(a_vm));
		}

		void reset() noexcept
		{
			_proxy.reset();
		}

		[[nodiscard]]
		constexpr friend auto operator==(const ArrayWrapper& a_lhs, const ArrayWrapper& a_rhs) noexcept -> bool
		{
			return a_lhs._proxy == a_rhs._proxy;
		}

		[[nodiscard]]
		constexpr friend auto operator==(const ArrayWrapper& a_lhs, std::nullptr_t) noexcept -> bool
		{
			return a_lhs._proxy == nullptr;
		}

		[[nodiscard]]
		constexpr friend auto operator==(std::nullptr_t, const ArrayWrapper& a_rhs) noexcept -> bool
		{
			return a_rhs._proxy == nullptr;
		}

		[[nodiscard]]
		constexpr friend auto operator==(const ArrayWrapper& a_lhs, const BSTSmartPointer<Array>& a_rhs) noexcept
			-> bool
		{
			return a_lhs._proxy == a_rhs;
		}

		[[nodiscard]]
		constexpr friend auto operator==(const BSTSmartPointer<Array>& a_lhs, const ArrayWrapper& a_rhs) noexcept
			-> bool
		{
			return a_lhs == a_rhs._proxy;
		}

		[[nodiscard]]
		constexpr friend auto operator<=>(const ArrayWrapper& a_lhs, const ArrayWrapper& a_rhs) noexcept -> auto
		{
			return a_lhs._proxy <=> a_rhs._proxy;
		}

		[[nodiscard]]
		constexpr friend auto operator<=>(const ArrayWrapper& a_lhs, std::nullptr_t) noexcept -> auto
		{
			return a_lhs._proxy <=> nullptr;
		}

		[[nodiscard]]
		constexpr friend auto operator<=>(std::nullptr_t, const ArrayWrapper& a_rhs) noexcept -> auto
		{
			return nullptr <=> a_rhs._proxy;
		}

		[[nodiscard]]
		constexpr friend auto operator<=>(const ArrayWrapper& a_lhs, const BSTSmartPointer<Array>& a_rhs) noexcept
			-> auto
		{
			return a_lhs._proxy <=> a_rhs;
		}

		[[nodiscard]]
		constexpr friend auto operator<=>(const BSTSmartPointer<Array>& a_lhs, const ArrayWrapper& a_rhs) noexcept
			-> auto
		{
			return a_lhs <=> a_rhs._proxy;
		}

	private:
		template <class>
		friend class ArrayWrapper;

		BSTSmartPointer<Array> _proxy;
	};
}
