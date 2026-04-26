#pragma once

namespace Scaleform
{
	template <class T>
	class Ptr
	{
	public:
		using element_type = T;

		constexpr Ptr() noexcept = default;

		constexpr ~Ptr() noexcept
		{
			reset();
		}

		constexpr Ptr(std::nullptr_t) noexcept
			: _ptr(nullptr)
		{
		}

		template <class U>
		constexpr explicit Ptr(U* a_rhs) noexcept
			requires(std::is_convertible_v<U*, element_type*>)
			: _ptr(a_rhs)
		{
			try_attach();
		}

		template <class U>
		constexpr Ptr(const Ptr<U>& a_rhs) noexcept
			requires(std::is_convertible_v<U*, element_type*>)
			: _ptr(static_cast<element_type*>(a_rhs._ptr))
		{
			try_attach();
		}

		template <class U>
		constexpr Ptr(Ptr<U>&& a_rhs) noexcept // NOLINT(cppcoreguidelines-rvalue-reference-param-not-moved)
			requires(std::is_convertible_v<U*, element_type*>)
			: _ptr(static_cast<element_type*>(std::exchange(a_rhs._ptr, nullptr)))
		{
		}

		constexpr Ptr(const Ptr& a_rhs) noexcept
			: _ptr(a_rhs._ptr)
		{
			try_attach();
		}

		constexpr Ptr(Ptr&& a_rhs) noexcept
			: _ptr(std::exchange(a_rhs._ptr, nullptr))
		{
		}

		constexpr Ptr& operator=(std::nullptr_t) noexcept
		{
			try_detach();
			return *this;
		}

		template <class U>
		constexpr Ptr& operator=(U* a_rhs) noexcept
			requires(std::is_convertible_v<U*, element_type*>)
		{
			try_detach();
			_ptr = static_cast<element_type*>(a_rhs);
			try_attach();
			return *this;
		}

		template <class U>
		constexpr Ptr& operator=(const Ptr<U>& a_rhs) noexcept
			requires(std::is_convertible_v<U*, element_type*>)
		{
			try_detach();
			_ptr = static_cast<element_type*>(a_rhs._ptr);
			try_attach();
			return *this;
		}

		template <class U>
		constexpr Ptr& operator=(Ptr<U>&& a_rhs) noexcept // NOLINT(cppcoreguidelines-rvalue-reference-param-not-moved)
			requires(std::is_convertible_v<U*, element_type*>)
		{
			try_detach();
			_ptr = static_cast<element_type*>(std::exchange(a_rhs._ptr, nullptr));
			return *this;
		}

		constexpr Ptr& operator=(const Ptr& a_rhs) noexcept
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			try_detach();
			_ptr = a_rhs._ptr;
			try_attach();
			return *this;
		}

		constexpr Ptr& operator=(Ptr&& a_rhs) noexcept
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			try_detach();
			_ptr = std::exchange(a_rhs._ptr, nullptr);
			return *this;
		}

		[[nodiscard]] constexpr explicit operator bool() const noexcept
		{
			return _ptr != nullptr;
		}

		[[nodiscard]] constexpr element_type& operator*() const noexcept
		{
			REX::Assert(static_cast<bool>(*this));
			return *_ptr;
		}

		[[nodiscard]] constexpr element_type* operator->() const noexcept
		{
			REX::Assert(static_cast<bool>(*this));
			return _ptr;
		}

		[[nodiscard]] constexpr element_type* get() const noexcept
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

		constexpr void swap(Ptr& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(_ptr, a_other._ptr);
		}

	protected:
		template <class>
		friend class Ptr;

		constexpr void try_attach() noexcept
		{
			if (!_ptr) {
				return;
			}

			try {
				_ptr->AddRef();
			}
			catch (...) {
				REX::QuickFail("Failed to add reference to Scaleform object."sv);
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
				REX::QuickFail("Failed to release reference to Scaleform object."sv);
			}
		}

		// members
		element_type* _ptr{ nullptr }; // 00
	};
	static_assert(sizeof(Ptr<void*>) == sizeof(std::uintptr_t));

	template <class T>
	Ptr(T*) -> Ptr<T>;

	template <class T>
	[[nodiscard]] constexpr bool operator==(const Ptr<T>& a_lhs, const Ptr<T>& a_rhs) noexcept
	{
		return a_lhs.get() == a_rhs.get();
	}

	template <class T>
	[[nodiscard]] constexpr bool operator==(const Ptr<T>& a_lhs, std::nullptr_t) noexcept
	{
		return a_lhs == static_cast<const T*>(nullptr);
	}

	template <class T>
	[[nodiscard]] constexpr bool operator==(std::nullptr_t, const Ptr<T>& a_rhs) noexcept
	{
		return static_cast<const T*>(nullptr) == a_rhs;
	}

	template <class T>
	[[nodiscard]] constexpr bool operator==(const Ptr<T>& a_lhs, const T* a_rhs) noexcept
	{
		return a_lhs.get() == a_rhs;
	}

	template <class T>
	[[nodiscard]] constexpr bool operator==(const T* a_lhs, const Ptr<T>& a_rhs) noexcept
	{
		return a_lhs == a_rhs.get();
	}

	template <class T>
	[[nodiscard]] constexpr auto operator<=>(const Ptr<T>& a_lhs, const Ptr<T>& a_rhs) noexcept
	{
		return a_lhs.get() <=> a_rhs.get();
	}

	template <class T>
	[[nodiscard]] constexpr auto operator<=>(const Ptr<T>& a_lhs, std::nullptr_t) noexcept
	{
		return a_lhs.get() <=> static_cast<const T*>(nullptr);
	}

	template <class T>
	[[nodiscard]] constexpr auto operator<=>(std::nullptr_t, const Ptr<T>& a_rhs) noexcept
	{
		return static_cast<const T*>(nullptr) <=> a_rhs.get();
	}

	template <class T>
	[[nodiscard]] constexpr auto operator<=>(const Ptr<T>& a_lhs, const T* a_rhs) noexcept
	{
		return a_lhs.get() <=> a_rhs;
	}

	template <class T>
	[[nodiscard]] constexpr auto operator<=>(const T* a_lhs, const Ptr<T>& a_rhs) noexcept
	{
		return a_lhs <=> a_rhs.get();
	}

	template <class T>
	constexpr void swap(Ptr<T>& a_lhs, Ptr<T>& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}

	template <class T, class... Args>
	[[nodiscard]] Ptr<T> make_shared(Args&&... a_args)
		requires(std::is_constructible_v<T, Args && ...>)
	{
		auto ptr = Ptr<T>{ new T(std::forward<Args>(a_args)...) };
		if (ptr) {
			ptr->Release(); // ensure lifetime ends with smart pointer
		}

		return ptr;
	}

	template <class T1, class T2>
	[[nodiscard]] Ptr<T1> static_pointer_cast(const Ptr<T2>& a_ptr) noexcept
		requires(std::is_convertible_v<T2*, T1*>)
	{
		return Ptr<T1>{ static_cast<T1*>(a_ptr.get()) };
	}

	template <class T1, class T2>
	[[nodiscard]] Ptr<T1> dynamic_pointer_cast(const Ptr<T2>& a_ptr) noexcept
		requires(REL::RTTI::valid_cast<T2*, T1*>)
	{
		return Ptr<T1>{ DynamicCast<T1*>(a_ptr.get()) };
	}

	template <class T1, class T2>
	[[nodiscard]] Ptr<T1> const_pointer_cast(const Ptr<T2>& a_ptr) noexcept
		requires(std::is_convertible_v<T2*, T1*>)
	{
		return Ptr<T1>{ const_cast<T1*>(a_ptr.get()) };
	}

	template <class T1, class T2>
	[[nodiscard]] Ptr<T1> reinterpret_pointer_cast(const Ptr<T2>& a_ptr) noexcept
	{
		return Ptr<T1>{ reinterpret_cast<T1*>(a_ptr.get()) };
	}
}

namespace std
{
	template <class T>
	struct hash<Scaleform::Ptr<T>>
	{
	public:
		[[nodiscard]] std::size_t operator()(const Scaleform::Ptr<T>& a_key) const noexcept
		{
			return REX::Hash<const void*>(a_key.get());
		}
	};
}
