#pragma once

#include "RE/B/BSCRC32.hpp"

namespace RE
{
	template <class T>
	class BSTSmartPointerIntrusiveRefCount
	{
	public:
		static_assert(requires(const T* a_ptr) { a_ptr->IncRef(); });
		static_assert(requires(const T* a_ptr) { a_ptr->DecRef(); });
		static_assert(requires(const T* a_ptr) { delete a_ptr; });

		static void Acquire(const T* a_ptr) noexcept
		{
			a_ptr->IncRef();
		}

		static void Release(const T* a_ptr) noexcept
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
		static_assert(requires(const T* a_ptr) { delete a_ptr; });

		static void Acquire([[maybe_unused]] const T* a_ptr) noexcept
		{
			return;
		}

		static void Release(const T* a_ptr) noexcept
		{
			delete a_ptr;
		}
	};

	template <class T>
	class BSTSmartPointerGamebryoRefCount
	{
	public:
		static_assert(requires(const T* a_ptr) { a_ptr->IncRefCount(); });
		static_assert(requires(const T* a_ptr) { a_ptr->DecRefCount(); });

		static void Acquire(const T* a_ptr) noexcept
		{
			a_ptr->IncRefCount();
		}

		static void Release(const T* a_ptr) noexcept
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

		// NOLINTNEXTLINE(misc-explicit-constructor)
		constexpr BSTSmartPointer(std::nullptr_t) noexcept :
			_ptr(nullptr)
		{
		}

		template <class U>
		constexpr explicit BSTSmartPointer(U* a_rhs) noexcept
			requires(std::is_convertible_v<U*, element_type*>)
			:
			_ptr(static_cast<element_type*>(a_rhs))
		{
			try_attach();
		}

		template <class U>
		// NOLINTNEXTLINE(misc-explicit-constructor)
		constexpr BSTSmartPointer(const BSTSmartPointer<U>& a_rhs) noexcept
			requires(std::is_convertible_v<U*, element_type*>)
			:
			_ptr(static_cast<element_type*>(a_rhs._ptr))
		{
			try_attach();
		}

		template <class U>
		// NOLINTNEXTLINE(misc-explicit-constructor, cppcoreguidelines-rvalue-reference-param-not-moved)
		constexpr BSTSmartPointer(BSTSmartPointer<U>&& a_rhs) noexcept
			requires(std::is_convertible_v<U*, element_type*>)
			:
			_ptr(static_cast<element_type*>(std::exchange(a_rhs._ptr, nullptr)))
		{
		}

		constexpr BSTSmartPointer(const BSTSmartPointer& a_rhs) noexcept :
			_ptr(a_rhs._ptr)
		{
			try_attach();
		}

		constexpr BSTSmartPointer(BSTSmartPointer&& a_rhs) noexcept :
			_ptr(std::exchange(a_rhs._ptr, nullptr))
		{
		}

		constexpr auto operator=(std::nullptr_t) noexcept -> BSTSmartPointer&
		{
			try_detach();
			return *this;
		}

		template <class U>
		constexpr auto operator=(U* a_rhs) noexcept -> BSTSmartPointer&
			requires(std::is_convertible_v<U*, element_type*>)
		{
			try_detach();
			_ptr = static_cast<element_type*>(a_rhs);
			try_attach();
			return *this;
		}

		template <class U>
		constexpr auto operator=(const BSTSmartPointer<U>& a_rhs) noexcept -> BSTSmartPointer&
			requires(std::is_convertible_v<U*, element_type*>)
		{
			try_detach();
			_ptr = static_cast<element_type*>(a_rhs._ptr);
			try_attach();
			return *this;
		}

		template <class U>
		// NOLINTNEXTLINE(cppcoreguidelines-rvalue-reference-param-not-moved)
		constexpr auto operator=(BSTSmartPointer<U>&& a_rhs) noexcept -> BSTSmartPointer&
			requires(std::is_convertible_v<U*, element_type*>)
		{
			try_detach();
			_ptr = static_cast<element_type*>(std::exchange(a_rhs._ptr, nullptr));
			return *this;
		}

		constexpr auto operator=(const BSTSmartPointer& a_rhs) noexcept -> BSTSmartPointer&
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			try_detach();
			_ptr = a_rhs._ptr;
			try_attach();
			return *this;
		}

		constexpr auto operator=(BSTSmartPointer&& a_rhs) noexcept -> BSTSmartPointer&
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
				REX::Fail("Failed to acquire object."sv);
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
				REX::Fail("Failed to release object."sv);
			}
		}

		// members
		element_type* _ptr{nullptr}; // 0x00
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
	[[nodiscard]]
	constexpr auto operator==(const BSTSmartPointer<T, R>& a_lhs, const BSTSmartPointer<T, R>& a_rhs) noexcept -> bool
	{
		return a_lhs.get() == a_rhs.get();
	}

	template <class T, template <class> class R>
	[[nodiscard]]
	constexpr auto operator==(const BSTSmartPointer<T, R>& a_lhs, std::nullptr_t) noexcept -> bool
	{
		return a_lhs == static_cast<const T*>(nullptr);
	}

	template <class T, template <class> class R>
	[[nodiscard]]
	constexpr auto operator==(std::nullptr_t, const BSTSmartPointer<T, R>& a_rhs) noexcept -> bool
	{
		return static_cast<const T*>(nullptr) == a_rhs;
	}

	template <class T, template <class> class R>
	[[nodiscard]]
	constexpr auto operator==(const BSTSmartPointer<T, R>& a_lhs, const T* a_rhs) noexcept -> bool
	{
		return a_lhs.get() == a_rhs;
	}

	template <class T, template <class> class R>
	[[nodiscard]]
	constexpr auto operator==(const T* a_lhs, const BSTSmartPointer<T, R>& a_rhs) noexcept -> bool
	{
		return a_lhs == a_rhs.get();
	}

	template <class T, template <class> class R>
	[[nodiscard]]
	constexpr auto operator<=>(const BSTSmartPointer<T, R>& a_lhs, const BSTSmartPointer<T, R>& a_rhs) noexcept -> auto
	{
		return a_lhs.get() <=> a_rhs.get();
	}

	template <class T, template <class> class R>
	[[nodiscard]]
	constexpr auto operator<=>(const BSTSmartPointer<T, R>& a_lhs, std::nullptr_t) noexcept -> auto
	{
		return a_lhs.get() <=> static_cast<const T*>(nullptr);
	}

	template <class T, template <class> class R>
	[[nodiscard]]
	constexpr auto operator<=>(std::nullptr_t, const BSTSmartPointer<T, R>& a_rhs) noexcept -> auto
	{
		return static_cast<const T*>(nullptr) <=> a_rhs.get();
	}

	template <class T, template <class> class R>
	[[nodiscard]]
	constexpr auto operator<=>(const BSTSmartPointer<T, R>& a_lhs, const T* a_rhs) noexcept -> auto
	{
		return a_lhs.get() <=> a_rhs;
	}

	template <class T, template <class> class R>
	[[nodiscard]]
	constexpr auto operator<=>(const T* a_lhs, const BSTSmartPointer<T, R>& a_rhs) noexcept -> auto
	{
		return a_lhs <=> a_rhs.get();
	}

	template <class T, class... Args>
	[[nodiscard]]
	auto make_shared(Args&&... a_args) -> BSTSmartPointer<T>
		requires(std::is_constructible_v<T, Args...>)
	{
		return BSTSmartPointer{new T(std::forward<Args>(a_args)...)};
	}

	template <class T1, class T2, template <class> class R>
	[[nodiscard]]
	auto static_pointer_cast(const BSTSmartPointer<T2, R>& a_ptr) noexcept -> BSTSmartPointer<T1, R>
		requires(std::is_convertible_v<T2*, T1*>)
	{
		return BSTSmartPointer<T1, R>{static_cast<T1*>(a_ptr.get())};
	}

	template <class T1, class T2, template <class> class R>
	[[nodiscard]]
	auto dynamic_pointer_cast(const BSTSmartPointer<T2, R>& a_ptr) noexcept -> BSTSmartPointer<T1, R>
		requires(REL::RTTI::valid_cast<T2*, T1*>)
	{
		return BSTSmartPointer<T1, R>{RE::DynamicCast<T1*>(a_ptr.get())};
	}

	template <class T1, class T2, template <class> class R>
	[[nodiscard]]
	auto const_pointer_cast(const BSTSmartPointer<T2, R>& a_ptr) noexcept -> BSTSmartPointer<T1, R>
		requires(std::is_convertible_v<T2*, T1*>)
	{
		return BSTSmartPointer<T1, R>{const_cast<T1*>(a_ptr.get())};
	}

	template <class T1, class T2, template <class> class R>
	[[nodiscard]]
	auto reinterpret_pointer_cast(const BSTSmartPointer<T2, R>& a_ptr) noexcept -> BSTSmartPointer<T1, R>
	{
		return BSTSmartPointer<T1, R>{reinterpret_cast<T1*>(a_ptr.get())};
	}
}

namespace RE
{
	template <class T, template <class> class R>
	struct BSCRC32<RE::BSTSmartPointer<T, R>>
	{
	public:
		[[nodiscard]]
		constexpr auto operator()(const RE::BSTSmartPointer<T, R>& a_key) const noexcept -> std::uint32_t
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
		[[nodiscard]]
		auto operator()(const RE::BSTSmartPointer<T, R>& a_key) const noexcept -> std::size_t
		{
			return REX::Hash<const void*>(a_key.get());
		}
	};
}
