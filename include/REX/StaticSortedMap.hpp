#pragma once

#include "REX/Contract.hpp"

namespace REX
{
	template <class Key, class T, std::size_t N, class KeyCompare = std::less<Key>>
	struct StaticSortedMap final
	{
	public:
		inline static constexpr auto MAX_SIZE = N;

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

		static_assert(std::is_copy_constructible_v<value_type>, "`REX::StaticSortedMap` requires `value_type` to be copy constructible.");
		static_assert(std::is_copy_assignable_v<value_type>, "`REX::StaticSortedMap` requires `value_type` to be copy assignable.");

		constexpr StaticSortedMap() = delete;

		constexpr ~StaticSortedMap() //
			noexcept(std::is_nothrow_destructible_v<value_type>) = default;

		constexpr StaticSortedMap(const_iterator a_first, const_iterator a_last) //
			noexcept(std::is_nothrow_copy_constructible_v<value_type>)
			: _data{ a_first, a_last }
		{
			REX::Assert(std::distance(a_first, a_last) == size());

			std::sort(begin(), end(), [this](const value_type& a_lhs, const value_type& a_rhs) {
				return _keyCompare(a_lhs.first, a_rhs.first);
			});

			REX::Assert(std::adjacent_find(begin(), end(), [this](const value_type& a_lhs, const value_type& a_rhs) {
				return !_keyCompare(a_lhs.first, a_rhs.first) && !_keyCompare(a_rhs.first, a_lhs.first);
			}) == end());
		}

		constexpr StaticSortedMap(std::span<const value_type, MAX_SIZE> a_value) //
			noexcept(std::is_nothrow_copy_constructible_v<value_type>)
			: _data{ a_value.begin(), a_value.end() }
		{
			std::sort(begin(), end(), [this](const value_type& a_lhs, const value_type& a_rhs) {
				return _keyCompare(a_lhs.first, a_rhs.first);
			});

			REX::Assert(std::adjacent_find(begin(), end(), [this](const value_type& a_lhs, const value_type& a_rhs) {
				return !_keyCompare(a_lhs.first, a_rhs.first) && !_keyCompare(a_rhs.first, a_lhs.first);
			}) == end());
		}

		constexpr StaticSortedMap(std::array<value_type, MAX_SIZE> a_value) //
			noexcept(std::is_nothrow_copy_constructible_v<value_type>)
			: _data(std::move(a_value))
		{
			std::sort(begin(), end(), [this](const value_type& a_lhs, const value_type& a_rhs) {
				return _keyCompare(a_lhs.first, a_rhs.first);
			});

			REX::Assert(std::adjacent_find(begin(), end(), [this](const value_type& a_lhs, const value_type& a_rhs) {
				return !_keyCompare(a_lhs.first, a_rhs.first) && !_keyCompare(a_rhs.first, a_lhs.first);
			}) == end());
		}

		constexpr StaticSortedMap(std::initializer_list<value_type> a_value) //
			noexcept(std::is_default_constructible_v<value_type> &&
					 std::is_nothrow_copy_constructible_v<value_type>)
		{
			REX::Assert(a_value.size() == size());

			std::copy_n(a_value.begin(), size(), _data.data());
			std::sort(begin(), end(), [this](const value_type& a_lhs, const value_type& a_rhs) {
				return _keyCompare(a_lhs.first, a_rhs.first);
			});

			REX::Assert(std::adjacent_find(begin(), end(), [this](const value_type& a_lhs, const value_type& a_rhs) {
				return !_keyCompare(a_lhs.first, a_rhs.first) && !_keyCompare(a_rhs.first, a_lhs.first);
			}) == end());
		}

		constexpr StaticSortedMap(const StaticSortedMap&) //
			noexcept(std::is_nothrow_copy_constructible_v<value_type>) = default;

		constexpr StaticSortedMap(StaticSortedMap&&) //
			noexcept(std::is_nothrow_move_constructible_v<value_type>)
			requires(std::is_move_constructible_v<value_type>)
		= default;

		constexpr StaticSortedMap& operator=(std::span<const value_type, MAX_SIZE> a_value) //
			noexcept(std::is_nothrow_copy_assignable_v<value_type>)
		{
			std::copy_n(a_value.begin(), size(), _data.data());
			std::sort(begin(), end(), [this](const value_type& a_lhs, const value_type& a_rhs) {
				return _keyCompare(a_lhs.first, a_rhs.first);
			});

			REX::Assert(std::adjacent_find(begin(), end(), [this](const value_type& a_lhs, const value_type& a_rhs) {
				return !_keyCompare(a_lhs.first, a_rhs.first) && !_keyCompare(a_rhs.first, a_lhs.first);
			}) == end());

			return *this;
		}

		constexpr StaticSortedMap& operator=(std::array<value_type, MAX_SIZE> a_value) //
			noexcept(std::is_nothrow_copy_assignable_v<value_type>)
		{
			_data = std::move(a_value);

			std::sort(begin(), end(), [this](const value_type& a_lhs, const value_type& a_rhs) {
				return _keyCompare(a_lhs.first, a_rhs.first);
			});

			REX::Assert(std::adjacent_find(begin(), end(), [this](const value_type& a_lhs, const value_type& a_rhs) {
				return !_keyCompare(a_lhs.first, a_rhs.first) && !_keyCompare(a_rhs.first, a_lhs.first);
			}) == end());

			return *this;
		}

		constexpr StaticSortedMap& operator=(std::initializer_list<value_type> a_value) //
			noexcept(std::is_default_constructible_v<value_type> &&
					 std::is_nothrow_copy_assignable_v<value_type>)
		{
			REX::Assert(a_value.size() == size());

			std::copy_n(a_value.begin(), size(), _data.data());
			std::sort(begin(), end(), [this](const value_type& a_lhs, const value_type& a_rhs) {
				return _keyCompare(a_lhs.first, a_rhs.first);
			});

			REX::Assert(std::adjacent_find(begin(), end(), [this](const value_type& a_lhs, const value_type& a_rhs) {
				return !_keyCompare(a_lhs.first, a_rhs.first) && !_keyCompare(a_rhs.first, a_lhs.first);
			}) == end());

			return *this;
		}

		constexpr StaticSortedMap& operator=(const StaticSortedMap&) //
			noexcept(std::is_nothrow_copy_assignable_v<value_type>) = default;

		constexpr StaticSortedMap& operator=(StaticSortedMap&&) //
			noexcept(std::is_nothrow_move_assignable_v<value_type>)
			requires(std::is_move_assignable_v<value_type>)
		= default;

		[[nodiscard]] constexpr mapped_type& operator[](const key_type& a_key) { return at(a_key); }
		[[nodiscard]] constexpr const mapped_type& operator[](const key_type& a_key) const { return at(a_key); }

		[[nodiscard]] constexpr mapped_type& at(const key_type& a_key)
		{
			auto it = find(a_key);
			REX::Assert(it != end());
			return it->second;
		}

		[[nodiscard]] constexpr const mapped_type& at(const key_type& a_key) const
		{
			const auto it = find(a_key);
			REX::Assert(it != end());
			return it->second;
		}

		[[nodiscard]] constexpr reference front() noexcept { return _data.front(); }
		[[nodiscard]] constexpr const_reference front() const noexcept { return _data.front(); }

		[[nodiscard]] constexpr reference back() noexcept { return _data.back(); }
		[[nodiscard]] constexpr const_reference back() const noexcept { return _data.back(); }

		[[nodiscard]] constexpr pointer data() noexcept { return _data.data(); }
		[[nodiscard]] constexpr const_pointer data() const noexcept { return _data.data(); }

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

		[[nodiscard]] constexpr size_type size() const noexcept { return _data.size(); }
		[[nodiscard]] constexpr size_type max_size() const noexcept { return _data.max_size(); }

		[[nodiscard]] constexpr bool empty() const noexcept { return _data.empty(); }

		[[nodiscard]] constexpr bool contains(const key_type& a_key) const
		{
			return find(a_key) != end();
		}

		[[nodiscard]] constexpr iterator find(const key_type& a_key)
		{
			const auto it = std::lower_bound(begin(), end(), a_key, [this](const value_type& a_entry, const key_type& a_key) {
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

		[[nodiscard]] constexpr const_iterator find(const key_type& a_key) const
		{
			const auto it = std::lower_bound(begin(), end(), a_key, [this](const value_type& a_entry, const key_type& a_key) {
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

		[[nodiscard]] constexpr std::pair<iterator, iterator> equal_range(const key_type& a_key)
		{
			return std::equal_range(begin(), end(), a_key, [this](const value_type& a_entry, const key_type& a_key) {
				return _keyCompare(a_entry.first, a_key);
			});
		}

		[[nodiscard]] constexpr std::pair<const_iterator, const_iterator> equal_range(const key_type& a_key) const
		{
			return std::equal_range(begin(), end(), a_key, [this](const value_type& a_entry, const key_type& a_key) {
				return _keyCompare(a_entry.first, a_key);
			});
		}

		[[nodiscard]] constexpr iterator lower_bound(const key_type& a_key)
		{
			return std::lower_bound(begin(), end(), a_key, [this](const value_type& a_entry, const key_type& a_key) {
				return _keyCompare(a_entry.first, a_key);
			});
		}

		[[nodiscard]] constexpr const_iterator lower_bound(const key_type& a_key) const
		{
			return std::lower_bound(begin(), end(), a_key, [this](const value_type& a_entry, const key_type& a_key) {
				return _keyCompare(a_entry.first, a_key);
			});
		}

		[[nodiscard]] constexpr iterator upper_bound(const key_type& a_key)
		{
			return std::upper_bound(begin(), end(), a_key, [this](const key_type& a_key, const value_type& a_entry) {
				return _keyCompare(a_key, a_entry.first);
			});
		}

		[[nodiscard]] constexpr const_iterator upper_bound(const key_type& a_key) const
		{
			return std::upper_bound(begin(), end(), a_key, [this](const key_type& a_key, const value_type& a_entry) {
				return _keyCompare(a_key, a_entry.first);
			});
		}

		[[nodiscard]] constexpr size_type count(const key_type& a_key) const
		{
			const auto range = equal_range(a_key);
			return static_cast<size_type>(std::distance(range.first, range.second));
		}

		[[nodiscard]] constexpr key_compare key_comp() const //
			noexcept(std::is_nothrow_copy_constructible_v<key_compare>)
			requires(std::is_copy_constructible_v<key_compare>)
		{
			return _keyCompare;
		}

		constexpr void swap(StaticSortedMap& a_other) //
			noexcept(std::is_nothrow_swappable_v<value_type>)
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap_ranges(begin(), end(), a_other.begin());
			std::swap(_keyCompare, a_other._keyCompare);
		}

		std::array<value_type, MAX_SIZE> _data{};
#if _MSC_VER > 0l
		[[msvc::no_unique_address]]
#else
		[[no_unique_address]]
#endif
		key_compare _keyCompare{};
	};

	template <class Key, class T, std::size_t N, class KeyCompare = std::equal_to<Key>>
	StaticSortedMap(std::span<const std::pair<Key, T>, N>, KeyCompare = KeyCompare()) -> StaticSortedMap<Key, T, N, KeyCompare>;

	template <class Key, class T, std::size_t N, class KeyCompare = std::equal_to<Key>>
	StaticSortedMap(std::array<std::pair<Key, T>, N>, KeyCompare = KeyCompare()) -> StaticSortedMap<Key, T, N, KeyCompare>;

	template <class Key, class T, std::size_t N, class KeyCompare = std::equal_to<Key>>
	constexpr void swap(StaticSortedMap<Key, T, N, KeyCompare>& a_lhs, StaticSortedMap<Key, T, N, KeyCompare>& a_rhs) //
		noexcept(std::is_nothrow_swappable_v<typename StaticSortedMap<Key, T, N, KeyCompare>::value_type>)
	{
		a_lhs.swap(a_rhs);
	}
}
