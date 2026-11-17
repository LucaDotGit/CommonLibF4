#pragma once

namespace RE
{
	template <class T>
	class hkRefPtr
	{
	public:
		using element_type = T;

		constexpr hkRefPtr() noexcept = default;

		constexpr ~hkRefPtr() noexcept
		{
			reset();
		}

		// NOLINTNEXTLINE(misc-explicit-constructor)
		constexpr hkRefPtr(std::nullptr_t) noexcept :
			_ptr(nullptr)
		{
		}

		template <class U>
		constexpr explicit hkRefPtr(U* a_rhs) noexcept
			requires(std::is_convertible_v<U*, element_type*>)
			:
			_ptr(static_cast<element_type*>(a_rhs))
		{
			try_attach();
		}

		template <class U>
		// NOLINTNEXTLINE(misc-explicit-constructor)
		constexpr hkRefPtr(const hkRefPtr<U>& a_rhs) noexcept
			requires(std::is_convertible_v<U*, element_type*>)
			:
			_ptr(static_cast<element_type*>(a_rhs._ptr))
		{
			try_attach();
		}

		template <class U>
		// NOLINTNEXTLINE(misc-explicit-constructor, cppcoreguidelines-rvalue-reference-param-not-moved)
		constexpr hkRefPtr(hkRefPtr<U>&& a_rhs) noexcept
			requires(std::is_convertible_v<U*, element_type*>)
			:
			_ptr(static_cast<element_type*>(std::exchange(a_rhs._ptr, nullptr)))
		{
		}

		constexpr hkRefPtr(const hkRefPtr& a_rhs) noexcept :
			_ptr(a_rhs._ptr)
		{
			try_attach();
		}

		constexpr hkRefPtr(hkRefPtr&& a_rhs) noexcept :
			_ptr(std::exchange(a_rhs._ptr, nullptr))
		{
		}

		constexpr auto operator=(std::nullptr_t) noexcept -> hkRefPtr&
		{
			try_detach();
			return *this;
		}

		template <class U>
		constexpr auto operator=(U* a_rhs) noexcept -> hkRefPtr&
			requires(std::is_convertible_v<U*, element_type*>)
		{
			try_detach();
			_ptr = static_cast<element_type*>(a_rhs);
			try_attach();
			return *this;
		}

		template <class U>
		constexpr auto operator=(const hkRefPtr<U>& a_rhs) noexcept -> hkRefPtr&
			requires(std::is_convertible_v<U*, element_type*>)
		{
			try_detach();
			_ptr = static_cast<element_type*>(a_rhs._ptr);
			try_attach();
			return *this;
		}

		template <class U>
		// NOLINTNEXTLINE(cppcoreguidelines-rvalue-reference-param-not-moved)
		constexpr auto operator=(hkRefPtr<U>&& a_rhs) noexcept -> hkRefPtr&
			requires(std::is_convertible_v<U*, element_type*>)
		{
			try_detach();
			_ptr = static_cast<element_type*>(std::exchange(a_rhs._ptr, nullptr));
			return *this;
		}

		constexpr auto operator=(const hkRefPtr& a_rhs) noexcept -> hkRefPtr&
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			try_detach();
			_ptr = std::exchange(a_rhs._ptr, nullptr);
			try_attach();
			return *this;
		}

		constexpr auto operator=(hkRefPtr&& a_rhs) noexcept -> hkRefPtr&
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
			REX::Assert(static_cast<bool>(*this));
			return *_ptr;
		}

		[[nodiscard]]
		constexpr auto operator->() const noexcept -> T*
		{
			REX::Assert(static_cast<bool>(*this));
			return _ptr;
		}

		[[nodiscard]]
		constexpr auto get() const noexcept -> T*
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

		constexpr void swap(hkRefPtr& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(_ptr, a_other._ptr);
		}

	protected:
		template <class>
		friend class hkRefPtr;

		constexpr void try_attach() noexcept
		{
			if (!_ptr) {
				return;
			}

			try {
				_ptr->AddReference();
			}
			catch (...) {
				REX::Fail("Failed to acquire object."sv);
			}
		}

		constexpr void try_detach() noexcept
		{
			if (!_ptr) {
				return;
			}

			try {
				_ptr->RemoveReference();
				_ptr = nullptr;
			}
			catch (...) {
				REX::Fail("Failed to release object."sv);
			}
		}

		// members
		T* _ptr{nullptr}; // 0x00
	};

	static_assert(sizeof(hkRefPtr<void*>) == 0x08);

	template <class T>
	hkRefPtr(T*) -> hkRefPtr<T>;

	template <class T>
	[[nodiscard]]
	constexpr auto operator==(const hkRefPtr<T>& a_lhs, const hkRefPtr<T>& a_rhs) noexcept -> bool
	{
		return a_lhs.get() == a_rhs.get();
	}

	template <class T>
	[[nodiscard]]
	constexpr auto operator==(const hkRefPtr<T>& a_lhs, std::nullptr_t) noexcept -> bool
	{
		return a_lhs.get() == static_cast<const T*>(nullptr);
	}

	template <class T>
	[[nodiscard]]
	constexpr auto operator==(std::nullptr_t, const hkRefPtr<T>& a_rhs) noexcept -> bool
	{
		return static_cast<const T*>(nullptr) == a_rhs.get();
	}

	template <class T>
	[[nodiscard]]
	constexpr auto operator==(const hkRefPtr<T>& a_lhs, const T* a_rhs) noexcept -> bool
	{
		return a_lhs.get() == a_rhs;
	}

	template <class T>
	[[nodiscard]]
	constexpr auto operator==(const T* a_lhs, const hkRefPtr<T>& a_rhs) noexcept -> bool
	{
		return a_lhs == a_rhs.get();
	}

	template <class T>
	[[nodiscard]]
	constexpr auto operator<=>(const hkRefPtr<T>& a_lhs, const hkRefPtr<T>& a_rhs) noexcept -> auto
	{
		return a_lhs.get() <=> a_rhs.get();
	}

	template <class T>
	[[nodiscard]]
	constexpr auto operator<=>(const hkRefPtr<T>& a_lhs, std::nullptr_t) noexcept -> auto
	{
		return a_lhs.get() <=> static_cast<const T*>(nullptr);
	}

	template <class T>
	[[nodiscard]]
	constexpr auto operator<=>(std::nullptr_t, const hkRefPtr<T>& a_rhs) noexcept -> auto
	{
		return static_cast<const T*>(nullptr) <=> a_rhs.get();
	}

	template <class T>
	[[nodiscard]]
	constexpr auto operator<=>(const hkRefPtr<T>& a_lhs, const T* a_rhs) noexcept -> auto
	{
		return a_lhs.get() <=> a_rhs;
	}

	template <class T>
	[[nodiscard]]
	constexpr auto operator<=>(const T* a_lhs, const hkRefPtr<T>& a_rhs) noexcept -> auto
	{
		return a_lhs <=> a_rhs.get();
	}

	template <class T, class... Args>
	[[nodiscard]]
	constexpr auto make_hk_shared(Args&&... a_args) -> hkRefPtr<T>
		requires(std::is_constructible_v<T, Args&&...>)
	{
		return hkRefPtr<T>{new T(std::forward<Args>(a_args)...)};
	}

	template <class T1, class T2>
	[[nodiscard]]
	constexpr auto static_hk_pointer_cast(const hkRefPtr<T2>& a_ptr) noexcept -> hkRefPtr<T1>
		requires(std::is_convertible_v<T2*, T1*>)
	{
		return hkRefPtr<T1>{static_cast<T1*>(a_ptr.get())};
	}

	template <class T1, class T2>
	[[nodiscard]]
	constexpr auto dynamic_hk_pointer_cast(const hkRefPtr<T2>& a_ptr) noexcept -> hkRefPtr<T1>
		requires(REL::RTTI::valid_cast<T2*, T1*>)
	{
		return hkRefPtr<T1>{RE::DynamicCast<T1*>(a_ptr.get())};
	}

	template <class T1, class T2>
	[[nodiscard]]
	constexpr auto const_hk_pointer_cast(const hkRefPtr<T2>& a_ptr) noexcept -> hkRefPtr<T1>
		requires(std::is_convertible_v<T2*, T1*>)
	{
		return hkRefPtr<T1>{const_cast<T1*>(a_ptr.get())};
	}

	template <class T1, class T2>
	[[nodiscard]]
	constexpr auto reinterpret_hk_pointer_cast(const hkRefPtr<T2>& a_ptr) noexcept -> hkRefPtr<T1>
	{
		return hkRefPtr<T1>{reinterpret_cast<T1*>(a_ptr.get())};
	}
}

namespace std
{
	template <class T>
	struct hash<RE::hkRefPtr<T>>
	{
	public:
		[[nodiscard]]
		auto operator()(const RE::hkRefPtr<T>& a_key) const noexcept -> std::size_t
		{
			return REX::Hash<const void*>(a_key.get());
		}
	};
}
