#pragma once

#include "RE/B/BSCRC32.hpp"

namespace RE
{
	template <class T>
	class NiPointer
	{
	public:
		using element_type = T;

		constexpr NiPointer() noexcept = default;

		constexpr ~NiPointer() noexcept
		{
			reset();
		}

		// NOLINTNEXTLINE(misc-explicit-constructor)
		constexpr NiPointer(std::nullptr_t) noexcept :
			_ptr(nullptr)
		{
		}

		template <class U>
		constexpr explicit NiPointer(U* a_rhs) noexcept
			requires(std::is_convertible_v<U*, element_type*>)
			:
			_ptr(static_cast<element_type*>(a_rhs))
		{
			try_attach();
		}

		template <class U>
		// NOLINTNEXTLINE(misc-explicit-constructor)
		constexpr NiPointer(const NiPointer<U>& a_rhs) noexcept
			requires(std::is_convertible_v<U*, element_type*>)
			:
			_ptr(static_cast<element_type*>(a_rhs._ptr))
		{
			try_attach();
		}

		template <class U>
		// NOLINTNEXTLINE(misc-explicit-constructor, cppcoreguidelines-rvalue-reference-param-not-moved)
		constexpr NiPointer(NiPointer<U>&& a_rhs) noexcept
			requires(std::is_convertible_v<U*, element_type*>)
			:
			_ptr(static_cast<element_type*>(std::exchange(a_rhs._ptr, nullptr)))
		{
		}

		constexpr NiPointer(const NiPointer& a_rhs) noexcept :
			_ptr(a_rhs._ptr)
		{
			try_attach();
		}

		constexpr NiPointer(NiPointer&& a_rhs) noexcept :
			_ptr(std::exchange(a_rhs._ptr, nullptr))
		{
		}

		constexpr auto operator=(std::nullptr_t) noexcept -> NiPointer&
		{
			try_detach();
			return *this;
		}

		template <class U>
		constexpr auto operator=(U* a_rhs) noexcept -> NiPointer&
			requires(std::is_convertible_v<U*, element_type*>)
		{
			try_detach();
			_ptr = static_cast<element_type*>(a_rhs);
			try_attach();
			return *this;
		}

		template <class U>
		constexpr auto operator=(const NiPointer<U>& a_rhs) noexcept -> NiPointer&
			requires(std::is_convertible_v<U*, element_type*>)
		{
			try_detach();
			_ptr = static_cast<element_type*>(a_rhs._ptr);
			try_attach();
			return *this;
		}

		template <class U>
		// NOLINTNEXTLINE(cppcoreguidelines-rvalue-reference-param-not-moved)
		constexpr auto operator=(NiPointer<U>&& a_rhs) noexcept -> NiPointer&
			requires(std::is_convertible_v<U*, element_type*>)
		{
			try_detach();
			_ptr = std::exchange(a_rhs._ptr, nullptr);
			return *this;
		}

		constexpr auto operator=(const NiPointer& a_rhs) noexcept -> NiPointer&
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			try_detach();
			_ptr = a_rhs._ptr;
			try_attach();
			return *this;
		}

		constexpr auto operator=(NiPointer&& a_rhs) noexcept -> NiPointer&
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
		constexpr auto operator*() const noexcept -> element_type&
		{
			REX::Assert(static_cast<bool>(*this));
			return *_ptr;
		}

		[[nodiscard]]
		constexpr auto operator->() const noexcept -> element_type*
		{
			REX::Assert(static_cast<bool>(*this));
			return _ptr;
		}

		[[nodiscard]]
		constexpr auto get() const noexcept -> element_type*
		{
			return _ptr;
		}

		constexpr void reset() noexcept
		{
			try_detach();
		}

		template <class U>
		constexpr void reset(U* a_ptr) noexcept
			requires(std::is_convertible_v<U*, element_type*>)
		{
			if (_ptr == a_ptr) {
				return;
			}

			try_detach();
			_ptr = static_cast<element_type*>(a_ptr);
			try_attach();
		}

		constexpr void swap(NiPointer& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(_ptr, a_other._ptr);
		}

	protected:
		template <class>
		friend class NiPointer;

		constexpr void try_attach() noexcept
		{
			if (!_ptr) {
				return;
			}

			try {
				_ptr->IncRefCount();
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
				_ptr->DecRefCount();
				_ptr = nullptr;
			}
			catch (...) {
				REX::Fail("Failed to decrement ref count."sv);
			}
		}

		// members
		element_type* _ptr{nullptr}; // 0x00
	};

	static_assert(sizeof(NiPointer<void*>) == 0x08);

	template <class T>
	NiPointer(T*) -> NiPointer<T>;

	template <class T>
	[[nodiscard]]
	constexpr auto operator==(const NiPointer<T>& a_lhs, const NiPointer<T>& a_rhs) noexcept -> bool
	{
		return a_lhs.get() == a_rhs.get();
	}

	template <class T>
	[[nodiscard]]
	constexpr auto operator==(const NiPointer<T>& a_lhs, std::nullptr_t) noexcept -> bool
	{
		return a_lhs == static_cast<const T*>(nullptr);
	}

	template <class T>
	[[nodiscard]]
	constexpr auto operator==(std::nullptr_t, const NiPointer<T>& a_rhs) noexcept -> bool
	{
		return static_cast<const T*>(nullptr) == a_rhs;
	}

	template <class T>
	[[nodiscard]]
	constexpr auto operator==(const NiPointer<T>& a_lhs, const T* a_rhs) noexcept -> bool
	{
		return a_lhs.get() == a_rhs;
	}

	template <class T>
	[[nodiscard]]
	constexpr auto operator==(const T* a_lhs, const NiPointer<T>& a_rhs) noexcept -> bool
	{
		return a_lhs == a_rhs.get();
	}

	template <class T>
	[[nodiscard]]
	constexpr auto operator<=>(const NiPointer<T>& a_lhs, const NiPointer<T>& a_rhs) noexcept -> auto
	{
		return a_lhs.get() <=> a_rhs.get();
	}

	template <class T>
	[[nodiscard]]
	constexpr auto operator<=>(const NiPointer<T>& a_lhs, std::nullptr_t) noexcept -> auto
	{
		return a_lhs.get() <=> static_cast<const T*>(nullptr);
	}

	template <class T>
	[[nodiscard]]
	constexpr auto operator<=>(std::nullptr_t, const NiPointer<T>& a_rhs) noexcept -> auto
	{
		return static_cast<const T*>(nullptr) <=> a_rhs.get();
	}

	template <class T>
	[[nodiscard]]
	constexpr auto operator<=>(const NiPointer<T>& a_lhs, const T* a_rhs) noexcept -> auto
	{
		return a_lhs.get() <=> a_rhs;
	}

	template <class T>
	[[nodiscard]]
	constexpr auto operator<=>(const T* a_lhs, const NiPointer<T>& a_rhs) noexcept -> auto
	{
		return a_lhs <=> a_rhs.get();
	}

	template <class T, class... Args>
	[[nodiscard]]
	auto make_ni_shared(Args&&... a_args) -> NiPointer<T>
		requires(std::is_constructible_v<T, Args...>)
	{
		return NiPointer{new T(std::forward<Args>(a_args)...)};
	}

	template <class T1, class T2>
	[[nodiscard]]
	auto static_ni_pointer_cast(const NiPointer<T2>& a_ptr) noexcept -> NiPointer<T1>
		requires(std::is_convertible_v<T2*, T1*>)
	{
		return NiPointer<T1>{static_cast<T1*>(a_ptr.get())};
	}

	template <class T1, class T2>
	[[nodiscard]]
	auto dynamic_ni_pointer_cast(const NiPointer<T2>& a_ptr) noexcept -> NiPointer<T1>
		requires(REL::RTTI::valid_cast<T2*, T1*> && !NiImpl::valid_cast<T2*, T1*>)
	{
		return NiPointer<T1>{RE::DynamicCast<T1*>(a_ptr.get())};
	}

	template <class T1, class T2>
	[[nodiscard]]
	auto dynamic_ni_pointer_cast(const NiPointer<T2>& a_ptr) noexcept -> NiPointer<T1>
		requires(NiImpl::valid_cast<T2*, T1*>)
	{
		return NiPointer<T1>{RE::NiDynamicCast<T1*>(a_ptr.get())};
	}

	template <class T1, class T2>
	[[nodiscard]]
	auto const_ni_pointer_cast(const NiPointer<T2>& a_ptr) noexcept -> NiPointer<T1>
		requires(std::is_convertible_v<T2*, T1*>)
	{
		return NiPointer<T1>{const_cast<T1*>(a_ptr.get())};
	}

	template <class T1, class T2>
	[[nodiscard]]
	auto reinterpret_ni_pointer_cast(const NiPointer<T2>& a_ptr) noexcept -> NiPointer<T1>
	{
		return NiPointer<T1>{reinterpret_cast<T1*>(a_ptr.get())};
	}
}

namespace RE
{
	template <class T>
	struct BSCRC32<RE::NiPointer<T>>
	{
	public:
		[[nodiscard]]
		constexpr auto operator()(const RE::NiPointer<T>& a_key) const noexcept -> std::uint32_t
		{
			return RE::HashCRC32<const void*>(a_key.get());
		}
	};
}

namespace std
{
	template <class T>
	struct hash<RE::NiPointer<T>>
	{
	public:
		[[nodiscard]]
		auto operator()(const RE::NiPointer<T>& a_key) const noexcept -> std::size_t
		{
			return REX::Hash<const void*>(a_key.get());
		}
	};
}
