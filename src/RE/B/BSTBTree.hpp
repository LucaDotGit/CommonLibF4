#pragma once

#include "RE/B/BSTTuple.hpp"

namespace RE::Impl
{
	template <class C, class K>
	concept transparent_comparator =
		requires(const K& a_transparent, const C::key_type& a_key, C::key_compare& a_compare) {
			typename C::key_compare::is_transparent;
			{
				a_compare(a_transparent, a_key)
			} -> std::convertible_to<bool>;
			{
				a_compare(a_key, a_transparent)
			} -> std::convertible_to<bool>;
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

			[[nodiscard]]
			auto begin() noexcept -> iterator
			{
				return entries.data();
			}

			[[nodiscard]]
			auto begin() const noexcept -> const_iterator
			{
				return entries.data();
			}

			[[nodiscard]]
			auto cbegin() const noexcept -> const_iterator
			{
				return entries.data();
			}

			[[nodiscard]]
			auto end() noexcept -> iterator
			{
				return entries.data() + usedEntries;
			}

			[[nodiscard]]
			auto end() const noexcept -> const_iterator
			{
				return entries.data() + usedEntries;
			}

			[[nodiscard]]
			auto cend() const noexcept -> const_iterator
			{
				return entries.data() + usedEntries;
			}

			// members
			std::array<value_type, 4> entries;		  // 0x00
			std::array<node_type*, 5> nodes{nullptr}; // 0x??
			size_type usedEntries{0};				  // 0x??
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
			// NOLINTNEXTLINE(misc-explicit-constructor)
			iterator_base(const iterator_base<V>& a_rhs)
				requires(std::is_convertible_v<typename iterator_base<V>::reference, reference>)
				:
				_queued(a_rhs._queued),
				_current(a_rhs._current),
				_pos(a_rhs._pos)
			{
			}

			iterator_base(const iterator_base&) = default;
			iterator_base(iterator_base&&) noexcept = default;

			template <class V>
			auto operator=(const iterator_base<V>& a_rhs) -> iterator_base&
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

			auto operator=(const iterator_base&) -> iterator_base& = default;
			auto operator=(iterator_base&&) noexcept -> iterator_base& = default;

			[[nodiscard]]
			auto operator*() const noexcept -> reference
			{
				REX::Assert(_current != nullptr);
				REX::Assert(_pos < _current->usedEntries);
				return _current->entries[_pos];
			}

			[[nodiscard]]
			auto operator->() const noexcept -> pointer
			{
				return std::pointer_traits<pointer>::pointer_to(operator*());
			}

			template <class V>
			[[nodiscard]]
			auto operator==(const iterator_base<V>& a_rhs) const noexcept -> bool
			{
				return _current == nullptr && a_rhs._current == nullptr;
			}

			auto operator++() noexcept -> iterator_base&
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

			auto operator++(std::int32_t) noexcept -> iterator_base
			{
				auto temp = iterator_base(*this);
				operator++();
				return temp;
			}

		private:
			template <class, class, class>
			friend class BSTBTree;

			template <class>
			friend class iterator_base;

			explicit iterator_base(node_type* a_node) noexcept :
				iterator_base(a_node, 0)
			{
			}

			iterator_base(node_type* a_node, size_type a_position) :
				_pos(a_position)
			{
				if (a_node && a_node->usedEntries > 0) {
					_current = a_node;
					push_level();
				}
			}

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
			node_type* _current{nullptr};
			size_type _pos{0};
		};

	public:
		using iterator = iterator_base<value_type>;
		using const_iterator = iterator_base<const value_type>;

		[[nodiscard]]
		auto begin() noexcept -> iterator
		{
			return make_iterator<iterator>();
		}

		[[nodiscard]]
		auto begin() const noexcept -> const_iterator
		{
			return make_iterator<const_iterator>();
		}

		[[nodiscard]]
		auto cbegin() const noexcept -> const_iterator
		{
			return make_iterator<const_iterator>();
		}

		[[nodiscard]]
		auto end() noexcept -> iterator
		{
			return {};
		}

		[[nodiscard]]
		auto end() const noexcept -> const_iterator
		{
			return {};
		}

		[[nodiscard]]
		auto cend() const noexcept -> const_iterator
		{
			return {};
		}

		[[nodiscard]]
		auto empty() const noexcept -> bool
		{
			return !_root;
		}

		[[nodiscard]]
		auto find(const key_type& a_key) -> iterator
		{
			return do_find<iterator>(a_key);
		}

		[[nodiscard]]
		auto find(const key_type& a_key) const -> const_iterator
		{
			return do_find<const_iterator>(a_key);
		}

		template <class K>
		[[nodiscard]]
		auto find(const K& a_key) -> iterator
			requires(Impl::transparent_comparator<BSTBTree, K>)
		{
			return do_find<iterator>(a_key);
		}

		template <class K>
		[[nodiscard]]
		auto find(const K& a_key) const -> const_iterator
			requires(Impl::transparent_comparator<BSTBTree, K>)
		{
			return do_find<const_iterator>(a_key);
		}

		[[nodiscard]]
		auto key_comp() const -> key_compare
		{
			return key_compare();
		}

	private:
		template <class It>
		[[nodiscard]]
		auto make_iterator() const noexcept -> It
		{
			return It(_root);
		}

		template <class It, class K>
		[[nodiscard]]
		auto do_find(const K& a_key) const -> It
		{
			auto* node = _root;
			while (node) {
				const auto it = std::lower_bound(
					node->begin(),
					node->end(),
					a_key,
					[this](const value_type& a_lhs, const key_type& a_rhs) -> bool {
						return key_comp()(a_lhs.first, a_rhs);
					});

				if (it == node->end()) {
					node = node->nodes[node->usedEntries];
					continue;
				}

				const auto pos = static_cast<size_type>(it - node->begin());
				if (!key_comp()(it->first, a_key)) {
					return It(node, pos);
				}

				node = node->nodes[pos];
			}

			return It();
		}

		std::array<std::byte, 0x08> _pad00{static_cast<std::byte>(0)}; // 0x00
		size_type _activeEntry{0};									   // 0x08
		size_type _allocatedSize{0};								   // 0x0C
		node_type* _root{nullptr};									   // 0x10
		node_type* _availNodes{nullptr};							   // 0x18
	};
}
