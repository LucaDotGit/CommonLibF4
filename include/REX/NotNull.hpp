#pragma once

#include "REX/Concepts.hpp"
#include "REX/Contract.hpp"
#include "REX/Hash.hpp"

namespace REX::Impl
{
	inline constexpr auto BASIC_NOT_NULL_ERROR_MESSAGE = "`REX::NotNull` pointer is null."sv;
}

namespace REX
{
	template <class T>
	class NotNull final
	{
	public:
		using value_type = T;

		static_assert(REX::equality_comparable_with<value_type, std::nullptr_t>,
			"`REX::NotNull` requires an equality comparable type to `nullptr`.");

		constexpr NotNull() = delete;

		constexpr ~NotNull() //
			noexcept(std::is_nothrow_destructible_v<value_type>)
			requires(std::is_destructible_v<value_type>)
		= default;

		constexpr NotNull(std::nullptr_t) = delete;

		template <class U>
		constexpr NotNull(const U& a_ptr, std::source_location a_location = std::source_location::current()) //
			noexcept(std::is_nothrow_convertible_v<U, value_type> &&
					 std::is_nothrow_copy_constructible_v<value_type>)
			requires(std::is_convertible_v<U, value_type> &&
					 std::is_copy_constructible_v<value_type>)
			: _ptr(static_cast<value_type>(a_ptr))
		{
			REX::Ensure(_ptr != nullptr, Impl::BASIC_NOT_NULL_ERROR_MESSAGE, a_location);
		}

		template <class U>
		constexpr NotNull(U&& a_ptr, std::source_location a_location = std::source_location::current()) //
			noexcept(std::is_nothrow_convertible_v<U, value_type> &&
					 std::is_nothrow_move_constructible_v<value_type>)
			requires(std::is_convertible_v<U, value_type> &&
					 std::is_move_constructible_v<value_type>)
			: _ptr(static_cast<value_type>(std::forward<U>(a_ptr)))
		{
			REX::Ensure(_ptr != nullptr, Impl::BASIC_NOT_NULL_ERROR_MESSAGE, a_location);
		}

		template <class U>
		constexpr NotNull(const NotNull<U>& a_rhs) //
			noexcept(std::is_nothrow_convertible_v<U, value_type> &&
					 std::is_nothrow_copy_constructible_v<value_type>)
			requires(std::is_convertible_v<U, value_type> &&
					 std::is_copy_constructible_v<value_type>)
			: _ptr(static_cast<value_type>(a_rhs._ptr))
		{
			REX::Assume(_ptr != nullptr, Impl::BASIC_NOT_NULL_ERROR_MESSAGE);
		}

		template <class U>
		constexpr NotNull(NotNull<U>&& a_rhs) // NOLINT(cppcoreguidelines-rvalue-reference-param-not-moved)
			noexcept(std::is_nothrow_convertible_v<U, value_type> &&
					 std::is_nothrow_move_constructible_v<value_type>)
			requires(std::is_convertible_v<U, value_type> &&
					 std::is_move_constructible_v<value_type>)
			: _ptr(static_cast<value_type>(std::move(a_rhs._ptr)))
		{
			REX::Assume(_ptr != nullptr, Impl::BASIC_NOT_NULL_ERROR_MESSAGE);
		}

		constexpr NotNull(const NotNull&) //
			noexcept(std::is_nothrow_copy_constructible_v<value_type>)
			requires(std::is_copy_constructible_v<value_type>)
		= default;

		constexpr NotNull(NotNull&&) //
			noexcept(std::is_nothrow_move_constructible_v<value_type>)
			requires(std::is_move_constructible_v<value_type>)
		= default;

		constexpr NotNull& operator=(std::nullptr_t) = delete;

		template <class U>
		constexpr NotNull& operator=(const NotNull<U>& a_rhs) //
			noexcept(std::is_nothrow_convertible_v<U, value_type> &&
					 std::is_nothrow_copy_assignable_v<value_type>)
			requires(std::is_convertible_v<U, value_type> &&
					 std::is_copy_assignable_v<value_type>)
		{
			_ptr = static_cast<value_type>(a_rhs._ptr);
			REX::Assume(_ptr != nullptr, Impl::BASIC_NOT_NULL_ERROR_MESSAGE);

			return *this;
		}

		template <class U>
		constexpr NotNull& operator=(NotNull<U>&& a_rhs) // NOLINT(cppcoreguidelines-rvalue-reference-param-not-moved)
			noexcept(std::is_nothrow_convertible_v<U, value_type> &&
					 std::is_nothrow_move_assignable_v<value_type>)
			requires(std::is_convertible_v<U, value_type> &&
					 std::is_move_assignable_v<value_type>)
		{
			_ptr = static_cast<value_type>(std::move(a_rhs._ptr));
			REX::Assume(_ptr != nullptr, Impl::BASIC_NOT_NULL_ERROR_MESSAGE);

			return *this;
		}

		constexpr NotNull& operator=(const NotNull&) //
			noexcept(std::is_nothrow_copy_assignable_v<value_type>)
			requires(std::is_copy_assignable_v<value_type>)
		= default;

		constexpr NotNull& operator=(NotNull&&) //
			noexcept(std::is_nothrow_move_assignable_v<value_type>)
			requires(std::is_move_assignable_v<value_type>)
		= default;

		[[nodiscard]] constexpr explicit operator value_type() const //
			noexcept(std::is_nothrow_copy_constructible_v<value_type>)
			requires(std::is_copy_constructible_v<value_type>)
		{
			REX::Assume(_ptr != nullptr, Impl::BASIC_NOT_NULL_ERROR_MESSAGE);
			return _ptr;
		}

		[[nodiscard]] constexpr value_type& operator*() & noexcept
		{
			REX::Assume(_ptr != nullptr, Impl::BASIC_NOT_NULL_ERROR_MESSAGE);
			return _ptr;
		}

		[[nodiscard]] constexpr const value_type& operator*() const& noexcept
		{
			REX::Assume(_ptr != nullptr, Impl::BASIC_NOT_NULL_ERROR_MESSAGE);
			return _ptr;
		}

		[[nodiscard]] constexpr value_type&& operator*() && //
			noexcept(std::is_nothrow_move_constructible_v<value_type>)
			requires(std::is_move_constructible_v<value_type>)
		{
			REX::Assume(_ptr != nullptr, Impl::BASIC_NOT_NULL_ERROR_MESSAGE);
			return std::move(_ptr);
		}

		[[nodiscard]] constexpr const value_type&& operator*() const&& //
			noexcept(std::is_nothrow_move_constructible_v<value_type>)
			requires(std::is_move_constructible_v<value_type>)
		{
			REX::Assume(_ptr != nullptr, Impl::BASIC_NOT_NULL_ERROR_MESSAGE);
			return std::move(_ptr);
		}

		[[nodiscard]] constexpr value_type& operator->() noexcept
		{
			REX::Assume(_ptr != nullptr, Impl::BASIC_NOT_NULL_ERROR_MESSAGE);
			return _ptr;
		}

		[[nodiscard]] constexpr const value_type& operator->() const noexcept
		{
			REX::Assume(_ptr != nullptr, Impl::BASIC_NOT_NULL_ERROR_MESSAGE);
			return _ptr;
		}

		[[nodiscard]] constexpr value_type& get() & noexcept
		{
			REX::Assume(_ptr != nullptr, Impl::BASIC_NOT_NULL_ERROR_MESSAGE);
			return _ptr;
		}

		[[nodiscard]] constexpr const value_type& get() const& noexcept
		{
			REX::Assume(_ptr != nullptr, Impl::BASIC_NOT_NULL_ERROR_MESSAGE);
			return _ptr;
		}

		[[nodiscard]] constexpr value_type&& get() && //
			noexcept(std::is_nothrow_move_constructible_v<value_type>)
			requires(std::is_move_constructible_v<value_type>)
		{
			REX::Assume(_ptr != nullptr, Impl::BASIC_NOT_NULL_ERROR_MESSAGE);
			return std::move(_ptr);
		}

		[[nodiscard]] constexpr const value_type&& get() const&& //
			noexcept(std::is_nothrow_move_constructible_v<value_type>)
			requires(std::is_move_constructible_v<value_type>)
		{
			REX::Assume(_ptr != nullptr, Impl::BASIC_NOT_NULL_ERROR_MESSAGE);
			return std::move(_ptr);
		}

		constexpr void swap(NotNull& a_other) //
			noexcept(std::is_nothrow_swappable_v<value_type>)
			requires(std::is_swappable_v<value_type>)
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			REX::Assume(_ptr != nullptr, Impl::BASIC_NOT_NULL_ERROR_MESSAGE);
			REX::Assume(a_other._ptr != nullptr, Impl::BASIC_NOT_NULL_ERROR_MESSAGE);

			std::swap(_ptr, a_other._ptr);
		}

	private:
		template <class>
		friend class NotNull;

		value_type _ptr;
	};

	template <class T>
	NotNull(T) -> NotNull<T>;

	static_assert(sizeof(NotNull<void*>) == sizeof(void*));

	static_assert(std::is_trivially_destructible_v<NotNull<void*>>);
	static_assert(std::is_trivially_copyable_v<NotNull<void*>>);
	;

	template <class T>
	[[nodiscard]] constexpr bool operator==(const NotNull<T>& a_lhs, const NotNull<T>& a_rhs) //
		noexcept(nothrow_equality_comparable<T>)
		requires(equality_comparable<T>)
	{
		return a_lhs.get() == a_rhs.get();
	}

	template <class T>
	[[nodiscard]] constexpr bool operator==(const NotNull<T>& a_lhs, T&& a_rhs) //
		noexcept(nothrow_equality_comparable<T>)
		requires(equality_comparable<T>)
	{
		return a_lhs.get() == std::forward<T>(a_rhs);
	}

	template <class T>
	[[nodiscard]] constexpr bool operator==(T&& a_lhs, const NotNull<T>& a_rhs) //
		noexcept(nothrow_equality_comparable<T>)
		requires(equality_comparable<T>)
	{
		return std::forward<T>(a_lhs) == a_rhs.get();
	}

	template <class T>
	[[nodiscard]] constexpr auto operator<=>(const NotNull<T>& a_lhs, const NotNull<T>& a_rhs) //
		noexcept(nothrow_three_way_comparable<T>)
		requires(three_way_comparable<T>)
	{
		return a_lhs.get() <=> a_rhs.get();
	}

	template <class T>
	[[nodiscard]] constexpr auto operator<=>(const NotNull<T>& a_lhs, T&& a_rhs) //
		noexcept(nothrow_three_way_comparable<T>)
		requires(three_way_comparable<T>)
	{
		return a_lhs.get() <=> std::forward<T>(a_rhs);
	}

	template <class T>
	[[nodiscard]] constexpr auto operator<=>(T&& a_lhs, const NotNull<T>& a_rhs) //
		noexcept(nothrow_three_way_comparable<T>)
		requires(three_way_comparable<T>)
	{
		return std::forward<T>(a_lhs) <=> a_rhs.get();
	}

	template <class T>
	constexpr void swap(NotNull<T>& a_lhs, NotNull<T>& a_rhs) //
		noexcept(std::is_nothrow_swappable_v<T>)
		requires(std::is_swappable_v<T>)
	{
		a_lhs.swap(a_rhs);
	}
}

namespace std
{
	template <REX::hashable T>
	struct hash<REX::NotNull<T>>
	{
	public:
		[[nodiscard]] std::size_t operator()(const REX::NotNull<T>& a_key) const //
			noexcept(REX::nothrow_hashable<T>)
		{
			return REX::Hash(a_key.get());
		}
	};
}
