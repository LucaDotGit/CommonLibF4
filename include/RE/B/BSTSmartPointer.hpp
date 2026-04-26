#pragma once

#include "RE/B/BSCRC32.hpp"

namespace RE
{
	template <class T>
	class BSTSmartPointerIntrusiveRefCount
	{
	public:
		static_assert(requires(T* a_ptr) { a_ptr->IncRef(); });
		static_assert(requires(T* a_ptr) { a_ptr->DecRef(); });
		static_assert(requires(T* a_ptr) { delete a_ptr; });

		static void Acquire(T* a_ptr) noexcept
		{
			a_ptr->IncRef();
		}

		static void Release(T* a_ptr) noexcept
		{
			if (a_ptr->DecRef() == 0) {
				delete a_ptr;
			}
		}
	};

	template <class T>
	class BSTSmartPointerAutoPtr
	{
	public:
		static_assert(requires(T* a_ptr) { delete a_ptr; });

		static void Acquire([[maybe_unused]] T* a_ptr) noexcept
		{
			return;
		}

		static void Release(T* a_ptr) noexcept
		{
			delete a_ptr;
		}
	};

	template <class T>
	class BSTSmartPointerGamebryoRefCount
	{
	public:
		static_assert(requires(T* a_ptr) { a_ptr->IncRefCount(); });
		static_assert(requires(T* a_ptr) { a_ptr->DecRefCount(); });

		static void Acquire(T* a_ptr) noexcept
		{
			a_ptr->IncRefCount();
		}

		static void Release(T* a_ptr) noexcept
		{
			a_ptr->DecRefCount();
		}
	};

	template <class T, template <class> class RefManager = BSTSmartPointerIntrusiveRefCount>
	class BSTSmartPointer
	{
	public:
		using element_type = T;
		using reference_manager = RefManager<T>;

		constexpr BSTSmartPointer() noexcept = default;

		constexpr ~BSTSmartPointer() noexcept
		{
			reset();
		}

		constexpr BSTSmartPointer(std::nullptr_t) noexcept
			: _ptr(nullptr)
		{
		}

		template <class U>
		constexpr explicit BSTSmartPointer(U* a_rhs) noexcept
			requires(std::is_convertible_v<U*, element_type*>)
			: _ptr(static_cast<element_type*>(a_rhs))
		{
			try_attach();
		}

		template <class U>
		constexpr BSTSmartPointer(const BSTSmartPointer<U>& a_rhs) noexcept
			requires(std::is_convertible_v<U*, element_type*>)
			: _ptr(static_cast<element_type*>(a_rhs._ptr))
		{
			try_attach();
		}

		template <class U>
		constexpr BSTSmartPointer(BSTSmartPointer<U>&& a_rhs) noexcept // NOLINT(cppcoreguidelines-rvalue-reference-param-not-moved)
			requires(std::is_convertible_v<U*, element_type*>)
			: _ptr(static_cast<element_type*>(std::exchange(a_rhs._ptr, nullptr)))
		{
		}

		constexpr BSTSmartPointer(const BSTSmartPointer& a_rhs) noexcept
			: _ptr(a_rhs._ptr)
		{
			try_attach();
		}

		constexpr BSTSmartPointer(BSTSmartPointer&& a_rhs) noexcept
			: _ptr(std::exchange(a_rhs._ptr, nullptr))
		{
		}

		constexpr BSTSmartPointer& operator=(std::nullptr_t) noexcept
		{
			try_detach();
			return *this;
		}

		template <class U>
		constexpr BSTSmartPointer& operator=(U* a_rhs) noexcept
			requires(std::is_convertible_v<U*, element_type*>)
		{
			try_detach();
			_ptr = static_cast<element_type*>(a_rhs);
			try_attach();
			return *this;
		}

		template <class U>
		constexpr BSTSmartPointer& operator=(const BSTSmartPointer<U>& a_rhs) noexcept
			requires(std::is_convertible_v<U*, element_type*>)
		{
			try_detach();
			_ptr = static_cast<element_type*>(a_rhs._ptr);
			try_attach();
			return *this;
		}

		template <class U>
		constexpr BSTSmartPointer& operator=(BSTSmartPointer<U>&& a_rhs) noexcept // NOLINT(cppcoreguidelines-rvalue-reference-param-not-moved)
			requires(std::is_convertible_v<U*, element_type*>)
		{
			try_detach();
			_ptr = static_cast<element_type*>(std::exchange(a_rhs._ptr, nullptr));
			return *this;
		}

		constexpr BSTSmartPointer& operator=(const BSTSmartPointer& a_rhs) noexcept
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			try_detach();
			_ptr = a_rhs._ptr;
			try_attach();
			return *this;
		}

		constexpr BSTSmartPointer& operator=(BSTSmartPointer&& a_rhs) noexcept
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

		constexpr void swap(BSTSmartPointer& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(_ptr, a_other._ptr);
		}

	protected:
		template <class, template <class> class>
		friend class BSTSmartPointer;

		constexpr void try_attach() noexcept
		{
			if (!_ptr) {
				return;
			}

			try {
				reference_manager::Acquire(_ptr);
			}
			catch (...) {
				REX::QuickFail("Failed to add reference to Bethesda object."sv);
			}
		}

		constexpr void try_detach() noexcept
		{
			if (!_ptr) {
				return;
			}

			try {
				reference_manager::Release(_ptr);
				_ptr = nullptr;
			}
			catch (...) {
				REX::QuickFail("Failed to release reference to Bethesda object."sv);
			}
		}

		// members
		element_type* _ptr{ nullptr }; // 00
	};
	static_assert(sizeof(BSTSmartPointer<void*>) == 0x08);

	template <class T>
	BSTSmartPointer(T*) -> BSTSmartPointer<T, BSTSmartPointerIntrusiveRefCount>;

	template <class T>
	using BSTAutoPointer = BSTSmartPointer<T, BSTSmartPointerAutoPtr>;
	static_assert(sizeof(BSTAutoPointer<void*>) == 0x08);

	template <class T>
	using BSTGamebryoPointer = BSTSmartPointer<T, BSTSmartPointerGamebryoRefCount>;
	static_assert(sizeof(BSTGamebryoPointer<void*>) == 0x08);

	template <class T, template <class> class R>
	[[nodiscard]] constexpr bool operator==(const BSTSmartPointer<T, R>& a_lhs, const BSTSmartPointer<T, R>& a_rhs) noexcept
	{
		return a_lhs.get() == a_rhs.get();
	}

	template <class T, template <class> class R>
	[[nodiscard]] constexpr bool operator==(const BSTSmartPointer<T, R>& a_lhs, std::nullptr_t) noexcept
	{
		return a_lhs == static_cast<const T*>(nullptr);
	}

	template <class T, template <class> class R>
	[[nodiscard]] constexpr bool operator==(std::nullptr_t, const BSTSmartPointer<T, R>& a_rhs) noexcept
	{
		return static_cast<const T*>(nullptr) == a_rhs;
	}

	template <class T, template <class> class R>
	[[nodiscard]] constexpr bool operator==(const BSTSmartPointer<T, R>& a_lhs, const T* a_rhs) noexcept
	{
		return a_lhs.get() == a_rhs;
	}

	template <class T, template <class> class R>
	[[nodiscard]] constexpr bool operator==(const T* a_lhs, const BSTSmartPointer<T, R>& a_rhs) noexcept
	{
		return a_lhs == a_rhs.get();
	}

	template <class T, template <class> class R>
	[[nodiscard]] constexpr auto operator<=>(const BSTSmartPointer<T, R>& a_lhs, const BSTSmartPointer<T, R>& a_rhs) noexcept
	{
		return a_lhs.get() <=> a_rhs.get();
	}

	template <class T, template <class> class R>
	[[nodiscard]] constexpr auto operator<=>(const BSTSmartPointer<T, R>& a_lhs, std::nullptr_t) noexcept
	{
		return a_lhs.get() <=> static_cast<const T*>(nullptr);
	}

	template <class T, template <class> class R>
	[[nodiscard]] constexpr auto operator<=>(std::nullptr_t, const BSTSmartPointer<T, R>& a_rhs) noexcept
	{
		return static_cast<const T*>(nullptr) <=> a_rhs.get();
	}

	template <class T, template <class> class R>
	[[nodiscard]] constexpr auto operator<=>(const BSTSmartPointer<T, R>& a_lhs, const T* a_rhs) noexcept
	{
		return a_lhs.get() <=> a_rhs;
	}

	template <class T, template <class> class R>
	[[nodiscard]] constexpr auto operator<=>(const T* a_lhs, const BSTSmartPointer<T, R>& a_rhs) noexcept
	{
		return a_lhs <=> a_rhs.get();
	}

	template <class T, template <class> class R>
	constexpr void swap(BSTSmartPointer<T, R>& a_lhs, BSTSmartPointer<T, R>& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}

	template <class T, class... Args>
	[[nodiscard]] BSTSmartPointer<T> make_shared(Args&&... a_args)
		requires(std::is_constructible_v<T, Args...>)
	{
		return BSTSmartPointer{ new T(std::forward<Args>(a_args)...) };
	}

	template <class T1, class T2, template <class> class R>
	[[nodiscard]] BSTSmartPointer<T1, R> static_pointer_cast(const BSTSmartPointer<T2, R>& a_ptr) noexcept
		requires(std::is_convertible_v<T2*, T1*>)
	{
		return BSTSmartPointer<T1, R>{ static_cast<T1*>(a_ptr.get()) };
	}

	template <class T1, class T2, template <class> class R>
	[[nodiscard]] BSTSmartPointer<T1, R> dynamic_pointer_cast(const BSTSmartPointer<T2, R>& a_ptr) noexcept
		requires(REL::RTTI::valid_cast<T2*, T1*>)
	{
		return BSTSmartPointer<T1, R>{ DynamicCast<T1*>(a_ptr.get()) };
	}

	template <class T1, class T2, template <class> class R>
	[[nodiscard]] BSTSmartPointer<T1, R> const_pointer_cast(const BSTSmartPointer<T2, R>& a_ptr) noexcept
		requires(std::is_convertible_v<T2*, T1*>)
	{
		return BSTSmartPointer<T1, R>{ const_cast<T1*>(a_ptr.get()) };
	}

	template <class T1, class T2, template <class> class R>
	[[nodiscard]] BSTSmartPointer<T1, R> reinterpret_pointer_cast(const BSTSmartPointer<T2, R>& a_ptr) noexcept
	{
		return BSTSmartPointer<T1, R>{ reinterpret_cast<T1*>(a_ptr.get()) };
	}
}

namespace RE
{
	template <class T, template <class> class R>
	struct BSCRC32<RE::BSTSmartPointer<T, R>>
	{
	public:
		[[nodiscard]] constexpr std::uint32_t operator()(const RE::BSTSmartPointer<T, R>& a_key) const noexcept
		{
			return RE::HashCRC32<const void*>(a_key.get());
		}
	};
}

namespace std
{
	template <class T, template <class> class R>
	struct hash<RE::BSTSmartPointer<T, R>>
	{
	public:
		[[nodiscard]] std::size_t operator()(const RE::BSTSmartPointer<T, R>& a_key) const noexcept
		{
			return REX::Hash<const void*>(a_key.get());
		}
	};
}
