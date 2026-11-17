#pragma once

#include "REX/Contract.hpp"
#include "REX/Hashing.hpp"
#include "REX/Macros.hpp"

namespace REX
{
	template <class Key, class T, std::size_t N, class KeyCompare = std::less<Key>>
	class StaticSortedMap final
	{
	public:
		inline static constexpr auto MAX_SIZE = N;

		static_assert(MAX_SIZE > 0, "`REX::StaticSortedMap` requires a size greater than zero.");

		using key_type = Key;
		using mapped_type = T;
		using value_type = std::pair<key_type, mapped_type>;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using key_compare = KeyCompare;
		using reference = value_type&;
		using const_reference = const value_type&;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using iterator = pointer;
		using const_iterator = const_pointer;
		using reverse_iterator = std::reverse_iterator<iterator>;
		using const_reverse_iterator = std::reverse_iterator<const_iterator>;

		constexpr StaticSortedMap() = delete;

		constexpr ~StaticSortedMap() noexcept(std::is_nothrow_destructible_v<value_type>)
			requires(std::is_destructible_v<value_type>)
		= default;

		constexpr explicit StaticSortedMap(std::array<value_type, MAX_SIZE> a_value)
			noexcept(std::is_nothrow_copy_constructible_v<value_type>)
			requires(std::is_copy_constructible_v<value_type>)
			:
			_data(std::move(a_value))
		{
			EnsureUniqueKeys();
		}

		template <std::input_iterator InputIt>
		constexpr StaticSortedMap(InputIt a_first, InputIt a_last) noexcept(
			std::is_nothrow_default_constructible_v<value_type> && std::is_nothrow_copy_constructible_v<value_type>)
			requires(std::is_default_constructible_v<value_type> && std::is_copy_constructible_v<value_type>)
		{
			std::copy_n(
				a_first,
				std::min(static_cast<size_type>(std::distance(a_first, a_last)), size()),
				_data.data());

			EnsureUniqueKeys();
		}

		template <std::ranges::input_range Range>
		// NOLINTNEXTLINE(misc-explicit-constructor, cppcoreguidelines-missing-std-forward)
		constexpr StaticSortedMap(std::from_range_t /*a_fromRange*/, Range&& a_range) noexcept(
			std::is_nothrow_default_constructible_v<value_type> && std::is_nothrow_copy_constructible_v<value_type>)
			requires(std::is_default_constructible_v<value_type> && std::is_copy_constructible_v<value_type>)
		{
			std::copy_n(
				a_range.begin(),
				std::min(static_cast<size_type>(std::ranges::distance(a_range)), size()),
				_data.data());

			EnsureUniqueKeys();
		}

		constexpr StaticSortedMap(std::initializer_list<value_type> a_value) noexcept(
			std::is_nothrow_default_constructible_v<value_type> && std::is_nothrow_copy_constructible_v<value_type>)
			requires(std::is_default_constructible_v<value_type> && std::is_copy_constructible_v<value_type>)
		{
			std::copy_n(a_value.begin(), std::min(static_cast<size_type>(a_value.size()), size()), _data.data());

			EnsureUniqueKeys();
		}

		constexpr StaticSortedMap(const StaticSortedMap&) noexcept(std::is_nothrow_copy_constructible_v<value_type>)
			requires(std::is_copy_constructible_v<value_type>)
		= default;

		constexpr StaticSortedMap(StaticSortedMap&&) noexcept(std::is_nothrow_move_constructible_v<value_type>)
			requires(std::is_move_constructible_v<value_type>)
		= default;

		constexpr auto operator=(std::array<value_type, MAX_SIZE> a_value)
			noexcept(std::is_nothrow_copy_assignable_v<value_type>) -> StaticSortedMap&
			requires(std::is_copy_assignable_v<value_type>)
		{
			if (this == std::addressof(a_value)) {
				return *this;
			}

			_data = std::move(a_value);

			EnsureUniqueKeys();
			return *this;
		}

		constexpr auto operator=(std::initializer_list<value_type> a_value)
			noexcept(std::is_nothrow_copy_assignable_v<value_type>) -> StaticSortedMap&
			requires(std::is_copy_assignable_v<value_type>)
		{
			if (this == std::addressof(a_value)) {
				return *this;
			}

			std::copy_n(a_value.begin(), std::min(static_cast<size_type>(a_value.size()), size()), _data.data());

			EnsureUniqueKeys();
			return *this;
		}

		constexpr auto operator=(const StaticSortedMap&) noexcept(std::is_nothrow_copy_assignable_v<value_type>)
			-> StaticSortedMap&
			requires(std::is_copy_assignable_v<value_type>)
		= default;

		constexpr auto operator=(StaticSortedMap&&) noexcept(std::is_nothrow_move_assignable_v<value_type>)
			-> StaticSortedMap&
			requires(std::is_move_assignable_v<value_type>)
		= default;

		[[nodiscard]]
		constexpr auto operator[](const key_type& a_key) noexcept -> mapped_type&
		{
			return at(a_key);
		}

		[[nodiscard]]
		constexpr auto operator[](const key_type& a_key) const noexcept -> const mapped_type&
		{
			return at(a_key);
		}

		[[nodiscard]]
		constexpr auto at(const key_type& a_key) noexcept -> mapped_type&
		{
			auto it = find(a_key);
			REX::Assert(it != end());
			return it->second;
		}

		[[nodiscard]]
		constexpr auto at(const key_type& a_key) const noexcept -> const mapped_type&
		{
			const auto it = find(a_key);
			REX::Assert(it != end());
			return it->second;
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
			return _data.size();
		}

		[[nodiscard]]
		constexpr auto max_size() const noexcept -> size_type
		{
			return _data.max_size();
		}

		[[nodiscard]]
		constexpr auto empty() const noexcept -> bool
		{
			return _data.empty();
		}

		[[nodiscard]]
		constexpr auto contains(const key_type& a_key) const noexcept -> bool
		{
			return find(a_key) != end();
		}

		[[nodiscard]]
		constexpr auto find(const key_type& a_key) noexcept -> iterator
		{
			const auto it = std::lower_bound(
				begin(),
				end(),
				a_key,
				[this](const value_type& a_entry, const key_type& a_key) noexcept -> bool {
					return _keyCompare(a_entry.first, a_key);
				});

			if (it == end() || _keyCompare(it->first, a_key)) {
				return end();
			}

			return it;
		}

		[[nodiscard]]
		constexpr auto find(const key_type& a_key) const noexcept -> const_iterator
		{
			const auto it = std::lower_bound(
				begin(),
				end(),
				a_key,
				[this](const value_type& a_entry, const key_type& a_key) noexcept -> bool {
					return _keyCompare(a_entry.first, a_key);
				});

			if (it == end()) {
				return end();
			}

			if (_keyCompare(it->first, a_key) || _keyCompare(a_key, it->first)) {
				return end();
			}

			return it;
		}

		[[nodiscard]]
		constexpr auto equal_range(const key_type& a_key) noexcept -> std::pair<iterator, iterator>
		{
			return std::equal_range(
				begin(),
				end(),
				a_key,
				[this](const value_type& a_entry, const key_type& a_key) noexcept -> bool {
					return _keyCompare(a_entry.first, a_key);
				});
		}

		[[nodiscard]]
		constexpr auto equal_range(const key_type& a_key) const noexcept -> std::pair<const_iterator, const_iterator>
		{
			return std::equal_range(
				begin(),
				end(),
				a_key,
				[this](const value_type& a_entry, const key_type& a_key) noexcept -> bool {
					return _keyCompare(a_entry.first, a_key);
				});
		}

		[[nodiscard]]
		constexpr auto lower_bound(const key_type& a_key) noexcept -> iterator
		{
			return std::lower_bound(
				begin(),
				end(),
				a_key,
				[this](const value_type& a_entry, const key_type& a_key) noexcept -> bool {
					return _keyCompare(a_entry.first, a_key);
				});
		}

		[[nodiscard]]
		constexpr auto lower_bound(const key_type& a_key) const noexcept -> const_iterator
		{
			return std::lower_bound(
				begin(),
				end(),
				a_key,
				[this](const value_type& a_entry, const key_type& a_key) noexcept -> bool {
					return _keyCompare(a_entry.first, a_key);
				});
		}

		[[nodiscard]]
		constexpr auto upper_bound(const key_type& a_key) noexcept -> iterator
		{
			return std::upper_bound(
				begin(),
				end(),
				a_key,
				[this](const key_type& a_key, const value_type& a_entry) noexcept -> bool {
					return _keyCompare(a_key, a_entry.first);
				});
		}

		[[nodiscard]]
		constexpr auto upper_bound(const key_type& a_key) const noexcept -> const_iterator
		{
			return std::upper_bound(
				begin(),
				end(),
				a_key,
				[this](const key_type& a_key, const value_type& a_entry) noexcept -> bool {
					return _keyCompare(a_key, a_entry.first);
				});
		}

		[[nodiscard]]
		constexpr auto count(const key_type& a_key) const noexcept -> size_type
		{
			const auto range = equal_range(a_key);
			return static_cast<size_type>(std::distance(range.first, range.second));
		}

		[[nodiscard]]
		constexpr auto key_comp() const //
			noexcept(std::is_nothrow_copy_constructible_v<key_compare>) -> key_compare
			requires(std::is_copy_constructible_v<key_compare>)
		{
			return _keyCompare;
		}

		constexpr void swap(StaticSortedMap& a_other) noexcept(std::is_nothrow_swappable_v<value_type>)
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(_data, a_other._data);
			std::swap(_keyCompare, a_other._keyCompare);
		}

	private:
		constexpr void EnsureUniqueKeys() noexcept
		{
			std::sort(begin(), end(), [this](const value_type& a_lhs, const value_type& a_rhs) noexcept -> bool {
				return _keyCompare(a_lhs.first, a_rhs.first);
			});

			REX::Assert(
				std::adjacent_find(
					begin(),
					end(),
					[this](const value_type& a_lhs, const value_type& a_rhs) noexcept -> bool {
						return !_keyCompare(a_lhs.first, a_rhs.first) && !_keyCompare(a_rhs.first, a_lhs.first);
					}) == end());
		}

	public:
		// NOLINTBEGIN(readability-identifier-naming)
		std::array<value_type, MAX_SIZE> _data{};
		[[REX_NO_UNIQUE_ADDRESS]]
		key_compare _keyCompare{};
		// NOLINTEND(readability-identifier-naming)
	};

	template <class Key, class T, std::size_t N, class KeyCompare = std::equal_to<Key>>
	StaticSortedMap(std::span<const std::pair<Key, T>, N>, KeyCompare = KeyCompare())
		-> StaticSortedMap<Key, T, N, KeyCompare>;

	template <class Key, class T, std::size_t N, class KeyCompare = std::equal_to<Key>>
	StaticSortedMap(std::array<std::pair<Key, T>, N>, KeyCompare = KeyCompare())
		-> StaticSortedMap<Key, T, N, KeyCompare>;

	template <class... Args>
	[[nodiscard]]
	constexpr auto CreateStaticSortedMap(Args&&... a_args)
		noexcept((std::is_nothrow_convertible_v<Args, std::common_type_t<Args...>> && ...)) -> StaticSortedMap<
			typename std::common_type_t<Args...>::first_type,
			typename std::common_type_t<Args...>::second_type,
			sizeof...(Args)>
		requires(sizeof...(Args) > 0 && (std::is_convertible_v<Args, std::common_type_t<Args...>> && ...))
	{
		return StaticSortedMap(std::array{static_cast<std::common_type_t<Args...>>(std::forward<Args>(a_args))...});
	}

	template <template <class> class KeyCompare, class... Args>
	[[nodiscard]]
	constexpr auto CreateStaticSortedMap(Args&&... a_args)
		noexcept((std::is_nothrow_convertible_v<Args, std::common_type_t<Args...>> && ...)) -> StaticSortedMap<
			typename std::common_type_t<Args...>::first_type,
			typename std::common_type_t<Args...>::second_type,
			sizeof...(Args),
			KeyCompare<typename std::common_type_t<Args...>::first_type>>
		requires(sizeof...(Args) > 0 && (std::is_convertible_v<Args, std::common_type_t<Args...>> && ...))
	{
		return StaticSortedMap(std::array{static_cast<std::common_type_t<Args...>>(std::forward<Args>(a_args))...});
	}
}

namespace std
{
	template <class Key, class T, std::size_t N, class KeyCompare>
	struct hash<REX::StaticSortedMap<Key, T, N, KeyCompare>>
	{
	public:
		[[nodiscard]]
		constexpr auto operator()(const REX::StaticSortedMap<Key, T, N, KeyCompare>& a_key) const noexcept
		{
			return REX::HashRange(a_key);
		}
	};
}

#if (__cpp_lib_format > 0l)
namespace std
{
	template <class Key, class T, std::size_t N, class KeyCompare>
	struct formatter<REX::StaticSortedMap<Key, T, N, KeyCompare>> : public formatter<std::string_view>
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
		constexpr auto format(const REX::StaticSortedMap<Key, T, N, KeyCompare>& a_map, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, a_map._data);
		}
	};
}
#endif

#if (FMT_VERSION > 0l)
namespace fmt
{
	template <class Key, class T, std::size_t N, class KeyCompare>
	struct formatter<REX::StaticSortedMap<Key, T, N, KeyCompare>> : public formatter<std::string_view>
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
		constexpr auto format(const REX::StaticSortedMap<Key, T, N, KeyCompare>& a_map, FormatContext& a_context) const
		{
			using namespace std::string_view_literals;

			return format_to(a_context.out(), "{}"sv, a_map._data);
		}
	};
}
#endif

#if __has_include(<glaze/glaze.hpp>)
namespace glz
{
	template <class Key, class T, std::size_t N, class KeyCompare>
	struct meta<REX::StaticSortedMap<Key, T, N, KeyCompare>>
	{
	public:
		inline static constexpr auto value = [](auto&& a_self) -> decltype(auto) {
			return a_self._data;
		};
	};
}
#endif
