#pragma once

#include "REX/Concepts.hpp"
#include "REX/Locale.hpp"

namespace REX
{
	template <REX::win32_character T>
	[[nodiscard]] constexpr bool IsNullOrEmpty(const T* a_value) noexcept
	{
		return !a_value || a_value[0] == static_cast<T>(0);
	}

	extern template bool IsNullOrEmpty<char>(const char* a_value) noexcept;
	extern template bool IsNullOrEmpty<wchar_t>(const wchar_t* a_value) noexcept;

	template <REX::win32_character T>
	[[nodiscard]] constexpr bool IsNullOrEmpty(std::basic_string_view<T> a_value) noexcept
	{
		return !a_value.data() || a_value.empty();
	}

	extern template bool IsNullOrEmpty(std::string_view a_value) noexcept;
	extern template bool IsNullOrEmpty(std::wstring_view a_value) noexcept;

	template <REX::win32_character T>
	[[nodiscard]] constexpr bool IsNullOrWhiteSpace(std::basic_string_view<T> a_value) noexcept
	{
		if (!a_value.data()) {
			return true;
		}

		return std::all_of(a_value.begin(), a_value.end(), [](const auto a_char) {
			return REX::IsWhiteSpace(a_char);
		});
	}

	extern template bool IsNullOrWhiteSpace(std::string_view a_value) noexcept;
	extern template bool IsNullOrWhiteSpace(std::wstring_view a_value) noexcept;

	template <REX::win32_character T>
	[[nodiscard]] constexpr bool IsNullTerminated(std::basic_string_view<T> a_value) noexcept
	{
		return a_value.data() && a_value.data()[a_value.size()] == static_cast<T>(0);
	}

	extern template bool IsNullTerminated(std::string_view a_value) noexcept;
	extern template bool IsNullTerminated(std::wstring_view a_value) noexcept;

	[[nodiscard]] constexpr std::int8_t GetNumericStrongOrdering(std::strong_ordering a_ordering) noexcept
	{
		if (a_ordering == std::strong_ordering::less) {
			return -1;
		}

		if (a_ordering == std::strong_ordering::greater) {
			return 1;
		}

		return 0;
	}

	[[nodiscard]] constexpr std::int8_t GetNumericPartialOrdering(std::partial_ordering a_ordering) noexcept
	{
		if (a_ordering == std::partial_ordering::less) {
			return -1;
		}

		if (a_ordering == std::partial_ordering::greater) {
			return 1;
		}

		if (a_ordering == std::partial_ordering::unordered) {
			return std::numeric_limits<std::int8_t>::min();
		}

		return 0;
	}

	[[nodiscard]] constexpr std::int8_t GetNumericWeakOrdering(std::weak_ordering a_ordering) noexcept
	{
		if (a_ordering == std::weak_ordering::less) {
			return -1;
		}

		if (a_ordering == std::weak_ordering::greater) {
			return 1;
		}

		return 0;
	}

	template <class T>
	[[nodiscard]] constexpr bool Equals(T&& a_lhs, T&& a_rhs) //
		noexcept(nothrow_equality_comparable<std::remove_cvref_t<T>>)
		requires(equality_comparable<std::remove_cvref_t<T>>)
	{
		return std::forward<T>(a_lhs) == std::forward<T>(a_rhs);
	}

	[[nodiscard]] constexpr bool EqualsIgnoreCase(char a_lhs, char a_rhs) noexcept
	{
		return ToLower(a_lhs) == ToLower(a_rhs);
	}

	[[nodiscard]] inline bool EqualsIgnoreCase(wchar_t a_lhs, wchar_t a_rhs) noexcept
	{
		return std::towlower(a_lhs) == std::towlower(a_rhs);
	}

	template <REX::win32_character T>
	[[nodiscard]] constexpr bool EqualsIgnoreCase(std::basic_string_view<T> a_lhs, std::basic_string_view<T> a_rhs) noexcept //
	{
		return std::equal(a_lhs.begin(), a_lhs.end(), a_rhs.begin(), a_rhs.end(), [](const auto a_leftChar, const auto a_rightChar) {
			return EqualsIgnoreCase(a_leftChar, a_rightChar);
		});
	}

	extern template bool EqualsIgnoreCase(std::string_view a_left, std::string_view a_right) noexcept;
	extern template bool EqualsIgnoreCase(std::wstring_view a_left, std::wstring_view a_right) noexcept;

	template <class T>
	[[nodiscard]] constexpr auto Compare(T&& a_lhs, T&& a_rhs) //
		noexcept(nothrow_three_way_comparable<std::remove_cvref_t<T>>)
		requires(three_way_comparable<std::remove_cvref_t<T>>)
	{
		return std::forward<T>(a_lhs) <=> std::forward<T>(a_rhs);
	}

	[[nodiscard]] constexpr auto CompareIgnoreCase(char a_lhs, char a_rhs) noexcept
	{
		return ToLower(a_lhs) <=> ToLower(a_rhs);
	}

	[[nodiscard]] inline auto CompareIgnoreCase(wchar_t a_lhs, wchar_t a_rhs) noexcept
	{
		return std::towlower(a_lhs) <=> std::towlower(a_rhs);
	}

	template <REX::win32_character T>
	[[nodiscard]] constexpr auto CompareIgnoreCase(std::basic_string_view<T> a_lhs, std::basic_string_view<T> a_rhs) noexcept //
	{
		return std::lexicographical_compare_three_way(a_lhs.begin(), a_lhs.end(), a_rhs.begin(), a_rhs.end(), [](const auto a_leftChar, const auto a_rightChar) {
			return CompareIgnoreCase(a_leftChar, a_rightChar);
		});
	}

	extern template auto CompareIgnoreCase(std::string_view a_left, std::string_view a_right) noexcept;
	extern template auto CompareIgnoreCase(std::wstring_view a_left, std::wstring_view a_right) noexcept;

	template <class T>
	[[nodiscard]] constexpr bool Contains(std::basic_string_view<T> a_lhs, std::basic_string_view<T> a_rhs) noexcept
	{
		return std::ranges::contains_subrange(a_lhs, a_rhs);
	}

	extern template bool Contains(std::string_view, std::string_view) noexcept;
	extern template bool Contains(std::wstring_view, std::wstring_view) noexcept;

	template <REX::win32_character T>
	[[nodiscard]] constexpr bool ContainsIgnoreCase(std::basic_string_view<T> a_lhs, std::basic_string_view<T> a_rhs) noexcept
	{
		return std::ranges::contains_subrange(a_lhs, a_rhs, [](const auto a_leftChar, const auto a_rightChar) {
			return EqualsIgnoreCase(a_leftChar, a_rightChar);
		});
	}

	extern template bool ContainsIgnoreCase(std::string_view, std::string_view) noexcept;
	extern template bool ContainsIgnoreCase(std::wstring_view, std::wstring_view) noexcept;

	template <class T>
	[[nodiscard]] constexpr bool StartsWith(std::basic_string_view<T> a_lhs, std::basic_string_view<T> a_rhs) noexcept
	{
		return a_lhs.starts_with(a_rhs);
	}

	extern template bool StartsWith(std::string_view, std::string_view) noexcept;
	extern template bool StartsWith(std::wstring_view, std::wstring_view) noexcept;

	template <REX::win32_character T>
	[[nodiscard]] constexpr bool StartsWithIgnoreCase(std::basic_string_view<T> a_lhs, std::basic_string_view<T> a_rhs) noexcept
	{
		if (a_rhs.size() > a_lhs.size()) {
			return false;
		}

		return std::equal(a_rhs.begin(), a_rhs.end(), a_lhs.begin(), [](const auto a_leftChar, const auto a_rightChar) {
			return EqualsIgnoreCase(a_leftChar, a_rightChar);
		});
	}

	extern template bool StartsWithIgnoreCase(std::string_view, std::string_view) noexcept;
	extern template bool StartsWithIgnoreCase(std::wstring_view, std::wstring_view) noexcept;

	template <class T>
	[[nodiscard]] constexpr bool EndsWith(std::basic_string_view<T> a_lhs, std::basic_string_view<T> a_rhs) noexcept
	{
		return a_lhs.ends_with(a_rhs);
	}

	extern template bool EndsWith(std::string_view, std::string_view) noexcept;
	extern template bool EndsWith(std::wstring_view, std::wstring_view) noexcept;

	template <REX::win32_character T>
	[[nodiscard]] constexpr bool EndsWithIgnoreCase(std::basic_string_view<T> a_lhs, std::basic_string_view<T> a_rhs) noexcept
	{
		if (a_rhs.size() > a_lhs.size()) {
			return false;
		}

		return std::equal(a_rhs.rbegin(), a_rhs.rend(), a_lhs.rbegin(), [](const auto a_leftChar, const auto a_rightChar) {
			return EqualsIgnoreCase(a_leftChar, a_rightChar);
		});
	}

	extern template bool EndsWithIgnoreCase(std::string_view, std::string_view) noexcept;
	extern template bool EndsWithIgnoreCase(std::wstring_view, std::wstring_view) noexcept;

	template <class T>
	[[nodiscard]] constexpr std::size_t Find(std::basic_string_view<T> a_lhs, std::basic_string_view<T> a_rhs, std::size_t a_offset = 0) noexcept
	{
		return a_lhs.find(a_rhs, a_offset);
	}

	extern template std::size_t Find(std::string_view, std::string_view, std::size_t) noexcept;
	extern template std::size_t Find(std::wstring_view, std::wstring_view, std::size_t) noexcept;

	template <REX::win32_character T>
	[[nodiscard]] constexpr std::size_t FindIgnoreCase(std::basic_string_view<T> a_lhs, std::basic_string_view<T> a_rhs, std::size_t a_offset = 0) noexcept
	{
		if (a_rhs.empty()) {
			return 0;
		}

		const auto it = std::search(a_lhs.begin() + a_offset, a_lhs.end(), a_rhs.begin(), a_rhs.end(), [](const auto a_leftChar, const auto a_rightChar) {
			return EqualsIgnoreCase(a_leftChar, a_rightChar);
		});

		if (it == a_lhs.end()) {
			return std::basic_string_view<T>::npos;
		}

		return static_cast<std::size_t>(std::distance(a_lhs.begin(), it));
	}

	extern template std::size_t FindIgnoreCase(std::string_view, std::string_view, std::size_t) noexcept;
	extern template std::size_t FindIgnoreCase(std::wstring_view, std::wstring_view, std::size_t) noexcept;

	template <class T>
	[[nodiscard]] constexpr std::size_t FindLast(std::basic_string_view<T> a_lhs, std::basic_string_view<T> a_rhs, std::size_t a_offset = std::basic_string_view<T>::npos) noexcept
	{
		return a_lhs.rfind(a_rhs, a_offset);
	}

	extern template std::size_t FindLast(std::string_view, std::string_view, std::size_t) noexcept;
	extern template std::size_t FindLast(std::wstring_view, std::wstring_view, std::size_t) noexcept;

	template <REX::win32_character T>
	[[nodiscard]] constexpr std::size_t FindLastIgnoreCase(std::basic_string_view<T> a_lhs, std::basic_string_view<T> a_rhs, std::size_t a_offset = std::basic_string_view<T>::npos) noexcept
	{
		if (a_rhs.empty()) {
			return a_lhs.size();
		}

		const auto rit = std::search(a_lhs.rbegin() + (a_lhs.size() - a_offset - a_rhs.size()), a_lhs.rend(), a_rhs.rbegin(), a_rhs.rend(), [](const auto a_leftChar, const auto a_rightChar) {
			return EqualsIgnoreCase(a_leftChar, a_rightChar);
		});

		if (rit == a_lhs.rend()) {
			return std::basic_string_view<T>::npos;
		}

		return static_cast<std::size_t>(std::distance(a_lhs.begin(), rit.base() - a_rhs.size()));
	}

	extern template std::size_t FindLastIgnoreCase(std::string_view, std::string_view, std::size_t) noexcept;
	extern template std::size_t FindLastIgnoreCase(std::wstring_view, std::wstring_view, std::size_t) noexcept;

	class LessIgnoreCase final
	{
	public:
		template <class T>
		[[nodiscard]] constexpr bool operator()(const T& a_lhs, const T& a_rhs) const //
			noexcept(REX::nothrow_three_way_comparable<T> && std::is_nothrow_convertible_v<T, std::basic_string_view<typename T::value_type>>)
			requires(REX::three_way_comparable<T> && std::is_convertible_v<T, std::basic_string_view<typename T::value_type>>)
		{
			const auto leftView = static_cast<std::basic_string_view<typename T::value_type>>(a_lhs);
			const auto rightView = static_cast<std::basic_string_view<typename T::value_type>>(a_rhs);
			return CompareIgnoreCase(leftView, rightView) < 0;
		}
	};

	extern template bool LessIgnoreCase::operator()(const std::string_view&, const std::string_view&) const noexcept;
	extern template bool LessIgnoreCase::operator()(const std::wstring_view&, const std::wstring_view&) const noexcept;
	extern template bool LessIgnoreCase::operator()(const std::string&, const std::string&) const noexcept;
	extern template bool LessIgnoreCase::operator()(const std::wstring&, const std::wstring&) const noexcept;

	class GreaterIgnoreCase final
	{
	public:
		template <class T>
		[[nodiscard]] constexpr bool operator()(const T& a_lhs, const T& a_rhs) const //
			noexcept(REX::nothrow_three_way_comparable<T> && std::is_nothrow_convertible_v<T, std::basic_string_view<typename T::value_type>>)
			requires(REX::three_way_comparable<T> && std::is_convertible_v<T, std::basic_string_view<typename T::value_type>>)
		{
			const auto leftView = static_cast<std::basic_string_view<typename T::value_type>>(a_lhs);
			const auto rightView = static_cast<std::basic_string_view<typename T::value_type>>(a_rhs);
			return CompareIgnoreCase(leftView, rightView) > 0;
		}
	};

	extern template bool GreaterIgnoreCase::operator()(const std::string_view&, const std::string_view&) const noexcept;
	extern template bool GreaterIgnoreCase::operator()(const std::wstring_view&, const std::wstring_view&) const noexcept;
	extern template bool GreaterIgnoreCase::operator()(const std::string&, const std::string&) const noexcept;
	extern template bool GreaterIgnoreCase::operator()(const std::wstring&, const std::wstring&) const noexcept;
}
