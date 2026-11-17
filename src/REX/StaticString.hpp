#pragma once

#include "REX/Contract.hpp"
#include "REX/Hashing.hpp"

namespace REX
{
	// NOLINTBEGIN(modernize-avoid-c-arrays)

	template <class CharT, std::size_t N, class Traits = std::char_traits<CharT>>
	class BasicStaticString final
	{
	public:
		inline static constexpr auto MAX_SIZE = N;
		inline static constexpr auto MAX_SIZE_WITHOUT_NULL = MAX_SIZE - 1;

		static_assert(MAX_SIZE > 0, "`REX::BasicStaticString` requires a size greater than zero.");

		using value_type = CharT;
		using container_type = std::array<value_type, MAX_SIZE>;
		using traits_type = Traits;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using reference = value_type&;
		using const_reference = const value_type&;
		using iterator = pointer;
		using const_iterator = const_pointer;
		using reverse_iterator = std::reverse_iterator<iterator>;
		using const_reverse_iterator = std::reverse_iterator<const_iterator>;

		inline static constexpr auto npos = std::basic_string_view<value_type>::npos;

		constexpr BasicStaticString() noexcept = default;
		constexpr ~BasicStaticString() noexcept = default;

		constexpr BasicStaticString(std::nullptr_t) = delete;

		template <std::size_t N2>
		// NOLINTNEXTLINE(misc-explicit-constructor)
		constexpr BasicStaticString(const value_type (&a_value)[N2]) noexcept
		{
			std::copy_n(static_cast<const value_type*>(a_value), std::min(N2, size()), data());
		}

		constexpr explicit BasicStaticString(std::array<value_type, MAX_SIZE> a_value) noexcept :
			_data(std::move(a_value))
		{
		}

		constexpr BasicStaticString(value_type a_value, size_type a_count) noexcept
		{
			std::fill_n(data(), std::min(a_count, size()), a_value);
		}

		template <std::input_iterator InputIt>
		constexpr BasicStaticString(InputIt a_first, InputIt a_last) noexcept
		{
			std::copy_n(a_first, std::min(static_cast<size_type>(std::distance(a_first, a_last)), size()), data());
		}

		template <std::ranges::input_range Range>
		// NOLINTNEXTLINE(misc-explicit-constructor, cppcoreguidelines-missing-std-forward)
		constexpr BasicStaticString(std::from_range_t /*a_fromRange*/, Range&& a_range) noexcept
		{
			std::copy_n(
				a_range.begin(),
				std::min(static_cast<size_type>(std::ranges::distance(a_range)), size()),
				data());
		}

		constexpr explicit BasicStaticString(std::basic_string_view<value_type> a_value) noexcept
		{
			std::copy_n(a_value.data(), std::min(a_value.size(), size()), data());
		}

		constexpr BasicStaticString(std::initializer_list<value_type> a_value) noexcept
		{
			std::copy_n(a_value.begin(), std::min(static_cast<size_type>(a_value.size()), size()), data());
		}

		constexpr BasicStaticString(const BasicStaticString&) noexcept = default;
		constexpr BasicStaticString(BasicStaticString&&) noexcept = default;

		constexpr auto operator=(std::nullptr_t) -> BasicStaticString& = delete;

		template <std::size_t N2>
		constexpr auto operator=(const value_type (&a_rhs)[N2]) noexcept -> BasicStaticString&
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			std::copy_n(static_cast<const value_type*>(a_rhs), std::min(N2, size()), data());
			return *this;
		}

		constexpr auto operator=(std::array<value_type, MAX_SIZE> a_value) noexcept -> BasicStaticString&
		{
			if (this == std::addressof(a_value)) {
				return *this;
			}

			_data = std::move(a_value);
			return *this;
		}

		constexpr auto operator=(std::basic_string_view<value_type> a_rhs) noexcept -> BasicStaticString&
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			std::copy_n(a_rhs.data(), std::min(a_rhs.size(), size()), data());
			return *this;
		}

		constexpr auto operator=(std::initializer_list<value_type> a_rhs) noexcept -> BasicStaticString&
		{
			if (this == std::addressof(a_rhs)) {
				return *this;
			}

			std::copy_n(a_rhs.begin(), std::min(static_cast<size_type>(a_rhs.size()), size()), data());
			return *this;
		}

		constexpr auto operator=(const BasicStaticString&) noexcept -> BasicStaticString& = default;
		constexpr auto operator=(BasicStaticString&&) noexcept -> BasicStaticString& = default;

		template <std::size_t N2>
		[[nodiscard]]
		constexpr auto operator+(const value_type (&a_rhs)[N2]) const noexcept
		{
			auto result = BasicStaticString<value_type, N + N2 - 1>();
			std::copy_n(data(), size(), result.data());
			std::copy_n(static_cast<const value_type*>(a_rhs), N2, result.data() + size());
			return result;
		}

		template <std::size_t N2>
		[[nodiscard]]
		constexpr auto operator+(const std::array<value_type, N2>& a_rhs) const noexcept
		{
			auto result = BasicStaticString<value_type, N + N2 - 1>();
			std::copy_n(data(), size(), result.data());
			std::copy_n(a_rhs.data(), a_rhs.size(), result.data() + size());
			return result;
		}

		template <std::size_t N2>
		[[nodiscard]]
		constexpr auto operator+(const BasicStaticString<value_type, N2>& a_rhs) const noexcept
		{
			auto result = BasicStaticString<value_type, N + N2 - 1>();
			std::copy_n(data(), size(), result.data());
			std::copy_n(a_rhs.data(), a_rhs.size(), result.data() + size());
			return result;
		}

		[[nodiscard]]
		// NOLINTNEXTLINE(misc-explicit-constructor)
		constexpr operator std::basic_string_view<value_type>() const noexcept
		{
			return {data(), size()};
		}

		[[nodiscard]]
		constexpr auto operator[](size_type a_index) noexcept -> reference
		{
			return at(a_index);
		}

		[[nodiscard]]
		constexpr auto operator[](size_type a_index) const noexcept -> const_reference
		{
			return at(a_index);
		}

		[[nodiscard]]
		constexpr auto at(size_type a_index) noexcept -> reference
		{
			REX::Assert(a_index < size());
			return _data[a_index];
		}

		[[nodiscard]]
		constexpr auto at(size_type a_index) const noexcept -> const_reference
		{
			REX::Assert(a_index < size());
			return _data[a_index];
		}

		[[nodiscard]]
		constexpr auto front() noexcept -> reference
		{
			return _data.front();
		}

		[[nodiscard]]
		constexpr auto front() const noexcept -> const_reference
		{
			return _data.front();
		}

		[[nodiscard]]
		constexpr auto back() noexcept -> reference
		{
			return _data.back();
		}

		[[nodiscard]]
		constexpr auto back() const noexcept -> const_reference
		{
			return _data.back();
		}

		[[nodiscard]]
		constexpr auto data() noexcept -> pointer
		{
			return _data.data();
		}

		[[nodiscard]]
		constexpr auto data() const noexcept -> const_pointer
		{
			return _data.data();
		}

		[[nodiscard]]
		constexpr auto c_str() const noexcept -> const_pointer
		{
			return _data.data();
		}

		[[nodiscard]]
		constexpr auto begin() noexcept -> iterator
		{
			return _data.data();
		}

		[[nodiscard]]
		constexpr auto begin() const noexcept -> const_iterator
		{
			return _data.data();
		}

		[[nodiscard]]
		constexpr auto cbegin() const noexcept -> const_iterator
		{
			return _data.data();
		}

		[[nodiscard]]
		constexpr auto end() noexcept -> iterator
		{
			return _data.data() + size();
		}

		[[nodiscard]]
		constexpr auto end() const noexcept -> const_iterator
		{
			return _data.data() + size();
		}

		[[nodiscard]]
		constexpr auto cend() const noexcept -> const_iterator
		{
			return _data.data() + size();
		}

		[[nodiscard]]
		constexpr auto rbegin() noexcept -> reverse_iterator
		{
			return reverse_iterator(end());
		}

		[[nodiscard]]
		constexpr auto rbegin() const noexcept -> const_reverse_iterator
		{
			return const_reverse_iterator(end());
		}

		[[nodiscard]]
		constexpr auto crbegin() const noexcept -> const_reverse_iterator
		{
			return const_reverse_iterator(cend());
		}

		[[nodiscard]]
		constexpr auto rend() noexcept -> reverse_iterator
		{
			return reverse_iterator(begin());
		}

		[[nodiscard]]
		constexpr auto rend() const noexcept -> const_reverse_iterator
		{
			return const_reverse_iterator(begin());
		}

		[[nodiscard]]
		constexpr auto crend() const noexcept -> const_reverse_iterator
		{
			return const_reverse_iterator(cbegin());
		}

		[[nodiscard]]
		constexpr auto size() const noexcept -> size_type
		{
			return MAX_SIZE_WITHOUT_NULL;
		}

		[[nodiscard]]
		constexpr auto length() const noexcept -> size_type
		{
			return size();
		}

		[[nodiscard]]
		constexpr auto max_size() const noexcept -> size_type
		{
			return size();
		}

		[[nodiscard]]
		constexpr auto empty() const noexcept -> bool
		{
			return size() == 0;
		}

		[[nodiscard]]
		constexpr auto compare(std::basic_string_view<value_type> a_rhs) const noexcept -> std::int32_t
		{
			return std::basic_string_view<value_type>(*this).compare(a_rhs);
		}

		[[nodiscard]]
		constexpr auto contains(std::basic_string_view<value_type> a_value) const noexcept -> bool
		{
			return std::basic_string_view<value_type>(*this).contains(a_value);
		}

		[[nodiscard]]
		constexpr auto contains(value_type a_value) const noexcept -> bool
		{
			return std::basic_string_view<value_type>(*this).contains(a_value);
		}

		[[nodiscard]]
		constexpr auto starts_with(std::basic_string_view<value_type> a_value) const noexcept -> bool
		{
			return std::basic_string_view<value_type>(*this).starts_with(a_value);
		}

		[[nodiscard]]
		constexpr auto starts_with(value_type a_value) const noexcept -> bool
		{
			return std::basic_string_view<value_type>(*this).starts_with(a_value);
		}

		[[nodiscard]]
		constexpr auto ends_with(std::basic_string_view<value_type> a_value) const noexcept -> bool
		{
			return std::basic_string_view<value_type>(*this).ends_with(a_value);
		}

		[[nodiscard]]
		constexpr auto ends_with(value_type a_value) const noexcept -> bool
		{
			return std::basic_string_view<value_type>(*this).ends_with(a_value);
		}

		[[nodiscard]]
		constexpr auto remove_prefix(size_type a_count) const noexcept -> std::basic_string_view<value_type>
		{
			REX::Assert(a_count <= size());
			return std::basic_string_view<value_type>(*this).substr(a_count);
		}

		[[nodiscard]]
		constexpr auto remove_suffix(size_type a_count) const noexcept -> std::basic_string_view<value_type>
		{
			REX::Assert(a_count <= size());
			return std::basic_string_view<value_type>(*this).substr(0, size() - a_count);
		}

		[[nodiscard]]
		constexpr auto copy(pointer a_destination, size_type a_count, size_type a_position = 0) const noexcept
			-> size_type
		{
			REX::Assert(a_position <= size());
			return std::basic_string_view<value_type>(*this).copy(a_destination, a_count, a_position);
		}

		[[nodiscard]]
		constexpr auto substr(size_type a_position = 0, size_type a_count = npos) const noexcept
			-> std::basic_string_view<value_type>
		{
			REX::Assert(a_position <= size());
			return std::basic_string_view<value_type>(*this).substr(a_position, a_count);
		}

		[[nodiscard]]
		constexpr auto subview(size_type a_position = 0, size_type a_count = npos) const noexcept
			-> std::basic_string_view<value_type>
		{
			REX::Assert(a_position <= size());
			return std::basic_string_view<value_type>(*this).substr(a_position, a_count);
		}

		[[nodiscard]]
		constexpr auto find(std::basic_string_view<value_type> a_value, size_type a_position = 0) const noexcept
			-> size_type
		{
			return std::basic_string_view<value_type>(*this).find(a_value, a_position);
		}

		[[nodiscard]]
		constexpr auto find(value_type a_value, size_type a_position = 0) const noexcept -> size_type
		{
			return std::basic_string_view<value_type>(*this).find(a_value, a_position);
		}

		[[nodiscard]]
		constexpr auto rfind(std::basic_string_view<value_type> a_value, size_type a_position = npos) const noexcept
			-> size_type
		{
			return std::basic_string_view<value_type>(*this).rfind(a_value, a_position);
		}

		[[nodiscard]]
		constexpr auto rfind(value_type a_value, size_type a_position = npos) const noexcept -> size_type
		{
			return std::basic_string_view<value_type>(*this).rfind(a_value, a_position);
		}

		[[nodiscard]]
		constexpr auto find_first_of(std::basic_string_view<value_type> a_value, size_type a_position = 0)
			const noexcept -> size_type
		{
			return std::basic_string_view<value_type>(*this).find_first_of(a_value, a_position);
		}

		[[nodiscard]]
		constexpr auto find_first_of(value_type a_value, size_type a_position = 0) const noexcept -> size_type
		{
			return std::basic_string_view<value_type>(*this).find_first_of(a_value, a_position);
		}

		[[nodiscard]]
		constexpr auto find_last_of(std::basic_string_view<value_type> a_value, size_type a_position = npos)
			const noexcept -> size_type
		{
			return std::basic_string_view<value_type>(*this).find_last_of(a_value, a_position);
		}

		[[nodiscard]]
		constexpr auto find_last_of(value_type a_value, size_type a_position = npos) const noexcept -> size_type
		{
			return std::basic_string_view<value_type>(*this).find_last_of(a_value, a_position);
		}

		[[nodiscard]]
		constexpr auto find_first_not_of(std::basic_string_view<value_type> a_value, size_type a_position = 0)
			const noexcept -> size_type
		{
			return std::basic_string_view<value_type>(*this).find_first_not_of(a_value, a_position);
		}

		[[nodiscard]]
		constexpr auto find_first_not_of(value_type a_value, size_type a_position = 0) const noexcept -> size_type
		{
			return std::basic_string_view<value_type>(*this).find_first_not_of(a_value, a_position);
		}

		[[nodiscard]]
		constexpr auto find_last_not_of(std::basic_string_view<value_type> a_value, size_type a_position = npos)
			const noexcept -> size_type
		{
			return std::basic_string_view<value_type>(*this).find_last_not_of(a_value, a_position);
		}

		[[nodiscard]]
		constexpr auto find_last_not_of(value_type a_value, size_type a_position = npos) const noexcept -> size_type
		{
			return std::basic_string_view<value_type>(*this).find_last_not_of(a_value, a_position);
		}

		constexpr void swap(BasicStaticString& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(_data, a_other._data);
		}

		template <size_type Count>
		[[nodiscard]]
		constexpr auto static_remove_prefix() const noexcept
		{
			static_assert(Count <= MAX_SIZE_WITHOUT_NULL);

			auto result = BasicStaticString<value_type, MAX_SIZE - Count>();
			std::copy_n(data() + Count, size() - Count, result.data());
			return result;
		}

		template <size_type Count>
		[[nodiscard]]
		constexpr auto static_remove_suffix() const noexcept
		{
			static_assert(Count <= MAX_SIZE_WITHOUT_NULL);

			auto result = BasicStaticString<value_type, MAX_SIZE - Count>();
			std::copy_n(data(), size() - Count, result.data());
			return result;
		}

		template <size_type Count, size_type Position = 0>
		[[nodiscard]]
		constexpr auto static_copy() const noexcept
		{
			static_assert(Position <= MAX_SIZE_WITHOUT_NULL);
			static_assert(Count <= MAX_SIZE_WITHOUT_NULL - Position);

			auto result = BasicStaticString<value_type, Count + 1>();
			std::copy_n(data() + Position, Count, result.data());
			return result;
		}

		template <size_type Position = 0, size_type Count = npos>
		[[nodiscard]]
		constexpr auto static_substr() const noexcept
		{
			static_assert(Position <= MAX_SIZE_WITHOUT_NULL);
			constexpr auto LENGTH = Count == npos ? MAX_SIZE_WITHOUT_NULL - Position : Count;
			static_assert(LENGTH <= MAX_SIZE_WITHOUT_NULL - Position);

			auto result = BasicStaticString<value_type, LENGTH + 1>();
			std::copy_n(data() + Position, LENGTH, result.data());
			return result;
		}

		template <size_type Position = 0, size_type Count = npos>
		[[nodiscard]]
		constexpr auto static_subview() const noexcept -> std::basic_string_view<value_type>
		{
			static_assert(Position <= MAX_SIZE_WITHOUT_NULL);
			constexpr auto LENGTH = Count == npos ? MAX_SIZE_WITHOUT_NULL - Position : Count;
			static_assert(LENGTH <= MAX_SIZE_WITHOUT_NULL - Position);

			return std::basic_string_view<value_type>{data() + Position, LENGTH};
		}

		// private:
		// NOLINTBEGIN(readability-identifier-naming)
		container_type _data{};
		// NOLINTEND(readability-identifier-naming)
	};

	template <class CharT, std::size_t N>
	BasicStaticString(const CharT (&)[N]) -> BasicStaticString<CharT, N>;

	template <class CharT, std::size_t N>
	BasicStaticString(std::array<CharT, N>) -> BasicStaticString<CharT, N>;

	template <class CharT, std::size_t N>
	BasicStaticString(std::span<const CharT, N>) -> BasicStaticString<CharT, N>;

	template <std::size_t N, class Traits = std::char_traits<char>>
	using StaticString = BasicStaticString<char, N, Traits>;

	template <std::size_t N, class Traits = std::char_traits<wchar_t>>
	using StaticWString = BasicStaticString<wchar_t, N, Traits>;

	template <std::size_t N, class Traits = std::char_traits<char8_t>>
	using StaticU8String = BasicStaticString<char8_t, N, Traits>;

	template <std::size_t N, class Traits = std::char_traits<char16_t>>
	using StaticU16String = BasicStaticString<char16_t, N, Traits>;

	template <std::size_t N, class Traits = std::char_traits<char32_t>>
	using StaticU32String = BasicStaticString<char32_t, N, Traits>;

	template <class CharT, std::size_t N1, std::size_t N2, class Traits>
	[[nodiscard]]
	constexpr auto operator==(
		const BasicStaticString<CharT, N1, Traits>& a_lhs,
		const BasicStaticString<CharT, N2, Traits>& a_rhs) noexcept -> bool
	{
		return std::equal(a_lhs.begin(), a_lhs.end(), a_rhs.begin());
	}

	template <class CharT, std::size_t N1, std::size_t N2, class Traits>
	[[nodiscard]]
	constexpr auto operator==(const BasicStaticString<CharT, N1, Traits>& a_lhs, const CharT (&a_rhs)[N2]) noexcept
		-> bool
	{
		return std::equal(a_lhs.begin(), a_lhs.end(), static_cast<const CharT*>(a_rhs));
	}

	template <class CharT, std::size_t N1, std::size_t N2, class Traits>
	[[nodiscard]]
	constexpr auto operator==(const CharT (&a_lhs)[N1], const BasicStaticString<CharT, N2, Traits>& a_rhs) noexcept
		-> bool
	{
		return std::equal(static_cast<const CharT*>(a_lhs), static_cast<const CharT*>(a_lhs) + N1, a_rhs.begin());
	}

	template <class CharT, std::size_t N1, std::size_t N2, class Traits>
	[[nodiscard]]
	constexpr auto operator==(const BasicStaticString<CharT, N1, Traits>& a_lhs, std::span<const CharT, N2> a_rhs)
		noexcept -> bool
	{
		return std::equal(a_lhs.begin(), a_lhs.end(), a_rhs.begin());
	}

	template <class CharT, std::size_t N1, std::size_t N2, class Traits>
	[[nodiscard]]
	constexpr auto operator==(std::span<const CharT, N1> a_lhs, const BasicStaticString<CharT, N2, Traits>& a_rhs)
		noexcept -> bool
	{
		return std::equal(a_lhs.begin(), a_lhs.end(), a_rhs.begin());
	}

	template <class CharT, std::size_t N1, std::size_t N2, class Traits>
	[[nodiscard]]
	constexpr auto operator==(
		const BasicStaticString<CharT, N1, Traits>& a_lhs,
		const std::array<const CharT, N2>& a_rhs) noexcept -> bool
	{
		return std::equal(a_lhs.begin(), a_lhs.end(), a_rhs.data());
	}

	template <class CharT, std::size_t N1, std::size_t N2, class Traits>
	[[nodiscard]]
	constexpr auto operator==(
		const std::array<const CharT, N1>& a_lhs,
		const BasicStaticString<CharT, N2, Traits>& a_rhs) noexcept -> bool
	{
		return std::equal(a_lhs.begin(), a_lhs.end(), a_rhs.begin());
	}

	template <class CharT, std::size_t N1, std::size_t N2, class Traits>
	[[nodiscard]]
	constexpr auto operator==(const BasicStaticString<CharT, N1, Traits>& a_lhs, std::basic_string_view<CharT> a_rhs)
		noexcept -> bool
	{
		return std::equal(a_lhs.begin(), a_lhs.end(), a_rhs.begin());
	}

	template <class CharT, std::size_t N1, std::size_t N2, class Traits>
	[[nodiscard]]
	constexpr auto operator==(std::basic_string_view<CharT> a_lhs, const BasicStaticString<CharT, N2, Traits>& a_rhs)
		noexcept -> bool
	{
		return std::equal(a_lhs.begin(), a_lhs.end(), a_rhs.begin());
	}

	template <class CharT, std::size_t N1, std::size_t N2, class Traits>
	[[nodiscard]]
	constexpr auto operator<=>(
		const BasicStaticString<CharT, N1, Traits>& a_lhs,
		const BasicStaticString<CharT, N2, Traits>& a_rhs) noexcept
	{
		return std::lexicographical_compare_three_way(a_lhs.begin(), a_lhs.end(), a_rhs.begin(), a_rhs.end());
	}

	template <class CharT, std::size_t N1, std::size_t N2, class Traits>
	[[nodiscard]]
	constexpr auto operator<=>(const BasicStaticString<CharT, N1, Traits>& a_lhs, const CharT (&a_rhs)[N2]) noexcept
		-> auto
	{
		return std::lexicographical_compare_three_way(
			a_lhs.begin(),
			a_lhs.end(),
			static_cast<const CharT*>(a_rhs),
			static_cast<const CharT*>(a_rhs) + N2);
	}

	template <class CharT, std::size_t N1, std::size_t N2, class Traits>
	[[nodiscard]]
	constexpr auto operator<=>(const CharT (&a_lhs)[N1], const BasicStaticString<CharT, N2, Traits>& a_rhs) noexcept
		-> auto
	{
		return std::lexicographical_compare_three_way(
			static_cast<const CharT*>(a_lhs),
			static_cast<const CharT*>(a_lhs) + N1,
			a_rhs.begin(),
			a_rhs.end());
	}

	template <class CharT, std::size_t N1, std::size_t N2, class Traits>
	[[nodiscard]]
	constexpr auto operator<=>(const BasicStaticString<CharT, N1, Traits>& a_lhs, std::span<const CharT, N2> a_rhs)
		noexcept -> auto
	{
		return std::lexicographical_compare_three_way(a_lhs.begin(), a_lhs.end(), a_rhs.begin(), a_rhs.end());
	}

	template <class CharT, std::size_t N1, std::size_t N2, class Traits>
	[[nodiscard]]
	constexpr auto operator<=>(std::span<const CharT, N1> a_lhs, const BasicStaticString<CharT, N2, Traits>& a_rhs)
		noexcept -> auto
	{
		return std::lexicographical_compare_three_way(a_lhs.begin(), a_lhs.end(), a_rhs.begin(), a_rhs.end());
	}

	template <class CharT, std::size_t N1, std::size_t N2, class Traits>
	[[nodiscard]]
	constexpr auto operator<=>(
		const BasicStaticString<CharT, N1, Traits>& a_lhs,
		const std::array<const CharT, N2>& a_rhs) noexcept
	{
		return std::lexicographical_compare_three_way(a_lhs.begin(), a_lhs.end(), a_rhs.begin(), a_rhs.end());
	}

	template <class CharT, std::size_t N1, std::size_t N2, class Traits>
	[[nodiscard]]
	constexpr auto operator<=>(
		const std::array<const CharT, N1>& a_lhs,
		const BasicStaticString<CharT, N2, Traits>& a_rhs) noexcept
	{
		return std::lexicographical_compare_three_way(a_lhs.begin(), a_lhs.end(), a_rhs.begin(), a_rhs.end());
	}

	template <class CharT, std::size_t N1, std::size_t N2, class Traits>
	[[nodiscard]]
	constexpr auto operator<=>(const BasicStaticString<CharT, N1, Traits>& a_lhs, std::basic_string_view<CharT> a_rhs)
		noexcept -> auto
	{
		return std::lexicographical_compare_three_way(a_lhs.begin(), a_lhs.end(), a_rhs.begin(), a_rhs.end());
	}

	template <class CharT, std::size_t N1, std::size_t N2, class Traits>
	[[nodiscard]]
	constexpr auto operator<=>(std::basic_string_view<CharT> a_lhs, const BasicStaticString<CharT, N2, Traits>& a_rhs)
		noexcept -> auto
	{
		return std::lexicographical_compare_three_way(a_lhs.begin(), a_lhs.end(), a_rhs.begin(), a_rhs.end());
	}

	// NOLINTEND(modernize-avoid-c-arrays)
}

namespace std
{
	template <class CharT, std::size_t N, class Traits>
	struct hash<REX::BasicStaticString<CharT, N, Traits>>
	{
	public:
		[[nodiscard]]
		auto operator()(const REX::BasicStaticString<CharT, N, Traits>& a_value) const noexcept -> std::size_t
		{
			return REX::Hash(std::basic_string_view<CharT>(a_value));
		}
	};
}

#if (__cpp_lib_format > 0l)
namespace std
{
	template <class CharT, std::size_t N, class Traits>
	struct formatter<REX::BasicStaticString<CharT, N, Traits>, CharT> :
		public formatter<std::basic_string_view<CharT>, CharT>
	{
	public:
		template <class ParseContext>
		[[nodiscard]]
		constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]]
		constexpr auto format(const REX::BasicStaticString<CharT, N, Traits>& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, std::basic_string_view<CharT>(a_value));
		}
	};
}
#endif

#if (FMT_VERSION > 0l)
namespace fmt
{
	template <class CharT, std::size_t N, class Traits>
	struct formatter<REX::BasicStaticString<CharT, N, Traits>, CharT> :
		public formatter<std::basic_string_view<CharT>, CharT>
	{
	public:
		template <class ParseContext>
		[[nodiscard]]
		constexpr auto parse(ParseContext& a_context) const noexcept
		{
			return a_context.begin();
		}

		template <class FormatContext>
		[[nodiscard]]
		constexpr auto format(const REX::BasicStaticString<CharT, N, Traits>& a_value, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, std::basic_string_view<CharT>(a_value));
		}
	};
}
#endif

#if __has_include(<glaze/glaze.hpp>)
namespace glz
{
	template <class CharT, std::size_t N, class Traits>
	struct meta<REX::BasicStaticString<CharT, N, Traits>>
	{
	public:
		inline static constexpr auto value = [](auto&& a_self) -> decltype(auto) {
			return a_self._data;
		};
	};
}
#endif
