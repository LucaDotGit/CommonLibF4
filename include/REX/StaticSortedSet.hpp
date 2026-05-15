#pragma once

#include "REX/Contract.hpp"

namespace REX
{
	template <class T, std::size_t N, class KeyCompare = std::less<T>>
	struct StaticSortedSet final
	{
	public:
		inline static constexpr auto MAX_SIZE = N;

		using key_type = T;
		using value_type = T;
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

		static_assert(std::is_copy_constructible_v<value_type>, "`REX::StaticSortedSet` requires `value_type` to be copy constructible.");
		static_assert(std::is_copy_assignable_v<value_type>, "`REX::StaticSortedSet` requires `value_type` to be copy assignable.");

		constexpr StaticSortedSet() = delete;

		constexpr ~StaticSortedSet() //
			noexcept(std::is_nothrow_destructible_v<value_type>) = default;

		constexpr StaticSortedSet(const_iterator a_first, const_iterator a_last) //
			noexcept(std::is_nothrow_copy_constructible_v<value_type>)
		{
			std::copy_n(a_first, std::min(static_cast<size_type>(std::distance(a_first, a_last)), MAX_SIZE), _data.data());
			std::sort(begin(), end(), [this](const value_type& a_lhs, const value_type& a_rhs) -> auto {
				return _keyCompare(a_lhs, a_rhs);
			});

			REX::Assert(std::adjacent_find(begin(), end(), [this](const value_type& a_lhs, const value_type& a_rhs) -> auto {
				return !_keyCompare(a_lhs, a_rhs) && !_keyCompare(a_rhs, a_lhs);
			}) == end());
		}

		constexpr StaticSortedSet(std::span<const value_type, MAX_SIZE> a_value) //
			noexcept(std::is_nothrow_copy_constructible_v<value_type>)
			: _data{ a_value.begin(), a_value.end() }
		{
			std::sort(begin(), end(), [this](const value_type& a_lhs, const value_type& a_rhs) -> auto {
				return _keyCompare(a_lhs, a_rhs);
			});

			REX::Assert(std::adjacent_find(begin(), end(), [this](const value_type& a_lhs, const value_type& a_rhs) -> auto {
				return !_keyCompare(a_lhs, a_rhs) && !_keyCompare(a_rhs, a_lhs);
			}) == end());
		}

		constexpr StaticSortedSet(std::array<value_type, MAX_SIZE> a_value) //
			noexcept(std::is_nothrow_copy_constructible_v<value_type>)
			: _data(std::move(a_value))
		{
			std::sort(begin(), end(), [this](const value_type& a_lhs, const value_type& a_rhs) -> auto {
				return _keyCompare(a_lhs, a_rhs);
			});

			REX::Assert(std::adjacent_find(begin(), end(), [this](const value_type& a_lhs, const value_type& a_rhs) -> auto {
				return !_keyCompare(a_lhs, a_rhs) && !_keyCompare(a_rhs, a_lhs);
			}) == end());
		}

		constexpr StaticSortedSet(std::initializer_list<value_type> a_value) //
			noexcept(std::is_default_constructible_v<value_type> &&
					 std::is_nothrow_copy_constructible_v<value_type>)
		{
			std::copy_n(a_value.begin(), std::min(static_cast<size_type>(a_value.size()), MAX_SIZE), _data.data());
			std::sort(begin(), end(), [this](const value_type& a_lhs, const value_type& a_rhs) -> auto {
				return _keyCompare(a_lhs, a_rhs);
			});

			REX::Assert(std::adjacent_find(begin(), end(), [this](const value_type& a_lhs, const value_type& a_rhs) -> auto {
				return !_keyCompare(a_lhs, a_rhs) && !_keyCompare(a_rhs, a_lhs);
			}) == end());
		}

		constexpr StaticSortedSet(const StaticSortedSet&) //
			noexcept(std::is_nothrow_copy_constructible_v<value_type>) = default;

		constexpr StaticSortedSet(StaticSortedSet&&) //
			noexcept(std::is_nothrow_move_constructible_v<value_type>)
			requires(std::is_move_constructible_v<value_type>)
		= default;

		constexpr StaticSortedSet& operator=(std::span<const value_type, MAX_SIZE> a_value) //
			noexcept(std::is_nothrow_copy_assignable_v<value_type>)
		{
			std::copy_n(a_value.begin(), size(), _data.data());
			std::sort(begin(), end(), [this](const value_type& a_lhs, const value_type& a_rhs) -> auto {
				return _keyCompare(a_lhs, a_rhs);
			});

			REX::Assert(std::adjacent_find(begin(), end(), [this](const value_type& a_lhs, const value_type& a_rhs) -> auto {
				return !_keyCompare(a_lhs, a_rhs) && !_keyCompare(a_rhs, a_lhs);
			}) == end());

			return *this;
		}

		constexpr StaticSortedSet& operator=(std::array<value_type, MAX_SIZE> a_value) //
			noexcept(std::is_nothrow_copy_assignable_v<value_type>)
		{
			_data = std::move(a_value);

			std::sort(begin(), end(), [this](const value_type& a_lhs, const value_type& a_rhs) -> auto {
				return _keyCompare(a_lhs, a_rhs);
			});

			REX::Assert(std::adjacent_find(begin(), end(), [this](const value_type& a_lhs, const value_type& a_rhs) -> auto {
				return !_keyCompare(a_lhs, a_rhs) && !_keyCompare(a_rhs, a_lhs);
			}) == end());

			return *this;
		}

		constexpr StaticSortedSet& operator=(std::initializer_list<value_type> a_value) //
			noexcept(std::is_default_constructible_v<value_type> &&
					 std::is_nothrow_copy_assignable_v<value_type>)
		{
			std::copy_n(a_value.begin(), std::min(static_cast<size_type>(a_value.size()), MAX_SIZE), _data.data());
			std::sort(begin(), end(), [this](const value_type& a_lhs, const value_type& a_rhs) -> auto {
				return _keyCompare(a_lhs, a_rhs);
			});

			REX::Assert(std::adjacent_find(begin(), end(), [this](const value_type& a_lhs, const value_type& a_rhs) -> auto {
				return !_keyCompare(a_lhs, a_rhs) && !_keyCompare(a_rhs, a_lhs);
			}) == end());

			return *this;
		}

		constexpr StaticSortedSet& operator=(const StaticSortedSet&) //
			noexcept(std::is_nothrow_copy_assignable_v<value_type>) = default;

		constexpr StaticSortedSet& operator=(StaticSortedSet&&) //
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
			const auto it = std::lower_bound(begin(), end(), a_key, [this](const value_type& a_entry, const key_type& a_key) -> auto {
				return _keyCompare(a_entry, a_key);
			});

			if (it == end()) {
				return end();
			}

			if (_keyCompare(*it, a_key) || _keyCompare(a_key, *it)) {
				return end();
			}

			return it;
		}

		[[nodiscard]] constexpr const_iterator find(const key_type& a_key) const
		{
			const auto it = std::lower_bound(begin(), end(), a_key, [this](const value_type& a_entry, const key_type& a_key) -> auto {
				return _keyCompare(a_entry, a_key);
			});

			if (it == end()) {
				return end();
			}

			if (_keyCompare(*it, a_key) || _keyCompare(a_key, *it)) {
				return end();
			}

			return it;
		}

		[[nodiscard]] constexpr std::pair<iterator, iterator> equal_range(const key_type& a_key)
		{
			return std::equal_range(begin(), end(), a_key, [this](const value_type& a_entry, const key_type& a_key) -> auto {
				return _keyCompare(a_entry, a_key);
			});
		}

		[[nodiscard]] constexpr std::pair<const_iterator, const_iterator> equal_range(const key_type& a_key) const
		{
			return std::equal_range(begin(), end(), a_key, [this](const value_type& a_entry, const key_type& a_key) -> auto {
				return _keyCompare(a_entry, a_key);
			});
		}

		[[nodiscard]] constexpr iterator lower_bound(const key_type& a_key)
		{
			return std::lower_bound(begin(), end(), a_key, [this](const value_type& a_entry, const key_type& a_key) -> auto {
				return _keyCompare(a_entry, a_key);
			});
		}

		[[nodiscard]] constexpr const_iterator lower_bound(const key_type& a_key) const
		{
			return std::lower_bound(begin(), end(), a_key, [this](const value_type& a_entry, const key_type& a_key) -> auto {
				return _keyCompare(a_entry, a_key);
			});
		}

		[[nodiscard]] constexpr iterator upper_bound(const key_type& a_key)
		{
			return std::upper_bound(begin(), end(), a_key, [this](const key_type& a_key, const value_type& a_entry) -> auto {
				return _keyCompare(a_key, a_entry);
			});
		}

		[[nodiscard]] constexpr const_iterator upper_bound(const key_type& a_key) const
		{
			return std::upper_bound(begin(), end(), a_key, [this](const key_type& a_key, const value_type& a_entry) -> auto {
				return _keyCompare(a_key, a_entry);
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

		constexpr void swap(StaticSortedSet& a_other) //
			noexcept(std::is_nothrow_swappable_v<value_type>)
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(_data, a_other._data);
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

	template <class T, std::size_t N, class KeyCompare = std::less<T>>
	StaticSortedSet(std::span<const T, N>, KeyCompare = KeyCompare()) -> StaticSortedSet<T, N, KeyCompare>;

	template <class T, std::size_t N, class KeyCompare = std::less<T>>
	StaticSortedSet(std::array<T, N>, KeyCompare = KeyCompare()) -> StaticSortedSet<T, N, KeyCompare>;

	template <class... Args>
	[[nodiscard]] constexpr auto make_static_sorted_set(Args&&... a_args) //
		noexcept((std::is_nothrow_convertible_v<std::common_type_t<Args...>, Args> && ...))
			-> StaticSortedSet<std::common_type_t<Args...>, sizeof...(Args)>
		requires(sizeof...(Args) > 0 && (std::is_convertible_v<Args, std::common_type_t<Args...>> && ...))
	{
		return { static_cast<std::common_type_t<Args...>>(std::forward<Args>(a_args))... };
	}

	template <template <class> class KeyCompare, class... Args>
	[[nodiscard]] constexpr auto make_static_sorted_set(Args&&... a_args) //
		noexcept((std::is_nothrow_convertible_v<std::common_type_t<Args...>, Args> && ...))
			-> StaticSortedSet<std::common_type_t<Args...>, sizeof...(Args), KeyCompare<std::common_type_t<Args...>>> // NOLINT(modernize-use-transparent-functors)
		requires(sizeof...(Args) > 0 && (std::is_convertible_v<Args, std::common_type_t<Args...>> && ...))
	{
		return { static_cast<std::common_type_t<Args...>>(std::forward<Args>(a_args))... };
	}

	template <class T, std::size_t N, class KeyCompare = std::less<T>>
	constexpr void swap(StaticSortedSet<T, N, KeyCompare>& a_lhs, StaticSortedSet<T, N, KeyCompare>& a_rhs) //
		noexcept(std::is_nothrow_swappable_v<typename StaticSortedSet<T, N, KeyCompare>::value_type>)
	{
		a_lhs.swap(a_rhs);
	}
}
