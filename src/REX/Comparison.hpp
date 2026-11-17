#pragma once

#include "REX/Concepts.hpp"
#include "REX/Localization.hpp"

namespace REX
{
	using NumericOrderType = std::int8_t;

	inline constexpr auto NUMERIC_LESS = static_cast<NumericOrderType>(-1);
	inline constexpr auto NUMERIC_EQUAL = static_cast<NumericOrderType>(0);
	inline constexpr auto NUMERIC_GREATER = static_cast<NumericOrderType>(1);
	inline constexpr auto NUMERIC_UNORDERED =
		static_cast<NumericOrderType>(std::numeric_limits<NumericOrderType>::min());

	[[nodiscard]]
	constexpr auto GetNumericStrongOrdering(std::strong_ordering a_ordering) noexcept -> NumericOrderType
	{
		if (a_ordering == std::strong_ordering::less) {
			return NUMERIC_LESS;
		}

		if (a_ordering == std::strong_ordering::greater) {
			return NUMERIC_GREATER;
		}

		return NUMERIC_EQUAL;
	}

	[[nodiscard]]
	constexpr auto GetNumericPartialOrdering(std::partial_ordering a_ordering) noexcept -> NumericOrderType
	{
		if (a_ordering == std::partial_ordering::less) {
			return NUMERIC_LESS;
		}

		if (a_ordering == std::partial_ordering::greater) {
			return NUMERIC_GREATER;
		}

		if (a_ordering == std::partial_ordering::unordered) {
			return NUMERIC_UNORDERED;
		}

		return NUMERIC_EQUAL;
	}

	[[nodiscard]]
	constexpr auto GetNumericWeakOrdering(std::weak_ordering a_ordering) noexcept -> NumericOrderType
	{
		if (a_ordering == std::weak_ordering::less) {
			return NUMERIC_LESS;
		}

		if (a_ordering == std::weak_ordering::greater) {
			return NUMERIC_GREATER;
		}

		return NUMERIC_EQUAL;
	}

	template <REX::character CharT>
	[[nodiscard]]
	constexpr auto IsNullOrEmpty(const CharT* a_value) noexcept -> bool
	{
		return !a_value || a_value[0] == static_cast<CharT>(0);
	}

	template <REX::character CharT>
	[[nodiscard]]
	constexpr auto IsNullOrEmpty(std::basic_string_view<CharT> a_value) noexcept -> bool
	{
		return !a_value.data() || a_value.empty();
	}

	template <REX::win32_character CharT>
	[[nodiscard]]
	constexpr auto IsNullOrWhiteSpace(std::basic_string_view<CharT> a_value) noexcept -> bool
	{
		if (!a_value.data()) {
			return true;
		}

		return std::all_of(a_value.begin(), a_value.end(), [](auto a_char) noexcept -> bool {
			return REX::IsWhiteSpace(a_char);
		});
	}

	template <REX::character CharT>
	[[nodiscard]]
	constexpr auto IsNullTerminated(std::basic_string_view<CharT> a_value) noexcept -> bool
	{
		return a_value.data() && a_value.data()[a_value.size()] == static_cast<CharT>(0);
	}

	template <class T>
	[[nodiscard]]
	constexpr auto Equals(T&& a_lhs, T&& a_rhs) noexcept(nothrow_equality_comparable<std::remove_cvref_t<T>>) -> bool
		requires(equality_comparable<std::remove_cvref_t<T>>)
	{
		return std::forward<T>(a_lhs) == std::forward<T>(a_rhs);
	}

	[[nodiscard]]
	constexpr auto EqualsIgnoreCase(char a_lhs, char a_rhs) noexcept -> bool
	{
		return a_lhs == a_rhs || ToLower(a_lhs) == ToLower(a_rhs);
	}

	[[nodiscard]]
	inline auto EqualsIgnoreCase(wchar_t a_lhs, wchar_t a_rhs) noexcept -> bool
	{
		return a_lhs == a_rhs || std::towlower(a_lhs) == std::towlower(a_rhs);
	}

	template <REX::win32_character CharT>
	[[nodiscard]]
	constexpr auto EqualsIgnoreCase(std::basic_string_view<CharT> a_lhs, std::basic_string_view<CharT> a_rhs) noexcept
		-> bool
	{
		return std::equal(
			a_lhs.begin(),
			a_lhs.end(),
			a_rhs.begin(),
			a_rhs.end(),
			[](auto a_leftChar, auto a_rightChar) noexcept -> bool {
				return EqualsIgnoreCase(a_leftChar, a_rightChar);
			});
	}

	template <class T>
	[[nodiscard]]
	constexpr auto Compare(T&& a_lhs, T&& a_rhs) noexcept(nothrow_three_way_comparable<std::remove_cvref_t<T>>)
		requires(three_way_comparable<std::remove_cvref_t<T>>)
	{
		return std::forward<T>(a_lhs) <=> std::forward<T>(a_rhs);
	}

	[[nodiscard]]
	constexpr auto CompareIgnoreCase(char a_lhs, char a_rhs) noexcept -> auto
	{
		if (a_lhs == a_rhs) {
			return std::strong_ordering::equal;
		}

		return ToLower(a_lhs) <=> ToLower(a_rhs);
	}

	[[nodiscard]]
	inline auto CompareIgnoreCase(wchar_t a_lhs, wchar_t a_rhs) noexcept -> auto
	{
		if (a_lhs == a_rhs) {
			return std::strong_ordering::equal;
		}

		return std::towlower(a_lhs) <=> std::towlower(a_rhs);
	}

	template <REX::win32_character CharT>
	[[nodiscard]]
	constexpr auto CompareIgnoreCase(std::basic_string_view<CharT> a_lhs, std::basic_string_view<CharT> a_rhs) noexcept
		-> auto
	{
		return std::lexicographical_compare_three_way(
			a_lhs.begin(),
			a_lhs.end(),
			a_rhs.begin(),
			a_rhs.end(),
			[](auto a_leftChar, auto a_rightChar) noexcept -> std::strong_ordering {
				return CompareIgnoreCase(a_leftChar, a_rightChar);
			});
	}

	template <REX::character CharT>
	[[nodiscard]]
	constexpr auto Contains(std::basic_string_view<CharT> a_lhs, std::basic_string_view<CharT> a_rhs) noexcept -> bool
	{
		return std::ranges::contains_subrange(a_lhs, a_rhs);
	}

	template <REX::win32_character CharT>
	[[nodiscard]]
	constexpr auto ContainsIgnoreCase(std::basic_string_view<CharT> a_lhs, std::basic_string_view<CharT> a_rhs) noexcept
		-> bool
	{
		return std::ranges::contains_subrange(a_lhs, a_rhs, [](auto a_leftChar, auto a_rightChar) noexcept -> bool {
			return EqualsIgnoreCase(a_leftChar, a_rightChar);
		});
	}

	template <REX::character CharT>
	[[nodiscard]]
	constexpr auto StartsWith(std::basic_string_view<CharT> a_lhs, std::basic_string_view<CharT> a_rhs) noexcept -> bool
	{
		return a_lhs.starts_with(a_rhs);
	}

	template <REX::win32_character CharT>
	[[nodiscard]]
	constexpr auto StartsWithIgnoreCase(std::basic_string_view<CharT> a_lhs, std::basic_string_view<CharT> a_rhs)
		noexcept -> bool
	{
		if (a_rhs.size() > a_lhs.size()) {
			return false;
		}

		return std::equal(
			a_rhs.begin(),
			a_rhs.end(),
			a_lhs.begin(),
			[](auto a_leftChar, auto a_rightChar) noexcept -> bool {
				return EqualsIgnoreCase(a_leftChar, a_rightChar);
			});
	}

	template <REX::character CharT>
	[[nodiscard]]
	constexpr auto EndsWith(std::basic_string_view<CharT> a_lhs, std::basic_string_view<CharT> a_rhs) noexcept -> bool
	{
		return a_lhs.ends_with(a_rhs);
	}

	template <REX::win32_character CharT>
	[[nodiscard]]
	constexpr auto EndsWithIgnoreCase(std::basic_string_view<CharT> a_lhs, std::basic_string_view<CharT> a_rhs) noexcept
		-> bool
	{
		if (a_rhs.size() > a_lhs.size()) {
			return false;
		}

		return std::equal(
			a_rhs.rbegin(),
			a_rhs.rend(),
			a_lhs.rbegin(),
			[](auto a_leftChar, auto a_rightChar) noexcept -> bool {
				return EqualsIgnoreCase(a_leftChar, a_rightChar);
			});
	}

	template <REX::character CharT>
	[[nodiscard]]
	constexpr auto Find(
		std::basic_string_view<CharT> a_lhs,
		std::basic_string_view<CharT> a_rhs,
		std::size_t a_offset = 0) noexcept -> std::size_t
	{
		return a_lhs.find(a_rhs, a_offset);
	}

	template <REX::win32_character CharT>
	[[nodiscard]]
	constexpr auto FindIgnoreCase(
		std::basic_string_view<CharT> a_lhs,
		std::basic_string_view<CharT> a_rhs,
		std::size_t a_offset = 0) noexcept -> std::size_t
	{
		if (a_rhs.empty()) {
			return 0;
		}

		const auto it = std::search(
			a_lhs.begin() + a_offset,
			a_lhs.end(),
			a_rhs.begin(),
			a_rhs.end(),
			[](auto a_leftChar, auto a_rightChar) noexcept -> bool {
				return EqualsIgnoreCase(a_leftChar, a_rightChar);
			});

		if (it == a_lhs.end()) {
			return std::basic_string_view<CharT>::npos;
		}

		return static_cast<std::size_t>(std::distance(a_lhs.begin(), it));
	}

	template <REX::character CharT>
	[[nodiscard]]
	constexpr auto FindLast(
		std::basic_string_view<CharT> a_lhs,
		std::basic_string_view<CharT> a_rhs,
		std::size_t a_offset = std::basic_string_view<CharT>::npos) noexcept -> std::size_t
	{
		return a_lhs.rfind(a_rhs, a_offset);
	}

	template <REX::win32_character CharT>
	[[nodiscard]]
	constexpr auto FindLastIgnoreCase(
		std::basic_string_view<CharT> a_lhs,
		std::basic_string_view<CharT> a_rhs,
		std::size_t a_offset = std::basic_string_view<CharT>::npos) noexcept -> std::size_t
	{
		if (a_rhs.empty()) {
			return a_lhs.size();
		}

		const auto rit = std::search(
			a_lhs.rbegin() + (a_lhs.size() - a_offset - a_rhs.size()),
			a_lhs.rend(),
			a_rhs.rbegin(),
			a_rhs.rend(),
			[](auto a_leftChar, auto a_rightChar) noexcept -> bool {
				return EqualsIgnoreCase(a_leftChar, a_rightChar);
			});

		if (rit == a_lhs.rend()) {
			return std::basic_string_view<CharT>::npos;
		}

		return static_cast<std::size_t>(std::distance(a_lhs.begin(), rit.base() - a_rhs.size()));
	}

	template <REX::character CharT>
	struct StringEqual
	{
	public:
		using is_transparent = void;

		[[nodiscard]]
		constexpr auto operator()(std::basic_string_view<CharT> a_lhs, std::basic_string_view<CharT> a_rhs)
			const noexcept -> bool
		{
			return Equals(a_lhs, a_rhs);
		}
	};

	template <REX::character CharT>
	struct StringLess
	{
	public:
		using is_transparent = void;

		[[nodiscard]]
		constexpr auto operator()(std::basic_string_view<CharT> a_lhs, std::basic_string_view<CharT> a_rhs)
			const noexcept -> bool
		{
			return a_lhs < a_rhs;
		}
	};

	template <REX::character CharT>
	struct StringGreater
	{
	public:
		using is_transparent = void;

		[[nodiscard]]
		constexpr auto operator()(std::basic_string_view<CharT> a_lhs, std::basic_string_view<CharT> a_rhs)
			const noexcept -> bool
		{
			return a_lhs > a_rhs;
		}
	};

	template <REX::win32_character CharT>
	struct StringEqualIgnoreCase
	{
	public:
		using is_transparent = void;

		[[nodiscard]]
		constexpr auto operator()(std::basic_string_view<CharT> a_lhs, std::basic_string_view<CharT> a_rhs)
			const noexcept -> bool
		{
			return EqualsIgnoreCase(a_lhs, a_rhs);
		}
	};

	template <REX::win32_character CharT>
	struct StringLessIgnoreCase
	{
	public:
		using is_transparent = void;

		[[nodiscard]]
		constexpr auto operator()(std::basic_string_view<CharT> a_lhs, std::basic_string_view<CharT> a_rhs)
			const noexcept -> bool
		{
			return CompareIgnoreCase(a_lhs, a_rhs) < 0;
		}
	};

	template <REX::win32_character CharT>
	struct StringGreaterIgnoreCase
	{
	public:
		using is_transparent = void;

		[[nodiscard]]
		constexpr auto operator()(std::basic_string_view<CharT> a_lhs, std::basic_string_view<CharT> a_rhs)
			const noexcept -> bool
		{
			return CompareIgnoreCase(a_lhs, a_rhs) > 0;
		}
	};
}
