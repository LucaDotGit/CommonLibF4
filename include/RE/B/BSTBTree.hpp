#pragma once

#include "RE/B/BSTTuple.hpp"

namespace RE::Impl
{
	template <class C, class K>
	concept transparent_comparator =
		requires(
			const K& a_transparent,
			const C::key_type& a_key,
			C::key_compare& a_compare) {
			typename C::key_compare::is_transparent;
			{ a_compare(a_transparent, a_key) } -> std::convertible_to<bool>;
			{ a_compare(a_key, a_transparent) } -> std::convertible_to<bool>;
		};
}

namespace RE
{
	template <class Key, class T, class KeyCompare = std::less<Key>>
	class BSTBTree
	{
	public:
		using key_type = Key;
		using mapped_type = T;
		using value_type = BSTPair<const key_type, mapped_type>;
		using size_type = std::uint32_t;
		using key_compare = KeyCompare;

		static_assert(std::is_empty_v<key_compare>, "`BSTBTree` requires a stateless comparator.");

		// traverse entries using a leftmost binary search
		// index nodes with index of lower bound, if entry is not found at this level
		// nodes are always allocated as powers of 2
		// maybe `std::bit_ceil(sizeof(node_type))` ???
		class node_type
		{
		public:
			using iterator = value_type*;
			using const_iterator = const value_type*;

			[[nodiscard]] iterator begin() noexcept { return entries.data(); }
			[[nodiscard]] const_iterator begin() const noexcept { return entries.data(); }
			[[nodiscard]] const_iterator cbegin() const noexcept { return entries.data(); }

			[[nodiscard]] iterator end() noexcept { return entries.data() + usedEntries; }
			[[nodiscard]] const_iterator end() const noexcept { return entries.data() + usedEntries; }
			[[nodiscard]] const_iterator cend() const noexcept { return entries.data() + usedEntries; }

			// members
			std::array<value_type, 4> entries;			// 00
			std::array<node_type*, 5> nodes{ nullptr }; // ??
			size_type usedEntries{ 0 };					// ??
		};

	private:
		template <class U>
		class iterator_base
		{
		public:
			using value_type = std::remove_const_t<U>;
			using difference_type = std::int32_t;
			using pointer = value_type*;
			using reference = value_type&;
			using iterator_category = std::forward_iterator_tag;

			iterator_base() noexcept = default;
			~iterator_base() noexcept = default;

			template <class V>
			iterator_base(const iterator_base<V>& a_rhs)
				requires(std::is_convertible_v<typename iterator_base<V>::reference, reference>)
				: _queued(a_rhs._queued),
				  _current(a_rhs._current),
				  _pos(a_rhs._pos)
			{
			}

			template <class V>
			iterator_base& operator=(const iterator_base<V>& a_rhs)
				requires(std::is_convertible_v<typename iterator_base<V>::reference, reference>)
			{
				if (this == std::addressof(a_rhs)) {
					return *this;
				}

				_queued = a_rhs._queued;
				_current = a_rhs._current;
				_pos = a_rhs._pos;
				return *this;
			}

			[[nodiscard]] reference operator*() const noexcept
			{
				REX::Assert(_current != nullptr);
				REX::Assert(_pos < _current->usedEntries);
				return _current->entries[_pos];
			}

			[[nodiscard]] pointer operator->() const noexcept
			{
				return std::pointer_traits<pointer>::pointer_to(operator*());
			}

			template <class V>
			[[nodiscard]] bool operator==(const iterator_base<V>& a_rhs) const noexcept
			{
				return _current == nullptr && a_rhs._current == nullptr;
			}

			template <class V>
			[[nodiscard]] bool operator!=(const iterator_base<V>& a_rhs) const noexcept
			{
				return !operator==(a_rhs);
			}

			iterator_base& operator++() noexcept
			{
				REX::Assert(_current != nullptr);
				if (++_pos >= _current->usedEntries) {
					_current = nullptr;
					_pos = 0;
					if (!_queued.empty()) {
						_current = _queued.top();
						_queued.pop();
						push_level();
					}
				}

				return *this;
			}

			iterator_base operator++(std::int32_t) noexcept
			{
				auto temp = iterator_base(*this);
				operator++();
				return temp;
			}

		protected:
			template <class, class, class>
			friend class BSTBTree;

			explicit iterator_base(node_type* a_node) noexcept
				: iterator_base(a_node, 0)
			{
			}

			iterator_base(node_type* a_node, size_type a_position)
				: _pos(a_position)
			{
				if (a_node && a_node->usedEntries > 0) {
					_current = a_node;
					push_level();
				}
			}

		private:
			template <class>
			friend class iterator_base;

			void push_level()
			{
				for (auto i = static_cast<size_type>(0); i <= _current->usedEntries; i++) {
					auto* node = _current->nodes[i];
					if (node && node->usedEntries > 0) {
						_queued.push(node);
					}
				}
			}

			std::stack<node_type*> _queued;
			node_type* _current{ nullptr };
			size_type _pos{ 0 };
		};

	public:
		using iterator = iterator_base<value_type>;
		using const_iterator = iterator_base<const value_type>;

		[[nodiscard]] iterator begin() noexcept { return make_iterator<iterator>(); }
		[[nodiscard]] const_iterator begin() const noexcept { return make_iterator<const_iterator>(); }
		[[nodiscard]] const_iterator cbegin() const noexcept { return make_iterator<const_iterator>(); }

		[[nodiscard]] iterator end() noexcept { return {}; }
		[[nodiscard]] const_iterator end() const noexcept { return {}; }
		[[nodiscard]] const_iterator cend() const noexcept { return {}; }

		[[nodiscard]] bool empty() const noexcept { return !_root; }

		[[nodiscard]] iterator find(const key_type& a_key) { return do_find<iterator>(a_key); }
		[[nodiscard]] const_iterator find(const key_type& a_key) const { return do_find<const_iterator>(a_key); }

		template <class K>
		[[nodiscard]] iterator find(const K& a_key)
			requires(Impl::transparent_comparator<BSTBTree, K>)
		{
			return do_find<iterator>(a_key);
		}

		template <class K>
		[[nodiscard]] const_iterator find(const K& a_key) const
			requires(Impl::transparent_comparator<BSTBTree, K>)
		{
			return do_find<const_iterator>(a_key);
		}

		[[nodiscard]] key_compare key_comp() const { return key_compare{}; }

	private:
		template <class It>
		[[nodiscard]] It make_iterator() const noexcept
		{
			return It(_root);
		}

		template <class It, class K>
		[[nodiscard]] It do_find(const K& a_key) const
		{
			auto* node = _root;
			while (node) {
				const auto it = std::lower_bound(node->begin(), node->end(), a_key,
					[this](const value_type& a_lhs, const key_type& a_rhs) {
						return key_comp()(a_lhs.first, a_rhs);
					});

				if (it == node->end()) {
					node = node->nodes[node->usedEntries];
					continue;
				}

				const auto pos = static_cast<size_type>(it - node->begin());
				if (!key_comp()(a_key, it->first)) {
					return It(node, pos);
				}

				node = node->nodes[pos];
			}

			return It();
		}

		std::array<std::byte, 0x08> pad00{}; // 00
		size_type _activeEntry{ 0 };		 // 08
		size_type _allocatedSize{ 0 };		 // 0C
		node_type* _root{ nullptr };		 // 10
		node_type* _availNodes{ nullptr };	 // 18
	};
}
