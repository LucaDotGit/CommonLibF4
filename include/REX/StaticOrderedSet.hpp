#pragma once

#include "REX/Contract.hpp"

namespace REX
{
	template <class T, std::size_t N, class KeyEqual = std::equal_to<T>>
	struct StaticOrderedSet final
	{
		inline static constexpr auto MAX_SIZE = N;

		using key_type = T;
		using value_type = T;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using key_equal = KeyEqual;
		using reference = value_type&;
		using const_reference = const value_type&;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using iterator = pointer;
		using const_iterator = const_pointer;
		using reverse_iterator = std::reverse_iterator<iterator>;
		using const_reverse_iterator = std::reverse_iterator<const_iterator>;

		static_assert(std::is_copy_constructible_v<value_type>, "`REX::StaticOrderedSet` requires `value_type` to be copy constructible.");
		static_assert(std::is_copy_assignable_v<value_type>, "`REX::StaticOrderedSet` requires `value_type` to be copy assignable.");

		constexpr StaticOrderedSet() = delete;

		constexpr ~StaticOrderedSet() //
			noexcept(std::is_nothrow_destructible_v<value_type>) = default;

		constexpr StaticOrderedSet(const_iterator a_first, const_iterator a_last) //
			noexcept(std::is_nothrow_copy_constructible_v<value_type>)
			: _data{ a_first, a_last }
		{
			REX::Assert(std::distance(a_first, a_last) == size());

			REX::Assert(std::for_each(begin(), end(), [this](const value_type& a_entry) {
				return std::find_if(begin(), end(), [&a_entry, this](const value_type& a_otherEntry) {
					return _keyEqual(a_entry, a_otherEntry);
				}) == end();
			}) == end());
		}

		constexpr StaticOrderedSet(std::span<const value_type, MAX_SIZE> a_value) //
			noexcept(std::is_nothrow_copy_constructible_v<value_type>)
			: _data{ a_value.begin(), a_value.end() }
		{
			REX::Assert(std::for_each(begin(), end(), [this](const value_type& a_entry) {
				return std::find_if(begin(), end(), [&a_entry, this](const value_type& a_otherEntry) {
					return _keyEqual(a_entry, a_otherEntry);
				}) == end();
			}) == end());
		}

		constexpr StaticOrderedSet(std::array<value_type, MAX_SIZE> a_value) //
			noexcept(std::is_nothrow_copy_constructible_v<value_type>)
			: _data(std::move(a_value))
		{
			REX::Assert(std::for_each(begin(), end(), [this](const value_type& a_entry) {
				return std::find_if(begin(), end(), [&a_entry, this](const value_type& a_otherEntry) {
					return _keyEqual(a_entry, a_otherEntry);
				}) == end();
			}) == end());
		}

		constexpr StaticOrderedSet(std::initializer_list<value_type> a_value) //
			noexcept(std::is_default_constructible_v<value_type> &&
					 std::is_nothrow_copy_constructible_v<value_type>)
		{
			REX::Assert(a_value.size() == size());

			std::copy_n(a_value.begin(), size(), _data.data());

			REX::Assert(std::for_each(begin(), end(), [this](const value_type& a_entry) {
				return std::find_if(begin(), end(), [&a_entry, this](const value_type& a_otherEntry) {
					return _keyEqual(a_entry, a_otherEntry);
				}) == end();
			}) == end());
		}

		constexpr StaticOrderedSet(const StaticOrderedSet&) //
			noexcept(std::is_nothrow_copy_constructible_v<value_type>) = default;

		constexpr StaticOrderedSet(StaticOrderedSet&&) //
			noexcept(std::is_nothrow_move_constructible_v<value_type>)
			requires(std::is_move_constructible_v<value_type>)
		= default;

		constexpr StaticOrderedSet& operator=(std::span<const value_type, MAX_SIZE> a_value) //
			noexcept(std::is_nothrow_copy_assignable_v<value_type>)
		{
			std::copy_n(a_value.begin(), size(), _data.data());

			REX::Assert(std::for_each(begin(), end(), [this](const value_type& a_entry) {
				return std::find_if(begin(), end(), [&a_entry, this](const value_type& a_otherEntry) {
					return _keyEqual(a_entry, a_otherEntry);
				}) == end();
			}) == end());

			return *this;
		}

		constexpr StaticOrderedSet& operator=(std::array<value_type, MAX_SIZE> a_value) //
			noexcept(std::is_nothrow_copy_assignable_v<value_type>)
		{
			_data = std::move(a_value);

			REX::Assert(std::for_each(begin(), end(), [this](const value_type& a_entry) {
				return std::find_if(begin(), end(), [&a_entry, this](const value_type& a_otherEntry) {
					return _keyEqual(a_entry, a_otherEntry);
				}) == end();
			}) == end());

			return *this;
		}

		constexpr StaticOrderedSet& operator=(std::initializer_list<value_type> a_value) //
			noexcept(std::is_default_constructible_v<value_type> &&
					 std::is_nothrow_copy_assignable_v<value_type>)
		{
			REX::Assert(a_value.size() == size());

			std::copy_n(a_value.begin(), size(), _data.data());

			REX::Assert(std::for_each(begin(), end(), [this](const value_type& a_entry) {
				return std::find_if(begin(), end(), [&a_entry, this](const value_type& a_otherEntry) {
					return _keyEqual(a_entry, a_otherEntry);
				}) == end();
			}) == end());

			return *this;
		}

		constexpr StaticOrderedSet& operator=(const StaticOrderedSet&) //
			noexcept(std::is_nothrow_copy_assignable_v<value_type>) = default;

		constexpr StaticOrderedSet& operator=(StaticOrderedSet&&) //
			noexcept(std::is_nothrow_move_assignable_v<value_type>)
			requires(std::is_move_assignable_v<value_type>)
		= default;

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
			return std::find_if(begin(), end(), [this, &a_key](const value_type& a_entry) {
				return _keyEqual(a_entry, a_key);
			});
		}

		[[nodiscard]] constexpr const_iterator find(const key_type& a_key) const
		{
			return std::find_if(begin(), end(), [this, &a_key](const value_type& a_entry) {
				return _keyEqual(a_entry, a_key);
			});
		}

		[[nodiscard]] constexpr std::pair<iterator, iterator> equal_range(const key_type& a_key)
		{
			auto it = find(a_key);
			if (it == end()) {
				return std::make_pair(it, it);
			}

			auto nextIt = std::next(it);
			while (nextIt != end() && _keyEqual(nextIt->first, a_key)) {
				nextIt++;
			}

			return std::make_pair(it, nextIt);
		}

		[[nodiscard]] constexpr std::pair<const_iterator, const_iterator> equal_range(const key_type& a_key) const
		{
			const auto it = find(a_key);
			if (it == end()) {
				return std::make_pair(it, it);
			}

			auto nextIt = std::next(it);
			while (nextIt != end() && _keyEqual(nextIt->first, a_key)) {
				nextIt++;
			}

			return std::make_pair(it, nextIt);
		}

		[[nodiscard]] constexpr size_type count(const key_type& a_key) const
		{
			const auto range = equal_range(a_key);
			return static_cast<size_type>(std::distance(range.first, range.second));
		}

		[[nodiscard]] constexpr key_equal key_eq() const //
			noexcept(std::is_nothrow_copy_constructible_v<key_equal>)
			requires(std::is_copy_constructible_v<key_equal>)
		{
			return _keyEqual;
		}

		constexpr void swap(StaticOrderedSet& a_other) //
			noexcept(std::is_nothrow_swappable_v<value_type>)
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap_ranges(begin(), end(), a_other.begin());
			std::swap(_keyEqual, a_other._keyEqual);
		}

		std::array<value_type, MAX_SIZE> _data{};
#if _MSC_VER > 0l
		[[msvc::no_unique_address]]
#else
		[[no_unique_address]]
#endif
		key_equal _keyEqual{};
	};

	template <class T, std::size_t N, class KeyEqual = std::equal_to<T>>
	StaticOrderedSet(std::span<const T, N>, KeyEqual = KeyEqual()) -> StaticOrderedSet<T, N, KeyEqual>;

	template <class T, std::size_t N, class KeyEqual = std::equal_to<T>>
	StaticOrderedSet(std::array<T, N>, KeyEqual = KeyEqual()) -> StaticOrderedSet<T, N, KeyEqual>;

	template <class T, std::size_t N, class KeyEqual = std::equal_to<T>>
	constexpr void swap(StaticOrderedSet<T, N, KeyEqual>& a_lhs, StaticOrderedSet<T, N, KeyEqual>& a_rhs) //
		noexcept(std::is_nothrow_swappable_v<typename StaticOrderedSet<T, N, KeyEqual>::value_type>)
	{
		a_lhs.swap(a_rhs);
	}
}
