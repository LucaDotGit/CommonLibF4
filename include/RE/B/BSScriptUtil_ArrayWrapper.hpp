#pragma once

#include "RE/B/BSScriptUtil_Concepts.hpp"
#include "RE/B/BSScript_Array.hpp"
#include "RE/B/BSScript_TypeInfo.hpp"
#include "RE/B/BSScript_Variable.hpp"
#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/G/GameVM.hpp"

namespace RE::BSScript
{
	template <class T>
	class ArrayWrapper
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

		constexpr ArrayWrapper(std::nullptr_t) noexcept
			: _proxy(nullptr)
		{
		}

		constexpr explicit ArrayWrapper(BSTSmartPointer<Array> a_proxy)
			: _proxy(std::move(a_proxy))
		{
			REX::Assert(!_proxy || (_proxy->GetTypeInfo() == GetTypeInfo()));
		}

		constexpr ArrayWrapper(const ArrayWrapper&) noexcept = default;
		constexpr ArrayWrapper(ArrayWrapper&&) noexcept = default;

		constexpr ArrayWrapper& operator=(const ArrayWrapper&) noexcept = default;
		constexpr ArrayWrapper& operator=(ArrayWrapper&&) noexcept = default;

		constexpr ArrayWrapper& operator=(std::nullptr_t) noexcept
		{
			_proxy = nullptr;
			return *this;
		}

		constexpr ArrayWrapper& operator=(BSTSmartPointer<Array> a_proxy)
		{
			REX::Assert(!a_proxy || (a_proxy->GetTypeInfo() == GetTypeInfo()));
			_proxy = std::move(a_proxy);
			return *this;
		}

		[[nodiscard]] constexpr friend bool operator==(const ArrayWrapper& a_lhs, const ArrayWrapper& a_rhs) noexcept { return a_lhs._proxy == a_rhs._proxy; }
		[[nodiscard]] constexpr friend bool operator==(const ArrayWrapper& a_lhs, std::nullptr_t) noexcept { return a_lhs._proxy == nullptr; }
		[[nodiscard]] constexpr friend bool operator==(std::nullptr_t, const ArrayWrapper& a_rhs) noexcept { return a_rhs._proxy == nullptr; }
		[[nodiscard]] constexpr friend bool operator==(const ArrayWrapper& a_lhs, const BSTSmartPointer<Array>& a_rhs) noexcept { return a_lhs._proxy == a_rhs; }
		[[nodiscard]] constexpr friend bool operator==(const BSTSmartPointer<Array>& a_lhs, const ArrayWrapper& a_rhs) noexcept { return a_lhs == a_rhs._proxy; }
		[[nodiscard]] constexpr friend auto operator<=>(const ArrayWrapper& a_lhs, const ArrayWrapper& a_rhs) noexcept { return a_lhs._proxy <=> a_rhs._proxy; }
		[[nodiscard]] constexpr friend auto operator<=>(const ArrayWrapper& a_lhs, std::nullptr_t) noexcept { return a_lhs._proxy <=> nullptr; }
		[[nodiscard]] constexpr friend auto operator<=>(std::nullptr_t, const ArrayWrapper& a_rhs) noexcept { return nullptr <=> a_rhs._proxy; }
		[[nodiscard]] constexpr friend auto operator<=>(const ArrayWrapper& a_lhs, const BSTSmartPointer<Array>& a_rhs) noexcept { return a_lhs._proxy <=> a_rhs; }
		[[nodiscard]] constexpr friend auto operator<=>(const BSTSmartPointer<Array>& a_lhs, const ArrayWrapper& a_rhs) noexcept { return a_lhs <=> a_rhs._proxy; }

		[[nodiscard]] constexpr BSTSmartPointer<Array>& operator*() & noexcept { return _proxy; }
		[[nodiscard]] constexpr const BSTSmartPointer<Array>& operator*() const& noexcept { return _proxy; }

		[[nodiscard]] constexpr BSTSmartPointer<Array>&& operator*() && noexcept { return std::move(_proxy); }
		[[nodiscard]] constexpr const BSTSmartPointer<Array>&& operator*() const&& noexcept { return std::move(_proxy); }

		[[nodiscard]] constexpr BSTSmartPointer<Array>& operator->() noexcept { return _proxy; }
		[[nodiscard]] constexpr const BSTSmartPointer<Array>& operator->() const noexcept { return _proxy; }

		[[nodiscard]] constexpr explicit operator bool() const noexcept { return _proxy != nullptr; }
		[[nodiscard]] constexpr bool IsNone() const noexcept { return _proxy == nullptr; }

		[[nodiscard]] constexpr explicit operator BSTSmartPointer<Array>&() noexcept { return _proxy; }
		[[nodiscard]] constexpr explicit operator const BSTSmartPointer<Array>&() const noexcept { return _proxy; }

		[[nodiscard]] constexpr RE::BSTSmartPointer<Array>& get() & noexcept { return _proxy; }
		[[nodiscard]] constexpr const RE::BSTSmartPointer<Array>& get() const& noexcept { return _proxy; }

		[[nodiscard]] constexpr RE::BSTSmartPointer<Array>&& get() && noexcept { return std::move(_proxy); }
		[[nodiscard]] constexpr const RE::BSTSmartPointer<Array>&& get() const&& noexcept { return std::move(_proxy); }

		[[nodiscard]] reference operator[](size_type a_index) noexcept { return _proxy->operator[](a_index); }
		[[nodiscard]] const_reference operator[](size_type a_index) const noexcept { return _proxy->operator[](a_index); }

		[[nodiscard]] reference at(size_type a_index) noexcept { return _proxy->at(a_index); }
		[[nodiscard]] const_reference at(size_type a_index) const noexcept { return _proxy->at(a_index); }

		[[nodiscard]] reference front() noexcept { return _proxy->front(); }
		[[nodiscard]] const_reference front() const noexcept { return _proxy->front(); }

		[[nodiscard]] reference back() noexcept { return _proxy->back(); }
		[[nodiscard]] const_reference back() const noexcept { return _proxy->back(); }

		[[nodiscard]] pointer data() noexcept { return _proxy->data(); }
		[[nodiscard]] const_pointer data() const noexcept { return _proxy->data(); }

		[[nodiscard]] iterator begin() noexcept { return _proxy->begin(); }
		[[nodiscard]] const_iterator begin() const noexcept { return _proxy->begin(); }
		[[nodiscard]] const_iterator cbegin() const noexcept { return _proxy->cbegin(); }

		[[nodiscard]] iterator end() noexcept { return _proxy->end(); }
		[[nodiscard]] const_iterator end() const noexcept { return _proxy->end(); }
		[[nodiscard]] const_iterator cend() const noexcept { return _proxy->cend(); }

		[[nodiscard]] reverse_iterator rbegin() noexcept { return _proxy->rbegin(); }
		[[nodiscard]] const_reverse_iterator rbegin() const noexcept { return _proxy->rbegin(); }
		[[nodiscard]] const_reverse_iterator crbegin() const noexcept { return _proxy->crbegin(); }

		[[nodiscard]] reverse_iterator rend() noexcept { return _proxy->rend(); }
		[[nodiscard]] const_reverse_iterator rend() const noexcept { return _proxy->rend(); }
		[[nodiscard]] const_reverse_iterator crend() const noexcept { return _proxy->crend(); }

		[[nodiscard]] size_type size() const noexcept { return _proxy->size(); }
		[[nodiscard]] size_type capacity() const noexcept { return _proxy->capacity(); }
		[[nodiscard]] constexpr size_type max_size() const noexcept { return _proxy->max_size(); }

		[[nodiscard]] bool empty() const noexcept { return _proxy->empty(); }

		[[nodiscard]] BSTArray<value_type>& elements() noexcept { return _proxy->elements; }
		[[nodiscard]] const BSTArray<value_type>& elements() const noexcept { return _proxy->elements; }

		[[nodiscard]] static ArrayWrapper Create(std::uint32_t a_size = 0)
		{
			const auto scriptVM = GameVM::GetVMInterface();
			if (!scriptVM) [[unlikely]] {
				REX::Fail("Failed to get the game's script VM."sv);
			}

			auto array = BSTSmartPointer<Array>();
			if (!scriptVM->CreateArray(GetElementTypeInfo(), a_size, array) || !array) [[unlikely]] {
				REX::Fail(R"(Failed to create array proxy of array type "{}".)"sv,
					GetElementTypeInfo().ToString());
			}

			return ArrayWrapper{ std::move(array) };
		}

		[[nodiscard]] static TypeInfo GetTypeInfo()
		{
			const auto typeInfo = Impl::GetTypeInfo<ArrayWrapper>();
			return typeInfo.value_or(nullptr);
		}

		[[nodiscard]] static TypeInfo GetElementTypeInfo()
		{
			const auto typeInfo = Impl::GetTypeInfo<element_type>();
			return typeInfo.value_or(nullptr);
		}

		[[nodiscard]] BSAutoLock<BSSpinLock> Lock() const
		{
			return BSAutoLock(_proxy->elementsLock);
		}

		[[nodiscard]] bool Equals(const ArrayWrapper& a_rhs) const noexcept
		{
			if (_proxy == a_rhs._proxy) {
				return true;
			}

			if (!_proxy || !a_rhs._proxy) {
				return false;
			}

			return _proxy->Equals(*a_rhs._proxy);
		}

		[[nodiscard]] std::strong_ordering Compare(const ArrayWrapper& a_rhs) const noexcept
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

		[[nodiscard]] bool DeepEquals(const ArrayWrapper& a_rhs) const noexcept
		{
			if (_proxy == a_rhs._proxy) {
				return true;
			}

			if (!_proxy || !a_rhs._proxy) {
				return false;
			}

			return _proxy->DeepEquals(*a_rhs._proxy);
		}

		[[nodiscard]] std::partial_ordering DeepCompare(const ArrayWrapper& a_rhs) const noexcept
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

		[[nodiscard]] ArrayWrapper Clone() const
		{
			if (!_proxy) {
				return {};
			}

			auto scriptVM = GameVM::GetVMInterface();
			if (!scriptVM) [[unlikely]] {
				REX::Assert(false);
				return {};
			}

			return ArrayWrapper(_proxy->Clone(*scriptVM));
		}

		[[nodiscard]] ArrayWrapper DeepClone() const
		{
			if (!_proxy) {
				return {};
			}

			auto scriptVM = GameVM::GetVMInterface();
			if (!scriptVM) [[unlikely]] {
				REX::Assert(false);
				return {};
			}

			return ArrayWrapper(_proxy->DeepClone(*scriptVM));
		}

		void reset() noexcept
		{
			_proxy.reset();
		}

	protected:
		template <class>
		friend class ArrayWrapper;

	private:
		BSTSmartPointer<Array> _proxy;
	};
}
