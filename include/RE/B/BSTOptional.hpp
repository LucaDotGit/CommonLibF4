#pragma once

#include "RE/M/MemoryManager.hpp"

namespace RE
{
	template <class T>
	class BSTOptional
	{
	public:
		using value_type = T;

		constexpr BSTOptional() noexcept = default;

		constexpr ~BSTOptional() //
			noexcept(std::is_nothrow_destructible_v<value_type>)
			requires(!std::is_trivially_destructible_v<value_type>)
		{
			reset();
		}

		constexpr ~BSTOptional()
			requires(std::is_trivially_destructible_v<value_type>)
		= default;

		constexpr BSTOptional(std::nullopt_t /*a_nullopt*/) noexcept
		{
			return;
		}

		constexpr BSTOptional(const BSTOptional& a_rhs) //
			noexcept(std::is_nothrow_copy_constructible_v<value_type>)
			requires(std::is_copy_constructible_v<value_type> &&
					 !std::is_trivially_copy_constructible_v<value_type>)
		{
			if (a_rhs.has_value()) {
				std::construct_at(std::addressof(_value), a_rhs.value());
				_active = true;
			}
		}

		constexpr BSTOptional(const BSTOptional&)
			requires(std::is_trivially_copy_constructible_v<value_type>)
		= default;

		constexpr BSTOptional(BSTOptional&& a_rhs) //
			noexcept(std::is_nothrow_move_constructible_v<value_type>)
			requires(std::is_move_constructible_v<value_type> &&
					 !std::is_trivially_move_constructible_v<value_type>)
		{
			if (a_rhs.has_value()) {
				std::construct_at(std::addressof(_value), std::move(a_rhs).value());
				_active = true;
			}
		}

		constexpr BSTOptional(BSTOptional&&)
			requires(std::is_trivially_move_constructible_v<value_type>)
		= default;

		template <class U>
		constexpr explicit(!std::is_convertible_v<const U&, value_type>)
			BSTOptional(const BSTOptional<U>& a_rhs) //
			noexcept(std::is_nothrow_constructible_v<value_type, const U&>)
			requires(std::is_constructible_v<value_type, const U&> &&
					 !std::is_constructible_v<value_type, BSTOptional<U>&> &&
					 !std::is_constructible_v<value_type, const BSTOptional<U>&> &&
					 !std::is_constructible_v<value_type, BSTOptional<U> &&> &&
					 !std::is_constructible_v<value_type, const BSTOptional<U> &&> &&
					 !std::is_convertible_v<BSTOptional<U>&, value_type> &&
					 !std::is_convertible_v<const BSTOptional<U>&, value_type> &&
					 !std::is_convertible_v<BSTOptional<U> &&, value_type> &&
					 !std::is_convertible_v<const BSTOptional<U> &&, value_type>)
		{
			if (a_rhs.has_value()) {
				std::construct_at(std::addressof(_value), a_rhs.value());
				_active = true;
			}
		}

		template <class U>
		constexpr explicit(!std::is_convertible_v<U&&, T>)
			BSTOptional(BSTOptional<U>&& a_rhs) //
			noexcept(std::is_nothrow_constructible_v<value_type, U&&>)
			requires(std::is_constructible_v<value_type, U &&> &&
					 !std::is_constructible_v<value_type, BSTOptional<U>&> &&
					 !std::is_constructible_v<value_type, const BSTOptional<U>&> &&
					 !std::is_constructible_v<value_type, BSTOptional<U> &&> &&
					 !std::is_constructible_v<value_type, const BSTOptional<U> &&> &&
					 !std::is_convertible_v<BSTOptional<U>&, value_type> &&
					 !std::is_convertible_v<const BSTOptional<U>&, value_type> &&
					 !std::is_convertible_v<BSTOptional<U> &&, value_type> &&
					 !std::is_convertible_v<const BSTOptional<U> &&, value_type>)
		{
			if (a_rhs.has_value()) {
				std::construct_at(std::addressof(_value), std::move(a_rhs).value());
				_active = true;
			}
		}

		template <class... Args>
		constexpr explicit BSTOptional(std::in_place_t /*a_inPlace*/, Args&&... a_args) //
			noexcept(std::is_nothrow_constructible_v<value_type, Args&&...>)
			requires(std::is_constructible_v<value_type, Args && ...>)
			: _active(true)
		{
			std::construct_at(std::addressof(_value), std::forward<Args>(a_args)...);
		}

		template <class U, class... Args>
		constexpr explicit BSTOptional(std::in_place_t /*a_inPlace*/, std::initializer_list<U> a_ilist, Args&&... a_args) //
			noexcept(std::is_nothrow_constructible_v<value_type, std::initializer_list<U>&, Args&&...>)
			requires(std::is_constructible_v<value_type, std::initializer_list<U>&, Args && ...>)
			: _active(true)
		{
			std::construct_at(std::addressof(_value), a_ilist, std::forward<Args>(a_args)...);
		}

		template <class U = value_type>
		constexpr explicit(!std::is_convertible_v<U&&, value_type>)
			BSTOptional(U&& a_value) //
			noexcept(std::is_nothrow_constructible_v<value_type, U&&>)
			requires(std::is_constructible_v<value_type, U &&> &&
					 !std::same_as<std::remove_cvref_t<U>, std::in_place_t> &&
					 !std::same_as<std::remove_cvref_t<U>, BSTOptional<value_type>>)
			: _active(true)
		{
			std::construct_at(std::addressof(_value), std::forward<U>(a_value));
		}

		constexpr BSTOptional& operator=(std::nullopt_t /*a_nullopt*/)
			noexcept(noexcept(reset()))
		{
			reset();
			return *this;
		}

		constexpr BSTOptional& operator=(const BSTOptional& a_rhs) //
			noexcept(std::is_nothrow_destructible_v<value_type> &&
					 std::is_nothrow_copy_constructible_v<value_type> &&
					 std::is_nothrow_copy_assignable_v<value_type>)
			requires(std::is_copy_constructible_v<value_type> &&
					 std::is_copy_assignable_v<value_type>)
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			if (!a_rhs.has_value()) {
				do_reset();
			}

			if (has_value()) {
				_value = a_rhs.value();
			}
			else {
				std::construct_at(std::addressof(_value), a_rhs.value());
				_active = true;
			}

			return *this;
		}

		constexpr BSTOptional& operator=(const BSTOptional&)
			requires(!std::is_copy_constructible_v<value_type> ||
						!std::is_copy_assignable_v<value_type>)
		= delete;

		constexpr BSTOptional& operator=(BSTOptional&& a_rhs) //
			noexcept(std::is_nothrow_destructible_v<value_type> &&
					 std::is_nothrow_move_constructible_v<value_type> &&
					 std::is_nothrow_move_assignable_v<value_type>)
			requires(std::is_move_constructible_v<value_type> &&
					 std::is_move_assignable_v<value_type>)
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			if (!a_rhs.has_value()) {
				do_reset();
				return *this;
			}

			if (has_value()) {
				_value = std::move(a_rhs).value();
			}
			else {
				std::construct_at(std::addressof(_value), std::move(a_rhs).value());
				_active = true;
			}

			return *this;
		}

		BSTOptional& operator=(BSTOptional&&)
			requires(!std::is_move_constructible_v<value_type> ||
						!std::is_move_assignable_v<value_type>)
		= delete;

		template <class U = value_type>
		constexpr BSTOptional& operator=(U&& a_value) //
			noexcept((std::is_nothrow_destructible_v<value_type> &&
					  std::is_nothrow_constructible_v<value_type, U&&> &&
					  std::is_nothrow_assignable_v<value_type&, U&&>))
			requires(!std::same_as<std::remove_cvref_t<U>, BSTOptional<value_type>> &&
					 std::is_constructible_v<value_type, U &&> &&
					 std::is_assignable_v<value_type&, U &&> &&
					 (!std::is_scalar_v<value_type> || !std::same_as<std::decay_t<U>, T>))
		{
			if (has_value()) {
				_value = std::forward<U>(a_value);
			}
			else {
				std::construct_at(std::addressof(_value), std::forward<U>(a_value));
				_active = true;
			}

			return *this;
		}

		template <class U>
		constexpr BSTOptional& operator=(const BSTOptional<U>& a_rhs) //
			noexcept((std::is_nothrow_destructible_v<value_type> &&
					  std::is_nothrow_constructible_v<value_type, const U&> &&
					  std::is_nothrow_assignable_v<value_type&, const U&>))
			requires(!std::is_constructible_v<value_type, BSTOptional<U>&> &&
					 !std::is_constructible_v<value_type, const BSTOptional<U>&> &&
					 !std::is_constructible_v<value_type, BSTOptional<U> &&> &&
					 !std::is_constructible_v<value_type, const BSTOptional<U> &&> &&
					 !std::is_convertible_v<BSTOptional<U>&, value_type> &&
					 !std::is_convertible_v<const BSTOptional<U>&, value_type> &&
					 !std::is_convertible_v<BSTOptional<U> &&, value_type> &&
					 !std::is_convertible_v<const BSTOptional<U> &&, value_type> &&
					 !std::is_assignable_v<value_type&, BSTOptional<U>&> &&
					 !std::is_assignable_v<value_type&, const BSTOptional<U>&> &&
					 !std::is_assignable_v<value_type&, BSTOptional<U> &&> &&
					 !std::is_assignable_v<value_type&, const BSTOptional<U> &&> &&
					 std::is_constructible_v<value_type, const U&> &&
					 std::is_assignable_v<value_type&, const U&>)
		{
			if (!a_rhs.has_value()) {
				reset();
			}

			if (has_value()) {
				_value = a_rhs.value();
			}
			else {
				std::construct_at(std::addressof(_value), a_rhs.value());
				_active = true;
			}

			return *this;
		}

		template <class U>
		constexpr BSTOptional& operator=(BSTOptional<U>&& a_rhs) //
			noexcept((std::is_nothrow_destructible_v<value_type> &&
					  std::is_nothrow_constructible_v<value_type, U> &&
					  std::is_nothrow_assignable_v<value_type&, U>))
			requires(!std::is_constructible_v<value_type, BSTOptional<U>&> &&
					 !std::is_constructible_v<value_type, const BSTOptional<U>&> &&
					 !std::is_constructible_v<value_type, BSTOptional<U> &&> &&
					 !std::is_constructible_v<value_type, const BSTOptional<U> &&> &&
					 !std::is_convertible_v<BSTOptional<U>&, value_type> &&
					 !std::is_convertible_v<const BSTOptional<U>&, value_type> &&
					 !std::is_convertible_v<BSTOptional<U> &&, value_type> &&
					 !std::is_convertible_v<const BSTOptional<U> &&, value_type> &&
					 !std::is_assignable_v<value_type&, BSTOptional<U>&> &&
					 !std::is_assignable_v<value_type&, const BSTOptional<U>&> &&
					 !std::is_assignable_v<value_type&, BSTOptional<U> &&> &&
					 !std::is_assignable_v<value_type&, const BSTOptional<U> &&> &&
					 std::is_constructible_v<value_type, U> &&
					 std::is_assignable_v<value_type&, U>)
		{
			if (!a_rhs.has_value()) {
				reset();
			}

			if (has_value()) {
				_value = std::move(a_rhs).value();
			}
			else {
				std::construct_at(std::addressof(_value), std::move(a_rhs).value());
				_active = true;
			}

			return *this;
		}

		GAME_HEAP_REDEFINE_NEW(BSTOptional);

		[[nodiscard]] constexpr explicit operator bool() const noexcept { return has_value(); }

		[[nodiscard]] constexpr const value_type* operator->() const noexcept { return std::addressof(value()); }
		[[nodiscard]] constexpr value_type* operator->() noexcept { return std::addressof(value()); }
		[[nodiscard]] constexpr const value_type& operator*() const& noexcept { return value(); }
		[[nodiscard]] constexpr value_type& operator*() & noexcept { return value(); }
		[[nodiscard]] constexpr const value_type&& operator*() const&& noexcept { return std::move(*this).value(); }
		[[nodiscard]] constexpr value_type&& operator*() && noexcept { return std::move(*this).value(); }

		[[nodiscard]] constexpr bool has_value() const noexcept { return _active; }

		[[nodiscard]] constexpr value_type& value() & //
			noexcept(std::is_nothrow_copy_constructible_v<value_type>)
			requires(std::is_copy_constructible_v<value_type>)
		{
			REX::Assert(has_value());
			return _value;
		}

		[[nodiscard]] constexpr const value_type& value() const& //
			noexcept(std::is_nothrow_copy_constructible_v<value_type>)
			requires(std::is_copy_constructible_v<value_type>)
		{
			REX::Assert(has_value());
			return _value;
		}

		[[nodiscard]] constexpr value_type&& value() && //
			noexcept(std::is_nothrow_move_constructible_v<value_type>)
			requires(std::is_move_constructible_v<value_type>)
		{
			REX::Assert(has_value());
			return std::move(_value);
		}

		[[nodiscard]] constexpr const value_type&& value() const&& //
			noexcept(std::is_nothrow_move_constructible_v<value_type>)
			requires(std::is_move_constructible_v<value_type>)
		{
			REX::Assert(has_value());
			return std::move(_value);
		}

		template <class U>
		[[nodiscard]] constexpr value_type value_or(U&& a_default) const& //
			noexcept(std::is_nothrow_copy_constructible_v<value_type> &&
					 std::is_nothrow_constructible_v<value_type, U&&>)
			requires(std::is_copy_constructible_v<value_type> &&
					 std::is_convertible_v<U &&, value_type>)
		{
			return has_value() ? value() : static_cast<T>(std::forward<U>(a_default));
		}

		template <class U>
		[[nodiscard]] constexpr value_type value_or(U&& a_default) && //
			noexcept(std::is_nothrow_move_constructible_v<value_type> &&
					 std::is_nothrow_constructible_v<value_type, U&&>)
			requires(std::is_move_constructible_v<value_type> &&
					 std::is_convertible_v<U &&, value_type>)
		{
			return has_value() ? std::move(*this).value() : static_cast<T>(std::forward<U>(a_default));
		}

		template <class F>
		constexpr auto and_then(F&& a_func) & //
			noexcept(std::is_nothrow_invocable_v<F, value_type&> &&
					 std::is_nothrow_constructible_v<std::remove_cvref_t<std::invoke_result_t<F, value_type&>>, value_type&>)
			requires(std::is_invocable_v<F, value_type&> &&
					 std::is_constructible_v<std::remove_cvref_t<std::invoke_result_t<F, value_type&>>, value_type&>)
		{
			if (has_value()) {
				return std::invoke(std::forward<F>(a_func), value());
			}

			return std::remove_cvref_t<std::invoke_result_t<F, value_type&>>{};
		}

		template <class F>
		constexpr auto and_then(F&& a_func) const& //
			noexcept(std::is_nothrow_invocable_v<F, const value_type&> &&
					 std::is_nothrow_constructible_v<std::remove_cvref_t<std::invoke_result_t<F, const value_type&>>, const value_type&>)
			requires(std::is_invocable_v<F, const value_type&> &&
					 std::is_constructible_v<std::remove_cvref_t<std::invoke_result_t<F, const value_type&>>, const value_type&>)
		{
			if (has_value()) {
				return std::invoke(std::forward<F>(a_func), value());
			}

			return std::remove_cvref_t<std::invoke_result_t<F, const value_type&>>{};
		}

		template <class F>
		constexpr auto and_then(F&& a_func) && //
			noexcept(std::is_nothrow_invocable_v<F, value_type&&> &&
					 std::is_nothrow_constructible_v<std::remove_cvref_t<std::invoke_result_t<F, value_type&&>>, value_type&&>)
			requires(std::is_invocable_v<F, value_type &&> &&
					 std::is_constructible_v<std::remove_cvref_t<std::invoke_result_t<F, value_type &&>>, value_type &&>)
		{
			if (has_value()) {
				return std::invoke(std::forward<F>(a_func), std::move(*this).value());
			}

			return std::remove_cvref_t<std::invoke_result_t<F, value_type&&>>{};
		}

		template <class F>
		constexpr auto and_then(F&& a_func) const&& //
			noexcept(std::is_nothrow_invocable_v<F, const value_type&&> &&
					 std::is_nothrow_constructible_v<std::remove_cvref_t<std::invoke_result_t<F, const value_type&&>>, const value_type&&>)
			requires(std::is_invocable_v<F, const value_type &&> &&
					 std::is_constructible_v<std::remove_cvref_t<std::invoke_result_t<F, const value_type &&>>, const value_type &&>)
		{
			if (has_value()) {
				return std::invoke(std::forward<F>(a_func), std::move(*this).value());
			}

			return std::remove_cvref_t<std::invoke_result_t<F, const value_type&&>>{};
		}

		template <class F>
		constexpr auto or_else(F&& a_func) & //
			noexcept(std::is_nothrow_invocable_v<F> &&
					 std::is_nothrow_constructible_v<std::remove_cvref_t<std::invoke_result_t<F>>, value_type>)
			requires(std::is_invocable_v<F> &&
					 std::is_constructible_v<std::remove_cvref_t<std::invoke_result_t<F>>, value_type>)
		{
			if (has_value()) {
				return *this;
			}

			return std::invoke(std::forward<F>(a_func));
		}

		template <class F>
		constexpr auto or_else(F&& a_func) const& //
			noexcept(std::is_nothrow_invocable_v<F> &&
					 std::is_nothrow_constructible_v<std::remove_cvref_t<std::invoke_result_t<F>>, value_type>)
			requires(std::is_invocable_v<F> &&
					 std::is_constructible_v<std::remove_cvref_t<std::invoke_result_t<F>>, value_type>)
		{
			if (has_value()) {
				return *this;
			}

			return std::invoke(std::forward<F>(a_func));
		}

		template <class F>
		constexpr auto or_else(F&& a_func) && //
			noexcept(std::is_nothrow_invocable_v<F> &&
					 std::is_nothrow_constructible_v<std::remove_cvref_t<std::invoke_result_t<F>>, value_type>)
			requires(std::is_invocable_v<F> &&
					 std::is_constructible_v<std::remove_cvref_t<std::invoke_result_t<F>>, value_type>)
		{
			if (has_value()) {
				return std::move(*this);
			}

			return std::invoke(std::forward<F>(a_func));
		}

		template <class F>
		constexpr auto or_else(F&& a_func) const&& //
			noexcept(std::is_nothrow_invocable_v<F> &&
					 std::is_nothrow_constructible_v<std::remove_cvref_t<std::invoke_result_t<F>>, value_type>)
			requires(std::is_invocable_v<F> &&
					 std::is_constructible_v<std::remove_cvref_t<std::invoke_result_t<F>>, value_type>)
		{
			if (has_value()) {
				return std::move(*this);
			}

			return std::invoke(std::forward<F>(a_func));
		}

		template <class F>
		constexpr auto transform(F&& a_func) & //
			noexcept(std::is_nothrow_invocable_v<F, value_type&> &&
					 std::is_nothrow_constructible_v<std::remove_cvref_t<std::invoke_result_t<F, value_type&>>, value_type>)
			requires(std::is_invocable_v<F, value_type&> &&
					 std::is_constructible_v<std::remove_cvref_t<std::invoke_result_t<F, value_type&>>, value_type>)
		{
			if (has_value()) {
				return BSTOptional(std::invoke(std::forward<F>(a_func), value()));
			}

			return BSTOptional<std::invoke_result_t<F, value_type&>>();
		}

		template <class F>
		constexpr auto transform(F&& a_func) const& //
			noexcept(std::is_nothrow_invocable_v<F, const value_type&> &&
					 std::is_nothrow_constructible_v<std::remove_cvref_t<std::invoke_result_t<F, const value_type&>>, value_type>)
			requires(std::is_invocable_v<F, const value_type&> &&
					 std::is_constructible_v<std::remove_cvref_t<std::invoke_result_t<F, const value_type&>>, value_type>)
		{
			if (has_value()) {
				return BSTOptional(std::invoke(std::forward<F>(a_func), value()));
			}

			return BSTOptional<std::invoke_result_t<F, const value_type&>>();
		}

		template <class F>
		constexpr auto transform(F&& a_func) && //
			noexcept(std::is_nothrow_invocable_v<F, value_type&&> &&
					 std::is_nothrow_constructible_v<std::remove_cvref_t<std::invoke_result_t<F, value_type&&>>, value_type>)
			requires(std::is_invocable_v<F, value_type &&> &&
					 std::is_constructible_v<std::remove_cvref_t<std::invoke_result_t<F, value_type &&>>, value_type>)
		{
			if (has_value()) {
				return BSTOptional(std::invoke(std::forward<F>(a_func), std::move(*this).value()));
			}

			return BSTOptional<std::invoke_result_t<F, value_type&&>>();
		}

		template <class F>
		constexpr auto transform(F&& a_func) const&& //
			noexcept(std::is_nothrow_invocable_v<F, const value_type&&> &&
					 std::is_nothrow_constructible_v<std::remove_cvref_t<std::invoke_result_t<F, const value_type&&>>, value_type>)
			requires(std::is_invocable_v<F, const value_type &&> &&
					 std::is_constructible_v<std::remove_cvref_t<std::invoke_result_t<F, const value_type &&>>, value_type>)
		{
			if (has_value()) {
				return BSTOptional(std::invoke(std::forward<F>(a_func), std::move(*this).value()));
			}

			return BSTOptional<std::invoke_result_t<F, const value_type&&>>();
		}

		template <class... Args>
		constexpr value_type& emplace(Args&&... a_args) //
			noexcept(std::is_nothrow_constructible_v<value_type, Args&&...>)
			requires(std::is_constructible_v<value_type, Args && ...>)
		{
			reset();
			std::construct_at(std::addressof(_value), std::forward<Args>(a_args)...);
			_active = true;
			return value();
		}

		template <class U, class... Args>
		constexpr value_type& emplace(std::initializer_list<U> a_ilist, Args&&... a_args) //
			noexcept(std::is_nothrow_constructible_v<value_type, std::initializer_list<U>&, Args&&...>)
			requires(std::is_constructible_v<value_type, std::initializer_list<U>&, Args && ...>)
		{
			reset();
			std::construct_at(std::addressof(_value), a_ilist, std::forward<Args>(a_args)...);
			_active = true;
			return value();
		}

		constexpr void reset() //
			noexcept(noexcept(do_reset()))
		{
			do_reset();
		}

	private:
		constexpr void do_reset() //
			noexcept(std::is_nothrow_destructible_v<value_type>)
		{
			if (has_value()) {
				std::destroy_at(std::addressof(_value));
				_active = false;
			}
		}

		// members
		union
		{
			std::remove_const_t<value_type> _value;
			std::array<std::byte, sizeof(value_type)> _buffer{ static_cast<std::byte>(0) };
		}; // 00
		bool _active{ false }; // ??
	};

	template <class T>
	BSTOptional(T) -> BSTOptional<T>;

	template <class T, class... Args>
	[[nodiscard]] constexpr BSTOptional<T> make_optional(Args&&... a_args)
		requires(std::is_constructible_v<T, Args && ...>)
	{
		return BSTOptional<T>{ std::forward<Args>(a_args)... };
	}
}

namespace RE::BSScript
{
	template <class>
	struct script_traits;

	template <class T>
	struct script_traits<BSTOptional<T>>
	{
		using is_optional = std::true_type;
	};
}
