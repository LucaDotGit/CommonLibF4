#pragma once

#include "RE/M/MemoryManager.hpp"

namespace RE
{
	template <class T>
	class BSSimpleList
	{
	public:
		using value_type = T;
		using size_type = std::uint32_t;
		using difference_type = std::int32_t;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using reference = value_type&;
		using const_reference = const value_type&;

	private:
		class node_type
		{
		public:
			GAME_HEAP_REDEFINE_NEW(node_type);

			// members
			value_type value{};		  // 0x00
			node_type* next{nullptr}; // 0x??
		};

		template <class U>
		class iterator_base
		{
		public:
			using difference_type = std::int32_t;
			using value_type = std::remove_const_t<U>;
			using pointer = value_type*;
			using reference = value_type&;
			using iterator_category = std::forward_iterator_tag;

			iterator_base() noexcept = default;
			~iterator_base() noexcept = default;

			template <class V>
			// NOLINTNEXTLINE(misc-explicit-constructor)
			iterator_base(iterator_base<V> a_rhs) noexcept
				requires(std::is_convertible_v<typename iterator_base<V>::reference, reference>)
				:
				_proxy(a_rhs._proxy),
				_current(a_rhs._current)
			{
			}

			iterator_base(const iterator_base&) = default;
			iterator_base(iterator_base&&) noexcept = default;

			template <class V>
			auto operator=(iterator_base<V> a_rhs) noexcept -> iterator_base&
				requires(std::is_convertible_v<typename iterator_base<V>::reference, reference>)
			{
				_current = a_rhs._current;
				return *this;
			}

			auto operator=(const iterator_base&) -> iterator_base& = default;
			auto operator=(iterator_base&&) noexcept -> iterator_base& = default;

			[[nodiscard]]
			auto operator*() noexcept -> reference
			{
				REX::Assert(_current && _current != nullptr);
				return get()->value;
			}

			[[nodiscard]]
			auto operator->() noexcept -> pointer
			{
				return std::pointer_traits<pointer>::pointer_to(operator*());
			}

			template <class V>
			[[nodiscard]]
			auto operator==(const iterator_base<V>& a_rhs) const noexcept -> bool
			{
				REX::Assert(_proxy == a_rhs._proxy);
				return _current == a_rhs._current;
			}

			auto operator++() noexcept -> iterator_base&
			{
				if (_current) {
					REX::Assert(_current != nullptr);
					_current = get()->next;
				}
				else {
					*this = _proxy->begin();
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
			template <class>
			friend class BSSimpleList;

			iterator_base(BSSimpleList<value_type>* a_proxy, node_type* a_current) noexcept :
				_proxy(a_proxy),
				_current(a_current)
			{
			}

			iterator_base(BSSimpleList<value_type>* a_proxy, std::optional<node_type*> a_current) noexcept :
				_proxy(a_proxy),
				_current(a_current)
			{
			}

			[[nodiscard]]
			auto get() const noexcept -> node_type*
			{
				REX::Assert(_current && _current != nullptr);
				return _current.value();
			}

			[[nodiscard]]
			auto make_mutable() const noexcept
			{
				return iterator_base<std::remove_const_t<value_type>>(_proxy, _current);
			}

			// members
			BSSimpleList<value_type>* _proxy{nullptr};	 // 0x00
			std::optional<node_type*> _current{nullptr}; // 0x08
		};

		template <class F>
		class counted_function_iterator
		{
		public:
			using value_type = std::remove_const_t<std::remove_reference_t<decltype(std::declval<F>()())>>;
			using size_type = std::uint32_t;
			using difference_type = std::int32_t;
			using pointer = value_type*;
			using reference = value_type&;
			using iterator_category = std::input_iterator_tag;

			counted_function_iterator() noexcept(std::is_nothrow_default_constructible_v<F>) = default;

			counted_function_iterator(F a_func, size_type a_count) noexcept(std::is_nothrow_move_constructible_v<F>) :
				_func(std::move(a_func)),
				_left(a_count)
			{
			}

			~counted_function_iterator() noexcept(std::is_nothrow_destructible_v<F>) = default;

			counted_function_iterator(const counted_function_iterator&)
				noexcept(std::is_nothrow_copy_constructible_v<F>) = default;
			counted_function_iterator(counted_function_iterator&&)
				noexcept(std::is_nothrow_move_constructible_v<F>) = default;

			auto operator=(const counted_function_iterator&) noexcept(std::is_nothrow_copy_assignable_v<F>)
				-> counted_function_iterator& = default;
			auto operator=(counted_function_iterator&&) noexcept(std::is_nothrow_move_assignable_v<F>)
				-> counted_function_iterator& = default;

			[[nodiscard]]
			auto operator*() const noexcept(noexcept(std::declval<F>()())) -> reference
			{
				REX::Assert(_func.has_value());
				return std::invoke(_func.value());
			}

			[[nodiscard]]
			auto operator->() const -> pointer
			{
				return std::pointer_traits<pointer>::pointer_to(operator*());
			}

			auto operator++() noexcept -> counted_function_iterator&
			{
				REX::Assert(_left > 0);
				_left -= 1;
				return *this;
			}

			auto operator++(std::int32_t) noexcept -> counted_function_iterator
			{
				auto temp = counted_function_iterator(*this);
				operator++();
				return temp;
			}

			[[nodiscard]]
			friend auto operator==(const counted_function_iterator& a_lhs, const counted_function_iterator& a_rhs)
				noexcept -> bool
			{
				return a_lhs._left == a_rhs._left;
			}

		private:
			// members
			std::optional<F> _func; // 0x00
			size_type _left{0};		// 0x??
		};

	public:
		using iterator = iterator_base<value_type>;
		using const_iterator = iterator_base<const value_type>;

		BSSimpleList() noexcept = default;

		~BSSimpleList() noexcept
		{
			clear();
		}

		explicit BSSimpleList(size_type a_count)
		{
			assign(a_count, value_type());
		}

		template <std::input_iterator InputIt>
		BSSimpleList(InputIt a_first, InputIt a_last)
		{
			assign(a_first, a_last);
		}

		template <std::ranges::input_range Range>
		// NOLINTNEXTLINE(misc-explicit-constructor)
		BSSimpleList(std::from_range_t /*a_fromRange*/, Range&& a_range)
		{
			assign_range(std::forward<Range>(a_range));
		}

		BSSimpleList(std::initializer_list<value_type> a_initList)
		{
			assign(a_initList.begin(), a_initList.end());
		}

		BSSimpleList(const BSSimpleList& a_rhs)
		{
			assign(a_rhs.begin(), a_rhs.end());
		}

		BSSimpleList(BSSimpleList&& a_rhs) noexcept :
			_root(std::exchange(a_rhs._root, node_type()))
		{
		}

		auto operator=(std::initializer_list<value_type> a_rhs) -> BSSimpleList&
		{
			assign(a_rhs.begin(), a_rhs.end());
			return *this;
		}

		auto operator=(const BSSimpleList& a_rhs) -> BSSimpleList&
		{
			assign(a_rhs.begin(), a_rhs.end());
			return *this;
		}

		auto operator=(BSSimpleList&& a_rhs) noexcept -> BSSimpleList&
		{
			clear();
			_root = std::exchange(a_rhs._root, node_type());
			return *this;
		}

		GAME_HEAP_REDEFINE_NEW(BSSimpleList);

		[[nodiscard]]
		auto front() noexcept -> reference
		{
			REX::Assert(!empty());
			return *begin();
		}

		[[nodiscard]]
		auto back() noexcept -> reference
		{
			REX::Assert(!empty());
			return *std::prev(end());
		}

		[[nodiscard]]
		auto front() const noexcept -> const_reference
		{
			REX::Assert(!empty());
			return *begin();
		}

		[[nodiscard]]
		auto back() const noexcept -> const_reference
		{
			REX::Assert(!empty());
			return *std::prev(end());
		}

		[[nodiscard]]
		auto before_begin() noexcept -> iterator
		{
			return make_iterator<iterator>(std::nullopt);
		}

		[[nodiscard]]
		auto before_begin() const noexcept -> const_iterator
		{
			return make_iterator<const_iterator>(std::nullopt);
		}

		[[nodiscard]]
		auto cbefore_begin() const noexcept -> const_iterator
		{
			return before_begin();
		}

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
			return begin();
		}

		[[nodiscard]]
		auto end() noexcept -> iterator
		{
			return make_iterator<iterator>(nullptr);
		}

		[[nodiscard]]
		auto end() const noexcept -> const_iterator
		{
			return make_iterator<const_iterator>(nullptr);
		}

		[[nodiscard]]
		auto cend() const noexcept -> const_iterator
		{
			return end();
		}

		[[nodiscard]]
		auto empty() const noexcept -> bool
		{
			return !_root.next && !_root.value;
		}

		template <std::input_iterator InputIt>
		void assign(InputIt a_first, InputIt a_last)
		{
			clear();
			insert_after(cbefore_begin(), std::move(a_first), std::move(a_last));
		}

		void assign(std::initializer_list<value_type> a_initList)
		{
			assign(a_initList.begin(), a_initList.end());
		}

		template <std::ranges::input_range Range>
		// NOLINTNEXTLINE(cppcoreguidelines-missing-std-forward)
		void assign_range(Range&& a_range)
		{
			assign(std::ranges::begin(a_range), std::ranges::end(a_range));
		}

		template <std::ranges::input_range Range>
		// NOLINTNEXTLINE(cppcoreguidelines-missing-std-forward)
		void append_range(Range&& a_range)
		{
			insert_after(cbefore_begin(), std::ranges::begin(a_range), std::ranges::end(a_range));
		}

		auto insert_after(const_iterator a_position, const_reference a_value) -> iterator
		{
			return emplace_after(a_position, a_value);
		}

		auto insert_after(const_iterator a_position, value_type&& a_value) -> iterator
		{
			return emplace_after(a_position, std::move(a_value));
		}

		auto insert_after(const_iterator a_position, size_type a_count, const_reference a_value) -> iterator
		{
			const auto generate = [&a_value]() noexcept -> const_reference {
				return a_value;
			};
			return insert_after(
				a_position,
				counted_function_iterator{generate, a_count},
				counted_function_iterator<decltype(generate)>());
		}

		template <std::input_iterator InputIt>
		auto insert_after(const_iterator a_position, InputIt a_first, InputIt a_last) -> iterator
		{
			const auto&& [first, last] = allocate_range(std::move(a_first), std::move(a_last));
			return insert_range(a_position, first, last);
		}

		auto insert_after(const_iterator a_position, std::initializer_list<value_type> a_initList) -> iterator
		{
			return insert_after(a_position, a_initList.begin(), a_initList.end());
		}

		template <class... Args>
		auto emplace_after(const_iterator a_position, Args&&... a_args) -> iterator
		{
			const auto node = new node_type{{std::forward<Args>(a_args)...}, nullptr};
			return insert_range(a_position, node, node);
		}

		auto erase_after(const_iterator a_position) -> iterator
		{
			return erase_after(a_position, ++a_position);
		}

		auto erase_after(const_iterator a_first, const_iterator a_last) -> iterator
		{
			REX::Assert(a_first != cend());
			if (a_first != a_last) {
				const auto deleteRange = [](node_type* a_first, node_type* a_last) -> void {
					while (a_first != a_last) {
						auto prev = a_first;
						a_first = a_first->next;
						delete prev;
					}
				};

				if (a_first == cbefore_begin()) {
					deleteRange(_root.next, a_last.get());
					if (a_last == cend()) {
						_root = node_type();
					}
					else {
						// invalidates a_last, nonconforming
						_root = std::move(*(a_last.get()));
						delete a_last.get();
						return begin();
					}
				}
				else {
					deleteRange(a_first.get()->next, a_last.get());
					a_first.get()->next = a_last.get();
				}
			}

			return a_last.make_mutable();
		}

		void push_front(const_reference a_value)
		{
			emplace_front(a_value);
		}

		void push_front(value_type&& a_value)
		{
			emplace_front(std::move(a_value));
		}

		template <class... Args>
		auto emplace_front(Args&&... a_args) -> reference
		{
			return *emplace_after(cbefore_begin(), std::forward<Args>(a_args)...);
		}

		void pop_front()
		{
			erase_after(cbefore_begin());
		}

		void push_back(const_reference a_value)
		{
			emplace_back(a_value);
		}

		void push_back(value_type&& a_value)
		{
			emplace_back(std::move(a_value));
		}

		template <class... Args>
		auto emplace_back(Args&&... a_args) -> reference
		{
			return *emplace_after(cend(), std::forward<Args>(a_args)...);
		}

		void resize(size_type a_newSize)
		{
			resize(a_newSize, value_type());
		}

		void resize(size_type a_newSize, const value_type& a_value)
		{
			auto n = static_cast<size_type>(-1);
			auto it = cbefore_begin();
			auto prev = const_iterator();

			while (++n != a_newSize) {
				prev = it;
				if (++it == cend()) {
					break;
				}
			}

			if (it != cend()) {
				REX::Assert(n == a_newSize);
				erase_after(it, cend());
			}
			else {
				REX::Assert(n != a_newSize);
				insert_after(prev, a_newSize - n, a_value);
			}
		}

		void clear() noexcept
		{
			erase_after(cbefore_begin(), cend());
		}

		void swap(BSSimpleList& a_other) noexcept
		{
			if (this == std::addressof(a_other)) {
				return;
			}

			std::swap(_root.value, a_other._root.value);
			std::swap(_root.next, a_other._root.next);
		}

	private:
		template <class It>
		[[nodiscard]]
		auto make_iterator() const noexcept -> It
		{
			return It(
				const_cast<BSSimpleList*>(this),
				!empty() ? std::addressof(const_cast<node_type&>(_root)) : nullptr);
		}

		template <class It>
		[[nodiscard]]
		auto make_iterator(node_type* a_current) const noexcept -> It
		{
			return It(const_cast<BSSimpleList*>(this), a_current);
		}

		template <class It>
		[[nodiscard]]
		auto make_iterator(std::optional<node_type*> a_current) const noexcept -> It
		{
			return It(const_cast<BSSimpleList*>(this), a_current);
		}

		template <std::input_iterator InputIt>
		[[nodiscard]]
		static auto allocate_range(InputIt a_first, InputIt a_last) -> std::pair<node_type*, node_type*>
		{
			auto range = std::make_pair<node_type*, node_type*>(nullptr, nullptr);
			if (a_first != a_last) {
				range.first = new node_type{*a_first};
				a_first++;

				range.second = range.first;
				for (; a_first != a_last; a_first++) {
					range.second->next = new node_type{*a_first};
					range.second = range.second->next;
				}
			}

			return range;
		}

		// assumes ownership of given range
		[[nodiscard]]
		auto insert_range(const_iterator a_position, node_type* a_first, node_type* a_last) -> iterator
		{
			REX::Assert(a_position != cend());
			if (!a_first) {
				REX::Assert(a_last == nullptr);
				return a_position.make_mutable();
			}

			REX::Assert(a_last != nullptr);

			if (a_position == cbefore_begin()) {
				if (_root.value) {
					_root.next = new node_type{std::move(_root.value), _root.next};
				}

				a_last->next = _root.next;
				_root = std::move(*a_first);
				delete a_first;
			}
			else {
				a_last->next = a_position.get()->next;
				a_position.get()->next = a_first;
			}

			return iterator(this, a_last);
		}

		// members
		node_type _root{}; // 0x00
	};
}
