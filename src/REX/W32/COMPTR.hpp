#pragma once

#include "REX/Contract.hpp"
#include "REX/Hashing.hpp"
#include "REX/Message.hpp"
#include "REX/W32/CORE.hpp"

namespace REX::W32
{
	// Source: https://learn.microsoft.com/en-us/cpp/cppcx/wrl/comptr-class

	template <class T>
	class ComPtr final
	{
	public:
		using element_type = T;

		constexpr ComPtr() noexcept = default;

		constexpr ~ComPtr() noexcept
		{
			reset();
		}

		// NOLINTNEXTLINE(misc-explicit-constructor)
		constexpr ComPtr(std::nullptr_t) noexcept :
			_ptr(nullptr)
		{
		}

		template <class U>
		constexpr explicit ComPtr(U* a_rhs) noexcept
			requires(std::is_convertible_v<U*, T*>)
			:
			_ptr(static_cast<T*>(a_rhs))
		{
			try_attach();
		}

		template <class U>
		// NOLINTNEXTLINE(misc-explicit-constructor)
		constexpr ComPtr(const ComPtr<U>& a_rhs) noexcept
			requires(std::is_convertible_v<U*, T*>)
			:
			_ptr(static_cast<T*>(a_rhs._ptr))
		{
			try_attach();
		}

		template <class U>
		// NOLINTNEXTLINE(misc-explicit-constructor, cppcoreguidelines-rvalue-reference-param-not-moved)
		constexpr ComPtr(ComPtr<U>&& a_rhs) noexcept
			requires(std::is_convertible_v<U*, T*>)
			:
			_ptr(std::exchange(static_cast<T*>(a_rhs._ptr), nullptr))
		{
		}

		constexpr ComPtr(const ComPtr& a_rhs) noexcept :
			_ptr(a_rhs._ptr)
		{
			try_attach();
		}

		constexpr ComPtr(ComPtr&& a_rhs) noexcept :
			_ptr(std::exchange(a_rhs._ptr, nullptr))
		{
		}

		constexpr auto operator=(std::nullptr_t) noexcept -> ComPtr&
		{
			try_detach();
			return *this;
		}

		template <class U>
		constexpr auto operator=(U* a_rhs) noexcept -> ComPtr&
			requires(std::is_convertible_v<U*, T*>)
		{
			try_detach();
			_ptr = static_cast<T*>(a_rhs);
			try_attach();
			return *this;
		}

		template <class U>
		constexpr auto operator=(const ComPtr<U>& a_rhs) noexcept -> ComPtr&
			requires(std::is_convertible_v<U*, T*>)
		{
			try_detach();
			_ptr = static_cast<T*>(a_rhs._ptr);
			try_attach();
			return *this;
		}

		template <class U>
		// NOLINTNEXTLINE(cppcoreguidelines-rvalue-reference-param-not-moved)
		constexpr auto operator=(ComPtr<U>&& a_rhs) noexcept -> ComPtr&
			requires(std::is_convertible_v<U*, T*>)
		{
			try_detach();
			_ptr = std::exchange(static_cast<T*>(a_rhs._ptr), nullptr);
			return *this;
		}

		constexpr auto operator=(const ComPtr& a_rhs) noexcept -> ComPtr&
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			try_detach();
			_ptr = a_rhs._ptr;
			try_attach();
			return *this;
		}

		constexpr auto operator=(ComPtr&& a_rhs) noexcept -> ComPtr&
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			try_detach();
			_ptr = std::exchange(a_rhs._ptr, nullptr);
			return *this;
		}

		[[nodiscard]]
		constexpr explicit operator bool() const noexcept
		{
			return _ptr != nullptr;
		}

		[[nodiscard]]
		constexpr auto operator*() const noexcept -> T&
		{
			REX::Assert(static_cast<bool>(_ptr));
			return *_ptr;
		}

		[[nodiscard]]
		constexpr auto operator->() const noexcept -> T*
		{
			REX::Assert(static_cast<bool>(_ptr));
			return _ptr;
		}

		[[nodiscard]]
		constexpr auto get() const noexcept -> T*
		{
			return _ptr;
		}

		template <class U>
		auto try_as(ComPtr<U>* a_ptr) const noexcept -> HRESULT
		{
			return _ptr->QueryInterface(
				__uuidof(U),
				static_cast<void**>(a_ptr ? a_ptr->try_detach_and_address_of() : nullptr));
		}

		template <class U>
		auto try_as(const IID& a_iid, ComPtr<U>* a_ptr) const noexcept -> HRESULT
		{
			return _ptr->QueryInterface(
				a_iid,
				static_cast<void**>(a_ptr ? a_ptr->try_detach_and_address_of() : nullptr));
		}

		auto copy_to(T** a_ptr) const noexcept -> HRESULT
		{
			try_attach();
			*a_ptr = _ptr;
			return 0;
		}

		template <class U>
		auto copy_to(U** a_ptr) const noexcept -> HRESULT
		{
			return _ptr->QueryInterface(__uuidof(U), static_cast<void**>(a_ptr));
		}

		auto copy_to(const IID& a_iid, void** a_ptr) const noexcept -> HRESULT
		{
			return _ptr->QueryInterface(a_iid, a_ptr);
		}

		constexpr void attach(T* a_rhs) noexcept
		{
			if (_ptr != nullptr) {
				[[maybe_unused]]
				auto refCount = _ptr->Release();
				REX::Assert((refCount != 0) || (_ptr != a_rhs));
			}

			_ptr = a_rhs;
		}

		[[nodiscard]]
		constexpr auto detach() noexcept -> T*
		{
			return std::exchange(_ptr, nullptr);
		}

		constexpr void reset() noexcept
		{
			return try_detach();
		}

		template <class U>
		constexpr void reset(U* a_ptr) noexcept
			requires(std::is_convertible_v<U*, T*>)
		{
			if (_ptr == a_ptr) {
				return;
			}

			try_detach();
			_ptr = static_cast<T*>(a_ptr);
			try_attach();
		}

		constexpr void swap(ComPtr& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(_ptr, a_other._ptr);
		}

	protected:
		template <class U>
		friend class ComPtr;

		constexpr auto try_detach_and_address_of() noexcept -> element_type**
		{
			try_detach();
			return std::addressof(_ptr);
		}

		constexpr void try_attach() noexcept
		{
			if (!_ptr) {
				return;
			}

			try {
				_ptr->AddRef();
			}
			catch (...) {
				REX::Fail("Failed to increment ref count."sv);
			}
		}

		constexpr void try_detach() noexcept
		{
			if (!_ptr) {
				return;
			}

			try {
				_ptr->Release();
				_ptr = nullptr;
			}
			catch (...) {
				REX::Fail("Failed to decrement ref count."sv);
			}
		}

		// members
		T* _ptr{nullptr}; // 0x00
	};

	static_assert(sizeof(ComPtr<void*>) == 0x08);

	template <class T>
	ComPtr(T*) -> ComPtr<T>;

	template <class T>
	[[nodiscard]]
	constexpr auto operator==(const ComPtr<T>& a_lhs, const ComPtr<T>& a_rhs) noexcept -> bool
	{
		return a_lhs.get() == a_rhs.get();
	}

	template <class T>
	[[nodiscard]]
	constexpr auto operator==(const ComPtr<T>& a_lhs, std::nullptr_t) noexcept -> bool
	{
		return a_lhs.get() == static_cast<T*>(nullptr);
	}

	template <class T>
	[[nodiscard]]
	constexpr auto operator==(std::nullptr_t, const ComPtr<T>& a_rhs) noexcept -> bool
	{
		return static_cast<T*>(nullptr) == a_rhs.get();
	}

	template <class T>
	[[nodiscard]]
	constexpr auto operator==(const ComPtr<T>& a_lhs, const T* a_rhs) noexcept -> bool
	{
		return a_lhs.get() == a_rhs;
	}

	template <class T>
	[[nodiscard]]
	constexpr auto operator==(const T* a_lhs, const ComPtr<T>& a_rhs) noexcept -> bool
	{
		return a_lhs == a_rhs.get();
	}

	template <class T>
	[[nodiscard]]
	constexpr auto operator<=>(const ComPtr<T>& a_lhs, const ComPtr<T>& a_rhs) noexcept -> auto
	{
		return a_lhs.get() <=> a_rhs.get();
	}

	template <class T>
	[[nodiscard]]
	constexpr auto operator<=>(const ComPtr<T>& a_lhs, std::nullptr_t) noexcept -> auto
	{
		return a_lhs.get() <=> static_cast<T*>(nullptr);
	}

	template <class T>
	[[nodiscard]]
	constexpr auto operator<=>(std::nullptr_t, const ComPtr<T>& a_rhs) noexcept -> auto
	{
		return static_cast<T*>(nullptr) <=> a_rhs.get();
	}

	template <class T>
	[[nodiscard]]
	constexpr auto operator<=>(const ComPtr<T>& a_lhs, const T* a_rhs) noexcept -> auto
	{
		return a_lhs.get() <=> a_rhs;
	}

	template <class T>
	[[nodiscard]]
	constexpr auto operator<=>(const T* a_lhs, const ComPtr<T>& a_rhs) noexcept -> auto
	{
		return a_lhs <=> a_rhs.get();
	}

	template <class T, class... Args>
	[[nodiscard]]
	auto make_com_ptr(Args&&... a_args) -> ComPtr<T>
		requires(std::is_constructible_v<T, Args...>)
	{
		return ComPtr{new T(std::forward<Args>(a_args)...)};
	}

	template <class T1, class T2>
	[[nodiscard]]
	auto static_com_ptr_cast(const ComPtr<T2>& a_ptr) noexcept -> ComPtr<T1>
		requires(std::is_convertible_v<T2*, T1*>)
	{
		return ComPtr<T1>{static_cast<T1*>(a_ptr.get())};
	}

	template <class T1, class T2>
	[[nodiscard]]
	auto dynamic_com_ptr_cast(const ComPtr<T2>& a_ptr) noexcept -> ComPtr<T1>
	{
		auto result = ComPtr<T1>();
		a_ptr.try_as(result);
		return result;
	}

	template <class T1, class T2>
	[[nodiscard]]
	auto reinterpret_com_ptr_cast(const ComPtr<T2>& a_ptr) noexcept -> ComPtr<T1>
	{
		return ComPtr<T1>{reinterpret_cast<T1*>(a_ptr.get())};
	}

	template <class T1, class T2>
	[[nodiscard]]
	auto const_com_ptr_cast(const ComPtr<T2>& a_ptr) noexcept -> ComPtr<T1>
	{
		return ComPtr<T1>{const_cast<T1*>(a_ptr.get())};
	}
}

namespace std
{
	template <class T>
	struct hash<REX::W32::ComPtr<T>>
	{
	public:
		[[nodiscard]]
		auto operator()(const REX::W32::ComPtr<T>& a_key) const noexcept -> std::size_t
		{
			return REX::Hash<const void*>(a_key.get());
		}
	};
}
