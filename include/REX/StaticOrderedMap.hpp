#pragma once

#include "REX/Contract.hpp"

namespace REX
{
	template <class Key, class T, std::size_t N, class KeyEqual = std::equal_to<Key>>
	struct StaticOrderedMap final
	{
	public:
		inline static constexpr auto MAX_SIZE = N;

		using key_type = Key;
		using mapped_type = T;
		using value_type = std::pair<key_type, mapped_type>;
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

		static_assert(std::is_copy_constructible_v<value_type>, "`REX::StaticOrderedMap` requires `value_type` to be copy constructible.");
		static_assert(std::is_copy_assignable_v<value_type>, "`REX::StaticOrderedMap` requires `value_type` to be copy assignable.");

		constexpr StaticOrderedMap() = delete;

		constexpr ~StaticOrderedMap() //
			noexcept(std::is_nothrow_destructible_v<value_type>) = default;

		constexpr StaticOrderedMap(const_iterator a_first, const_iterator a_last) //
			noexcept(std::is_nothrow_copy_constructible_v<value_type>)
		{
			std::copy_n(a_first, std::min(static_cast<size_type>(std::distance(a_first, a_last)), MAX_SIZE), _data.data());

			REX::Assert(std::for_each(begin(), end(), [this](const value_type& a_entry) -> auto {
				return std::find_if(begin(), end(), [&a_entry, this](const value_type& a_otherEntry) -> auto {
					return _keyEqual(a_entry.first, a_otherEntry.first);
				}) == end();
			}) == end());
		}

		constexpr StaticOrderedMap(std::span<const value_type, MAX_SIZE> a_value) //
			noexcept(std::is_nothrow_copy_constructible_v<value_type>)
			: _data{ a_value.begin(), a_value.end() }
		{
			REX::Assert(std::for_each(begin(), end(), [this](const value_type& a_entry) -> auto {
				return std::find_if(begin(), end(), [&a_entry, this](const value_type& a_otherEntry) -> auto {
					return _keyEqual(a_entry.first, a_otherEntry.first);
				}) == end();
			}) == end());
		}

		constexpr StaticOrderedMap(std::array<value_type, MAX_SIZE> a_value) //
			noexcept(std::is_nothrow_copy_constructible_v<value_type>)
			: _data(std::move(a_value))
		{
			REX::Assert(std::for_each(begin(), end(), [this](const value_type& a_entry) -> auto {
				return std::find_if(begin(), end(), [&a_entry, this](const value_type& a_otherEntry) -> auto {
					return _keyEqual(a_entry.first, a_otherEntry.first);
				}) == end();
			}) == end());
		}

		constexpr StaticOrderedMap(std::initializer_list<value_type> a_value) //
			noexcept(std::is_default_constructible_v<value_type> &&
					 std::is_nothrow_copy_constructible_v<value_type>)
		{
			std::copy_n(a_value.begin(), std::min(static_cast<size_type>(a_value.size()), MAX_SIZE), _data.data());

			REX::Assert(std::for_each(begin(), end(), [this](const value_type& a_entry) -> auto {
				return std::find_if(begin(), end(), [&a_entry, this](const value_type& a_otherEntry) -> auto {
					return _keyEqual(a_entry.first, a_otherEntry.first);
				}) == end();
			}) == end());
		}

		constexpr StaticOrderedMap(const StaticOrderedMap&) //
			noexcept(std::is_nothrow_copy_constructible_v<value_type>) = default;

		constexpr StaticOrderedMap(StaticOrderedMap&&) //
			noexcept(std::is_nothrow_move_constructible_v<value_type>)
			requires(std::is_move_constructible_v<value_type>)
		= default;

		constexpr StaticOrderedMap& operator=(std::span<const value_type, MAX_SIZE> a_value) //
			noexcept(std::is_nothrow_copy_assignable_v<value_type>)
		{
			std::copy_n(a_value.begin(), size(), _data.data());

			REX::Assert(std::for_each(begin(), end(), [this](const value_type& a_entry) -> auto {
				return std::find_if(begin(), end(), [&a_entry, this](const value_type& a_otherEntry) -> auto {
					return _keyEqual(a_entry.first, a_otherEntry.first);
				}) == end();
			}) == end());

			return *this;
		}

		constexpr StaticOrderedMap& operator=(std::array<value_type, MAX_SIZE> a_value) //
			noexcept(std::is_nothrow_copy_assignable_v<value_type>)
		{
			_data = std::move(a_value);

			REX::Assert(std::for_each(begin(), end(), [this](const value_type& a_entry) -> auto {
				return std::find_if(begin(), end(), [&a_entry, this](const value_type& a_otherEntry) -> auto {
					return _keyEqual(a_entry.first, a_otherEntry.first);
				}) == end();
			}) == end());

			return *this;
		}

		constexpr StaticOrderedMap& operator=(std::initializer_list<value_type> a_value) //
			noexcept(std::is_default_constructible_v<value_type> &&
					 std::is_nothrow_copy_assignable_v<value_type>)
		{
			std::copy_n(a_value.begin(), std::min(static_cast<size_type>(a_value.size()), MAX_SIZE), _data.data());

			REX::Assert(std::for_each(begin(), end(), [this](const value_type& a_entry) -> auto {
				return std::find_if(begin(), end(), [&a_entry, this](const value_type& a_otherEntry) -> auto {
					return _keyEqual(a_entry.first, a_otherEntry.first);
				}) == end();
			}) == end());

			return *this;
		}

		constexpr StaticOrderedMap& operator=(const StaticOrderedMap&) //
			noexcept(std::is_nothrow_copy_assignable_v<value_type>) = default;

		constexpr StaticOrderedMap& operator=(StaticOrderedMap&&) //
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
			return std::find_if(begin(), end(), [this, &a_key](const value_type& a_entry) -> auto {
				return _keyEqual(a_entry.first, a_key);
			});
		}

		[[nodiscard]] constexpr const_iterator find(const key_type& a_key) const
		{
			return std::find_if(begin(), end(), [this, &a_key](const value_type& a_entry) -> auto {
				return _keyEqual(a_entry.first, a_key);
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

		constexpr void swap(StaticOrderedMap& a_other) //
			noexcept(std::is_nothrow_swappable_v<value_type>)
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(_data, a_other._data);
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

	template <class Key, class T, std::size_t N, class KeyEqual = std::equal_to<Key>>
	StaticOrderedMap(std::span<const std::pair<Key, T>, N>, KeyEqual = KeyEqual()) -> StaticOrderedMap<Key, T, N, KeyEqual>;

	template <class Key, class T, std::size_t N, class KeyEqual = std::equal_to<Key>>
	StaticOrderedMap(std::array<std::pair<Key, T>, N>, KeyEqual = KeyEqual()) -> StaticOrderedMap<Key, T, N, KeyEqual>;

	template <class... Args>
	[[nodiscard]] constexpr auto make_static_ordered_map(Args&&... a_args) //
		noexcept((std::is_nothrow_convertible_v<std::common_type_t<Args...>, Args> && ...))
			-> StaticOrderedMap<typename std::common_type_t<Args...>::first_type, typename std::common_type_t<Args...>::second_type, sizeof...(Args)>
		requires(sizeof...(Args) > 0 && (std::is_convertible_v<Args, std::common_type_t<Args...>> && ...))
	{
		return { static_cast<std::common_type_t<Args...>>(std::forward<Args>(a_args))... };
	}

	template <template <class> class KeyEqual, class... Args>
	[[nodiscard]] constexpr auto make_static_ordered_map(Args&&... a_args) //
		noexcept((std::is_nothrow_convertible_v<std::common_type_t<Args...>, Args> && ...))
			-> StaticOrderedMap<typename std::common_type_t<Args...>::first_type, typename std::common_type_t<Args...>::second_type, sizeof...(Args), KeyEqual<typename std::common_type_t<Args...>::first_type>>
		requires(sizeof...(Args) > 0 && (std::is_convertible_v<Args, std::common_type_t<Args...>> && ...))
	{
		return { static_cast<std::common_type_t<Args...>>(std::forward<Args>(a_args))... };
	}

	template <class Key, class T, std::size_t N, class KeyEqual = std::equal_to<Key>>
	constexpr void swap(StaticOrderedMap<Key, T, N, KeyEqual>& a_lhs, StaticOrderedMap<Key, T, N, KeyEqual>& a_rhs) //
		noexcept(std::is_nothrow_swappable_v<typename StaticOrderedMap<Key, T, N, KeyEqual>::value_type>)
	{
		a_lhs.swap(a_rhs);
	}
}
