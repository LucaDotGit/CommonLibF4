#pragma once

#include "REX/Contract.hpp"
#include "REX/Hash.hpp"

namespace REX
{
	// NOLINTBEGIN(modernize-avoid-c-arrays)

	template <class CharT, std::size_t N>
	struct StaticString final
	{
	public:
		inline static constexpr auto MAX_SIZE = N;

		using value_type = CharT;
		using container_type = std::array<value_type, MAX_SIZE>;
		using traits_type = std::char_traits<value_type>;
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

		constexpr StaticString() noexcept = default;
		constexpr ~StaticString() noexcept = default;

		constexpr StaticString(std::nullptr_t) = delete;

		constexpr StaticString(value_type a_fillChar) noexcept
		{
			std::fill_n(data(), size(), a_fillChar);
		}

		constexpr StaticString(const value_type (&a_value)[N]) noexcept
		{
			std::copy_n(static_cast<const value_type*>(a_value), size(), data());
		}

		constexpr StaticString(const_iterator a_first, const_iterator a_last) noexcept
		{
			REX::Assert(std::distance(a_first, a_last) == size());
			std::copy_n(a_first, size(), data());
		}

		constexpr StaticString(std::span<const value_type, MAX_SIZE> a_value) noexcept
		{
			std::copy_n(a_value.begin(), size(), data());
		}

		constexpr StaticString(std::array<value_type, MAX_SIZE> a_value) noexcept
			: _data(std::move(a_value))
		{
		}

		constexpr StaticString(std::initializer_list<value_type> a_value) noexcept
		{
			REX::Assert(a_value.size() == size());
			std::copy_n(a_value.begin(), size(), data());
		}

		constexpr StaticString(const StaticString&) noexcept = default;
		constexpr StaticString(StaticString&&) noexcept = default;

		constexpr StaticString& operator=(std::nullptr_t) = delete;

		constexpr StaticString& operator=(const value_type (&a_rhs)[N]) noexcept
		{
			std::copy_n(static_cast<const value_type*>(a_rhs), size(), data());
			return *this;
		}

		constexpr StaticString& operator=(std::array<value_type, MAX_SIZE> a_rhs) noexcept
		{
			_data = std::move(a_rhs);
			return *this;
		}

		constexpr StaticString& operator=(std::span<const value_type, MAX_SIZE> a_rhs) noexcept
		{
			std::copy_n(a_rhs.begin(), size(), data());
			return *this;
		}

		constexpr StaticString& operator=(std::initializer_list<value_type> a_rhs) noexcept
		{
			REX::Assert(a_rhs.size() == size());
			std::copy_n(a_rhs.begin(), size(), data());
			return *this;
		}

		constexpr StaticString& operator=(const StaticString&) noexcept = default;
		constexpr StaticString& operator=(StaticString&&) noexcept = default;

		template <std::size_t N2>
		[[nodiscard]] constexpr auto operator+(const StaticString<value_type, N2>& a_rhs) const noexcept
		{
			auto result = StaticString<value_type, N + N2 - 1>();
			std::copy_n(data(), size(), result.data());
			std::copy_n(a_rhs.data(), a_rhs.size(), result.data() + size());
			return result;
		}

		template <std::size_t N2>
		[[nodiscard]] constexpr auto operator+(const value_type (&a_rhs)[N2]) const noexcept
		{
			auto result = StaticString<value_type, N + N2 - 1>();
			std::copy_n(data(), size(), result.data());
			std::copy_n(static_cast<const value_type*>(a_rhs), N2, result.data() + size());
			return result;
		}

		template <std::size_t N2>
		[[nodiscard]] constexpr auto operator+(std::span<const value_type, N2> a_rhs) const noexcept
		{
			auto result = StaticString<value_type, N + N2 - 1>();
			std::copy_n(data(), size(), result.data());
			std::copy_n(a_rhs.begin(), a_rhs.size(), result.data() + size());
			return result;
		}

		template <std::size_t N2>
		[[nodiscard]] constexpr auto operator+(const std::array<value_type, N2>& a_rhs) const noexcept
		{
			auto result = StaticString<value_type, N + N2 - 1>();
			std::copy_n(data(), size(), result.data());
			std::copy_n(a_rhs.data(), a_rhs.size(), result.data() + size());
			return result;
		}

		[[nodiscard]] constexpr operator std::basic_string_view<value_type>() const noexcept { return { data(), size() }; }

		[[nodiscard]] constexpr reference operator[](size_type a_index) noexcept { return at(a_index); }
		[[nodiscard]] constexpr const_reference operator[](size_type a_index) const noexcept { return at(a_index); }

		[[nodiscard]] constexpr reference at(size_type a_index) noexcept
		{
			REX::Assert(a_index < size());
			return _data[a_index];
		}

		[[nodiscard]] constexpr const_reference at(size_type a_index) const noexcept
		{
			REX::Assert(a_index < size());
			return _data[a_index];
		}

		[[nodiscard]] constexpr reference front() noexcept { return _data.front(); }
		[[nodiscard]] constexpr const_reference front() const noexcept { return _data.front(); }

		[[nodiscard]] constexpr reference back() noexcept { return _data.front() + size(); }
		[[nodiscard]] constexpr const_reference back() const noexcept { return _data.front() + size(); }

		[[nodiscard]] constexpr pointer data() noexcept { return _data.data(); }
		[[nodiscard]] constexpr const_pointer data() const noexcept { return _data.data(); }

		[[nodiscard]] constexpr const_pointer c_str() const noexcept { return _data.data(); }

		[[nodiscard]] constexpr iterator begin() noexcept { return _data.data(); }
		[[nodiscard]] constexpr const_iterator begin() const noexcept { return _data.data(); }
		[[nodiscard]] constexpr const_iterator cbegin() const noexcept { return _data.data(); }

		[[nodiscard]] constexpr iterator end() noexcept { return _data.data() + size(); }
		[[nodiscard]] constexpr const_iterator end() const noexcept { return _data.data() + size(); }
		[[nodiscard]] constexpr const_iterator cend() const noexcept { return _data.data() + size(); }

		[[nodiscard]] constexpr reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
		[[nodiscard]] constexpr const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
		[[nodiscard]] constexpr const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(cend()); }

		[[nodiscard]] constexpr reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
		[[nodiscard]] constexpr const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }
		[[nodiscard]] constexpr const_reverse_iterator crend() const noexcept { return const_reverse_iterator(cbegin()); }

		[[nodiscard]] constexpr size_type size() const noexcept { return MAX_SIZE - 1; }
		[[nodiscard]] constexpr size_type length() const noexcept { return size(); }
		[[nodiscard]] constexpr size_type max_size() const noexcept { return size(); }

		[[nodiscard]] constexpr bool empty() const noexcept { return _data.empty(); }

		template <std::size_t Pos = 0, std::size_t Count = npos>
		[[nodiscard]] constexpr auto substr() const noexcept
		{
			constexpr auto LENGTH = Count == npos ? MAX_SIZE - Pos : Count;

			static_assert(Pos < MAX_SIZE);
			static_assert(Pos + LENGTH <= MAX_SIZE);

			auto result = StaticString<value_type, LENGTH>();
			std::copy_n(data() + Pos, LENGTH, result.data());
			return result;
		}

		constexpr void swap(StaticString& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(_data, a_other._data);
		}

		container_type _data{};
	};

	template <class CharT, std::size_t N>
	StaticString(const CharT (&)[N]) -> StaticString<CharT, N>;

	template <class CharT, std::size_t N>
	StaticString(std::span<const CharT, N>) -> StaticString<CharT, N>;

	template <class CharT, std::size_t N>
	StaticString(std::array<CharT, N>) -> StaticString<CharT, N>;

	template <class CharT, std::size_t N>
	[[nodiscard]] constexpr bool operator==(const StaticString<CharT, N>& a_lhs, const StaticString<CharT, N>& a_rhs) noexcept
	{
		return std::equal(a_lhs.begin(), a_lhs.end(), a_rhs.begin());
	}

	template <class CharT, std::size_t N>
	[[nodiscard]] constexpr bool operator==(const StaticString<CharT, N>& a_lhs, const CharT (&a_rhs)[N]) noexcept
	{
		return std::equal(a_lhs.begin(), a_lhs.end(), static_cast<const CharT*>(a_rhs));
	}

	template <class CharT, std::size_t N>
	[[nodiscard]] constexpr bool operator==(const CharT (&a_lhs)[N], const StaticString<CharT, N>& a_rhs) noexcept
	{
		return std::equal(static_cast<const CharT*>(a_lhs), static_cast<const CharT*>(a_lhs) + N, a_rhs.begin());
	}

	template <class CharT, std::size_t N>
	[[nodiscard]] constexpr bool operator==(const StaticString<CharT, N>& a_lhs, std::span<const CharT, N> a_rhs) noexcept
	{
		return std::equal(a_lhs.begin(), a_lhs.end(), a_rhs.data());
	}

	template <class CharT, std::size_t N>
	[[nodiscard]] constexpr bool operator==(std::span<const CharT, N> a_lhs, const StaticString<CharT, N>& a_rhs) noexcept
	{
		return std::equal(a_lhs.begin(), a_lhs.end(), a_rhs.begin());
	}

	template <class CharT, std::size_t N>
	[[nodiscard]] constexpr bool operator==(const StaticString<CharT, N>& a_lhs, const std::array<const CharT, N>& a_rhs) noexcept
	{
		return std::equal(a_lhs.begin(), a_lhs.end(), a_rhs.data());
	}

	template <class CharT, std::size_t N>
	[[nodiscard]] constexpr bool operator==(const std::array<const CharT, N>& a_lhs, const StaticString<CharT, N>& a_rhs) noexcept
	{
		return std::equal(a_lhs.begin(), a_lhs.end(), a_rhs.begin());
	}

	template <class CharT, std::size_t N>
	[[nodiscard]] constexpr bool operator==(const StaticString<CharT, N>& a_lhs, std::basic_string_view<CharT> a_rhs) noexcept
	{
		return std::equal(a_lhs.begin(), a_lhs.end(), a_rhs.begin());
	}

	template <class CharT, std::size_t N>
	[[nodiscard]] constexpr bool operator==(std::basic_string_view<CharT> a_lhs, const StaticString<CharT, N>& a_rhs) noexcept
	{
		return std::equal(a_lhs.begin(), a_lhs.end(), a_rhs.begin());
	}

	template <class CharT, std::size_t N>
	[[nodiscard]] constexpr auto operator<=>(const StaticString<CharT, N>& a_lhs, const StaticString<CharT, N>& a_rhs) noexcept
	{
		return std::lexicographical_compare_three_way(
			a_lhs.begin(), a_lhs.end(), a_rhs.begin(), a_rhs.end());
	}

	template <class CharT, std::size_t N>
	[[nodiscard]] constexpr auto operator<=>(const StaticString<CharT, N>& a_lhs, const CharT (&a_rhs)[N]) noexcept
	{
		return std::lexicographical_compare_three_way(
			a_lhs.begin(), a_lhs.end(), static_cast<const CharT*>(a_rhs), static_cast<const CharT*>(a_rhs) + N);
	}

	template <class CharT, std::size_t N>
	[[nodiscard]] constexpr auto operator<=>(const CharT (&a_lhs)[N], const StaticString<CharT, N>& a_rhs) noexcept
	{
		return std::lexicographical_compare_three_way(
			static_cast<const CharT*>(a_lhs), static_cast<const CharT*>(a_lhs) + N, a_rhs.begin(), a_rhs.end());
	}

	template <class CharT, std::size_t N>
	[[nodiscard]] constexpr auto operator<=>(const StaticString<CharT, N>& a_lhs, std::span<const CharT, N> a_rhs) noexcept
	{
		return std::lexicographical_compare_three_way(
			a_lhs.begin(), a_lhs.end(), a_rhs.begin(), a_rhs.end());
	}

	template <class CharT, std::size_t N>
	[[nodiscard]] constexpr auto operator<=>(std::span<const CharT, N> a_lhs, const StaticString<CharT, N>& a_rhs) noexcept
	{
		return std::lexicographical_compare_three_way(
			a_lhs.begin(), a_lhs.end(), a_rhs.begin(), a_rhs.end());
	}

	template <class CharT, std::size_t N>
	[[nodiscard]] constexpr auto operator<=>(const StaticString<CharT, N>& a_lhs, const std::array<const CharT, N>& a_rhs) noexcept
	{
		return std::lexicographical_compare_three_way(
			a_lhs.begin(), a_lhs.end(), a_rhs.begin(), a_rhs.end());
	}

	template <class CharT, std::size_t N>
	[[nodiscard]] constexpr auto operator<=>(const std::array<const CharT, N>& a_lhs, const StaticString<CharT, N>& a_rhs) noexcept
	{
		return std::lexicographical_compare_three_way(
			a_lhs.begin(), a_lhs.end(), a_rhs.begin(), a_rhs.end());
	}

	template <class CharT, std::size_t N>
	[[nodiscard]] constexpr auto operator<=>(const StaticString<CharT, N>& a_lhs, std::basic_string_view<CharT> a_rhs) noexcept
	{
		return std::lexicographical_compare_three_way(
			a_lhs.begin(), a_lhs.end(), a_rhs.begin(), a_rhs.end());
	}

	template <class CharT, std::size_t N>
	[[nodiscard]] constexpr auto operator<=>(std::basic_string_view<CharT> a_lhs, const StaticString<CharT, N>& a_rhs) noexcept
	{
		return std::lexicographical_compare_three_way(
			a_lhs.begin(), a_lhs.end(), a_rhs.begin(), a_rhs.end());
	}

	// NOLINTEND(modernize-avoid-c-arrays)

	template <class CharT, std::size_t N>
	constexpr void swap(StaticString<CharT, N>& a_lhs, StaticString<CharT, N>& a_rhs) noexcept
	{
		a_lhs.swap(a_rhs);
	}
}

namespace std
{
	template <class CharT, std::size_t N>
	struct hash<REX::StaticString<CharT, N>>
	{
	public:
		[[nodiscard]] std::size_t operator()(const REX::StaticString<CharT, N>& a_value) const noexcept
		{
			return REX::Hash(static_cast<std::basic_string_view<CharT>>(a_value));
		}
	};
}

#if __cpp_lib_format > 0l
namespace std
{
	template <class CharT, std::size_t N>
	struct formatter<REX::StaticString<CharT, N>, CharT>
		: public formatter<std::basic_string_view<CharT>, CharT>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_ctx) const
		{
			return a_ctx.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const REX::StaticString<CharT, N>& a_value, FormatContext& a_ctx) const
		{
			using namespace std::string_view_literals;

			return format_to(a_ctx.out(), "{}"sv, static_cast<std::basic_string_view<CharT>>(a_value));
		}
	};
}
#endif

#if FMT_VERSION > 0l
namespace fmt
{
	template <class CharT, std::size_t N>
	struct formatter<REX::StaticString<CharT, N>, CharT>
		: public formatter<std::basic_string_view<CharT>, CharT>
	{
	public:
		template <class ParseContext>
		[[nodiscard]] constexpr auto parse(ParseContext& a_ctx) const
		{
			return a_ctx.begin();
		}

		template <class FormatContext>
		[[nodiscard]] constexpr auto format(const REX::StaticString<CharT, N>& a_value, FormatContext& a_ctx) const
		{
			using namespace std::string_view_literals;

			return format_to(a_ctx.out(), "{}"sv, static_cast<std::basic_string_view<CharT>>(a_value));
		}
	};
}
#endif
