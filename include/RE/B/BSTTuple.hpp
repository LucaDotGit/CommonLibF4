#pragma once

#include "RE/M/MemoryManager.hpp"

namespace RE
{
	template <class T1, class T2>
	class BSTTuple
	{
	public:
		using first_type = T1;
		using second_type = T2;

		constexpr BSTTuple() //
			noexcept(std::is_nothrow_default_constructible_v<first_type> &&
					 std::is_nothrow_default_constructible_v<second_type>)
			requires(std::is_default_constructible_v<first_type> &&
						std::is_default_constructible_v<second_type>)
		= default;

		constexpr ~BSTTuple() //
			noexcept(std::is_nothrow_destructible_v<first_type> &&
					 std::is_nothrow_destructible_v<second_type>)
			requires(std::is_destructible_v<first_type> &&
						std::is_destructible_v<second_type>)
		= default;

		constexpr explicit(!std::is_convertible_v<const first_type&, first_type> ||
						   !std::is_convertible_v<const second_type&, second_type>)
			BSTTuple(const first_type& a_first, const second_type& a_second) //
			noexcept(std::is_nothrow_copy_constructible_v<first_type> &&
					 std::is_nothrow_copy_constructible_v<second_type>)
			requires(std::is_copy_constructible_v<first_type> &&
						std::is_copy_constructible_v<second_type>)
			: first(a_first),
			  second(a_second)
		{
		}

		template <class U1, class U2>
		constexpr explicit(!std::is_convertible_v<U1&&, first_type> ||
						   !std::is_convertible_v<U2&&, second_type>)
			BSTTuple(U1&& a_first, U2&& a_second) //
			noexcept(std::is_nothrow_constructible_v<first_type, U1&&> &&
					 std::is_nothrow_constructible_v<second_type, U2&&>)
			requires(std::is_constructible_v<first_type, U1 &&> &&
						std::is_constructible_v<second_type, U2 &&>)
			: first(std::forward<U1>(a_first)),
			  second(std::forward<U2>(a_second))
		{
		}

		template <class U1, class U2>
		constexpr explicit(!std::is_convertible_v<const U1&, first_type> ||
						   !std::is_convertible_v<const U2&, second_type>)
			BSTTuple(const BSTTuple<U1, U2>& a_rhs) //
			noexcept(std::is_nothrow_constructible_v<first_type, const U1&> &&
					 std::is_nothrow_constructible_v<second_type, const U2&>)
			requires(std::is_constructible_v<first_type, const U1&> &&
						std::is_constructible_v<second_type, const U2&>)
			: first(a_rhs.first),
			  second(a_rhs.second)
		{
		}

		template <class U1, class U2>
		constexpr explicit(!std::is_convertible_v<U1&&, first_type> ||
						   !std::is_convertible_v<U2&&, second_type>)
			BSTTuple(BSTTuple<U1, U2>&& a_rhs) // NOLINT(cppcoreguidelines-rvalue-reference-param-not-moved)
			noexcept(std::is_nothrow_constructible_v<first_type, U1&&> &&
					 std::is_nothrow_constructible_v<second_type, U2&&>)
			requires(std::is_constructible_v<first_type, U1 &&> &&
						std::is_constructible_v<second_type, U2 &&>)
			: first(std::forward<U1>(a_rhs.first)),
			  second(std::forward<U2>(a_rhs.second))
		{
		}

		template <class... Args1, class... Args2>
		constexpr BSTTuple(
			[[maybe_unused]] std::piecewise_construct_t a_tag, std::tuple<Args1...> a_firstArgs,
			std::tuple<Args2...> a_secondArgs)
			: BSTTuple(
				  a_firstArgs,
				  a_secondArgs,
				  std::index_sequence_for<Args1...>(),
				  std::index_sequence_for<Args2...>())
		{
		}

	private:
		template <class Tuple1, class Tuple2, std::size_t... I1, std::size_t... I2>
		constexpr BSTTuple(
			Tuple1& a_firstArgs,
			Tuple2& a_secondArgs,
			[[maybe_unused]] std::index_sequence<I1...> a_firstIndexes,
			[[maybe_unused]] std::index_sequence<I2...> a_secondIndexes)
			: first(std::get<I1>(std::move(a_firstArgs))...),
			  second(std::get<I2>(std::move(a_secondArgs))...)
		{
		}

	public:
		constexpr BSTTuple(const BSTTuple& a_rhs) //
			noexcept(std::is_nothrow_copy_constructible_v<first_type> &&
					 std::is_nothrow_copy_constructible_v<second_type>)
			requires(std::is_copy_constructible_v<first_type> &&
						std::is_copy_constructible_v<second_type>)
			: first(a_rhs.first),
			  second(a_rhs.second)
		{
		}

		constexpr BSTTuple(BSTTuple&& a_rhs) //
			noexcept(std::is_nothrow_move_constructible_v<first_type> &&
					 std::is_nothrow_move_constructible_v<second_type>)
			requires(std::is_move_constructible_v<first_type> &&
						std::is_move_constructible_v<second_type>)
			: first(std::move(a_rhs.first)),
			  second(std::move(a_rhs.second))
		{
		}

		constexpr BSTTuple& operator=(const BSTTuple& a_rhs) //
			noexcept(std::is_nothrow_copy_assignable_v<first_type> &&
					 std::is_nothrow_copy_assignable_v<second_type>)
			requires(std::is_copy_assignable_v<first_type> &&
					 std::is_copy_assignable_v<second_type>)
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			first = a_rhs.first;
			second = a_rhs.second;
			return *this;
		}

		template <class U1, class U2>
		constexpr BSTTuple& operator=(const BSTTuple<U1, U2>& a_rhs) //
			noexcept(std::is_nothrow_assignable_v<first_type&, const U1&> &&
					 std::is_nothrow_assignable_v<second_type&, const U2&>)
			requires(std::is_assignable_v<first_type&, const U1&> &&
					 std::is_assignable_v<second_type&, const U2&>)
		{
			first = a_rhs.first;
			second = a_rhs.second;
			return *this;
		}

		constexpr BSTTuple& operator=(BSTTuple&& a_rhs) //
			noexcept(std::is_nothrow_move_assignable_v<first_type> &&
					 std::is_nothrow_move_assignable_v<second_type>)
			requires(std::is_move_assignable_v<first_type> &&
					 std::is_move_assignable_v<second_type>)
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			first = std::move(a_rhs.first);
			second = std::move(a_rhs.second);
			return *this;
		}

		template <class U1, class U2>
		constexpr BSTTuple& operator=(BSTTuple<U1, U2>&& a_rhs) // NOLINT(cppcoreguidelines-rvalue-reference-param-not-moved)
			noexcept(std::is_nothrow_assignable_v<first_type&, U1> &&
					 std::is_nothrow_assignable_v<second_type&, U2>)
			requires(std::is_assignable_v<first_type&, U1> &&
					 std::is_assignable_v<second_type&, U2>)
		{
			first = std::move(a_rhs.first);
			second = std::move(a_rhs.second);
			return *this;
		}

		GAME_HEAP_REDEFINE_NEW(BSTTuple);

		constexpr void swap(BSTTuple& a_other) //
			noexcept(std::is_nothrow_swappable_v<first_type> &&
					 std::is_nothrow_swappable_v<second_type>)
			requires(std::is_swappable_v<first_type> &&
					 std::is_swappable_v<second_type>)
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(first, a_other.first);
			std::swap(second, a_other.second);
		}

		// members
		first_type first{};	  // 00
		second_type second{}; // ??
	};

	template <class T1, class T2>
	BSTTuple(T1, T2) -> BSTTuple<T1, T2>;

	template <class T1, class T2>
	using BSTPair = BSTTuple<T1, T2>;

	template <class T1, class T2>
	[[nodiscard]] constexpr bool operator==(
		const BSTTuple<T1, T2>& a_lhs,
		const BSTTuple<T1, T2>& a_rhs)
	{
		return a_lhs.first == a_rhs.first && a_lhs.second == a_rhs.second;
	}

	template <class T1, class T2>
	[[nodiscard]] constexpr auto operator<=>(
		const BSTTuple<T1, T2>& a_lhs,
		const BSTTuple<T1, T2>& a_rhs)
	{
		const auto firstCmp = a_lhs.first <=> a_rhs.first;
		if (firstCmp != 0) {
			return firstCmp;
		}

		return a_lhs.second <=> a_rhs.second;
	}

	template <class T1, class T2>
	constexpr void swap(BSTTuple<T1, T2>& a_lhs, BSTTuple<T1, T2>& a_rhs) //
		noexcept(std::is_nothrow_swappable_v<T1> &&
				 std::is_nothrow_swappable_v<T2>)
		requires(std::is_swappable_v<T1> &&
				 std::is_swappable_v<T2>)
	{
		a_lhs.swap(a_rhs);
	}

	template <class T1, class T2>
	[[nodiscard]] constexpr BSTTuple<T1, T2> make_tuple(T1&& a_first, T2&& a_second)
		requires(std::is_constructible_v<T1, T1> && std::is_constructible_v<T2, T2>)
	{
		return BSTTuple{ std::forward<T1>(a_first), std::forward<T2>(a_second) };
	}

	template <class T1, class T2>
	[[nodiscard]] constexpr BSTTuple<T1, T2> make_pair(T1&& a_first, T2&& a_second)
		requires(std::is_constructible_v<T1, T1> && std::is_constructible_v<T2, T2>)
	{
		return BSTTuple{ std::forward<T1>(a_first), std::forward<T2>(a_second) };
	}
}

#if __cpp_lib_format > 0l
namespace std
{
	template <class T1, class T2>
	struct formatter<RE::BSTTuple<T1, T2>>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const RE::BSTTuple<T1, T2>& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "({}, {})"sv, a_value.first, a_value.second);
		}
	};
}
#endif

#if FMT_VERSION > 0l
namespace fmt
{
	template <class T1, class T2>
	struct formatter<RE::BSTTuple<T1, T2>>
		: public formatter<std::string>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const RE::BSTTuple<T1, T2>& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "({}, {})"sv, a_value.first, a_value.second);
		}
	};
}
#endif
