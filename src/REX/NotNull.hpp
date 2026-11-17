#pragma once

#include "REX/Concepts.hpp"
#include "REX/Contract.hpp"
#include "REX/Hashing.hpp"
#include "REX/SourceLocation.hpp"

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

		static_assert(
			REX::equality_comparable_with<value_type, std::nullptr_t>,
			"`REX::NotNull` requires an equality comparable type to `nullptr`.");

		constexpr NotNull() = delete;

		constexpr ~NotNull() noexcept(std::is_nothrow_destructible_v<value_type>)
			requires(std::is_destructible_v<value_type>)
		= default;

		constexpr NotNull(std::nullptr_t) = delete;

		template <class U>
		// NOLINTNEXTLINE(misc-explicit-constructor)
		constexpr NotNull(const U& a_ptr, REX::SourceLocation a_location = REX::SourceLocation::GetCurrent())
			noexcept(std::is_nothrow_convertible_v<U, value_type> && std::is_nothrow_copy_constructible_v<value_type>)
			requires(std::is_convertible_v<U, value_type> && std::is_copy_constructible_v<value_type>)
			:
			_ptr(static_cast<value_type>(a_ptr))
		{
			REX::Ensure(_ptr != nullptr, Impl::BASIC_NOT_NULL_ERROR_MESSAGE, a_location);
		}

		template <class U>
		// NOLINTNEXTLINE(misc-explicit-constructor)
		constexpr NotNull(U&& a_ptr, REX::SourceLocation a_location = REX::SourceLocation::GetCurrent())
			noexcept(std::is_nothrow_convertible_v<U, value_type> && std::is_nothrow_move_constructible_v<value_type>)
			requires(std::is_convertible_v<U, value_type> && std::is_move_constructible_v<value_type>)
			:
			_ptr(static_cast<value_type>(std::forward<U>(a_ptr)))
		{
			REX::Ensure(_ptr != nullptr, Impl::BASIC_NOT_NULL_ERROR_MESSAGE, a_location);
		}

		template <class U>
		// NOLINTNEXTLINE(misc-explicit-constructor)
		constexpr NotNull(const NotNull<U>& a_rhs)
			noexcept(std::is_nothrow_convertible_v<U, value_type> && std::is_nothrow_copy_constructible_v<value_type>)
			requires(std::is_convertible_v<U, value_type> && std::is_copy_constructible_v<value_type>)
			:
			_ptr(static_cast<value_type>(a_rhs._ptr))
		{
			REX::Assume(_ptr != nullptr, Impl::BASIC_NOT_NULL_ERROR_MESSAGE);
		}

		template <class U>
		// NOLINTNEXTLINE(misc-explicit-constructor, cppcoreguidelines-rvalue-reference-param-not-moved)
		constexpr NotNull(NotNull<U>&& a_rhs)
			noexcept(std::is_nothrow_convertible_v<U, value_type> && std::is_nothrow_move_constructible_v<value_type>)
			requires(std::is_convertible_v<U, value_type> && std::is_move_constructible_v<value_type>)
			:
			_ptr(static_cast<value_type>(std::move(a_rhs._ptr)))
		{
			REX::Assume(_ptr != nullptr, Impl::BASIC_NOT_NULL_ERROR_MESSAGE);
		}

		constexpr NotNull(const NotNull&) noexcept(std::is_nothrow_copy_constructible_v<value_type>)
			requires(std::is_copy_constructible_v<value_type>)
		= default;

		constexpr NotNull(NotNull&&) noexcept(std::is_nothrow_move_constructible_v<value_type>)
			requires(std::is_move_constructible_v<value_type>)
		= default;

		constexpr auto operator=(std::nullptr_t) -> NotNull& = delete;

		template <class U>
		constexpr auto operator=(const NotNull<U>& a_rhs)
			noexcept(std::is_nothrow_convertible_v<U, value_type> && std::is_nothrow_copy_assignable_v<value_type>)
				-> NotNull&
			requires(std::is_convertible_v<U, value_type> && std::is_copy_assignable_v<value_type>)
		{
			_ptr = static_cast<value_type>(a_rhs._ptr);
			REX::Assume(_ptr != nullptr, Impl::BASIC_NOT_NULL_ERROR_MESSAGE);

			return *this;
		}

		template <class U>
		// NOLINTNEXTLINE(cppcoreguidelines-rvalue-reference-param-not-moved)
		constexpr auto operator=(NotNull<U>&& a_rhs)
			noexcept(std::is_nothrow_convertible_v<U, value_type> && std::is_nothrow_move_assignable_v<value_type>)
				-> NotNull&
			requires(std::is_convertible_v<U, value_type> && std::is_move_assignable_v<value_type>)
		{
			_ptr = static_cast<value_type>(std::move(a_rhs._ptr));
			REX::Assume(_ptr != nullptr, Impl::BASIC_NOT_NULL_ERROR_MESSAGE);

			return *this;
		}

		constexpr auto operator=(const NotNull&) noexcept(std::is_nothrow_copy_assignable_v<value_type>) -> NotNull&
			requires(std::is_copy_assignable_v<value_type>)
		= default;

		constexpr auto operator=(NotNull&&) noexcept(std::is_nothrow_move_assignable_v<value_type>) -> NotNull&
			requires(std::is_move_assignable_v<value_type>)
		= default;

		[[nodiscard]]
		constexpr explicit operator value_type() const //
			noexcept(std::is_nothrow_copy_constructible_v<value_type>)
			requires(std::is_copy_constructible_v<value_type>)
		{
			REX::Assume(_ptr != nullptr, Impl::BASIC_NOT_NULL_ERROR_MESSAGE);
			return _ptr;
		}

		[[nodiscard]]
		constexpr auto operator*() & noexcept -> value_type&
		{
			REX::Assume(_ptr != nullptr, Impl::BASIC_NOT_NULL_ERROR_MESSAGE);
			return _ptr;
		}

		[[nodiscard]]
		constexpr auto operator*() const& noexcept -> const value_type&
		{
			REX::Assume(_ptr != nullptr, Impl::BASIC_NOT_NULL_ERROR_MESSAGE);
			return _ptr;
		}

		[[nodiscard]]
		constexpr auto operator*() && //
			noexcept(std::is_nothrow_move_constructible_v<value_type>) -> value_type&&
			requires(std::is_move_constructible_v<value_type>)
		{
			REX::Assume(_ptr != nullptr, Impl::BASIC_NOT_NULL_ERROR_MESSAGE);
			return std::move(_ptr);
		}

		[[nodiscard]]
		constexpr auto operator*() const&& //
			noexcept(std::is_nothrow_move_constructible_v<value_type>) -> const value_type&&
			requires(std::is_move_constructible_v<value_type>)
		{
			REX::Assume(_ptr != nullptr, Impl::BASIC_NOT_NULL_ERROR_MESSAGE);
			return std::move(_ptr);
		}

		[[nodiscard]]
		constexpr auto operator->() noexcept -> value_type&
		{
			REX::Assume(_ptr != nullptr, Impl::BASIC_NOT_NULL_ERROR_MESSAGE);
			return _ptr;
		}

		[[nodiscard]]
		constexpr auto operator->() const noexcept -> const value_type&
		{
			REX::Assume(_ptr != nullptr, Impl::BASIC_NOT_NULL_ERROR_MESSAGE);
			return _ptr;
		}

		[[nodiscard]]
		constexpr auto get() & noexcept -> value_type&
		{
			REX::Assume(_ptr != nullptr, Impl::BASIC_NOT_NULL_ERROR_MESSAGE);
			return _ptr;
		}

		[[nodiscard]]
		constexpr auto get() const& noexcept -> const value_type&
		{
			REX::Assume(_ptr != nullptr, Impl::BASIC_NOT_NULL_ERROR_MESSAGE);
			return _ptr;
		}

		[[nodiscard]]
		constexpr auto get() && //
			noexcept(std::is_nothrow_move_constructible_v<value_type>) -> value_type&&
			requires(std::is_move_constructible_v<value_type>)
		{
			REX::Assume(_ptr != nullptr, Impl::BASIC_NOT_NULL_ERROR_MESSAGE);
			return std::move(_ptr);
		}

		[[nodiscard]]
		constexpr auto get() const&& //
			noexcept(std::is_nothrow_move_constructible_v<value_type>) -> const value_type&&
			requires(std::is_move_constructible_v<value_type>)
		{
			REX::Assume(_ptr != nullptr, Impl::BASIC_NOT_NULL_ERROR_MESSAGE);
			return std::move(_ptr);
		}

		constexpr void swap(NotNull& a_other) noexcept(std::is_nothrow_swappable_v<value_type>)
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
	static_assert(std::is_trivially_move_constructible_v<NotNull<void*>>);

	template <class T>
	[[nodiscard]]
	constexpr auto operator==(const NotNull<T>& a_lhs, const NotNull<T>& a_rhs) noexcept(nothrow_equality_comparable<T>)
		-> bool
		requires(equality_comparable<T>)
	{
		return a_lhs.get() == a_rhs.get();
	}

	template <class T>
	[[nodiscard]]
	constexpr auto operator==(const NotNull<T>& a_lhs, T&& a_rhs) noexcept(nothrow_equality_comparable<T>) -> bool
		requires(equality_comparable<T>)
	{
		return a_lhs.get() == std::forward<T>(a_rhs);
	}

	template <class T>
	[[nodiscard]]
	constexpr auto operator==(T&& a_lhs, const NotNull<T>& a_rhs) noexcept(nothrow_equality_comparable<T>) -> bool
		requires(equality_comparable<T>)
	{
		return std::forward<T>(a_lhs) == a_rhs.get();
	}

	template <class T>
	[[nodiscard]]
	constexpr auto operator<=>(const NotNull<T>& a_lhs, const NotNull<T>& a_rhs)
		noexcept(nothrow_three_way_comparable<T>)
		requires(three_way_comparable<T>)
	{
		return a_lhs.get() <=> a_rhs.get();
	}

	template <class T>
	[[nodiscard]]
	constexpr auto operator<=>(const NotNull<T>& a_lhs, T&& a_rhs) noexcept(nothrow_three_way_comparable<T>) -> auto
		requires(three_way_comparable<T>)
	{
		return a_lhs.get() <=> std::forward<T>(a_rhs);
	}

	template <class T>
	[[nodiscard]]
	constexpr auto operator<=>(T&& a_lhs, const NotNull<T>& a_rhs) noexcept(nothrow_three_way_comparable<T>) -> auto
		requires(three_way_comparable<T>)
	{
		return std::forward<T>(a_lhs) <=> a_rhs.get();
	}
}

namespace std
{
	template <REX::hashable T>
	struct hash<REX::NotNull<T>>
	{
	public:
		[[nodiscard]]
		auto operator()(const REX::NotNull<T>& a_key) const //
			noexcept(REX::nothrow_hashable<T>) -> std::size_t
		{
			return REX::Hash(a_key.get());
		}
	};
}

#if (__cpp_lib_format > 0l)
namespace std
{
	template <REX::formattable T>
	struct formatter<REX::NotNull<T>> : public formatter<T>
	{
	public:
		template <class FormatContext>
		[[nodiscard]]
		constexpr auto parse(FormatContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]]
		constexpr auto format(const REX::NotNull<T>& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, a_value.get());
		}
	};
}
#endif

#if (FMT_VERSION > 0l)
namespace fmt
{
	template <REX::formattable T>
	struct formatter<REX::NotNull<T>> : public formatter<T>
	{
	public:
		template <class FormatContext>
		[[nodiscard]]
		constexpr auto parse(FormatContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]]
		constexpr auto format(const REX::NotNull<T>& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, a_value.get());
		}
	};
}
#endif
