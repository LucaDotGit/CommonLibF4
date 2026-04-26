#pragma once

#include "REX/Concepts.hpp"
#include "REX/Hash.hpp"

namespace REX
{
	template <class T>
	class NotAssignable final
	{
	public:
		using value_type = T;

		constexpr NotAssignable() //
			noexcept(std::is_nothrow_default_constructible_v<value_type>)
			requires(std::is_default_constructible_v<value_type>)
		= default;

		constexpr ~NotAssignable() //
			noexcept(std::is_nothrow_destructible_v<value_type>)
			requires(std::is_destructible_v<value_type>)
		= default;

		constexpr explicit NotAssignable(const value_type& a_value) //
			noexcept(std::is_nothrow_copy_constructible_v<value_type>)
			requires(std::is_copy_constructible_v<value_type>)
			: _value(a_value)
		{
		}

		constexpr explicit NotAssignable(value_type&& a_value) //
			noexcept(std::is_nothrow_move_constructible_v<value_type>)
			requires(std::is_move_constructible_v<value_type>)
			: _value(std::move(a_value))
		{
		}

		constexpr NotAssignable(const NotAssignable&) //
			noexcept(std::is_nothrow_copy_constructible_v<value_type>)
			requires(std::is_copy_constructible_v<value_type>)
		= default;

		constexpr NotAssignable(NotAssignable&&) //
			noexcept(std::is_nothrow_move_constructible_v<value_type>)
			requires(std::is_move_constructible_v<value_type>)
		= default;

		constexpr NotAssignable& operator=(const NotAssignable&) = delete;
		constexpr NotAssignable& operator=(NotAssignable&&) = delete;

		[[nodiscard]] constexpr value_type& operator*() noexcept { return _value; }
		[[nodiscard]] constexpr const value_type& operator*() const noexcept { return _value; }

		[[nodiscard]] constexpr value_type* operator->() noexcept { return std::addressof(_value); }
		[[nodiscard]] constexpr const value_type* operator->() const noexcept { return std::addressof(_value); }

		[[nodiscard]] constexpr value_type& get() noexcept { return _value; }
		[[nodiscard]] constexpr const value_type& get() const noexcept { return _value; }

	private:
		value_type _value;
	};
	static_assert(sizeof(NotAssignable<std::any>) == sizeof(std::any));

	template <class T>
	NotAssignable(T) -> NotAssignable<T>;

	template <class T>
	[[nodiscard]] constexpr bool operator==(const NotAssignable<T>& a_lhs, const NotAssignable<T>& a_rhs)
		noexcept(nothrow_equality_comparable<T>)
		requires(equality_comparable<T>)
	{
		return a_lhs.get() == a_rhs.get();
	}

	template <class T>
	[[nodiscard]] constexpr bool operator==(const NotAssignable<T>& a_lhs, T&& a_rhs)
		noexcept(nothrow_equality_comparable<T>)
		requires(equality_comparable<T>)
	{
		return a_lhs.get() == std::forward<T>(a_rhs);
	}

	template <class T>
	[[nodiscard]] constexpr bool operator==(T&& a_lhs, const NotAssignable<T>& a_rhs)
		noexcept(nothrow_equality_comparable<T>)
		requires(equality_comparable<T>)
	{
		return std::forward<T>(a_lhs) == a_rhs.get();
	}

	template <class T>
	[[nodiscard]] constexpr auto operator<=>(const NotAssignable<T>& a_lhs, const NotAssignable<T>& a_rhs)
		noexcept(nothrow_three_way_comparable<T>)
		requires(three_way_comparable<T>)
	{
		return a_lhs.get() <=> a_rhs.get();
	}

	template <class T>
	[[nodiscard]] constexpr auto operator<=>(const NotAssignable<T>& a_lhs, T&& a_rhs)
		noexcept(nothrow_three_way_comparable<T>)
		requires(three_way_comparable<T>)
	{
		return a_lhs.get() <=> std::forward<T>(a_rhs);
	}

	template <class T>
	[[nodiscard]] constexpr auto operator<=>(T&& a_lhs, const NotAssignable<T>& a_rhs)
		noexcept(nothrow_three_way_comparable<T>)
		requires(three_way_comparable<T>)
	{
		return std::forward<T>(a_lhs) <=> a_rhs.get();
	}
}

namespace std
{
	template <REX::hashable T>
	struct hash<REX::NotAssignable<T>>
	{
	public:
		[[nodiscard]] std::size_t operator()(const REX::NotAssignable<T>& a_key) const //
			noexcept(REX::nothrow_hashable<T>)
		{
			return REX::Hash(a_key.get());
		}
	};
}
